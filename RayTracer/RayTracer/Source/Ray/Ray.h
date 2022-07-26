#pragma once
#include "Vector/Vector.h"

class FRay
{
public:
	FRay()
	{

	}

	FRay(const FVector& InOriginal, const FVector& InDirection, double InTime)
		:m_Time(InTime), Original(InOriginal), Direction(InDirection)
	{

	}

	double GetTime() const { return m_Time; }
	FVector GetOriginal() const { return Original; }
	FVector GetDirection() const { return Direction; }

	FVector At(double t) const { return Original + Direction*t; }

private:
	double m_Time = 0;
	FVector Original = FVector::ZeroVector;
	FVector Direction = FVector::ZeroVector;
};
