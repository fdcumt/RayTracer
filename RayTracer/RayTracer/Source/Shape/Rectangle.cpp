#include "Rectangle.h"
#include "Math/MathUtility.h"


bool FRectangle_ZPlane::Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const
{
	double t = (m_Z-InRay.GetOriginal().Z)/InRay.GetDirection().Z;
	if (t>= MinT && t<=MaxT)
	{
		double HitX = InRay.GetOriginal().X+t*InRay.GetDirection().X;
		double HitY = InRay.GetOriginal().Y+t*InRay.GetDirection().Y;
		if (FMath::IsInRange(HitX, m_BeginX, m_EndX) && FMath::IsInRange(HitY, m_BeginY, m_EndY))
		{
			OutHitRecord.HitPoint = FVector(HitX, HitY, m_Z);

			FVector HitPointNormal = FVector(0, 0, 1);
			OutHitRecord.SetFaceNormal(InRay, HitPointNormal);

			OutHitRecord.t = t;
			OutHitRecord.U = (HitX-m_BeginX)/(m_EndX-m_BeginX);
			OutHitRecord.V = (HitY-m_BeginY)/(m_EndY-m_BeginY);
			
			OutHitRecord.HitObj = this;
			OutHitRecord.Mat = m_Material;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool FRectangle_ZPlane::BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const
{
	OutBox = FAABB(FVector(m_BeginX, m_BeginY, m_Z-0.1), FVector(m_EndX, m_EndY, m_Z+0.1));
	return true;
}

bool FRectangle_XPlane::Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const
{
	double t = (m_X - InRay.GetOriginal().X) / InRay.GetDirection().X;
	if (t >= MinT && t <= MaxT)
	{
		double HitY = InRay.GetOriginal().Y + t * InRay.GetDirection().Y;
		double HitZ = InRay.GetOriginal().Z + t * InRay.GetDirection().Z;
		if (FMath::IsInRange(HitY, m_BeginY, m_EndY) && FMath::IsInRange(HitZ, m_BeginZ, m_EndZ))
		{
			OutHitRecord.HitPoint = FVector(m_X, HitY, HitZ);

			FVector HitPointNormal = FVector(1, 0, 0);
			OutHitRecord.SetFaceNormal(InRay, HitPointNormal);

			OutHitRecord.t = t;
			OutHitRecord.U = (HitY - m_BeginY) / (m_EndY - m_BeginY);
			OutHitRecord.V = (HitZ - m_BeginZ) / (m_EndZ - m_BeginZ);

			OutHitRecord.HitObj = this;
			OutHitRecord.Mat = m_Material;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool FRectangle_XPlane::BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const
{
	OutBox = FAABB(FVector(m_X-0.1, m_BeginY, m_BeginZ), FVector(m_X+0.1, m_EndY, m_EndZ));
	return true;
}

bool FRectangle_YPlane::Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const
{
	double t = (m_Y - InRay.GetOriginal().Y) / InRay.GetDirection().Y;
	if (t >= MinT && t <= MaxT)
	{
		double HitX = InRay.GetOriginal().X + t * InRay.GetDirection().X;
		double HitZ = InRay.GetOriginal().Z + t * InRay.GetDirection().Z;
		if (FMath::IsInRange(HitX, m_BeginX, m_EndX) && FMath::IsInRange(HitZ, m_BeginZ, m_EndZ))
		{
			OutHitRecord.HitPoint = FVector(HitX, m_Y, HitZ);

			FVector HitPointNormal = FVector(0, 1, 0);
			OutHitRecord.SetFaceNormal(InRay, HitPointNormal);

			OutHitRecord.t = t;
			OutHitRecord.U = (HitX - m_BeginX) / (m_EndX - m_BeginX);
			OutHitRecord.V = (HitZ - m_BeginZ) / (m_EndZ - m_BeginZ);

			OutHitRecord.HitObj = this;
			OutHitRecord.Mat = m_Material;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool FRectangle_YPlane::BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const
{
	OutBox = FAABB(FVector(m_BeginX, m_Y-0.1, m_BeginZ), FVector(m_EndX, m_Y+0.1, m_EndZ));
	return true;
}
