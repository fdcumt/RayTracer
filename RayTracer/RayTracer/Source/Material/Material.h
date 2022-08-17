#pragma once
#include "Ray/Ray.h"
#include "Hit/BaseHit.h"
#include "Common/Color.h"

class IMaterial
{
public:
	virtual FColor Emmit(double InU, double InV, const FVector& InPoint) const { return FColor::Black; }
	virtual bool Scatter(const FRay &InRay, const FHitRecord &InHitRecord, FColor&OutAttenuation, FRay &OutScattered) const = 0;
};

