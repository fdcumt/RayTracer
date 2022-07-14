#pragma once

struct FMath
{
public:
	static const double M_PI; // 3.14159265358979323846

public:
	// return [0,1]
	static double Random();

	// return [min, max]
	static double Random(double InMin, double InMax) { return Random()*(InMax-InMin) +InMin; }

	static double Clamp(double X, double Min, double Max) { return X<=Min ? Min : (X>=Max ? Max:X); }

	static double Cos(double Radian);
	static float Cosf(float Radian);
	static double ACos(double Radian);
	static float ACosf(float Radian);

	static double Sin(double Radian);
	static float Sinf(float Radian);
	static double ASin(double Radian);
	static float ASinf(float Radian);

	static double Tan(double Radian);
	static float Tanf(float Radian);
	static double Atan(double Radian);
	static float Atanf(float Radian);

	static double Sqrt(double Radian);
	static float Sqrt(float Radian);

	static double Pow(double Base, double Exp);

	template< class T >
	static T Abs(const T A)
	{
		return (A >= (T)0) ? A : -A;
	}

};

