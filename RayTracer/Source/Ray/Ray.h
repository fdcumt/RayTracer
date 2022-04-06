#pragma once
#include "Vector/Vector.h"

class FRay
{
public:
	FRay()
	{

	}

	FRay(const FVector& InOriginal, const FVector& InDirection)
		:Original(InOriginal), Direction(InDirection)
	{

	}

	FVector GetOriginal() const { return Original; }
	FVector GetDirection() const { return Direction; }

	FVector At(float t) const { return Original + Direction*t; }

private:
	FVector Original = FVector::ZeroVector;
	FVector Direction = FVector::ZeroVector;
};
