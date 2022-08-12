#include "MathUtility.h"
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

const double FMath::M_PI = 3.14159265358979323846f;

double FMath::Random()
{
	//srand((unsigned)time(NULL));
	return  double(std::rand()) / (RAND_MAX);
}

int FMath::RandomInt(int InMin, int InMax)
{
	return std::rand()%(InMax-InMin)+InMin;
}

double FMath::Cos(double Radian)
{
	return std::cos(Radian);
}

float FMath::Cosf(float Radian)
{
	return std::cosf(Radian);
}

double FMath::ACos(double Radian)
{
	return std::acos(Radian);
}

float FMath::ACosf(float Radian)
{
	return std::acosf(Radian);
}

double FMath::Sin(double Radian)
{
	return std::sin(Radian);
}

float FMath::Sinf(float Radian)
{
	return std::sinf(Radian);
}

double FMath::ASin(double Radian)
{
	return std::asin(Radian);
}

float FMath::ASinf(float Radian)
{
	return std::asinf(Radian);
}

double FMath::Tan(double Radian)
{
	return std::tan(Radian);
}

float FMath::Tanf(float Radian)
{
	return std::tanf(Radian);
}

double FMath::Atan(double Radian)
{
	return std::atan(Radian);
}

float FMath::Atanf(float Radian)
{
	return std::atanf(Radian);
}

double FMath::Atan2(double InY, double InX)
{
	return std::atan2(InY, InX);
}

float FMath::Sqrt(float Radian)
{
	return std::sqrt(Radian);
}

double FMath::Sqrt(double Radian)
{
	return std::sqrt(Radian);
}

double FMath::Pow(double Base, double Exp)
{
	return std::pow(Base, Exp);
}

double FMath::Floor(double Base)
{
	return std::floor(Base);
}

void FMath::Swap(double& A, double& B)
{
	double Temp = A;
	A = B;
	B = Temp;
}

