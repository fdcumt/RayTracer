#pragma once
#include "Hit/BaseHit.h"
#include <vector>

class FHitTableList;

class FBVH : public IHitTable
{
public:
	FBVH()
	{

	}

	FBVH(FHitTableList& HitTableList, double InTime0, double InTime1);
	FBVH(std::vector<std::shared_ptr<IHitTable>>& ObjList, double InTime0, double InTime1);
	FBVH(std::vector<std::shared_ptr<IHitTable>>& ObjList, int InBeginIndex, int InEndIndex, double InTime0, double InTime1);

public:
	virtual bool Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const;
	virtual bool BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const;

protected:
	void ConstructBVHInner(std::vector<std::shared_ptr<IHitTable>>& ObjList, int InBeginIndex, int InEndIndex, double InTime0, double InTime1);

protected:
	FAABB m_Box;
	std::shared_ptr<IHitTable> m_Left;
	std::shared_ptr<IHitTable> m_Right;
};