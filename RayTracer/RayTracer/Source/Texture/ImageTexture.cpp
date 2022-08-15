#include "ImageTexture.h"
#include "Math/MathUtility.h"
#include "StbImage/RTW_StbImage.h"


FImageTexture::FImageTexture(const char* InFileName)
	:m_FileName(InFileName)
{
	int ComponentsPerPixel = m_BytePerPixel;
	m_Data = FRTWStbImage::stbi_load(InFileName, &m_Width, &m_Height, &ComponentsPerPixel, ComponentsPerPixel);

	if (m_Data==nullptr)
	{
		std::cerr<<"ERROR: Could not load texture image file:["<<InFileName<<"].\n";
	}
	else
	{
		std::cerr << "Succeed: load texture image file:[" << InFileName << "] OK.\n";
	}

	m_BytePerScanline = m_BytePerPixel*m_Width;

}

FImageTexture::~FImageTexture()
{
	delete m_Data;
}

FColor FImageTexture::Value(double InU, double InV, const FVector& InPoint) const
{
	if (m_Data==nullptr)
	{
		return FColor::Cyan;
	}

	// clamp input texture coordinates to [0,1]X[1,0]
	InU = FMath::Clamp(InU, 0, 1);
	InV = 1-FMath::Clamp(InV, 0, 1); // flip V into image coordinates

	int i = static_cast<int>(InU*m_Width);
	int j = static_cast<int>(InV*m_Height);

	if (i>=m_Width) i = m_Width-1;
	if (j>=m_Height) j = m_Height-1;

	double ColorScale = 1.0/255.0;
	int a = j * m_BytePerScanline;
	int b = i * m_BytePerPixel;
	unsigned char *Pixel = m_Data+a+b;
	//std::cerr<<"Pixel---"<<"i:"<<i<<",j:"<<j<<",a:" << a << ",b:" << b << "---" << static_cast<int>(Pixel[0]) << "," << static_cast<int>(Pixel[1]) << "," << static_cast<int>(Pixel[2]) << "\n";
	return FColor(Pixel[0] * ColorScale, Pixel[1] * ColorScale, Pixel[2] * ColorScale);

}

