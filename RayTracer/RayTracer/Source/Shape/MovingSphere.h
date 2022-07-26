#pragma once
#include "Hit/BaseHit.h"
#include "Sphere.h"

class FMovingSphere : public FSphere
{
public:
	FMovingSphere(const FVector& InBeginCenter, const FVector& InEndCenter, double InBeginTime, double InEndTime,
		const double InRadius, std::shared_ptr<IMaterial> InMat)
		: FSphere(InBeginCenter, InRadius, InMat)
		, m_EndCenter(InEndCenter)
		, m_BeginTime(InBeginTime)
		, m_EndTime(InEndTime)
	{
		
	}

	FVector GetCenter(double InTime) const
	{
		return FSphere::GetCenter() + (InTime-m_BeginTime)/(m_BeginTime-m_EndTime)*(m_EndCenter-FSphere::GetCenter());
	}

	virtual bool Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const override;


protected:
	FVector m_EndCenter; // begin to end
	double m_BeginTime = 0;
	double m_EndTime = 0;
};

