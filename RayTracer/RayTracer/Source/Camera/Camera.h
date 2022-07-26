#pragma once
#include "Vector/Vector.h"
#include "Ray/Ray.h"
#include "Math/MathUtility.h"

class FCamera
{
public:
	FCamera(const FVector &InLookFromPoint, const FVector &InLookAtPoint, const FVector &InUp, 
		double InFov, double InAspect, double InAperture, double InFoucsDistance, double InBeginTime, double InEndTime)
	{
		m_Fov = InFov;
		m_Aspect = InAspect;

		m_Origin = InLookFromPoint;

		m_ApertureRadius = InAperture/2;
		m_FoucsDistance = InFoucsDistance;

		//
		//m_LookAtDir = (InLookAtPoint-InLookFromPoint).Normal();
		//m_RightDir = FVector::CrossProduct(m_LookAtDir, InUp).Normal();
		//m_UpDir = FVector::CrossProduct(m_RightDir, m_LookAtDir).Normal();

		//
		m_LookAtDir = (InLookFromPoint-InLookAtPoint).Normal();
		m_RightDir = FVector::CrossProduct(InUp, m_LookAtDir).Normal();
		m_UpDir = FVector::CrossProduct(m_LookAtDir, m_RightDir).Normal();

		double theta = FMath::DegreesToRadians(InFov);
		double HalfHeight = FMath::Tan(theta/2);
		double HalfWidth = m_Aspect*HalfHeight;

		m_LowerLeftCorner = m_Origin-HalfHeight*m_FoucsDistance*m_UpDir-HalfWidth* m_FoucsDistance*m_RightDir-m_LookAtDir*m_FoucsDistance;

		m_Horizontial = m_RightDir*HalfWidth*2* m_FoucsDistance;
		m_Vertical = m_UpDir*HalfHeight*2* m_FoucsDistance;

		m_BeginTime = InBeginTime;
		m_EndTime = InEndTime;
	}

	FRay GetRay(double U, double V);

protected:
	FVector m_Origin;
	FVector m_UpDir;
	FVector m_RightDir;
	FVector m_LookAtDir;

	FVector m_LowerLeftCorner;
	FVector m_Horizontial;
	FVector m_Vertical;

	double m_ApertureRadius;
	double m_FoucsDistance;

	double m_Fov; // top 2 bottom in degrees
	double m_Aspect; //

	double m_BeginTime = 0;
	double m_EndTime = 0;
};

