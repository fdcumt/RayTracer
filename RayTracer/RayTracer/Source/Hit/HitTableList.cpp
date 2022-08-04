#include "HittableList.h"
#include "Common/CommonDefine.h"


void FHitTableList::Remove(std::shared_ptr<IHitTable> InObject)
{
	std::vector<std::shared_ptr<IHitTable>>::const_iterator it = ObjectList.begin();
	std::vector<std::shared_ptr<IHitTable>>::const_iterator ItEnd = ObjectList.begin();
	while (it != ItEnd)
	{
		if (*it == InObject)
		{
			ObjectList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool FHitTableList::Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const
{
	FHitRecord HitRecord;
	bool bHitAnything = false;
	double ClosestSoFar = MaxT;
	FHitRecord tempHitRecord;
	for (std::shared_ptr<IHitTable> HitObject : ObjectList)
	{
		if (HitObject->Hit(InRay, MinT, ClosestSoFar, tempHitRecord))
		{
			bHitAnything = true;
			ClosestSoFar = tempHitRecord.t;
			OutHitRecord = tempHitRecord;
		}
	}

	return bHitAnything;
}

bool FHitTableList::BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const
{
	int ObjNum = static_cast<int>(ObjectList.size());
	if (ObjNum>0)
	{
		if (!ObjectList[0]->BoundingBox(InTime0, InTime1, OutBox))
		{
			return false;
		}

		for (int i=1; i<ObjNum; ++i)
		{
			FAABB Box;
			if (!ObjectList[i]->BoundingBox(InTime0, InTime1, Box))
			{
				return false;
			}

			OutBox = FAABB::SurroundingBox(OutBox, Box);
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool FHitTableList::CheckIsPointInner(const FVector& InPoint) const
{
	for (std::shared_ptr<IHitTable> HitObject : ObjectList)
	{
		Checkf(!HitObject->CheckIsPointInner(InPoint), "point can`t inner");
	}
	return false;
}

