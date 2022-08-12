#pragma once
#include "Vector/Vector.h"


class FPerlinNoise
{
public:
	FPerlinNoise();
	~FPerlinNoise();

public:
	double Noise(const FVector &InPoint) const;

	double Turbulence(const FVector& InPoint, const int InDepth = 7) const;

protected:
	static int* GeneratePermute();
	static void DoPermute(int *p, int ArraySize);


	static double TrilinearInterpolation(double p[2][2][2], double u, double v, double w);

protected:
	static const int m_PointCount = 256;
	FVector *m_pRandomVector = nullptr;
	int *m_pPermuteList[3];
};
