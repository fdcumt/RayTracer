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
#include "BVH/BVH.h"
#include "Texture/CheckerTexture.h"
#include "Texture/NoiseTexture.h"
#include "Texture/ImageTexture.h"
#include "Material/DiffuseLight.h"
#include "Shape/Rectangle.h"
#include "Common/CommonDefine.h"

// 中文

FColor RayColor(const FRay &Ray, const FColor &BackgroundColor, const FHitTableList &InHitTableList, int InDepth)
{
	if (InDepth<=0)
	{
		// return FVector::ZeroVector;
		return FColor::Black;
	}

	FHitRecord ClosetHitRecord;
	if (InHitTableList.Hit(Ray, 0.001,	infinity, ClosetHitRecord))
	{
		FRay Scattered;
		FColor Attenuation;

		FColor EmmitColor = ClosetHitRecord.Mat->Emmit(ClosetHitRecord.U, ClosetHitRecord.V, ClosetHitRecord.HitPoint);
		//Checkf(EmmitColor.IsGrayScale(), "EmmitColor[%s] is not grayscale", EmmitColor.ToString());
		if (ClosetHitRecord.Mat->Scatter(Ray, ClosetHitRecord, Attenuation, Scattered))
		{
			FColor CurRayColor = RayColor(Scattered, BackgroundColor, InHitTableList, InDepth - 1);
			//Checkf(CurRayColor.IsGrayScale(), "CurRayColor[%s] is not grayscale", CurRayColor.ToString());

			return EmmitColor + Attenuation*CurRayColor;
		}
		else
		{
			return EmmitColor;
		}
	}
	else
	{
		return BackgroundColor;
	}
}

FHitTableList RandomScene()
{
	FHitTableList World;

	std::shared_ptr<ITexture> CheckerTexture = std::make_shared<FCheckerTexture>(FColor(0.2, 0.3, 0.1), FColor(0.9, 0.9, 0.9));
	World.Add(std::make_shared<FSphere>(FVector(0, -1000, 0), 1000, std::make_shared<FLambertian>(CheckerTexture)));

	int ItemNum = 0;
	int BeginIndex = -11;

	for (int a = BeginIndex; a<11; ++a)
	{
		for (int b = BeginIndex; b<11; ++b)
		{
			double ChooseMat = FMath::Random();
			FVector Center(a+0.9*FMath::Random(), 0.2, b+0.9*FMath::Random());
			if ((Center-FVector(4, 0.2, 0)).Size()>0.9)
			{
				if (ChooseMat<0.5)
				{ // diffuse
					FColor albedo = FColor::Random()* FColor::Random();
					FVector Center2 = Center+FVector(0, FMath::Random(0, 0.5), 0);
					World.Add(std::make_shared<FMovingSphere>(Center, Center2, 0, 1, 0.2, std::make_shared<FLambertian>(albedo)));
					++ItemNum;
				}
				else if (ChooseMat < 0.95)
				{
					FColor albedo = FColor::Random(0.5, 1);
					double Fuzz = FMath::Random(0, 0.5);
					World.Add(std::make_shared<FSphere>(Center, 0.2, std::make_shared<FMetal>(albedo, Fuzz)));
					++ItemNum;
				}
				else
				{
					World.Add(std::make_shared<FSphere>(Center, 0.2, std::make_shared<FDielectric>(1.5)));
					++ItemNum;
				}
			}
		}
	}

	World.Add(std::make_shared<FSphere>(FVector(0,1,0), 1.0, std::make_shared<FDielectric>(1.5)));
	World.Add(std::make_shared<FSphere>(FVector(-4,1,0), 1.0, std::make_shared<FLambertian>(FColor(0.4, 0.2, 0.1))));
	World.Add(std::make_shared<FSphere>(FVector(4,1,0), 1.0, std::make_shared<FMetal>(FColor(0.7, 0.6, 0.5), 0.0)));

	FHitTableList RetWorld;
	RetWorld.Add(std::make_shared<FBVH>(World, 0, 1));
	//return World;
	return RetWorld;
}


