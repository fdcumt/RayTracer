#include "Sphere.h"
#include <cmath>
#include <algorithm>
#include "Math/MathUtility.h"
#include "Common/CommonDefine.h"


bool FSphere::Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const
{
	//Checkf(!IsPointInSphere(InRay.GetOriginal()), "point can`t in sphere");

    FVector OC = InRay.GetOriginal()-m_Center;
    double a = InRay.GetDirection().SizeSquare();
    double half_b = FVector::DotProduct(InRay.GetDirection(),OC);
    double c = OC.SizeSquare() - m_Radius*m_Radius;
    double Discriminant = half_b*half_b -a*c;

    if (Discriminant>0)
    {
        double root = std::sqrt(Discriminant);

        // 先检测距离射线原点近的解是否满足条件
        double NearlyT = (-half_b-root) / a;
        double FarT = (-half_b + root) / a;

        if (NearlyT > MinT && NearlyT < MaxT)
        {
            OutHitRecord.t = NearlyT;
            OutHitRecord.HitPoint = InRay.At(NearlyT);
            double DisSquare = (OutHitRecord.HitPoint-m_Center).SizeSquare();
			//Checkf(DisSquare==Radius*Radius, "point can`t in sphere");

            FVector OutwardNormal = (OutHitRecord.HitPoint-m_Center)/m_Radius;
            OutHitRecord.SetFaceNormal(InRay, OutwardNormal);
			OutHitRecord.HitObj = this;
            OutHitRecord.Mat = Mat;

            return true;
        }

		if (FarT > MinT && FarT < MaxT)
		{
			OutHitRecord.t = FarT;
			OutHitRecord.HitPoint = InRay.At(FarT);
			//Checkf(!IsPointInSphere(OutHitRecord.HitPoint), "point can`t in sphere");

			FVector OutwardNormal = (OutHitRecord.HitPoint - m_Center) / m_Radius;
            //Checkf(OutwardNormal.IsNormal(), "OutwardNormal is not normal");
			OutHitRecord.SetFaceNormal(InRay, OutwardNormal);
			OutHitRecord.HitObj = this;
			OutHitRecord.Mat = Mat;

			return true;
		}
    }
    
    return false;
}

bool FSphere::BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const
{
    OutBox = FAABB(m_Center-m_Radius*2, m_Center+m_Radius*2);
    return true;
}

FVector FSphere::RandomPointInSphere(const bool bInclueSphereSurface /*= true*/) const
{
    double RandomRadius = 0;

    if (bInclueSphereSurface)
    {
        RandomRadius = FMath::Random(0, m_Radius);
    }
    else
    {
		do {
            RandomRadius = FMath::Random(0, m_Radius);
		} while (RandomRadius == m_Radius);
    }

	return RandomPointOnOriginalUnitSphereSurface() * RandomRadius + m_Center;
}

FVector FSphere::RandomPointOnSphereSurface() const
{
	return RandomPointOnOriginalUnitSphereSurface()*m_Radius+m_Center;
}

FVector FSphere::RandomPointInHemisphere(const FVector& InNormal, const bool bInclueSphereSurface /*= true*/) const
{
    FVector RandomPoint = RandomPointOnOriginalUnitSphereSurface();

	if (FVector::DotProduct(InNormal, RandomPoint)>=0)
	{
        RandomPoint = -RandomPoint;
	}

    double RandomRadius = 0;
    if (!bInclueSphereSurface)
    {
        do {
			RandomRadius = FMath::Random(0, m_Radius);
        } while (RandomRadius==m_Radius);
    }

    return RandomPoint*RandomRadius;
}

FVector FSphere::RandomPointOnHemisphereSurface(const FVector& InNormal) const
{
	FVector RandomPoint = RandomPointOnOriginalUnitSphereSurface();

	if (FVector::DotProduct(InNormal, RandomPoint)<0)
	{
		RandomPoint = -RandomPoint;
	}

	return RandomPoint;
}

FVector FSphere::RandomDirectionOnHemisphereSurface(const FVector& InNormal)
{
	FVector RandomPoint = RandomPointOnOriginalUnitSphereSurface();

	if (FVector::DotProduct(InNormal, RandomPoint) < 0)
	{
		RandomPoint = -RandomPoint;
	}

	return RandomPoint;
}

FVector FSphere::RandomPointOnOriginalUnitSphereSurface()
{
	const double DoublePI = FMath::M_PI * 2;
	double VectorZ = 0.f;
	double RandomAngle = 0.f;

	do {
		RandomAngle = FMath::Random(0, DoublePI);
	} while (RandomAngle == DoublePI);


	VectorZ = FMath::Random(-1, 1);
	double R = FMath::Sqrt(1 - VectorZ * VectorZ);

	return FVector(R * FMath::Sin(RandomAngle), R * FMath::Cos(RandomAngle), VectorZ);
}

bool FSphere::IsPointInSphere(const FVector& InPoint) const
{
    return (InPoint-m_Center).SizeSquare()<(m_Radius*m_Radius);
}





