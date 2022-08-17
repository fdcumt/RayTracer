#pragma once
#include "Vector/Vector.h"

class FColor
{
public:
	static const FColor White;
	static const FColor Black;
	static const FColor Red;
	static const FColor Green;
	static const FColor Blue;
	static const FColor Yellow;
	static const FColor Cyan;
	static const FColor Magenta;
	static const FColor Orange;
	static const FColor Purple;
	static const FColor Turquoise;
	static const FColor Silver;
	static const FColor Emerald;

public:
	double R = 0;
	double G = 0;
	double B = 0;

public:
	FColor()
	{

	}

	FColor(double InR, double InG, double InB)
		: R(InR), G(InG), B(InB)
	{
		
	}

	FColor(const FVector &InVector)
		: R(InVector.X), G(InVector.Y), B(InVector.Z)
	{

	}

	FColor(const FColor &InColor)
		: R(InColor.R), G(InColor.G), B(InColor.B)
	{
	 
	}

	FVector GetVector() const
	{
		return FVector(R, G, B);
	}

	void WriteColor(int SamplePerPixel) const;

	static FColor Random();
	static FColor Random(double InMin, double InMax);

	bool IsGrayScale() const {
		return R==B && B==G;
	}

	const char* ToString() const;

public:
	FColor& operator+=(const FColor& Other)
	{
		R += Other.R;
		G += Other.G;
		B += Other.B;
		return *this;
	}

public:
	friend FColor operator+(const FColor& InColorA, const FColor & InColorB)
	{
		return FColor(InColorA.R+InColorB.R, InColorA.B+InColorB.B, InColorA.G+InColorB.G);
	}

	friend FColor operator*(const FColor &InColor, double InValue)
	{
		return FColor(InColor.R*InValue, InColor.B*InValue, InColor.G*InValue);
	}

	friend FColor operator*(double InValue, const FColor& InColor)
	{
		return InColor*InValue;
	}

	friend FColor operator*(const FColor &A, const FColor&B)
	{
		return FColor(A.R * B.R, A.B * B.B, A.G * B.G);
	}

};