FHitTableList TwoSphere()
{
	FHitTableList Objects;

	auto checker = std::make_shared<FCheckerTexture>(FColor(0.2, 0.3, 0.1), FColor(0.9, 0.9, 0.9));
	Objects.Add(std::make_shared<FSphere>(FVector(0, -10, 0), 10, std::make_shared<FLambertian>(checker)));
	Objects.Add(std::make_shared<FSphere>(FVector(0, 10, 0), 10, std::make_shared<FLambertian>(checker)));

	return Objects;
}

FHitTableList TwoPerlinNoiseSphere()
{
	FHitTableList Objects;

	auto PerlinNoiseTexture = std::make_shared<FNoiseTexture>(4);
	//auto PerlinNoiseTexture = std::make_shared<FCheckerTexture>(FColor(0.2, 0.3, 0.1), FColor(0.9, 0.9, 0.9));

	Objects.Add(std::make_shared<FSphere>(FVector(0, -1000, 0), 1000, std::make_shared<FLambertian>(PerlinNoiseTexture)));
	Objects.Add(std::make_shared<FSphere>(FVector(0, 2, 0), 2, std::make_shared<FLambertian>(PerlinNoiseTexture)));

	return Objects;
}

FHitTableList SimpleLight()
{
	FHitTableList Objects;

	auto PerlinNoiseTexture = std::make_shared<FNoiseTexture>(4);
	Objects.Add(std::make_shared<FSphere>(FVector(0, -1000, 0), 1000, std::make_shared<FLambertian>(PerlinNoiseTexture)));
	Objects.Add(std::make_shared<FSphere>(FVector(0, 2, 0), 2, std::make_shared<FLambertian>(PerlinNoiseTexture)));

	auto DiffLight = std::make_shared<FDiffuseLight>(FColor(4.0,4.0,4.0));
	Objects.Add(std::make_shared<FRectangle_ZPlane>(3,5,1,3,-2, DiffLight));

	return Objects;
}

FHitTableList CornellBox()
{
	FHitTableList Objects;

	auto Red = std::make_shared<FLambertian>(FColor(.65, .05, .05));
	auto White = std::make_shared<FLambertian>(FColor(.73, .73, .73));
	auto Green = std::make_shared<FLambertian>(FColor(0.12, 0.45, 0.15));
	auto Light = std::make_shared<FDiffuseLight>(FColor(15, 15, 15));

	Objects.Add(std::make_shared<FRectangle_XPlane>(0, 555, 0, 555, 555, Green));
	Objects.Add(std::make_shared<FRectangle_XPlane>(0, 555, 0, 555, 0, Red));

	Objects.Add(std::make_shared<FRectangle_YPlane>(213, 343, 227, 332, 554, Light));

	Objects.Add(std::make_shared<FRectangle_YPlane>(0, 555, 0, 555, 0, White));
	Objects.Add(std::make_shared<FRectangle_YPlane>(0, 555, 0, 555, 555, White));

	Objects.Add(std::make_shared<FRectangle_ZPlane>(0, 555, 0, 555, 555, White));

	return Objects;
}


FHitTableList Earth()
{
	FHitTableList Objects;
#if _DEBUG
	const char* ImagePath = "./Images/earthmap.jpg"; // for debug
#else
	const char* ImagePath = "../../RayTracer/Images/earthmap.jpg"; // for cmd
#endif
	auto EarthTexture = std::make_shared<FImageTexture>(ImagePath);
	//auto PerlinNoiseTexture = std::make_shared<FCheckerTexture>(FColor(0.2, 0.3, 0.1), FColor(0.9, 0.9, 0.9));

	Objects.Add(std::make_shared<FSphere>(FVector(0, 0, 0), 2, std::make_shared<FLambertian>(EarthTexture)));

	return Objects;
}

enum class EObjectListType
{
	eWorld,
	eTwoSphere,
	eTwoPerlinNoiseSphere,
	eEarth,
	eSimpleLight,
	eCornellBox,
};

