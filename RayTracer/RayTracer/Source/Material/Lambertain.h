#pragma once
#include "Material.h"
#include "Vector/Vector.h"

// 漫反射
class FLambertian : public IMaterial
{
public:
	FLambertian(const FVector& InAlbedo) : Albedo(InAlbedo)
	{

	}

	virtual bool Scatter(const FRay& InRay, const FHitRecord& InHitRecord, FVector& OutAttenuation, FRay& OutScattered) const override;

public:
	FVector Albedo; // 反射率
};

