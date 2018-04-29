#include <iostream>
#include "Scene.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <sstream>

char gRendererInfo[512] = { 0 };
char gWindowTitle[512] = { 0 };

int gWidth, gHeight;

void init() 
{
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

}

void drawCubeElementsVBO(int a)
{

    static int vertexPosDataSizeInBytes;



        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        GLuint vertexAttribBuffer, indexBuffer;
        ///////////////////////////////
        glGenBuffers(1, &vertexAttribBuffer);
        glGenBuffers(1, &indexBuffer);

        assert(vertexAttribBuffer > 0 && indexBuffer > 0);

        glBindBuffer(GL_ARRAY_BUFFER, vertexAttribBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        vertexPosDataSizeInBytes = CurrentScene->howmany * sizeof(GLfloat);
        ///////////////////7
        GLfloat* vertexCol=CurrentScene->normalValues;
        int vertexColDataSizeInBytes = CurrentScene->howmany * sizeof(GLfloat);
        /*cout<<endl;
        cout<<vertexPosDataSizeInBytes<<endl;
        cout<<vertexColDataSizeInBytes<<endl;
        ///////////////////


        cout<<"----------------"<<endl;
        for (int i = 0; i < CurrentScene->meshes[1].howmany; ++i)
        {
            if (i%3==0)
            {
                cout<<endl;
            }
            cout<<CurrentScene->meshes[1].indices[i]<<" ";
        }
        cout<<"--------------"<<endl;*/


        int indexDataSizeInBytes = CurrentScene->meshes[a].howmany *  sizeof(GLuint);
        //cout<< CurrentScene->meshes[1].howmany <<endl;
        //cout<<indexDataSizeInBytes<<endl;
        glBufferData(GL_ARRAY_BUFFER, vertexPosDataSizeInBytes + vertexColDataSizeInBytes, 0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexPosDataSizeInBytes, CurrentScene->vertexPos);
        glBufferSubData(GL_ARRAY_BUFFER, vertexPosDataSizeInBytes, vertexColDataSizeInBytes, vertexCol);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSizeInBytes, CurrentScene->meshes[a].indices, GL_STATIC_DRAW);


    glVertexPointer(3, GL_FLOAT, 0, 0);
    glNormalPointer( GL_FLOAT, 0, (void*)vertexPosDataSizeInBytes);
    //cout<<CurrentScene->meshes[1].howmany<<endl;
    Material m=CurrentScene->materials[CurrentScene->meshes[a].materialId - 1 ];
    GLfloat ambColor[4] = {m._ambient[0], m._ambient[1], m._ambient[2], 1.0};
    GLfloat diffColor[4] = {m._diffuse[0], m._diffuse[1], m._diffuse[2], 1.0};
    GLfloat specColor[4] = {m._specular[0], m._specular[1],m._specular[2] , 1.0};
    GLfloat specExp[1] = {m.phong};
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambColor);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffColor);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specColor);
    glMaterialfv(GL_FRONT,GL_SHININESS,specExp);
    glDrawElements(GL_TRIANGLES, CurrentScene->meshes[a].howmany, GL_UNSIGNED_INT, 0);
    //////////////////////////////////////////
}

typedef void(*drawFunc)(int a);

