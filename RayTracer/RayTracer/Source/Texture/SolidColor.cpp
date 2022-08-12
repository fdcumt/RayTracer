#include "SolidColor.h"


FColor FSolidColor::Value(double InU, double InV, const FVector& InPoint) const
{
	return m_Color;
}

