#include "MovingSphere.h"
#include "Math/MathUtility.h"

bool FMovingSphere::Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const
{
	FVector NowCenter = GetCenter(InRay.GetTime());
	FVector OC = InRay.GetOriginal()-NowCenter;
	double a = InRay.GetDirection().SizeSquare();
	double half_b = FVector::DotProduct(OC, InRay.GetDirection());
	double c = OC.SizeSquare()-Radius*Radius;

	double Discriminant = half_b*half_b -a*c;
	if (Discriminant<0)
	{
		return false;
	}

	double sqrt = FMath::Sqrt(Discriminant);

	double root = (-half_b-sqrt)/a;
	if (root<MinT || root>MaxT)
	{
		root = (-half_b + sqrt) / a;
		if (root<MinT || root>MaxT)
		{
			return false;
		}
	}

	OutHitRecord.t = root;
	OutHitRecord.HitPoint = InRay.At(root);
	FVector OutwardNormal = (OutHitRecord.HitPoint-NowCenter)/Radius;
	OutHitRecord.SetFaceNormal(InRay, OutwardNormal);
	OutHitRecord.Mat = Mat;

	return true;
}

