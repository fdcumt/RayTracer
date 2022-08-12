#include "CheckerTexture.h"
#include "Math/MathUtility.h"

FColor FCheckerTexture::Value(double InU, double InV, const FVector& InPoint) const
{
	double Sines = FMath::Sin(10*InPoint.X)* FMath::Sin(10*InPoint.Y)* FMath::Sin(10*InPoint.Z);
	if (Sines<0)
	{
		return m_ODD->Value(InU, InV, InPoint);
	}
	else
	{
		return m_Even->Value(InU, InV, InPoint);
	}
}


