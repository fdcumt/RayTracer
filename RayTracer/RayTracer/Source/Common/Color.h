#pragma once
#include "Vector/Vector.h"

class FColor
{
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

	friend FColor operator*(const FColor &InColor, double InValue)
	{
		return FColor(InColor.R*InValue, InColor.B*InValue, InColor.G*InValue);
	}

	friend FColor operator*(double InValue, const FColor& InColor)
	{
		return InColor*InValue;
	}

};
