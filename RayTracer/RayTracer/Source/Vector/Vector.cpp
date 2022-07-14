#include "Vector.h"
#include "Math/MathUtility.h"


const FVector FVector::ZeroVector(0.f, 0.f, 0.f);

const FVector FVector::OneVector(1.f, 1.f, 1.f);

const FVector FVector::UpVector(0.f, 0.f, 1.f);

const FVector FVector::DownVector(0.f, 0.f, -1.f);

const FVector FVector::ForwardVector(1.f, 0.f, 0.f);

const FVector FVector::BackwardVector(-1.f, 0.f, 0.f);

const FVector FVector::RightVector(0.f, 1.f, 0.f);

const FVector FVector::LeftVector(0.f, -1.f, 0.f);

double FVector::Size() const
{
	return FMath::Sqrt(SizeSquare());
}

bool FVector::IsNormalized() const
{
	return FMath::Abs(SizeSquare()-1) < THRESH_VECTOR_NORMALIZED;
}

void FVector::WriteColor(int SamplePerPixel) const
{
	double R = FMath::Pow(X / SamplePerPixel, 0.45);
	double G = FMath::Pow(Y / SamplePerPixel, 0.45);
	double B = FMath::Pow(Z / SamplePerPixel, 0.45);

	std::cout << static_cast<int>(255.99 * FMath::Clamp(R, 0.f, 0.99999)) << ' '
		<< static_cast<int>(255.99 * FMath::Clamp(G, 0.f, 0.99999)) << ' '
		<< static_cast<int>(255.99 * FMath::Clamp(B, 0.f, 0.99999)) << '\n';
}
