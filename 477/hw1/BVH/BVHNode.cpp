#include "BVHNode.h"
using namespace std;
BVHNode::BVHNode(vector<Surface*> surfacelist, int axis){
    if (surfacelist.size()==1) {
        left = surfacelist[0];
        Surface::mins = surfacelist[0]->Surface::mins;
        Surface::maxs = surfacelist[0]->Surface::maxs;
        //cout<<"1"<<end<<" start:"<<start<<endl;
    }
    else if (surfacelist.size() == 2) {
        left = surfacelist[0];
        right = surfacelist[1];
        float minx = min(left->Surface::mins[0], right->Surface::mins[0]);
        float miny = min(left->Surface::mins[1], right->Surface::mins[1]);
        float minz = min(left->Surface::mins[2], right->Surface::mins[2]);
        float maxx = max(left->Surface::maxs[0], right->Surface::maxs[0]);
        float maxy = max(left->Surface::maxs[1], right->Surface::maxs[1]);
        float maxz = max(left->Surface::maxs[2], right->Surface::maxs[2]);
        Surface::mins = Vector3(minx, miny, minz);
        Surface::maxs = Vector3(maxx, maxy, maxz);
        //cout<<"end-start==2 -> end:"<<end<<" start:"<<start<<endl;
    }
    else {
        if (axis == 1) {
            sort(surfacelist.begin(), surfacelist.end(), compareX);
        }
        else if (axis == 2) {
            sort(surfacelist.begin(), surfacelist.end(), compareY);
        }
        else {
            sort(surfacelist.begin(), surfacelist.end(), compareZ);
        }
        int border=surfacelist.size() /2 ;
        left = new BVHNode(vector<Surface*>(surfacelist.begin(),surfacelist.begin()+border), (axis+1) % 3);
        right = new BVHNode(vector<Surface*>(surfacelist.begin()+border,surfacelist.end()), (axis+1) % 3);
        //cout<<"end-start -> end:"<<end<<" start:"<<start<<endl;
        float minx = min(left->Surface::mins[0], right->Surface::mins[0]);
        float miny = min(left->Surface::mins[1], right->Surface::mins[1]);
        float minz = min(left->Surface::mins[2], right->Surface::mins[2]);
        float maxx = max(left->Surface::maxs[0], right->Surface::maxs[0]);
        float maxy = max(left->Surface::maxs[1], right->Surface::maxs[1]);
        float maxz = max(left->Surface::maxs[2], right->Surface::maxs[2]);
        Surface::mins = Vector3(minx, miny, minz);
        Surface::maxs = Vector3(maxx, maxy, maxz);
    }
}
bool BVHNode::Intersect(const Ray& ray, RayHitInfo& hitInfo,int _id) const{
    
    if(!Surface::box_intersect(ray)){
        return false;
    }
    
    RayHitInfo rhiLeft,rhiRight;
    
    bool left_hit=false;
    bool right_hit=false;
    
    left_hit= (left!=NULL) && left->Intersect(ray,rhiLeft,_id);
    right_hit= (right!=NULL) && right->Intersect(ray,rhiRight,_id);
    
    if(left_hit && right_hit){
        if(rhiLeft.Parameter < rhiRight.Parameter){
            hitInfo=rhiLeft;
        }else
            hitInfo=rhiRight;
        
        return true;
    }
    else if(left_hit){
        hitInfo=rhiLeft;
        return true;
    }else if(right_hit){
        hitInfo=rhiRight;
        return true;
    }
    else
        return false;
}

void BVHNode::nofleaves()const{
    //int number=0;
    if(type().find("B")!=string::npos){
        std::cout<<"Box"<<std::endl;
    }
    if(left!=NULL){
        //number+=left->nofleaves();
        left->nofleaves();
    }
    if(right!=NULL){
        //number+=right->nofleaves();
        right->nofleaves();
    }
    //return number;
}

