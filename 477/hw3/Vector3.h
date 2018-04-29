#ifndef MATH_VECTOR3_H
#define MATH_VECTOR3_H

#include <iostream>
#include <cmath>
#include "Color.h"

class Vector3
{
public:
    float _data[3];

    Vector3(){
        _data[0]=_data[1]=_data[2]=0;
    }
    
    Vector3(float x,float y,float z){
        _data[0]=x;_data[1]=y;_data[2]=z;
    }
    
    Vector3(const Vector3& vector){
        _data[0]=vector._data[0];_data[1]=vector._data[1];_data[2]=vector._data[2];
    }
    
    Vector3 operator*(float number)const{
        return Vector3(_data[0]*number,_data[1]*number,_data[2]*number);
    }
    
    friend std::istream &operator>>(std::istream &stream, Vector3 &vertex)
    {
        return stream >> vertex._data[0] >> vertex._data[1] >> vertex._data[2];
    }
    
    friend std::ostream &operator<<(std::ostream &stream, const Vector3 &vertex)
    {
        return stream << vertex._data[0] <<" " <<vertex._data[1]<<" " << vertex._data[2] << std::endl;
    }
    
    Vector3 operator*(const Vector3& vector3)const{
        return Vector3(vector3._data[0]*_data[0],vector3._data[1]*_data[1],vector3._data[ 2]*_data[2]);
    }
    
    Vector3 operator*(float number){
        return Vector3(_data[0]*number,_data[1]*number,_data[2]*number);
    }

    Vector3 operator-(const Vector3& vector3)const{
        return Vector3(_data[0]-vector3._data[0],_data[1]-vector3._data[1],_data[2]-vector3._data[ 2]);
    }
    
    Vector3 operator+(const Vector3& vector3)const{
        return Vector3(_data[0]+vector3._data[0],_data[1]+vector3._data[1],_data[2]+vector3._data[ 2]);
    }
    
    Vector3 operator/(float number)const{
        return Vector3(_data[0] / number,_data[1] / number,_data[2] / number);
    }
    
    Vector3& operator=(const Vector3& vector3){
        _data[0]=vector3._data[0];_data[1]=vector3._data[1];_data[2]=vector3._data[2];
        return *this;
    }
    
    float dot(const Vector3& vector3)const{
        return _data[0]*vector3._data[0] + _data[1]*vector3._data[1] + _data[2]*vector3._data[2];
    }
    
    float length()const{
        return sqrt(dot(*this));
    }
    
    float& operator[](std::size_t idx){
        return _data[idx];
    }
    const float& operator[](std::size_t idx) const {
        return _data[idx];
    }
    
    Vector3& normalize(){
        float length=this->length();
        _data[0]=_data[0]/length;
        _data[1]=_data[1]/length;
        _data[2]=_data[2]/length;
        return *this;
    }

    Vector3 cnormalize(){
        float length=this->length();
        return Vector3(_data[0]/length , _data[1]/length , _data[2]/length);
    }
    
    bool operator==(const Vector3& vector3)const{
        return ((*this)-vector3).length() < 0.1;
    }
    
    Color operator*(const Color& color)const{
        return Color(color.R()*_data[0],color.G()*_data[1],color.B()*_data[2]);
    }
    
    Vector3 cross(const Vector3& vector3)const{
        return Vector3(_data[1]*vector3._data[2] - _data[2]*vector3._data[1],_data[2]*vector3._data[0] - _data[0]*vector3._data[2],_data[0]*vector3._data[1] - _data[1]*vector3._data[0]);
    }
    
    void Print()const{
        std::cout<<"x:" << _data[0] <<" y:" << _data[1] << " z:" << _data[2] <<std::endl;
    }
    
};

#endif //MATH_VECTOR3_H
