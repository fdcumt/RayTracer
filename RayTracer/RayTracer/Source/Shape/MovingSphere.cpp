#include "MovingSphere.h"
#include "Math/MathUtility.h"

bool FMovingSphere::Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const
{
	FVector NowCenter = GetCenter(InRay.GetTime());
	FVector OC = InRay.GetOriginal()-NowCenter;
	double a = InRay.GetDirection().SizeSquare();
	double half_b = FVector::DotProduct(OC, InRay.GetDirection());
	double c = OC.SizeSquare()-m_Radius*m_Radius;

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
	FVector OutwardNormal = (OutHitRecord.HitPoint-NowCenter)/m_Radius;
	OutHitRecord.SetFaceNormal(InRay, OutwardNormal);
	OutHitRecord.Mat = Mat;

	return true;
}

bool FMovingSphere::BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const
{
	FVector Center_1 = GetCenter(m_BeginTime);
	FVector Center_2 = GetCenter(m_EndTime);

	auto GenerateAABB = [](const FVector &InCenter, const double InRadius) {
		return FAABB(InCenter-InRadius, InCenter+InRadius);
	};

	FAABB AABB_1 = GenerateAABB(Center_1, m_Radius);
	FAABB AABB_2 = GenerateAABB(Center_2, m_Radius);
	
	OutBox = FAABB::SurroundingBox(AABB_1, AABB_2);
	return true;
}

