#ifndef TEXTURE_H
#define TEXTURE_H

#include "aoa_jpeg.h"
#include <string>
#include "Vector3.h"

using namespace std;

class Texture{
	public:
	UCOLOR** texture_image;
	int width,height;
	Texture(string filename);
	Vector3 value(float* uv,int sid)const;
};

#endif //TEXTURE_H
