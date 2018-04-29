#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <utility>
using namespace std;

template <class T> class BPT;

template <class T>
class Node
{
    vector<T> keys;
    int order;
    vector<Node<T>*> children;
    bool leaf;
    vector<int> pos;
public:
    Node(int order_, bool leaf_);
    void insertNonFull(T key,int pos_);
    void splitChild(Node<T> *y);
    bool isSN();
    Node<T>* bosArkiVer();
    friend class BPT<T>;
    int equality(string pkey);
    /*friend Node<T>* bosArkiVer(Node<T>* node);
    friend bool isSN(Node<T>* node);*/
};

// A BTree
template <class T>
class BPT
{
    Node<T>* root;
    int order;
public:
    BPT(int order_)
    {  root = NULL;  order=order_; }
    void insert(T key,int pos_);
    void search_btree_equailty(string arguments,vector<pair<string,string> > types,int limit,int nok,int posOfpkey);
    void search_btree_range(string arguments,vector<pair<string,string> > types,int limit,int nok,int posOfpkey,int begofrec);
    void traverse(int begofrec,int bsize);
    void output(int bsize,int bkfr,int rsize);
};

// Constructor for BTreeNode class
template <class T>
Node<T>::Node(int order_, bool leaf_)
{
    order=order_;
    leaf = leaf_;
}
template <class T>
bool Node<T>::isSN(){
    if (children.back()->leaf) {
        if(children.back()->keys.size()==2*(children.back()->order)){
            return true;
        }
        else
            return false;
    }
    else{
        if (children.back()->keys.size()==2*(children.back()->order)) {
            return children.back()->isSN();
        }
        return false;
    }
}
template <class T>
Node<T>* Node<T>::bosArkiVer(){
    if(children.back()->keys.size()!=2*(children.back()->order)){
        return children.back();
    }
    else
        return children.back()->bosArkiVer();
}
template <class T>
void BPT<T>::traverse(int begofrec,int bsize){
    ofstream out("printBPlustree.txt");
    if (root==NULL) {
        out<<"empty";
        cout<<"empty"<<endl;
    }
    else{
        int level=0;
        typedef pair<Node<T>*,int> node_level;
        queue<node_level> q;
        q.push(node_level(root,1));
        while (!q.empty()) {
            node_level nl = q.front();
            q.pop();
            if (!nl.first->leaf) {
                if (level != nl.second) {
                    level = nl.second;
                }
                out<<"<index>"<<endl;
                cout<<"<index>"<<endl;
                for (int i=0; i<nl.first->keys.size();i++) {
                    out<< nl.first->keys[i]<<endl;;
                    cout<< nl.first->keys[i]<<endl;
                }
                out<<"<index>"<<endl;
                cout<<"<index>"<<endl;
                for (int i=0; i<nl.first->children.size();i++) {
                    q.push(node_level(nl.first->children[i],level+1));
                }
            }else{
                if (level != nl.second) {
                    level = nl.second;
                }
                if (nl.first->keys.size()==0) {}
                else{
                    out<<"<index>"<<endl;
                    cout<<"<index>"<<endl;
                    int i;
                    for (i=0; i<nl.first->keys.size();i++) {
                        out<<nl.first->keys[i]<<endl;
                        cout<<nl.first->keys[i]<<endl;
                    }
                    out<<"<index>"<<endl;
                    cout<<"<index>"<<endl;
                }
                
            }
        }
        ifstream inp("input.txt");
        string record;
        inp.seekg(begofrec,inp.beg);
        int counter=0;
        while (!inp.eof()) {
            if (counter!=0 && counter%bsize==0) {
                out<<"<data>"<<endl;
                out<<"<data>"<<endl;
                cout<<"<data>"<<endl;
                cout<<"<data>"<<endl;
            }else if(counter==0){
                out<<"<data>"<<endl;
                cout<<"<data>"<<endl;
            }
            getline(inp,record);
            out<<"<record>"<<endl;
            cout<<"<record>"<<endl;
            out<<record<<endl;
            cout<<record<<endl;
            out<<"<record>"<<endl;
            cout<<"<record>"<<endl;
            counter++;
        }
        out<<"<data>"<<endl;
        cout<<"<data>"<<endl;
    }
}
template <class T>
void BPT<T>::insert(T key,int pos_)
{
    if (root == NULL)
    {
        root = new Node<T>(order, true);
        root->pos.push_back(pos_);
    }
    else
    {
        if (root->keys.size() == 2*order)
        {
            if (root->leaf) {
                Node<T>* yeni=new Node<T>(order,false);
                yeni->children.push_back(root);
                yeni->splitChild(root);
                /*int i = 0;
                 if (yeni->keys[0] < key)
                 i++;*/
                yeni->children.back()->insertNonFull(key,pos_);
                root = yeni;
            }
            else {
                if(root->isSN()){
                    Node<T>* yeni=new Node<T>(order,false);
                    yeni->children.push_back(root);
                    yeni->splitChild(root);
                    /*int i = 0;
                     if (yeni->keys[0] < key)
                     i++;*/
                    yeni->children.back()->insertNonFull(key,pos_);
                    root = yeni;
                }
                else{
                    root->bosArkiVer()->insertNonFull(key,pos_);
                }
            }
            
        }
        else
            root->insertNonFull(key,pos_);
    }
}
template <class T>
void Node<T>::insertNonFull(T key,int pos_)
{
    if(leaf)
    {
        keys.push_back(key);
        pos.push_back(pos_);
    }
    else
    {
        /*int i;
        for (i=key.size()-1;i>=0 && keys[i]>key;i--);*/
        if (children.back()->keys.size() == 2*order)
        {
            if(children.back()->leaf){
                splitChild(children.back());
                children.back()->insertNonFull(key,pos_);
            }
            else{
                if(children.back()->isSN()){
                    splitChild(children.back());
                    children.back()->insertNonFull(key,pos_);
                }
                else
                    this->bosArkiVer()->insertNonFull(key,pos_);
            }
        }
        else{
            children.back()->insertNonFull(key,pos_);
        }
        
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
template <class T>
void Node<T>::splitChild(Node<T> *y)
{
    Node<T> *z = new Node<T>(order,y->leaf);
    typename vector<T>::const_iterator it=y->keys.begin()+order+1;
    for (; it!=y->keys.end(); it++) {
        z->keys.push_back(*it);
    }
    for (int i=0; i<order-1; i++) {
        y->keys.pop_back();
    }
    T temp=y->keys.back();
    y->keys.pop_back();
    if(!y->leaf)
    {
        for (int i=order+1; i<2*order+1; i++) {
            z->children.push_back(y->children[i]);
        }
        for (int i=0; i<order; i++) {
            y->children.pop_back();
        }
    }
    else{
        for (int i=order+1; i<2*order+1; i++) {
            z->pos.push_back(y->pos[i]);
        }
        for (int i=0; i<order; i++) {
            y->pos.pop_back();
        }
        
    }
    children.push_back(z);
    keys.push_back(temp);
}
string getKey(string record,int nok,int pos_);
template <class T>
int Node<T>::equality(string pkey){
    int i;
    if(leaf){
        if (keys.size()==0) {
            return pos[0];
        } else {
            for (i=0; i<keys.size() && pkey>=keys[i]; i++);
            return pos[i];
        }
    }
    else{
        for (i=0; i<keys.size() && pkey>=keys[i]; i++);
        return children[i]->equality(pkey);
    }
}
template <class T>
void BPT<T>::search_btree_range(string arguments,vector<pair<string,string> > types,int limit,int nok,int posOfpkey,int begofrec){
    if (root==NULL) {
        cout<<"no matching records found"<<endl;
        return;
    }
    string pkey1,pkey2;
    vector<string> istenenler;
    string record;
    int counter=0;
    pkey1=arguments.substr(0,arguments.find(" "));
    arguments=arguments.substr(arguments.find(" ")+1,arguments.size()-arguments.find(" "));
    if(arguments.find(" ")==string::npos)
    {
        pkey2=arguments;
    }
    else{
        while (arguments.find(" ")!=string::npos) {
            if (counter==0) {
                pkey2=arguments.substr(0,arguments.find(" "));
            }
            else{
                istenenler.push_back(arguments.substr(0,arguments.find(" ")));
            }
            counter++;
            arguments=arguments.substr(arguments.find(" ")+1,arguments.size()-arguments.find(" "));
        }
        istenenler.push_back(arguments);
    }
    ifstream inp("input.txt");
    int pos1,pos2;
    if (pkey1=="NULL") {
        pos1=begofrec;
    }else{
        pos1=root->equality(pkey1);
    }
    inp.seekg(pos1,inp.beg);
    int begin=inp.tellg();
    counter=0;
    /*cout<<pos1<<endl;
    cout<<pkey1<<endl;
    for (int i=0; i<istenenler.size(); i++) {
        cout<<istenenler[i]<<endl;
    }*/
    if(pkey2=="NULL"){
        while (!inp.eof()) {
            getline(inp,record);
            if(getKey(record,nok,posOfpkey)>=pkey1){
                if(!(istenenler.size())){
                    cout<<record<<endl;
                }
                else{
                    int i;
                    for (i=0; i<istenenler.size()-1; i++) {
                        for (int j=0; j<types.size(); j++) {
                            if(types[j].first==istenenler[i]){
                                cout<<getKey(record,nok,j+1)<<"|";
                                break;
                            }
                        }
                    }
                    for (int j=0; j<types.size(); j++) {
                        if(types[j].first==istenenler[i]){
                            cout<<getKey(record,nok,j+1)<<endl;;
                            break;
                        }
                    }
                }
                counter++;
            }
        }
        if(counter==0)
            cout<<"no matching records found"<<endl;
        return;
    }
    else{
        pos2=root->equality(pkey2);
        while (inp.tellg()<pos2+limit && !inp.eof()) {
            getline(inp,record);
            if(pkey1=="NULL"){
                if(getKey(record,nok,posOfpkey)<=pkey2){
                    if(!(istenenler.size())){
                        cout<<record<<endl;
                    }
                    else{
                        int i;
                        for (i=0; i<istenenler.size()-1; i++) {
                            for (int j=0; j<types.size(); j++) {
                                if(types[j].first==istenenler[i]){
                                    cout<<getKey(record,nok,j+1)<<"|";
                                    break;
                                }
                            }
                        }
                        for (int j=0; j<types.size(); j++) {
                            if(types[j].first==istenenler[i]){
                                cout<<getKey(record,nok,j+1)<<endl;;
                                break;
                            }
                        }
                    }
                    counter++;
                }
            }
            else if( getKey(record,nok,posOfpkey)>=pkey1 && getKey(record,nok,posOfpkey)<=pkey2 ){
                if(!(istenenler.size())){
                    cout<<record<<endl;
                }
                else{
                    int i;
                    for (i=0; i<istenenler.size()-1; i++) {
                        for (int j=0; j<types.size(); j++) {
                            if(types[j].first==istenenler[i]){
                                cout<<getKey(record,nok,j+1)<<"|";
                                break;
                            }
                        }
                    }
                    for (int j=0; j<types.size(); j++) {
                        if(types[j].first==istenenler[i]){
                            cout<<getKey(record,nok,j+1)<<endl;;
                            break;
                        }
                    }
                }
                counter++;
            }
        }
        if(counter==0)
            cout<<"no matching records found"<<endl;
        return;
    }
    

}

template <class T>
void BPT<T>::search_btree_equailty(string arguments,vector<pair<string,string> > types,int limit,int nok,int posOfpkey){
    if (root==NULL) {
        cout<<"no matching records found"<<endl;
        return;
    }
    string pkey;
    vector<string> istenenler;
    string record;
    int counter=0;
    if(arguments.find(" ")==string::npos)
    {
        pkey=arguments;
    }
    else{
        while (arguments.find(" ")!=string::npos) {
            if (counter==0) {
                pkey=arguments.substr(0,arguments.find(" "));
            }
            else{
                istenenler.push_back(arguments.substr(0,arguments.find(" ")));
            }
            counter++;
            arguments=arguments.substr(arguments.find(" ")+1,arguments.size()-arguments.find(" "));
        }
        istenenler.push_back(arguments);
    }
    int pos=root->equality(pkey);
    //cout<<pos<<endl;
    //61688
    ifstream inp("input.txt");
    inp.seekg(pos,inp.beg);
    int begin=inp.tellg();
    while (inp.tellg()<limit+begin && !inp.eof()) {
        getline(inp,record);
        if(getKey(record,nok,posOfpkey)==pkey){
            if(!(istenenler.size())){
                cout<<record<<endl;
            }
            else{
                int i;
                for (i=0; i<istenenler.size()-1; i++) {
                    for (int j=0; j<types.size(); j++) {
                        if(types[j].first==istenenler[i]){
                            cout<<getKey(record,nok,j+1)<<"|";
                            break;
                        }
                    }
                }
                for (int j=0; j<types.size(); j++) {
                    if(types[j].first==istenenler[i]){
                        cout<<getKey(record,nok,j+1)<<endl;;
                        break;
                    }
                }
            }
            return;
        }
        
    }
        cout<<"no matching records found"<<endl;

    
}

template<class T>
void BPT<T>::output(int bsize,int bkfr,int rsize){
    int nok;
    ifstream inp("input.txt");
    ofstream out("output.data",ios::binary);
    string can;
    getline(inp,can);
    nok=atoi(can.substr(can.find(" ")+1,can.size()-can.find(" ")).c_str());
    for(int i=0;i<nok;i++){
        getline(inp,can);
    }

    
    string record;
    int counter1=0,flag=0;
    while (!inp.eof()) {
        getline(inp,record);
        if (flag==0) {
            out<<record<<endl;
            flag=1;
        }
        else{
            
            if (counter1%bsize==0) {
                for (int j=0; j<bkfr-bsize; j++) {
                    for (int i=0; i<rsize; i++) {
                        out<<'$';
                    }
                    
                    out<<endl;
                }
                out<<record<<endl;
            }
            else
                out<<record<<endl;
        }
        counter1++;
        
    }
    for (int j=0; j<bkfr-(counter1%bsize); j++) {
        for (int i=0; i<rsize; i++) {
            out<<'$';
        }
        if(bkfr-(counter1%bsize)-1!=j)
            out<<endl;
    }
    //cout<<counter1<<endl;
}

string getKey(string record,int nok,int pos_){
    if (nok==1) {
        return record;
    }
    else if(pos_<nok){
        int counter=0;
        string result;
        while (counter<pos_) {
            result=record.substr(0,record.find("|"));
            record=record.substr(record.find("|")+1,record.size()-record.find("|"));
            counter++;
        }
        return result;
    }
    else{
        int counter=0;
        string result;
        while (counter<pos_-1) {
            result=record.substr(0,record.find("|"));
            record=record.substr(record.find("|")+1,record.size()-record.find("|"));
            counter++;
        }
        return record;
    }
}
int main(int argc,char* argv[]){
    ifstream inp("input.txt");
    string pkey,can,typeOfpkey;
    int order,bkfr,nok,byteoffset,posOfpkey,pos,bsize;
    vector< pair<string,string> > types;
    //terminal oku
    
    for (int i=1; i<argc;i=i+2) {
        if (string(argv[i])=="--btree-order") {
            order=atoi(string(argv[i+1]).c_str());
        } else if(string(argv[i])=="--btree-bkfr"){
            bkfr=atoi(string(argv[i+1]).c_str());
        }
        else{
            pkey=argv[i+1];
        }
    }
    BPT<string> bpt(order);
    //types
    getline(inp,can);
    byteoffset=atoi(can.substr(1,can.find(" ")).c_str());
    nok=atoi(can.substr(can.find(" ")+1,can.size()-can.find(" ")).c_str());
    for(int i=0;i<nok;i++){
        getline(inp,can);
        pair<string,string> type;
        type.first=can.substr(can.find(" ")+1,can.size()-can.find(" "));
        if(can.find("string")!=string::npos){type.second="string";}
        else if(can.find("char")!=string::npos){type.second="char";}
        else if(can.find("float")!=string::npos){type.second="float";}
        else if(can.find("int")!=string::npos){type.second="int";}
        types.push_back(type);
    }
    
    //
    for(int i=0;i<types.size();i++){
        if(types[i].first==pkey){
            /*if(types[i].second=="string"){
                
                typeOfpkey=types[i].second;
                break;
            }
            else if(types[i].second=="char"){
                
                typeOfpkey=types[i].second;
                break;
            }
            else if(types[i].second=="float"){
                
                typeOfpkey=types[i].second;
                break;
            }
            else if(types[i].second=="int"){
                
                typeOfpkey=types[i].second;
                break;
            }*/
            posOfpkey=i+1;
            break;
        }
    }
    
    //
    bsize=bkfr*(0.7);
    //cout<<bsize<<endl;
    int counter=0;
    int numofrecords=0;
    int begofrec=inp.tellg();
    while (!inp.eof()) {
        if(counter%(bsize)==0){
            pos=inp.tellg();
            getline(inp,can);
            bpt.insert(getKey(can,nok,posOfpkey),pos);
            counter++;
            numofrecords++;
            //cout<<can<<' '<<pos<<endl;
        }
        else{
            getline(inp,can);
            counter++;
            numofrecords++;
            //cout<<can<<endl;
        }
        
    }
    
    bpt.output(bsize,bkfr,byteoffset);
    
    string commands,arguments;
    getline(cin,commands);
    while (commands!="quit") {
        if(commands.substr(0,commands.find(" "))=="search_btree_equality")
        {
            arguments=commands.substr(commands.find(" ")+1,commands.size()-commands.find(" "));
            //cout<<arguments<<endl;
            bpt.search_btree_equailty(arguments,types,(byteoffset+1)*bsize,nok,posOfpkey);
        }
        else if(commands.substr(0,commands.find(" "))=="search_btree_range"){
            arguments=commands.substr(commands.find(" ")+1,commands.size()-commands.find(" "));
            //cout<<arguments<<endl;
            bpt.search_btree_range(arguments,types,(byteoffset+1)*bsize,nok,posOfpkey,begofrec);
        }
        else if(commands.substr(0,commands.find(" "))=="print_btree"){
            bpt.traverse(begofrec,bsize);
        }
        getline(cin,commands);
        
    }
    
    //cout<<numofrecords<<endl;
    return 0;
}





/*class Node{
private:
    vector<int> keys;
    vector<Node*> children;
    int order;
    bool leaf;
public:
    Node(bool leaf_,int order_){
        order=order_;
        leaf=leaf_;
    }
    void split(Node* root,int bucketfactor){
        if (leaf) {
            Node* yeni=new Node(true,order);
            yeni->keys(root->keys.begin()+bucketfactor/2,root->keys.end());
            for (int i=0; i<bucketfactor-(bucketfactor/2); i++) {
                keys.pop_back();
            }
            addChild(root,)
        }
        else{}
    }
    friend class BPT;
};
class BPT{
private:
    Node* root;
    int order;
    int bucketfactor;
public:
    BPT(int order_,int bucketfactor_){
        order=order_;
        bucketfactor=bucketfactor_;
    }
    void add(int key){
        if(root==NULL){
            Node *root_=new Node(true,order);
            (root_->keys).push_back(key);
            root=root_;
        }
        else{
            if(root->leaf){
                if((root->keys).size==bucketfactor){
                    Node *root_=new Node(false,order);
                    root->split(root_,bucketfactor);
                    root=root_;
                }
                else{//bura tmm leaf ve dolu değilse
                    int osize=(root->keys).size();
                    (root->keys).resize(((root->keys).size())+1);
                    int size=(root->keys).size();
                    int i;
                    for (i=0; i<osize && key>=root->keys[i]; i++);
                    if(i==size){
                        root->keys[i-1]=key;
                    }
                    else{
                        int j=size;
                        while (j-1>=i) {
                            root->keys[j]=root->keys[j-1];
                            j--;
                        }
                        root->keys[i]=key;
                    }
                }
            }
        }
    }
};

int main(){
    string buffer;
    getline(cin,buffer);
    while (buffer!="quit") {
        cout<<buffer<<endl;
        getline(cin,buffer);
    }
    return 0;
}*/