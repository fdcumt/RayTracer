#include "PerlinNoise.h"
#include "Math/MathUtility.h"
#include "Shape/Sphere.h"

FPerlinNoise::FPerlinNoise()
{
	m_pRandomVector = new FVector[m_PointCount];
	for (int i = 0; i < m_PointCount; ++i)
	{
		m_pRandomVector[i] = FSphere::RandomPointOnOriginalUnitSphereSurface();
	}

	for (int i=0; i<3; ++i)
	{
		m_pPermuteList[i] = GeneratePermute();
	}
}

FPerlinNoise::~FPerlinNoise()
{
	delete []m_pRandomVector;
	for (int i = 0; i < 3; ++i)
	{
		delete []m_pPermuteList[i];
	}
}

double FPerlinNoise::Noise(const FVector& InPoint) const
{
	double u = InPoint.X - FMath::Floor(InPoint.X);
	double v = InPoint.Y - FMath::Floor(InPoint.Y);
	double w = InPoint.Z - FMath::Floor(InPoint.Z);


	int PositionX = static_cast<int>(FMath::Floor(InPoint.X));
	int PositionY = static_cast<int>(FMath::Floor(InPoint.Y));
	int PositionZ = static_cast<int>(FMath::Floor(InPoint.Z));

	u = u * u * (3 - 2 * u);
	v = v * v * (3 - 2 * v);
	w = w * w * (3 - 2 * w);


	double ValueList[2][2][2];
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				ValueList[i][j][k] = FVector::DotProduct(m_pRandomVector[
					m_pPermuteList[0][(PositionX + i) & 255] ^
					m_pPermuteList[1][(PositionY + j) & 255] ^
					m_pPermuteList[2][(PositionZ + k) & 255]], FVector(u-i, v-j, w-k));
			}
		}
	}

	return TrilinearInterpolation(ValueList, u, v, w);
}

double FPerlinNoise::Turbulence(const FVector& InPoint, const int InDepth /*= 7*/) const
{
	// https://www.cnblogs.com/KillerAery/p/10765897.html
	double Accumulated = 0;
	FVector Point = InPoint;
	double Weight = 1;
	for (int i=0; i<InDepth; ++i)
	{
		Accumulated += Weight*Noise(Point);
		Point *= 2;
		Weight *= 0.5;
	}

	return FMath::Abs(Accumulated);
}

int* FPerlinNoise::GeneratePermute()
{
	int *p = new int[m_PointCount];
	for (int i=0; i<m_PointCount; ++i)
	{
		p[i] = i;
	}

	DoPermute(p, m_PointCount);

	return p;
}

void FPerlinNoise::DoPermute(int* p, int ArraySize)
{
	for (int i= ArraySize-1; i>0; --i)
	{
		int SwapIndex = FMath::RandomInt(0, i);

		if (SwapIndex!=i)
		{
			FMath::Swap(p[SwapIndex], p[i]);
		}
	}
}

double FPerlinNoise::TrilinearInterpolation(double p[2][2][2], double u, double v, double w)
{
	// 三线性插值 参考:https://zhuanlan.zhihu.com/p/550252625
	return (1-u)*(1-v)*(1-w)*p[0][0][0]+ // A
			u*(1-v)*(1-w)*p[1][0][0]+ // B
			u*v*(1-w)*p[1][1][0]+ // C
			(1-u)*v*(1-w)*p[0][1][0]+ // D
			(1-u)*(1-v)*w*p[0][0][1]+ // E
			u*(1-v)*w*p[1][0][1]+ // F
			u*v*w*p[1][1][1]+ // G
			(1-u)*v*w*p[0][1][1]; // H

// 	auto accum = 0.0;
// 	for (int i = 0; i < 2; i++)
// 		for (int j = 0; j < 2; j++)
// 			for (int k = 0; k < 2; k++)
// 				accum += (i * u + (1.0 - i) * (1 - u)) *
// 				(j * v + (1.0 - j) * (1 - v)) *
// 				(k * w + (1.0 - k) * (1 - w)) * p[i][j][k];
// 
// 	return accum;
}

