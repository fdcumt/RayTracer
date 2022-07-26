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
#include "Shape/MovingSphere.h"

// 中文

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

FHitTableList RandomScene()
{
	FHitTableList World;

	World.Add(std::make_shared<FSphere>(FVector(0, -1000, 0), 1000, std::make_shared<FLambertian>(FVector(0.5, 0.5, 0.5))));

	for (int a = -11; a<11; ++a)
	{
		for (int b = -11; b<11; ++b)
		{
			double ChooseMat = FMath::Random();
			FVector Center(a+0.9*FMath::Random(), 0.2, b+0.9*FMath::Random());
			if ((Center-FVector(4, 0.2, 0)).Size()>0.9)
			{
				if (ChooseMat<0.8)
				{ // diffuse
					FVector albedo = FVector::Random()*FVector::Random();
					FVector Center2 = Center+FVector(0, FMath::Random(0, 0.5), 0);
					World.Add(std::make_shared<FMovingSphere>(Center, Center2, 0, 1, 0.2, std::make_shared<FLambertian>(albedo)));
				}
				else if (ChooseMat < 0.95)
				{
					FVector albedo = FVector::Random(0.5, 1);
					double Fuzz = FMath::Random(0, 0.5);
					World.Add(std::make_shared<FSphere>(Center, 0.2, std::make_shared<FMetal>(albedo, Fuzz)));
				}
				else
				{
					World.Add(std::make_shared<FSphere>(Center, 0.2, std::make_shared<FDielectric>(1.5)));
				}
			}
		}
	}

	World.Add(std::make_shared<FSphere>(FVector(0,1,0), 1.0, std::make_shared<FDielectric>(1.5)));
	World.Add(std::make_shared<FSphere>(FVector(-4,1,0), 1.0, std::make_shared<FLambertian>(FVector(0.4, 0.2, 0.1))));
	World.Add(std::make_shared<FSphere>(FVector(4,1,0), 1.0, std::make_shared<FMetal>(FVector(0.7, 0.6, 0.5), 0.0)));

	return World;
}

int main() 
{
	const double AspectRatio = 16/9;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width*AspectRatio);
	int SamplePerPixel = 4;
	int MaxDepth = 50;

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	FVector LookFromPoint(13, 2, 3);
	//FVector LookFromPoint(0, 0, 0);
	FVector LookAtPoint(0, 0, 0);
	FVector UpDir(0, 1, 0);

	double Aperture = 0.1;
	double FoucsDis = 10;
	FCamera Camera(LookFromPoint, LookAtPoint, UpDir, 
					20, image_width/image_height, 
					Aperture, FoucsDis,
					0, 1);

	// auto MaterialSmallBall = std::make_shared<FLambertian>(FVector(0.7, 0.3, 0.3));
	// auto MaterialBigBall = std::make_shared<FLambertian>(FVector(0.8, 0.8, 0));
	// auto MaterialLeft = std::make_shared<FMetal>(FVector(0.8, 0.6, 0.2), 0.3);
	// auto MaterialDielectric = std::make_shared<FDielectric>(1.5);

	double R = FMath::Cos(FMath::M_PI/4);

	FHitTableList WorldObjectList = RandomScene();
	//WorldObjectList.Add(std::make_shared<FSphere>(FVector(-R, 0.f, -1.f), R, std::make_shared<FLambertian>(FVector(0, 0, 1))));
	//WorldObjectList.Add(std::make_shared<FSphere>(FVector(R, 0.f, -1.f), R, std::make_shared<FLambertian>(FVector(1, 0, 0))));


	//WorldObjectList.Add(std::make_shared<FSphere>(FVector(0.f, 0.f, -1.f), 0.5, std::make_shared<FLambertian>(FVector(0.1, 0.2, 0.5))));
	//WorldObjectList.Add(std::make_shared<FSphere>(FVector(0.f, -100.5f, -1.f), 100.f, std::make_shared<FLambertian>(FVector(0.8, 0.8, 0))));
	//
	//WorldObjectList.Add(std::make_shared<FSphere>(FVector(1, 0, -1), 0.5, std::make_shared<FMetal>(FVector(0.8, 0.6, 0.2), 0.3)));
	//WorldObjectList.Add(std::make_shared<FSphere>(FVector(-1, 0, -1), 0.5, MaterialDielectric));
	//WorldObjectList.Add(std::make_shared<FSphere>(FVector(-1, 0, -1), -0.45, MaterialDielectric));
	
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