void display()
{
   
    glClearColor(CurrentScene->background[0], CurrentScene->background[1], CurrentScene->background[2], 1);//background
    glClearDepth(1.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    
    drawFunc drawCube = drawCubeElementsVBO;


   for (int i = 0; i < CurrentScene->meshes.size(); ++i)
   {
        if (CurrentScene->meshes[i].meshType==2)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else{
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
       CurrentScene->meshes[i].transformations();
        drawCube(i);
   }
    
    

    



    glutSwapBuffers();


    
}

void reshape(int w, int h)   // Create The Reshape Function (the viewport)
{
    w = w < 1 ? 1 : w;
    h = h < 1 ? 1 : h;

    gWidth = w;
    gHeight = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-10, 10, -10, 10, -10, 10);
    //gluPerspective(45, 1, 1, 500);
    glFrustum(CurrentScene->camera._imagePlane.Left,
            CurrentScene->camera._imagePlane.Right,
            CurrentScene->camera._imagePlane.Bottom,
            CurrentScene->camera._imagePlane.Top,
            CurrentScene->camera._imagePlane.near,
            CurrentScene->camera._imagePlane.far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void rotate(Vector3& eleman,const float& angle,const Vector3& vector){

    Vector3 rs=vector;
    rs.normalize();

    float angle4=(angle * 3.14159265358979323846) / 180;

    
    float a1,a2,a3,b1,b2,b3,d1,d2,d3;
    float _cos=cos(angle4),_sin=sin(angle4);
    a1=_cos + rs[0] * rs[0] * (1 - _cos);
    a2=rs[0]* rs[1] * (1- _cos) - rs[2] * _sin ;
    a3=rs[0] * rs[2] * (1- _cos) + rs[1] * _sin ;

    b1=rs[1]*rs[0]*(1-_cos) + rs[2]*_sin;
    b2=_cos + rs[1]*rs[1] * (1-_cos);
    b3=rs[1]*rs[2]*(1-_cos) - rs[0] * _sin;

    d1=rs[2]*rs[0]*(1-_cos) - rs[1] * _sin;
    d2=rs[2]*rs[1]*(1-_cos) + rs[0] * _sin;
    d3=_cos + rs[2] * rs[2] * (1- _cos);





    eleman=Vector3(eleman[0]*a1 + eleman[1]*a2 + eleman[2]*a3,
               eleman[0]*b1 + eleman[1]*b2 + eleman[2]*b3, 
               eleman[0]*d1 + eleman[1]*d2 + eleman[2]*d3);



}

void keyboard(unsigned char key, int x, int y)
{
    if(key=='W' || key=='w'){
        CurrentScene->camera._position=CurrentScene->camera._position + (CurrentScene->camera._gaze * 0.05);
    }else if(key=='S' || key=='s'){
        CurrentScene->camera._position=CurrentScene->camera._position + (CurrentScene->camera._gaze * -0.05);
    }else if(key=='A' || key=='a'){

        rotate(CurrentScene->camera._gaze,0.5,Vector3(0,1,0));
        rotate(CurrentScene->camera._space.Up,0.5,Vector3(0,1,0));
        rotate(CurrentScene->camera._space.Forward,0.5,Vector3(0,1,0));

    }
    else if(key=='D' || key=='d'){

        rotate(CurrentScene->camera._gaze,-0.5,Vector3(0,1,0));
        rotate(CurrentScene->camera._space.Up,-0.5,Vector3(0,1,0));
        rotate(CurrentScene->camera._space.Forward,-0.5,Vector3(0,1,0));

    }
    else if(key=='U' || key=='u'){

         rotate(CurrentScene->camera._gaze,0.5,CurrentScene->camera._space.Left);
        rotate(CurrentScene->camera._space.Up,0.5,CurrentScene->camera._space.Left);
        rotate(CurrentScene->camera._space.Forward,0.5,CurrentScene->camera._space.Left);

    }
    else if(key=='J' || key=='j'){

         rotate(CurrentScene->camera._gaze,-0.5,CurrentScene->camera._space.Left);
        rotate(CurrentScene->camera._space.Up,-0.5,CurrentScene->camera._space.Left);
        rotate(CurrentScene->camera._space.Forward,-0.5,CurrentScene->camera._space.Left);
    }else if(key==27){

        exit(0);
    }

    glutPostRedisplay();
}



int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Please provide scene and camera files" << std::endl;
        return 1;
    }

    ReadScene(argc, argv);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(CurrentScene->camera._imagePlane.Width, CurrentScene->camera._imagePlane.Height);
    glutCreateWindow("");
    glewInit();

    strcpy(gRendererInfo, (const char*) glGetString(GL_RENDERER));
    strcat(gRendererInfo, " - ");
    strcat(gRendererInfo, (const char*) glGetString(GL_VERSION));
    glutSetWindowTitle(gRendererInfo);

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}