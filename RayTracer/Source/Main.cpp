#include <iostream>
#include "Main.h"
#include "Vector/Vector.h"
#include "Ray/Ray.h"

FVector RayColor(const FRay &Ray)
{
	const FVector Direction = Ray.GetDirection();
	float Alpha = 0.5f*(Direction.Y + 1.0f);
	return FVector(1.0f, 1.0f, 1.0f)*(1.0f-Alpha)+FVector(0.5f, 0.7f, 1.0f)*Alpha;
}

int main() 
{
	const int image_width = 200;
	const int image_height = 100;

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	FVector TopLeftCorner(-2.0f, -1.0f, -1.0f);
	FVector Horizontal(4.0f, 0.0f, 0.0f);
	FVector Vertical(0.f, 2.0f, 0.f);
	FVector Original(0.f, 0.f, 0.f);

	for (int j = image_height - 1; j >= 0; --j) 
	{
		std::cerr<<"\rScanlines Remain [" <<j<<"]"<<std::flush;
		for (int i = 0; i < image_width; ++i) 
		{
			float U = float(i)/image_width;
			float V = float(j)/image_height;
			FRay Ray(Original, TopLeftCorner+U*Horizontal+V*Vertical);
			FVector Color = RayColor(Ray);
			Color.WriteColor();
		}
	}

	std::cerr<<"\nDone.\n";
}
