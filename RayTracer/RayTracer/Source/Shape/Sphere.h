#pragma once
#include "../Hit/BaseHit.h"


class FSphere : public IHitTable
{
public:
	FSphere(std::shared_ptr<IMaterial> InMat)
		: m_Radius(0.f), m_Center(FVector::ZeroVector), Mat(InMat)
	{
		
	}

	FSphere(double InRadius, std::shared_ptr<IMaterial> InMat)
		: m_Radius(InRadius), m_Center(FVector::ZeroVector), Mat(InMat)
	{

	}


	FSphere(const FVector &InCenter, const double InRadius, std::shared_ptr<IMaterial> InMat)
		: m_Radius(InRadius), m_Center(InCenter), Mat(InMat)
	{
		
	}

public:
	virtual bool Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const override;
	virtual bool BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const override;


public:
	double GetRadius() const { return m_Radius; }
	FVector GetCenter() const { return m_Center; }

	// calculate u,v by given point on unit sphere which origin point is zero
	static void GetSphereUV(const FVector &InPoint, double &OutU, double OutV);

	
	FVector RandomPointInSphere(const bool bInclueSphereSurface = true) const;

	FVector RandomPointOnSphereSurface() const;

	FVector RandomPointInHemisphere(const FVector & InNormal, const bool bInclueSphereSurface = true) const;
	FVector RandomPointOnHemisphereSurface(const FVector & InNormal) const;

	static FVector RandomDirectionOnHemisphereSurface(const FVector &InNormal);

	static FVector RandomPointOnOriginalUnitSphereSurface();

	bool IsPointInSphere(const FVector &InPoint) const;
	virtual bool CheckIsPointInner(const FVector& InPoint) const override {
		return IsPointInSphere(InPoint);
	}


protected:
	double m_Radius;
	FVector m_Center;

	std::shared_ptr<IMaterial> Mat;
};

