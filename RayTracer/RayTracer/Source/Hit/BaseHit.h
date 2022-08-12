#pragma once
#include "../Vector/Vector.h"
#include "../Ray/Ray.h"
#include <memory>
#include "Shape/AABB.h"

extern const double infinity;
class IHitTable;
class IMaterial;

struct FHitRecord
{
	FVector HitPoint;
	FVector Normal;
	double t; // for ray trace

	// u,v coordinates
	double U;
	double V;

	bool bFrontFace; 
	const IHitTable *HitObj = nullptr;
	std::shared_ptr<IMaterial> Mat;
	void SetFaceNormal(const FRay &InRay, const FVector &OutwardNormal);
};

class IHitTable
{
public:
	virtual bool Hit(const FRay &InRay, double MinT, double MaxT, FHitRecord &OutHitRecord) const = 0 ;
	virtual bool CheckIsPointInner(const FVector &InPoint) const { return false; }

	virtual bool BoundingBox(double InTime0, double InTime1, FAABB &OutBox) const = 0;
};


