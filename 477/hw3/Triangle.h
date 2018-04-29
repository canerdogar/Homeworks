#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include <string>
#include "Vector3.h"
#include "Image.h"

using namespace std;

class Triangle
{
public:
    Vector3 normal;
    Vector3 c1,c2,c3;
    Vector3 center;
    Color color1,color2,color3;
    float z[3]={0,0,0};
    bool culled=false;
    
    Triangle(int _c1,int _c2,int _c3){
        setCorners(_c1,_c2,_c3);
        setColors(_c1,_c2,_c3);
    }
    
    void setNormal();

    void setCorners(int _c1,int _c2,int _c3);
    
    void setColors(int _c1,int _c2,int _c3);
    
    friend std::ostream& operator<<(std::ostream& stream,Triangle& triangle)
    {

        stream<<"Triangle "<<endl;
        stream<<"c1:"<<triangle.c1[0]<<" "<<triangle.c1[1]<<" "<<triangle.c1[2]<<endl;
        stream<<"c2:"<<triangle.c2[0]<<" "<<triangle.c2[1]<<" "<<triangle.c2[2]<<endl;
        stream<<"c3:"<<triangle.c3[0]<<" "<<triangle.c3[1]<<" "<<triangle.c3[2]<<endl;
        stream<<"center:"<<triangle.center[0]<<" "<<triangle.center[1]<<" "<<triangle.center[2]<<endl;
        return stream;

    }

    float f(float x,float y,float x0,float y0,float x1,float y1)const;

    void draw(Image& image,const int& type)const;

    void lineDraw(Image& image,const Vector3& v1,const Vector3& v2,const Color& c1,const Color& c2)const;

    void Translate(const Vector3& vector);

    void Scale(const Vector3& vector);

    void Rotate(const float& angle,const Vector3& vector);
};

#endif //RAYTRACER_TRIANGLE_H

