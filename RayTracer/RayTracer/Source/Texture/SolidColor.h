#pragma once
#include "Texture.h"


class FSolidColor : public ITexture
{
public:
	FSolidColor()
	{
		
	}

	FSolidColor(const FColor &InColor)
		: m_Color(InColor)
	{

	}

	virtual FColor Value(double InU, double InV, const FVector &InPoint) const override;

protected:
	FColor m_Color;
};