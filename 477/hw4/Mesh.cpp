#include "Mesh.h"
#include "Scene.h"
#include "Vector3.h"

std::istream& operator>>(std::istream &stream,Mesh& mesh){
    char dummy;
    int dummyi;

    for (int i = 0; i < 5; ++i)
    {
        stream>>dummy;
    }
    stream >>dummyi;
    stream >> mesh.meshType;
    //cout<< mesh.meshType<<endl;
    stream >> mesh.materialId;
    //cout<<mesh.materialId<<endl;
    
    int counter=0;
    stream >> counter;
    //cout<<counter<<endl;
    int transformId;
    for (; counter>0; counter--) {
        stream >> dummy;
        stream >> transformId;
        mesh.transformTypes.push_back(dummy);
        mesh.transformIds.push_back(transformId);
    }
    

    stream>> counter;
    //cout<<counter<<endl;
    mesh.howmany=counter*3;
    mesh.indices=new GLuint[counter*3];
    for (int i=0; i<counter*3; i++) {
        int j;
        stream>>j;
        mesh.indices[i]=j-1;
        if (i%3==2 && i!=0)
        {
            Vector3 c1(CurrentScene->vertexPos[3*(int)mesh.indices[i]] , CurrentScene->vertexPos[3*(int)mesh.indices[i] +1], CurrentScene->vertexPos[3*(int)mesh.indices[i]+2]);
            //c1.Print();
            Vector3 c2(CurrentScene->vertexPos[3*(int)mesh.indices[i-1]] , CurrentScene->vertexPos[3*(int)mesh.indices[i-1] +1], CurrentScene->vertexPos[3*(int)mesh.indices[i-1]+2]);
            //c2.Print();
            Vector3 c3(CurrentScene->vertexPos[3*(int)mesh.indices[i-2]] , CurrentScene->vertexPos[3*(int)mesh.indices[i-2] +1], CurrentScene->vertexPos[3*(int)mesh.indices[i-2]+2]);
            //c3.Print();
            Vector3 normal=(c1-c2).cross(c3-c2).normalize();
            CurrentScene->normals[ (int)mesh.indices[i] ] = CurrentScene->normals[ (int)mesh.indices[i] ] + normal;
            CurrentScene->normals[ (int)mesh.indices[i-1] ] = CurrentScene->normals[ (int)mesh.indices[i-1] ] + normal;
            CurrentScene->normals[ (int)mesh.indices[i-2] ] = CurrentScene->normals[ (int)mesh.indices[i-2] ] + normal;
        }
    }
    
    return stream;
}

void Mesh::transformations(){

    glLoadIdentity();
    gluLookAt(CurrentScene->camera._position[0],CurrentScene->camera._position[1],CurrentScene->camera._position[2],
            CurrentScene->camera._position[0]+CurrentScene->camera._gaze[0],CurrentScene->camera._position[1]+CurrentScene->camera._gaze[1],CurrentScene->camera._position[2]+CurrentScene->camera._gaze[2],
            CurrentScene->camera._space.Up[0],CurrentScene->camera._space.Up[1],CurrentScene->camera._space.Up[2]
        );

    for (int i = 0; i < CurrentScene->lights.size(); ++i)
    {
        glEnable(GL_LIGHT0+i);
        GLfloat lightColor []={CurrentScene->lights[i]._intensity[0],
                                CurrentScene->lights[i]._intensity[1],
                                CurrentScene->lights[i]._intensity[2],
                                1.0};
        GLfloat ambientColor []={CurrentScene->ambient[0],
                                CurrentScene->ambient[1],
                                CurrentScene->ambient[2],
                                1.0};
        GLfloat lightPos []={CurrentScene->lights[i]._position[0],
                            CurrentScene->lights[i]._position[1],
                            CurrentScene->lights[i]._position[2],
                            1.0};
        glLightfv(GL_LIGHT0+i,GL_POSITION,lightPos);
        glLightfv(GL_LIGHT0+i,GL_AMBIENT,ambientColor);
        glLightfv(GL_LIGHT0+i,GL_DIFFUSE,lightColor);
        glLightfv(GL_LIGHT0+i,GL_SPECULAR,lightColor);

    }

    for (int i=transformTypes.size()-1;i>=0 ; i--) {
        
        if(transformTypes[i]=='s'){
            Vector3 scale=CurrentScene->scales[transformIds[i]-1];
            glScalef(scale[0],scale[1],scale[2]);
        }else if(transformTypes[i]=='t'){
            Vector3 translate=CurrentScene->translates[transformIds[i]-1];
            glTranslatef(translate[0],translate[1],translate[2]);
        }else{
            float angle=CurrentScene->rotateAngles[transformIds[i]-1];
            Vector3 _angle=CurrentScene->rotates[transformIds[i]-1];
            glRotatef(angle, _angle[0], _angle[1], _angle[2]);
        }
            
      
    }


}
