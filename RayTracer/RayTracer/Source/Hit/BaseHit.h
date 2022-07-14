#pragma once
#include "../Vector/Vector.h"
#include "../Ray/Ray.h"
#include <memory>

extern const double infinity;
class IHitTable;
class IMaterial;

struct FHitRecord
{
	FVector HitPoint;
	FVector Normal;
	double t;
	bool bFrontFace; // 正面朝向, 我们定义, 法线方向永远和入射光线方向相反
	const IHitTable *HitObj = nullptr;
	std::shared_ptr<IMaterial> Mat;
	void SetFaceNormal(const FRay &InRay, const FVector &OutwardNormal);
};

class IHitTable
{
public:
	virtual bool Hit(const FRay &InRay, double MinT, double MaxT, FHitRecord &OutHitRecord) const = 0 ;
	virtual bool CheckIsPointInner(const FVector &InPoint) const = 0;
};


