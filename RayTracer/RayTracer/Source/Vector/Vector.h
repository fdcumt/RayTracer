#pragma once
#include <cmath>
#include <iostream>
#include "Common/CommonDefine.h"

#define THRESH_VECTOR_NORMALIZED		(0.01f)		/** Allowed error for a normalized vector (against squared magnitude) */

struct FVector
{
public:
	double X = 0.f;
	double Y = 0.f;
	double Z = 0.f;

public:
	static const FVector ZeroVector;
	static const FVector OneVector;

	static const FVector UpVector;
	static const FVector DownVector;

	static const FVector ForwardVector;
	static const FVector BackwardVector;

	static const FVector RightVector;
	static const FVector LeftVector;
	
public:
	FVector() {}
	FVector(const double InX, const double InY, const double InZ)
		:X(InX), Y(InY), Z(InZ)
	{
		
	}
	
	FVector(const FVector &Other)
		:X(Other.X), Y(Other.Y), Z(Other.Z)
	{
		
	}

	FVector(double InValue)
		:X(InValue), Y(InValue), Z(InValue)
	{
		
	}

public:
	FVector operator-() const { return FVector(-X, -Y, -Z); }

	FVector& operator+=(const FVector &InOther) 
	{
		X += InOther.X;
		Y += InOther.Y;
		Z += InOther.Z;
		return *this;
	}

	FVector& operator -= (const FVector& InOther)
	{
		X -= InOther.X;
		Y -= InOther.Y;
		Z -= InOther.Z;
		return *this;
	}

	FVector& operator *= (const FVector& InOther)
	{
		X *= InOther.X;
		Y *= InOther.Y;
		Z *= InOther.Z;
		return *this;
	}

	FVector& operator *= (const double InValue)
	{
		X *= InValue;
		Y *= InValue;
		Z *= InValue;
		return *this;
	}

	FVector& operator /= (const FVector& InOther)
	{
		X /= InOther.X;
		Y /= InOther.Y;
		Z /= InOther.Z;
		return *this;
	}

	FVector& operator /= (const double InValue)
	{
		X /= InValue;
		Y /= InValue;
		Z /= InValue;
		return *this;
	}

	FVector operator + (const FVector& Other) const
	{
		return FVector(X + Other.X, Y + Other.Y, Z + Other.Z);
	}

	FVector operator + (const int& Other) const
	{
		return FVector(X + Other, Y + Other, Z + Other);
	}

	FVector operator - (const FVector& Other) const
	{
		return FVector(X - Other.X, Y - Other.Y, Z - Other.Z);
	}

	FVector operator * (const FVector& Other) const
	{
		return FVector(X * Other.X, Y * Other.Y, Z * Other.Z);
	}

	FVector operator * (const double InValue) const
	{
		return FVector(X * InValue, Y * InValue, Z * InValue);
	}

	FVector operator / (const FVector& Other) const
	{
		return FVector(X / Other.X, Y / Other.Y, Z / Other.Z);
	}

	FVector operator / (const double InValue) const
	{
		return FVector(X / InValue, Y / InValue, Z / InValue);
	}

	double SizeSquare() const
	{
		return X*X + Y*Y + Z*Z;
	}

	double Size() const;

	static double DotProduct (const FVector& A, const FVector &B)
	{
		return A.X*B.X+A.Y*B.Y+A.Z*B.Z;
	}

	FVector CrossProduct(const FVector& Other) const
	{
		return FVector(Y*Other.Z - Z*Other.Y, Z*Other.X - X*Other.Z, X*Other.Y - Y*Other.X);
	}

	static FVector CrossProduct(const FVector& A, const FVector& B)
	{
		return FVector(A.Y*B.Z - A.Z*B.Y, A.Z*B.X - A.X*B.Z, A.X*B.Y - A.Y*B.X);
	}

	FVector Normal() const
	{
		return *this/Size();
	}

	bool IsNormalized() const;

	// ??????
	static FVector Reflect(const FVector& InRayDirection, const FVector& InNormal)
	{
		Checkf(InNormal.IsNormalized(), "InNormal is not normalize");
		return InRayDirection-2*DotProduct(InRayDirection, InNormal)*InNormal;
	}

	// ??????, return is normal vector
	// InIndexOfRefractionReciprocal: ??????????????????
	static FVector Refraction(const FVector& InRayDirection, const FVector& InNormal, double InIndexOfRefractionReciprocal);

	void WriteColor(int SamplePerPixel) const;

	friend FVector operator *(double Scale, const FVector& InValue)
	{
		return InValue * Scale;
	}

};

inline std::ostream& operator << (std::ostream& Out, const FVector& V)
{
	return Out << V.X << ' ' << V.Y << ' ' << V.Z;
}





