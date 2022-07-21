#pragma once

#include "Material.h"
#include "Vector/Vector.h"


class FDielectric : public IMaterial
{
public:
	FDielectric(const double InIndexOfRefraction) : m_IndexOfRefraction(InIndexOfRefraction)
	{

	}

	virtual bool Scatter(const FRay& InRay, const FHitRecord& InHitRecord, FVector& OutAttenuation, FRay& OutScattered) const override;

protected:
	// use schlick`s approximate for refraction
	static double SchlickApproximate(double CosTheta, double InIndexOfRefractionReciprocal);

protected:
	double m_IndexOfRefraction; // 折射率
};


