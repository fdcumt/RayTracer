#pragma once
#include "Common/Color.h"
#include "Vector/Vector.h"


class ITexture
{
public:
	virtual FColor Value(double InU, double InV, const FVector& InPoint) const = 0;
};
