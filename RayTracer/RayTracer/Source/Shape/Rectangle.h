#pragma once
#include "Hit/BaseHit.h"


// a rectangle on plane z
class FRectangle_ZPlane : public IHitTable
{
public:
	FRectangle_ZPlane(double InBeginX, double InEndX, double InBeginY, double InEndY, double InZ, std::shared_ptr<IMaterial> InMaterial)
		: m_Material(InMaterial)
		, m_BeginX(InBeginX)
		, m_EndX(InEndX)
		, m_BeginY(InBeginY)
		, m_EndY(InEndY)
		, m_Z(InZ)
	{

	}
	
public:
	virtual bool Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const override;

	virtual bool BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const override;

protected:
	std::shared_ptr<IMaterial> m_Material;
	double m_BeginX = 0;
	double m_EndX = 0;
	double m_BeginY = 0;
	double m_EndY = 0;
	double m_Z = 0;
};

// a rectangle on plane x
class FRectangle_XPlane : public IHitTable
{
public:
	FRectangle_XPlane(double InBeginY, double InEndY, double InBeginZ, double InEndZ, double InX, std::shared_ptr<IMaterial> InMaterial)
		: m_Material(InMaterial)
		, m_BeginY(InBeginY)
		, m_EndY(InEndY)
		, m_BeginZ(InBeginZ)
		, m_EndZ(InEndZ)
		, m_X(InX)
	{

	}

public:
	virtual bool Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const override;

	virtual bool BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const override;

protected:
	std::shared_ptr<IMaterial> m_Material;
	double m_BeginY = 0;
	double m_EndY = 0;
	double m_BeginZ = 0;
	double m_EndZ = 0;
	double m_X = 0;
};


// a rectangle on plane x
class FRectangle_YPlane : public IHitTable
{
public:
	FRectangle_YPlane(double InBeginX, double InEndX, double InBeginZ, double InEndZ, double InY, std::shared_ptr<IMaterial> InMaterial)
		: m_Material(InMaterial)
		, m_BeginX(InBeginX)
		, m_EndX(InEndX)
		, m_BeginZ(InBeginZ)
		, m_EndZ(InEndZ)
		, m_Y(InY)
	{

	}

public:
	virtual bool Hit(const FRay& InRay, double MinT, double MaxT, FHitRecord& OutHitRecord) const override;

	virtual bool BoundingBox(double InTime0, double InTime1, FAABB& OutBox) const override;

protected:
	std::shared_ptr<IMaterial> m_Material;
	double m_BeginX = 0;
	double m_EndX = 0;
	double m_BeginZ = 0;
	double m_EndZ = 0;
	double m_Y = 0;
};
