#include "Texture.h"
#include "aoa_jpeg.c"
#include <math.h>

Texture::Texture(string filename){
	int *x = new int;
	int *y = new int;
	read_jpeg_header(filename.c_str(), x, y);
	texture_image = new UCOLOR*[*y];
	for(int t = 0 ; t < *y ; t++)
		texture_image[t] = new UCOLOR[*x];

	read_jpeg(filename.c_str(), texture_image, x, y);
	width = *x; 
	height = *y;
    //cout<<"x-> "<<*x <<" y-> "<<*y<<endl;
	delete x;
	delete y;
}
Vector3 Texture::value(float* uv,int sid)const{
    
    int i=0,j=0;
    //cout<<"sid: "<<sid<<endl;
    if(sid==0){
        i = (int)round ( uv[0] * width );
        j = (int)round ( uv[1] * height );
    }
    else if(sid==1){
        i = (int)round ( uv[0] * width/3.0);
        j = (int)round ( uv[1] * height/2.0 + height/2.0);
    }
    else if(sid==2){
        i = (int)round ( uv[0] * width/3.0);
        j = (int)round ( uv[1] * height/2.0 + height/2.0);
    }
    else if(sid==3){
        i = (int)round ( uv[0] * width/3.0 + width/3.0);
        j = (int)round ( uv[1] * height/2.0 + height/2.0);
    }
    else if(sid==4){
        i = (int)round ( uv[0] * width/3.0 + width/3.0);
        j = (int)round ( uv[1] * height/2.0 + height/2.0);
    }
    else if(sid==5){
        i = (int)round ( uv[0] * width/3.0 + 2.0 * width/3.0);
        j = (int)round ( uv[1] * height/2.0 + height/2.0);
    }
    else if(sid==6){
        i = (int)round ( uv[0] * width/3.0 + 2.0 * width/3.0);
        j = (int)round ( uv[1] * height/2.0 + height/2.0);
    }
    else if(sid==7){
        i = (int)round ( uv[0] * width/3.0);
        j = (int)round ( uv[1] * height/2.0);
    }
    else if(sid==8){
        i = (int)round ( uv[0] * width/3.0);
        j = (int)round ( uv[1] * height/2.0);
    }
    else if(sid==11){
        i = (int)round ( uv[0] * width/3.0 + width/3.0);
        j = (int)round ( uv[1] * height/2.0);
    }
    else if(sid==12){
        i = (int)round ( uv[0] * width/3.0 + width/3.0);
        j = (int)round ( uv[1] * height/2.0);
    }
    else if(sid==9){
        i = (int)round ( uv[0] * width/3.0 + 2.0 * width/3.0);
        j = (int)round ( uv[1] * height/2.0);
    }
    else if(sid==10){
        i = (int)round ( uv[0] * width/3.0 + 2.0 * width/3.0);
        j = (int)round ( uv[1] * height/2.0);
    }
    
    if(i>=width)
        i = width-1;
    if(j>=height)
        j = height-1;
    //cout<<"u: " << uv.first <<" v: "<<uv.second<<endl;
    //cout <<i << " " << j << endl;
    return Vector3((float) texture_image[j][i][0],
                   (float) texture_image[j][i][1],
                   (float) texture_image[j][i][2]);
}
