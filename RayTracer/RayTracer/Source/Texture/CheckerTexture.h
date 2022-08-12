#pragma once
#include "Texture.h"
#include "SolidColor.h"


class FCheckerTexture : public ITexture
{
public:
	FCheckerTexture()
	{

	}

	FCheckerTexture(std::shared_ptr<ITexture> InODD, std::shared_ptr<ITexture> InEven)
		: m_ODD(InODD), m_Even(InEven)
	{

	}

	FCheckerTexture(const FColor &InColor1, const FColor& InColor2)
		: m_ODD(std::make_shared<FSolidColor>(InColor1)), m_Even(std::make_shared<FSolidColor>(InColor2))
	{

	}

public:
	virtual FColor Value(double InU, double InV, const FVector& InPoint) const override;

protected:
	std::shared_ptr<ITexture> m_ODD;
	std::shared_ptr<ITexture> m_Even;
};

