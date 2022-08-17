#include "DiffuseLight.h"


FColor FDiffuseLight::Emmit(double InU, double InV, const FVector& InPoint) const
{
 	return m_Emit->Value(InU, InV, InPoint);
}

bool FDiffuseLight::Scatter(const FRay& InRay, const FHitRecord& InHitRecord, FColor& OutAttenuation, FRay& OutScattered) const
{
	return false;
}

