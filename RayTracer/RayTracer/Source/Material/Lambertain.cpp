#include "Lambertain.h"
#include "Shape/Sphere.h"

bool FLambertain::Scatter(const FRay& InRay, const FHitRecord& InHitRecord, FVector& OutAttenuation, FRay& OutScattered) const
{
	FVector ScatterDirection = FSphere::RandomPointOnOriginalUnitSphereSurface();
	OutScattered = FRay(InHitRecord.HitPoint, ScatterDirection);
	OutAttenuation = Albedo;

	return true;
}

