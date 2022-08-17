#include "Color.h"
#include "Math/MathUtility.h"
#include <stdio.h>

const FColor FColor::White(1, 1, 1);
const FColor FColor::Black(0, 0, 0);
const FColor FColor::Red(1, 0, 0);
const FColor FColor::Green(0, 1, 0);
const FColor FColor::Blue(0, 0, 1);
const FColor FColor::Yellow(1, 1, 0);
const FColor FColor::Cyan(0, 1, 1);
const FColor FColor::Magenta(1, 0, 1);
const FColor FColor::Orange(243.0/255.0, 156.0 / 255.0, 18.0 / 255.0);
const FColor FColor::Purple(169.0 / 255.0, 7.0 / 255.0, 228.0 / 255.0);
const FColor FColor::Turquoise(26.0 / 255.0, 188.0 / 255.0, 156.0 / 255.0);
const FColor FColor::Silver(189.0 / 255.0, 195.0 / 255.0, 199.0 / 255.0);
const FColor FColor::Emerald(46.0 / 255.0, 204.0 / 255.0, 113.0 / 255.0);

void FColor::WriteColor(int SamplePerPixel) const
{
	double CurrentR = FMath::Pow(R / SamplePerPixel, 0.45);
	double CurrentG = FMath::Pow(G / SamplePerPixel, 0.45);
	double CurrentB = FMath::Pow(B / SamplePerPixel, 0.45);

	std::cout << static_cast<int>(255.99 * FMath::Clamp(CurrentR, 0.f, 0.99999)) << ' '
		<< static_cast<int>(255.99 * FMath::Clamp(CurrentG, 0.f, 0.99999)) << ' '
		<< static_cast<int>(255.99 * FMath::Clamp(CurrentB, 0.f, 0.99999)) << '\n';
}

FColor FColor::Random()
{
	return FColor(FMath::Random(), FMath::Random(), FMath::Random());
}

FColor FColor::Random(double InMin, double InMax)
{
	return FColor(FMath::Random(InMin, InMax), FMath::Random(InMin, InMax), FMath::Random(InMin, InMax));
}

const char* FColor::ToString() const
{
	char data[1024] = {0};
	sprintf_s(data, "R:%lf, G:%lf, B:%lf", R, G, B);
	return data;
}
