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

	FColor(int InR, int InG, int InB)
		: R(double(InR)/255), G(double(InG)/255), B(double(InB)/255)
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

	friend FColor operator*(const FColor &InColor, double InValue)
	{
		return FColor(InColor.R*InValue, InColor.B*InValue, InColor.G*InValue);
	}

	friend FColor operator*(double InValue, const FColor& InColor)
	{
		return InColor*InValue;
	}

};
