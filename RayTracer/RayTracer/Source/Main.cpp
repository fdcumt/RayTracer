#include <iostream>
#include "Main.h"
#include "Vector/Vector.h"
#include "Ray/Ray.h"
#include "Hit/HittableList.h"
#include "Shape/Sphere.h"
#include "Camera/Camera.h"
#include "Math/MathUtility.h"
#include "Hit/BaseHit.h"
#include "Material/Material.h"
#include "Material/Lambertain.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"

// 右手坐标系, Y轴向上.

FVector RayColor(const FRay &Ray, const FHitTableList &InHitTableList, int InDepth)
{
	if (InDepth<=0)
	{
		// return FVector::ZeroVector;
		return FVector(0.f, 0.f, 0.f);
	}

	FHitRecord ClosetHitRecord;
	if (InHitTableList.Hit(Ray, 0.001,	infinity, ClosetHitRecord))
	{
		FRay Scattered;
		FVector Attenuation;
		if (ClosetHitRecord.Mat->Scatter(Ray, ClosetHitRecord, Attenuation, Scattered))
		{
			return Attenuation*RayColor(Scattered, InHitTableList, InDepth-1);
		}

		return FVector::ZeroVector;
	}
	else
	{
		const FVector Direction = Ray.GetDirection().Normal();
		double Alpha = 0.5f * (Direction.Y + 1.0f);
		return FVector(1.0f, 1.0f, 1.0f) * (1.0f - Alpha) + FVector(0.5f, 0.7f, 1.0f) * Alpha;
	}
}

int main() 
{
	const int image_width = 200;
	const int image_height = 100;
	int SamplePerPixel = 100;
	int MaxDepth = 50;

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	FVector LookFromPoint(-2, 2, 1);
	//FVector LookFromPoint(0, 0, 0);
	FVector LookAtPoint(0, 0, -1);
	FVector UpDir(0, 1, 0);
	FCamera Camera(LookFromPoint, LookAtPoint, UpDir, 20, image_width/image_height);

	auto MaterialSmallBall = std::make_shared<FLambertian>(FVector(0.7, 0.3, 0.3));
	auto MaterialBigBall = std::make_shared<FLambertian>(FVector(0.8, 0.8, 0));
	auto MaterialLeft = std::make_shared<FMetal>(FVector(0.8, 0.6, 0.2), 0.3);
	auto MaterialDielectric = std::make_shared<FDielectric>(1.5);

	double R = FMath::Cos(FMath::M_PI/4);

	FHitTableList WorldObjectList;
	//WorldObjectList.Add(std::make_shared<FSphere>(FVector(-R, 0.f, -1.f), R, std::make_shared<FLambertian>(FVector(0, 0, 1))));
	//WorldObjectList.Add(std::make_shared<FSphere>(FVector(R, 0.f, -1.f), R, std::make_shared<FLambertian>(FVector(1, 0, 0))));


	WorldObjectList.Add(std::make_shared<FSphere>(FVector(0.f, 0.f, -1.f), 0.5, std::make_shared<FLambertian>(FVector(0.1, 0.2, 0.5))));
	WorldObjectList.Add(std::make_shared<FSphere>(FVector(0.f, -100.5f, -1.f), 100.f, std::make_shared<FLambertian>(FVector(0.8, 0.8, 0))));
	
	WorldObjectList.Add(std::make_shared<FSphere>(FVector(1, 0, -1), 0.5, std::make_shared<FMetal>(FVector(0.8, 0.6, 0.2), 0.3)));
	WorldObjectList.Add(std::make_shared<FSphere>(FVector(-1, 0, -1), 0.5, MaterialDielectric));
	WorldObjectList.Add(std::make_shared<FSphere>(FVector(-1, 0, -1), -0.45, MaterialDielectric));
	
	for (int j = image_height - 1; j >= 0; --j) 
	{
		std::cerr<<"\rScanlines Remain [" <<j<<"]"<<std::flush;
		for (int i = 0; i < image_width; ++i) 
		{
			FVector Color;
			for (int s=0; s<SamplePerPixel; ++s)
			{
				double U = (double(i) + FMath::Random()) / image_width;
				double V = (double(j) + FMath::Random()) / image_height;
				FRay Ray = Camera.GetRay(U, V);
				Color += RayColor(Ray, WorldObjectList, MaxDepth);
			}

			Color.WriteColor(SamplePerPixel);
		}
	}

	std::cerr<<"\nDone.\n";
}
