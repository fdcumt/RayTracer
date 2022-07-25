#pragma once
#include "Material.h"
#include "Vector/Vector.h"

class FLambertian : public IMaterial
{
public:
	FLambertian(const FVector& InAlbedo) : Albedo(InAlbedo)
	{

	}

	virtual bool Scatter(const FRay& InRay, const FHitRecord& InHitRecord, FVector& OutAttenuation, FRay& OutScattered) const override;

public:
	FVector Albedo;
};

