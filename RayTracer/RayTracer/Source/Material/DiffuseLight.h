#pragma once
#include "Material.h"
#include "Texture/Texture.h"
#include "Texture/SolidColor.h"


class FDiffuseLight : public IMaterial
{
public:
	FDiffuseLight(std::shared_ptr<ITexture> InEmit)
		: m_Emit(InEmit)
	{

	}

	FDiffuseLight(const FColor &InColor)
		: m_Emit(std::make_shared<FSolidColor>(InColor))
	{
		
	}

public:
	virtual FColor Emmit(double InU, double InV, const FVector& InPoint) const override;
	virtual bool Scatter(const FRay& InRay, const FHitRecord& InHitRecord, FColor& OutAttenuation, FRay& OutScattered) const override;


protected:
	std::shared_ptr<ITexture> m_Emit;
};

