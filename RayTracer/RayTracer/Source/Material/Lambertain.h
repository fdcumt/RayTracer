#pragma once
#include "Material.h"
#include "Vector/Vector.h"
#include "Texture/Texture.h"
#include "Texture/SolidColor.h"

class FLambertian : public IMaterial
{
public:
	FLambertian(const FColor& InColor) : Albedo(std::make_shared<FSolidColor>(InColor))
	{

	}

	FLambertian(std::shared_ptr<ITexture> InTexture) : Albedo(InTexture)
	{

	}


	// 传播
	virtual bool Scatter(const FRay& InRay, const FHitRecord& InHitRecord, FColor& OutAttenuation, FRay& OutScattered) const override;

public:
	std::shared_ptr<ITexture> Albedo; // 反射率
};

