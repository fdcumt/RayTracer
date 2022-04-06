#pragma once
#include <cmath>
#include <iostream>


struct FVector
{
public:
	float X = 0.f;
	float Y = 0.f;
	float Z = 0.f;

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
	FVector(const float InX, const float InY, const float InZ)
		:X(InX), Y(InY), Z(InZ)
	{
		
	}
	
	FVector(const FVector &Other)
		:X(Other.X), Y(Other.Y), Z(Other.Z)
	{
		
	}

	FVector(float InValue)
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

	FVector& operator *= (const float InValue)
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

	FVector& operator /= (const float InValue)
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

	FVector operator - (const FVector& Other) const
	{
		return FVector(X - Other.X, Y - Other.Y, Z - Other.Z);
	}

	FVector operator * (const FVector& Other) const
	{
		return FVector(X * Other.X, Y * Other.Y, Z * Other.Z);
	}

	FVector operator * (const float InValue) const
	{
		return FVector(X * InValue, Y * InValue, Z * InValue);
	}

	FVector operator / (const FVector& Other) const
	{
		return FVector(X / Other.X, Y / Other.Y, Z / Other.Z);
	}

	FVector operator / (const float InValue) const
	{
		return FVector(X / InValue, Y / InValue, Z / InValue);
	}

	float SizeSquare() const
	{
		return X*X + Y*Y + Z*Z;
	}

	float Size() const
	{
		return sqrt(SizeSquare());
	}

	float DotProduct (const FVector& Other) const
	{
		return X*Other.X+Y*Other.Y+Z*Other.Z;
	}

	FVector CrossProduct(const FVector& Other) const
	{
		return FVector(Y*Other.Z - Z*Other.Y, Z*Other.X - X*Other.Z, X*Other.Y - Y*Other.X);
	}

	FVector Normal() const
	{
		return *this/Size();
	}

	void WriteColor() const
	{
		std::cout<<static_cast<int>(255.99*X) <<' '
				<<static_cast<int>(255.99*Y) <<' '
				<<static_cast<int>(255.99*Z) <<'\n';
	}
};

inline std::ostream& operator << (std::ostream& Out, const FVector& V)
{
	return Out << V.X << ' ' << V.Y << ' ' << V.Z;
}

inline FVector operator *(float Scale, const FVector &InValue)
{
	return InValue*Scale;
}



