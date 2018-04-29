#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include <vector>
#include "Vector3.h"
#include <GL/glew.h>
#include <GL/gl.h>   // The GL Header File
#include <GL/freeglut.h> // The GL Utility Toolkit (Glut) Header


class Mesh {
public:
    int materialId;
    int meshType;
    GLuint* indices=NULL;
    std::vector<int> transformIds;
    std::vector<char> transformTypes;
    int howmany=0;
    
    friend std::istream& operator>>(std::istream &stream,Mesh& mesh);

    void transformations();
};


#endif //RAYTRACER_MESH_H
