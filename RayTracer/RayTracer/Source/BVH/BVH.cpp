#include "BVH.h"
#include "Hit/HitTableList.h"
#include "Math/MathUtility.h"
#include <algorithm>


FBVH::FBVH(FHitTableList& HitTableList, double InTime0, double InTime1)
	:FBVH(HitTableList.GetObjectList(), InTime0, InTime1)
{

}

FBVH::FBVH(std::vector<std::shared_ptr<IHitTable>>& ObjList, double InTime0, double InTime1)
	: FBVH(ObjList, 0, (int)ObjList.size(), InTime0, InTime1)
{

}

FBVH::FBVH(std::vector<std::shared_ptr<IHitTable>>& ObjList, int InBeginIndex, int InEndIndex, double InTime0, double InTime1)
{
	ConstructBVHInner(ObjList, InBeginIndex, InEndIndex, InTime0, InTime1);
}

bool FBVH::Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const
{
	if (!m_Box.Hit(InRay, MinT, MaxT))
	{
		return false;
	}

	bool bHit = false;
	if (m_Left!=nullptr)
	{
		bHit = m_Left->Hit(InRay, MinT, MaxT, OutHitRecord);
	}

	if ( m_Right!=nullptr)
	{
		bHit |= m_Right->Hit(InRay, MinT, bHit ? OutHitRecord.t:MaxT, OutHitRecord);
	}
	
	return bHit;
}

bool FBVH::BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const
{
	OutBox = m_Box;

	return true;
}

void FBVH::ConstructBVHInner(std::vector<std::shared_ptr<IHitTable>>& ObjList, int InBeginIndex, int InEndIndex, double InTime0, double InTime1)
{
	int ObjNum = InEndIndex-InBeginIndex;

	int axis = FMath::RandomInt(0, 2);

	auto CompareLambda = [axis, InTime0, InTime1](const std::shared_ptr<IHitTable> &A, const std::shared_ptr<IHitTable> &B) -> bool {
		FAABB BoxA;
		FAABB BoxB;
		if (A->BoundingBox(InTime0, InTime1, BoxA) && B->BoundingBox(InTime0, InTime1, BoxB))
		{
			return BoxA.GetMin()[axis] < BoxB.GetMin()[axis];
		}
		else
		{
			std::cerr << "No bounding box in bvh_node constructor.\n";
			return false;
		}
	};


	if (ObjNum <= 0)
	{
		m_Left = nullptr;
		m_Right = nullptr;
	}
	else if (ObjNum == 1)
	{
		m_Left = ObjList[InBeginIndex];
		m_Right = nullptr;
	}
	else if (ObjNum == 2)
	{
		if (CompareLambda(ObjList[InBeginIndex], ObjList[InBeginIndex+1]))
		{
			m_Left = ObjList[InBeginIndex];
			m_Right = ObjList[InBeginIndex+1];
		}
		else
		{
			m_Left = ObjList[InBeginIndex+1];
			m_Right = ObjList[InBeginIndex];
		}
	}
	else
	{
		std::sort(ObjList.begin()+InBeginIndex, ObjList.begin()+InEndIndex, CompareLambda);

		int MidIndex = InBeginIndex+(ObjNum+1)/2;
		m_Left = std::make_shared<FBVH>(ObjList, InBeginIndex, MidIndex, InTime0, InTime1);
		m_Right = std::make_shared<FBVH>(ObjList, MidIndex, InEndIndex, InTime0, InTime1);
	}

	if (m_Left!=nullptr && m_Right!=nullptr )
	{
		FAABB BoxLeft, BoxRight;
		if (m_Left->BoundingBox(InTime0, InTime1, BoxLeft) && m_Right->BoundingBox(InTime0, InTime1, BoxRight))
		{
			m_Box = FAABB::SurroundingBox(BoxLeft, BoxRight);
		}
		else
		{
			std::cerr<<"No bounding box in bvh_node constructor.\n";
		}
	}
	else if (m_Left!=nullptr)
	{
		if (!m_Left->BoundingBox(InTime0, InTime1, m_Box))
		{
			std::cerr << "No bounding box in bvh_node constructor.\n";
		}
	}
	else if (m_Right != nullptr)
	{
		if (!m_Right->BoundingBox(InTime0, InTime1, m_Box))
		{
			std::cerr << "No bounding box in bvh_node constructor.\n";
		}
	}
}
