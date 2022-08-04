#pragma once
#include "BaseHit.h"
#include <vector>
#include <memory>

class FHitTableList : public IHitTable
{
public:
	FHitTableList()
	{
	}

	void Add(std::shared_ptr<IHitTable> InObject)
	{
		ObjectList.push_back(InObject);
	}

	std::vector<std::shared_ptr<IHitTable>>& GetObjectList() { return ObjectList; }

	void Remove(std::shared_ptr<IHitTable> InObject);

	virtual bool Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const override;
	virtual bool BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const override;


	virtual bool CheckIsPointInner(const FVector& InPoint) const;


protected:
	std::vector<std::shared_ptr<IHitTable>> ObjectList;
};

