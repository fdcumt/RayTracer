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

	static int RandomInt(int InMin, int InMax);


	static double Clamp(double X, double Min, double Max) { return X<=Min ? Min : (X>=Max ? Max:X); }

	static double DegreesToRadians(double InDegrees) { return InDegrees*M_PI/180.f; }

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
	static double Atan2(double InY, double InX);

	static double Sqrt(double Radian);
	static float Sqrt(float Radian);

	static double Pow(double Base, double Exp);

	static double Floor(double Base);

	static double Min(double A, double B) { return A<=B ? A:B;}
	static double Max(double A, double B) { return A >= B ? A : B; }

	template< class T >
	static T Abs(const T A)
	{
		return (A >= (T)0) ? A : -A;
	}

	static void Swap(double &A, double &B);

	template< class T >
	static void Swap(T &A, T &B)
	{
		T Temp;
		Temp = A;
		A = B;
		B = Temp;
	}


};

