#include "RTW_StbImage.h"



#ifdef _MSC_VER
// Microsoft visual c++ compiler
//#pragma warning (push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#ifdef _MSC_VER
	// Microsoft visual c++ compiler
	//#pragma warning (pop)
#endif

unsigned char* FRTWStbImage::stbi_load(char const* filename, int* x, int* y, int* channels_in_file, int desired_channels)
{
	return ::stbi_load(filename, x, y, channels_in_file, desired_channels);
}
