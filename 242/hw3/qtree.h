#ifndef QTREE_H
#define QTREE_H

#include "coordinate.h"
#include "rectangle.h"
#include <iostream>

using namespace std;

class QTree{
    private:
        // add private members, methods and constructors here as you need
	Coordinate topLeft,bottomRight;
	QTree* birinci;
	QTree* ikinci;
	QTree* ucuncu;
	QTree* dorduncu;
	const Rectangle* rec;
	int level;
    public:
        // do not make any modifications below
        QTree(int);
        QTree(const QTree&);
        ~QTree();
        void insert(const Rectangle&);
        const Rectangle* operator[](const Coordinate&) const;
        friend ostream& operator<<(ostream&, const QTree&);
        QTree& operator=(const QTree&);
};

#endif