int main() 
{
	double AspectRatio = double(16)/9;
	int image_width = 400;
	int SamplePerPixel = 100;
	int MaxDepth = 50;


	FVector LookFromPoint(13, 2, 3);
	//FVector LookFromPoint(0, 0, 0);
	FVector LookAtPoint(0, 0, 0);
	FVector UpDir(0, 1, 0);
	double Fov = 40;

	double Aperture = 0;
	double FoucsDis = 10;

	FColor BackgroundColor = FColor::Black;
	double R = FMath::Cos(FMath::M_PI / 4);

	FHitTableList WorldObjectList;
	EObjectListType eType = EObjectListType::eCornellBox;
	switch (eType)
	{
	case EObjectListType::eWorld:
	{ // render world
		WorldObjectList = RandomScene();
		LookFromPoint = FVector(13, 2, 3);
		LookAtPoint = FVector(0, 0, 0);
		Fov = 20;
		Aperture = 0.1;
		BackgroundColor = FColor(0.70, 0.80, 1.0);
		break;
	}

	case EObjectListType::eTwoSphere:
	{// render two sphere
		WorldObjectList = TwoSphere();
		LookFromPoint = FVector(13, 2, 3);
		LookAtPoint = FVector(0, 0, 0);
		Fov = 20;
		BackgroundColor = FColor(0.70, 0.80, 1.0);

		break;
	}

	case EObjectListType::eTwoPerlinNoiseSphere:
	{
		WorldObjectList = TwoPerlinNoiseSphere();
		LookFromPoint = FVector(13, 2, 3);
		LookAtPoint = FVector(0, 0, 0);
		Fov = 20;
		BackgroundColor = FColor(0.70, 0.80, 1.0);

		break;
	}

	case EObjectListType::eEarth:
	{
		WorldObjectList = Earth();
		LookFromPoint = FVector(13, 2, 3);
		LookAtPoint = FVector(0, 0, 0);
		Fov = 20;
		BackgroundColor = FColor(0.70, 0.80, 1.0);

		break;
	}
	case EObjectListType::eSimpleLight:
	{
		WorldObjectList = SimpleLight();
		SamplePerPixel = 400;
		BackgroundColor = FColor(0, 0, 0);

		LookFromPoint = FVector(26, 3, 6);
		LookAtPoint = FVector(0, 2, 0);
		Fov = 20;

		break;
	}

	case EObjectListType::eCornellBox:
	{
		WorldObjectList = CornellBox();
		AspectRatio = 1.0;
		image_width = 600;
		SamplePerPixel = 200;
		BackgroundColor = FColor(0, 0, 0);

		LookFromPoint = FVector(278, 278, -800);
		LookAtPoint = FVector(278, 278, 0);
		Fov = 60;

		break;
	}
	}

	const int image_height = static_cast<int>(image_width / AspectRatio);
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";


	FCamera Camera(LookFromPoint, LookAtPoint, UpDir, 
					Fov, AspectRatio,
					Aperture, FoucsDis,
					0, 1);

	// auto MaterialSmallBall = std::make_shared<FLambertian>(FVector(0.7, 0.3, 0.3));
	// auto MaterialBigBall = std::make_shared<FLambertian>(FVector(0.8, 0.8, 0));
	// auto MaterialLeft = std::make_shared<FMetal>(FVector(0.8, 0.6, 0.2), 0.3);
	// auto MaterialDielectric = std::make_shared<FDielectric>(1.5);

	
	
	for (int j = image_height - 1; j >= 0; --j) 
	{
		std::cerr<<"\rScanlines Remain [" <<j<<"]"<<std::flush;
		for (int i = 0; i < image_width; ++i) 
		{
			FColor Color;
			for (int s=0; s<SamplePerPixel; ++s)
			{
				double U = (double(i) + FMath::Random()) / image_width;
				double V = (double(j) + FMath::Random()) / image_height;
				FRay Ray = Camera.GetRay(U, V);
				Color += RayColor(Ray, BackgroundColor, WorldObjectList, MaxDepth);
			}

			Color.WriteColor(SamplePerPixel);
		}
	}

	std::cerr<<"\nDone.\n";
}
