#pragma once
#include "Material.h"
#include "Vector/Vector.h"


class FMetal : public IMaterial
{
public:
	FMetal(const FColor& InAlbedo, double InFuzzy)
		: Albedo(InAlbedo), Fuzzy(InFuzzy)
	{

	}

	virtual bool Scatter(const FRay& InRay, const FHitRecord& InHitRecord, FColor& OutAttenuation, FRay& OutScattered) const;

public:
	FColor Albedo; 
	double Fuzzy;
};

