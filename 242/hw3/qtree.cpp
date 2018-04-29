#include "qtree.h"
QTree::QTree(int input)
{
	topLeft.setx(0);
	topLeft.sety(0);
	bottomRight.setx(input-1);
	bottomRight.sety(input-1);
	birinci=NULL;
	ikinci=NULL;
	ucuncu=NULL;
	dorduncu=NULL;
	rec=NULL;
	level=0;
}
QTree::QTree(const QTree& rhs)
{
	*this=rhs;
}
QTree::~QTree()
{
	//cout<<"terminated"<<endl;
	delete birinci;
	delete ikinci;
	delete ucuncu;
	delete dorduncu;
}
void QTree::insert(const Rectangle& rhs)
{
	Rectangle tree(this->topLeft,this->bottomRight);
	if(rec==NULL && birinci==NULL && tree.intersects(rhs)){	
		//cout<<"bombos"<<endl;
		rec=&rhs;
	}else if(rec!=NULL && birinci==NULL && tree.intersects(rhs)){
		//cout<<"cocuguyoksadecedikdortgen"<<endl;		
		const Rectangle* temp=rec;
		rec=NULL;
		int length=(bottomRight.getx()-topLeft.getx()+1)/2;
		birinci=new QTree(length);
		ikinci=new QTree(length);
		ucuncu=new QTree(length);
		dorduncu=new QTree(length);
		//kareleri ayarla
		birinci->topLeft.setx(this->topLeft.getx());//birinciyi oturtma
		birinci->topLeft.sety(this->topLeft.gety());
		birinci->bottomRight.setx(this->topLeft.getx()+length-1);
		birinci->bottomRight.sety(this->topLeft.gety()+length-1);
		birinci->level=level+1;
		ikinci->topLeft.setx(birinci->topLeft.getx()+length);//ikinciyi oturtma
		ikinci->topLeft.sety(birinci->topLeft.gety());
		ikinci->bottomRight.setx(birinci->bottomRight.getx()+length);
		ikinci->bottomRight.sety(birinci->bottomRight.gety());
		ikinci->level=level+1;
		ucuncu->topLeft.setx(ikinci->topLeft.getx());//ucuncuyu oturtma
		ucuncu->topLeft.sety(ikinci->topLeft.gety()+length);
		ucuncu->bottomRight.setx(ikinci->bottomRight.getx());
		ucuncu->bottomRight.sety(ikinci->bottomRight.gety()+length);
		ucuncu->level=level+1;
		dorduncu->topLeft.setx(birinci->topLeft.getx());//dorduncuyu oturtma
		dorduncu->topLeft.sety(birinci->topLeft.gety()+length);
		dorduncu->bottomRight.setx(birinci->bottomRight.getx());
		dorduncu->bottomRight.sety(birinci->bottomRight.gety()+length);
		dorduncu->level=level+1;
		//tempi koy
		if(Rectangle(birinci->topLeft,birinci->bottomRight).intersects(*temp)){
			//cout<<"birincitreeyedikdörtgenkoydum"<<endl;
			birinci->rec=temp;		
		}	
		if(Rectangle(ikinci->topLeft,ikinci->bottomRight).intersects(*temp)){
			ikinci->rec=temp;
			//cout<<"ikincitreeyedikdörtgenkoydum"<<endl;
		}	
		if(Rectangle(ucuncu->topLeft,ucuncu->bottomRight).intersects(*temp)){
			//cout<<"ucuncutreeyedikdörtgenkoydum"<<endl;		
			ucuncu->rec=temp;
		}	
		if(Rectangle(dorduncu->topLeft,dorduncu->bottomRight).intersects(*temp)){
			dorduncu->rec=temp;
			//cout<<"dorduncutreeyedikdörtgenkoydum"<<endl;
		}	
		//rhsyi koy
		if(Rectangle(birinci->topLeft,birinci->bottomRight).intersects(rhs)){
			//cout<<"int1egirdim"<<endl;
			birinci->insert(rhs);
		}
		if(Rectangle(ikinci->topLeft,ikinci->bottomRight).intersects(rhs)){
			//cout<<"int2yegirdim"<<endl;
			ikinci->insert(rhs);
		}
		if(Rectangle(ucuncu->topLeft,ucuncu->bottomRight).intersects(rhs)){
			//cout<<"int3egirdim"<<endl;
			ucuncu->insert(rhs);
		}
		if(Rectangle(dorduncu->topLeft,dorduncu->bottomRight).intersects(rhs)){
			//cout<<"int4egirdim"<<endl;
			dorduncu->insert(rhs);
		}
	}else if(rec==NULL && birinci!=NULL && tree.intersects(rhs)){
		//cout<<"cocuguvardikdortgeniyok"<<endl;
		Rectangle tree1(birinci->topLeft,birinci->bottomRight);
		Rectangle tree2(ikinci->topLeft,ikinci->bottomRight);
		Rectangle tree3(ucuncu->topLeft,ucuncu->bottomRight);
		Rectangle tree4(dorduncu->topLeft,dorduncu->bottomRight);
		if(Rectangle(birinci->topLeft,birinci->bottomRight).intersects(rhs))birinci->insert(rhs);
		if(Rectangle(ikinci->topLeft,ikinci->bottomRight).intersects(rhs))ikinci->insert(rhs);
		if(Rectangle(ucuncu->topLeft,ucuncu->bottomRight).intersects(rhs))ucuncu->insert(rhs);
		if(Rectangle(dorduncu->topLeft,dorduncu->bottomRight).intersects(rhs))dorduncu->insert(rhs);
	}
}
const Rectangle* QTree::operator[](const Coordinate& rhs) const
{
		if(birinci==NULL && rec==NULL){
			return NULL;
		}
		else if(birinci==NULL && rec!=NULL){
			if(rec->contains(rhs)){
				//cout<<rec->getTopLeft().getx()<<' '<<rec->getTopLeft().gety()<<endl;				
				return rec;
			}
			else{
				return NULL;
			}
		}
		else{
			Rectangle can1(birinci->topLeft,birinci->bottomRight);
			Rectangle can2(ikinci->topLeft,ikinci->bottomRight);
			Rectangle can3(ucuncu->topLeft,ucuncu->bottomRight);
			Rectangle can4(dorduncu->topLeft,dorduncu->bottomRight);			
			if(can1.contains(rhs)){
				//cout<<"kasar";
				return (*birinci)[rhs];
			}else if(can2.contains(rhs)){
				return (*ikinci)[rhs];
			}else if(can3.contains(rhs)){
				return (*ucuncu)[rhs];
			}else if(can4.contains(rhs)){
				return (*dorduncu)[rhs];
			}else{
				return NULL;
			}
		}
}
ostream& operator<<(ostream& out, const QTree& rhs)
{	
	if(rhs.rec!=NULL && rhs.birinci==NULL){
		out<<'('<<rhs.topLeft.getx()<<','<<rhs.topLeft.gety()<<')'<<' ';
		out<<'['<<rhs.bottomRight.getx()-rhs.topLeft.getx()+1<<']'<<' ';
		out<<"***"<<' ';
		out<<'('<<(rhs.rec)->getTopLeft().getx()<<','<<(rhs.rec)->getTopLeft().gety()<<')'<<' ';
		out<<'['<<(rhs.rec)->getBottomRight().getx()-(rhs.rec)->getTopLeft().getx()+1<<',';
		out<<(rhs.rec)->getBottomRight().gety()-(rhs.rec)->getTopLeft().gety()+1<<']'<<' ';
		out<<"***"<<endl;
	}else if(rhs.rec==NULL && rhs.birinci==NULL){
		out<<'('<<rhs.topLeft.getx()<<','<<rhs.topLeft.gety()<<')'<<' ';
		out<<'['<<rhs.bottomRight.getx()-rhs.topLeft.getx()+1<<']'<<' ';
		out<<"..."<<endl;
	}else if(rhs.rec==NULL && rhs.birinci!=NULL){
		out<<'('<<rhs.topLeft.getx()<<','<<rhs.topLeft.gety()<<')'<<' ';
		out<<'['<<rhs.bottomRight.getx()-rhs.topLeft.getx()+1<<']'<<' ';
		out<<"..."<<endl;
		for(int i=rhs.birinci->level;i>0;i--)out<<"    ";
		out<<*(rhs.birinci);
		for(int i=rhs.ikinci->level;i>0;i--)out<<"    ";
		out<<*(rhs.ikinci);
		for(int i=rhs.ucuncu->level;i>0;i--)out<<"    ";
		out<<*(rhs.ucuncu);
		for(int i=rhs.dorduncu->level;i>0;i--)out<<"    ";
		out<<*(rhs.dorduncu);
	}
	return out;
}
QTree& QTree::operator=(const QTree& rhs)
{
	if(this!=&rhs){
		delete birinci;
		delete ikinci;
		delete ucuncu;
		delete dorduncu;
		if(rhs.birinci==NULL && rhs.rec==NULL)
		{
			this->topLeft.setx(rhs.topLeft.getx());
			this->topLeft.sety(rhs.topLeft.gety());
			this->bottomRight.setx(rhs.bottomRight.getx());
			this->bottomRight.sety(rhs.bottomRight.gety());			
			birinci=ikinci=ucuncu=dorduncu=NULL;
			rec=NULL;
			level=rhs.level;
		}else if(rhs.birinci==NULL && rhs.rec!=NULL){
			topLeft.setx(rhs.topLeft.getx());
			topLeft.sety(rhs.topLeft.gety());
			bottomRight.setx(rhs.bottomRight.getx());
			bottomRight.sety(rhs.bottomRight.gety());
			birinci=ikinci=ucuncu=dorduncu=NULL;
			rec=NULL;//yeni ekledin
			insert(*(rhs.rec));
			level=rhs.level;
		}else{
			topLeft.setx(rhs.topLeft.getx());
			topLeft.sety(rhs.topLeft.gety());
			bottomRight.setx(rhs.bottomRight.getx());
			bottomRight.sety(rhs.bottomRight.gety());
			level=rhs.level;
			rec=NULL;
			int length=(rhs.bottomRight.getx()-rhs.topLeft.getx()+1)/2;			
			birinci=new QTree(length);			
			*birinci=*(rhs.birinci);
			ikinci=new QTree(length);
			*ikinci=*(rhs.ikinci);
			ucuncu=new QTree(length);
			*ucuncu=*(rhs.ucuncu);
			dorduncu=new QTree(length);
			*dorduncu=*(rhs.dorduncu);
		}
	}
	else
		return *this;
	
}
