#include "Dielectric.h"
#include "Math/MathUtility.h"

bool FDielectric::Scatter(const FRay& InRay, const FHitRecord& InHitRecord, FVector& OutAttenuation, FRay& OutScattered) const
{
	double IndexOfRefractionReciprocal = InHitRecord.bFrontFace ? (1/m_IndexOfRefraction) : m_IndexOfRefraction;

	const FVector RayDirectionNormal = InRay.GetDirection().Normal();
	const FVector HitNormal = InHitRecord.Normal.Normal();

	double CosTheta = FMath::Min(FMath::Abs(FVector::DotProduct(-RayDirectionNormal, HitNormal)), 1);
	double SinTheta = FMath::Sqrt(1- CosTheta* CosTheta);

	OutAttenuation = FVector::OneVector;

	double ReflectProp = SchlickApproximate(CosTheta, IndexOfRefractionReciprocal);
	if (IndexOfRefractionReciprocal*SinTheta>=1 || FMath::Random()<ReflectProp)
	{
		FVector ReflectDir = FVector::Reflect(RayDirectionNormal, HitNormal);
		OutScattered = FRay(InHitRecord.HitPoint, ReflectDir, InRay.GetTime());
	}
	else
	{
		FVector RefractionDir = FVector::Refraction(RayDirectionNormal, HitNormal, IndexOfRefractionReciprocal);
		OutScattered = FRay(InHitRecord.HitPoint, RefractionDir, InRay.GetTime());
	}

	return true;
}

double FDielectric::SchlickApproximate(double CosTheta, double InIndexOfRefractionReciprocal)
{
	auto r0 = (1-InIndexOfRefractionReciprocal)/(1+InIndexOfRefractionReciprocal);
	r0 = r0*r0;
	return r0+(1-r0)*FMath::Pow(1-CosTheta, 5);
}

