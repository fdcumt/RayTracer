#pragma once
#include "Material.h"
#include "Vector/Vector.h"


class FMetal : public IMaterial
{
public:
	FMetal(const FVector& InAlbedo) : Albedo(InAlbedo)
	{

	}

	virtual bool Scatter(const FRay& InRay, const FHitRecord& InHitRecord, FVector& OutAttenuation, FRay& OutScattered) const;

public:
	FVector Albedo; // 反射率
};

