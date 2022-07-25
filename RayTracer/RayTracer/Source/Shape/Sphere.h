#pragma once
#include "../Hit/BaseHit.h"


class FSphere : public IHitTable
{
public:
	FSphere(std::shared_ptr<IMaterial> InMat)
		: Radius(0.f), Center(FVector::ZeroVector), Mat(InMat)
	{

	}

	FSphere(double InRadius, std::shared_ptr<IMaterial> InMat)
		: Radius(InRadius), Center(FVector::ZeroVector), Mat(InMat)
	{

	}


	FSphere(const FVector &InCenter, const double InRadius, std::shared_ptr<IMaterial> InMat)
		: Radius(InRadius), Center(InCenter), Mat(InMat)
	{
		
	}

	double GetRadius() const { return Radius; }
	FVector GetCenter() const { return Center; }
	
	virtual bool Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const override; 
	
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
	double Radius;
	FVector Center;

	std::shared_ptr<IMaterial> Mat;
};

