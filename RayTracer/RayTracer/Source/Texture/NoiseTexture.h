#pragma once
#include "Texture.h"
#include "PerlinNoise/PerlinNoise.h"


class FNoiseTexture : public ITexture
{
public:
	FNoiseTexture()
	{

	}

	FNoiseTexture(double InScale)
		: m_Scale(InScale)
	{

	}

public:
	virtual FColor Value(double InU, double InV, const FVector& InPoint) const override
	{
		return FColor(1, 1, 1)*0.5*(1+FMath::Sin(m_Scale*InPoint.Z + 10*m_PerlinNoise.Turbulence(InPoint)));
	}



protected:
	double m_Scale = 1;
	FPerlinNoise m_PerlinNoise;
};
