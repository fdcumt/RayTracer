#include "Camera.h"
#include "Math/MathUtility.h"

FRay FCamera::GetRay(double U, double V)
{
	U = FMath::Clamp(U, 0, 1);
	V = FMath::Clamp(V, 0, 1);

	FVector RandomOffset = m_ApertureRadius * FVector::RandomVector2DInUnitDisk();
	RandomOffset = m_UpDir*RandomOffset.X + m_RightDir*RandomOffset.Y;

	return FRay(m_Origin+RandomOffset, 
		m_LowerLeftCorner + U * m_Horizontial + V * m_Vertical-m_Origin-RandomOffset,
		FMath::Random(m_BeginTime, m_EndTime));
}

