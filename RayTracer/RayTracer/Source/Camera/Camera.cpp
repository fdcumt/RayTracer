#include "Camera.h"
#include "Math/MathUtility.h"

FRay FCamera::GetRay(double U, double V)
{
	U = FMath::Clamp(U, 0, 1);
	V = FMath::Clamp(V, 0, 1);
	return FRay(m_Origin, m_LowerLeftCorner + U * m_Horizontial + V * m_Vertical-m_Origin);
}

