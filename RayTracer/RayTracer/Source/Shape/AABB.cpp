#include "AABB.h"
#include "Math/MathUtility.h"

bool FAABB::Hit(const FRay& InRay, double InMinT, double InMaxT) const
{
	if (InRay.GetDirection() == FVector::ZeroVector)
	{
		return false;
	}

	bool bHit = CheckInterval(InMinT, InMaxT, m_MinPoint.X, m_MaxPoint.X, InRay.GetDirection().X, InRay.GetOriginal().X);
	bHit = bHit && CheckInterval(InMinT, InMaxT, m_MinPoint.Y, m_MaxPoint.Y, InRay.GetDirection().Y, InRay.GetOriginal().Y);
	bHit = bHit && CheckInterval(InMinT, InMaxT, m_MinPoint.Z, m_MaxPoint.Z, InRay.GetDirection().Z, InRay.GetOriginal().Z);

	return bHit;

}

FAABB FAABB::SurroundingBox(const FAABB &InA, const FAABB& InB)
{
	typedef double (*FCalValueFunc)(double, double);
	auto CalFunc = [](const FVector &InX, const FVector &InY, FCalValueFunc pFunc)
	{
		return FVector(
			(*pFunc)(InX.X, InY.X),
			(*pFunc)(InX.Y, InY.Y),
			(*pFunc)(InX.Z, InY.Z)
		);
	};

	return FAABB(
		CalFunc(InA.m_MinPoint, InB.m_MinPoint, &FMath::Min),
		CalFunc(InA.m_MaxPoint, InB.m_MaxPoint, &FMath::Max)
	);
}

bool FAABB::CheckInterval(double& InOutMinT, double &InOutMaxT, double InMinPointValue, double InMaxPointValue, double InDiectionValue, double OriginValue) const
{
	if (InDiectionValue == 0)
	{
		return true;
	}

	double Temp = 1 / InDiectionValue;
	double MinT = (InMinPointValue - OriginValue) * Temp;
	double MaxT = (InMaxPointValue - OriginValue) * Temp;
	if (Temp < 0)
	{
		FMath::Swap(MinT, MaxT);
	}

	InOutMinT = FMath::Max(InOutMinT, MinT);
	InOutMaxT = FMath::Min(InOutMaxT, MaxT);

	return InOutMinT <= InOutMaxT;
}
