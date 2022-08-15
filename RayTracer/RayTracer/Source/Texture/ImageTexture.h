#pragma once
#include "Texture.h"


class FImageTexture : public ITexture
{
public:
	FImageTexture()
	{

	}

	FImageTexture(const char *InFileName);

	~FImageTexture();

public:
	virtual FColor Value(double InU, double InV, const FVector& InPoint) const override;

protected:
	const static int m_BytePerPixel = 3;

	const char *m_FileName = nullptr;
	unsigned char *m_Data = nullptr;
	int m_Width = 0;
	int m_Height = 0;
	int m_BytePerScanline = 0;

};
