#pragma once
#include "Vector/Vector.h"
#include "Ray/Ray.h"

class FCamera
{
public:
	FCamera()
		: m_Origin(0.f, 0.f, 0.f)
		, m_LowerLeftCorner(-2.f, -1.f, -1.f)
		, m_Horizontial(4.f, 0.f, 0.f)
		, m_Vertical(0.f, 2.f, 0.f)
	{
		
	}

	FRay GetRay(double U, double V);
protected:
	FVector m_Origin;
	FVector m_LowerLeftCorner;
	FVector m_Horizontial;
	FVector m_Vertical;
};

