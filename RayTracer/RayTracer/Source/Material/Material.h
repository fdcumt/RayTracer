#pragma once
#include "Ray/Ray.h"
#include "Hit/BaseHit.h"

class IMaterial
{
public:
	virtual bool Scatter(const FRay &InRay, const FHitRecord &InHitRecord, FVector &OutAttenuation, FRay &OutScattered) const = 0;
};

