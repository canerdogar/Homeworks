#ifndef BVHNode_h
#define BVHNode_h

#include "Surface.h"
#include <vector>

using namespace std;

class BVHNode:public Surface {

public:
    Surface* left=NULL;
    Surface* right=NULL;
    bool static compareX (const Surface* lhs, const Surface* rhs) {
        float l = (lhs->Surface::mins._data[0] + lhs->Surface::maxs._data[0]) / 2;
        float r = (rhs->Surface::mins._data[0] + rhs->Surface::maxs._data[0]) / 2;
        return (l < r);
    };
    bool static compareY (const Surface* lhs, const Surface* rhs) {
        float l = (lhs->Surface::mins._data[1] + lhs->Surface::maxs._data[1]) / 2;
        float r = (rhs->Surface::mins._data[1] + rhs->Surface::maxs._data[1]) / 2;
        return (l < r);
    };
    bool static compareZ (const Surface* lhs, const Surface* rhs) {
        float l = (lhs->Surface::mins._data[2] + lhs->Surface::maxs._data[2]) / 2;
        float r = (rhs->Surface::mins._data[2] + rhs->Surface::maxs._data[2]) / 2;
        return (l < r);
    };
    BVHNode(vector<Surface*> surfacelist, int axis);
    bool Intersect(const Ray& ray, RayHitInfo& hitInfo,int _id) const;
    string type()const{return "B";}
    void nofleaves()const;
};




#endif //BVHNode_h