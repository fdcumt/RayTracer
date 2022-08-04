#pragma once
#include "Vector/Vector.h"
#include "Ray/Ray.h"

class FAABB
{
public:
	FAABB()
	{

	}

	FAABB(const FVector &InMinPoint, const FVector &InMaxPoint)
		:m_MinPoint(InMinPoint), m_MaxPoint(InMaxPoint)
	{

	}

public:
	FVector GetMin() const { return m_MinPoint; }
	FVector GetMax() const { return m_MaxPoint; }

public:
	bool Hit(const FRay &InRay, double InMinT, double InMaxT) const;

	static FAABB SurroundingBox(const FAABB &InA, const FAABB &InB);

protected:
	bool CheckInterval(double& InOutMinT, double& InOutMaxT, double InMinPointValue, double InMaxPointValue, double InDiectionValue, double OriginValue) const;

protected:
	FVector m_MinPoint = FVector::ZeroVector;
	FVector m_MaxPoint = FVector::ZeroVector;
};

