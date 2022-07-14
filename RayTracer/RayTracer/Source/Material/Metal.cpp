#include "Metal.h"
#include "Shape/Sphere.h"

bool FMetal::Scatter(const FRay& InRay, const FHitRecord& InHitRecord, FVector& OutAttenuation, FRay& OutScattered) const
{
	const FVector RefectDirection = FVector::Reflect(InRay.GetDirection(), InHitRecord.Normal);
	OutScattered = FRay(InHitRecord.HitPoint, RefectDirection+Fuzzy*FSphere::RandomPointOnOriginalUnitSphereSurface());
	OutAttenuation = Albedo;

	return (FVector::DotProduct(InRay.GetDirection(), InHitRecord.Normal));
}

