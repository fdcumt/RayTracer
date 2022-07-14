#include "BaseHit.h"

const double infinity = std::numeric_limits<double>::infinity();

void FHitRecord::SetFaceNormal(const FRay& InRay, const FVector& OutwardNormal)
{
	bFrontFace = FVector::DotProduct(InRay.GetDirection(), OutwardNormal)<0;
	Normal = bFrontFace ? OutwardNormal:-OutwardNormal;
}
