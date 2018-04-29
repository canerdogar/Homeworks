#include <iostream>
#include <vector>
using namespace std;

int main(){
    int myints[] = {16,2,77,29,30};
    vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
    
    /*int counter=0;
    for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it){
        counter++;
    }
        cout << counter<<endl;*/

    vector<int> other(fifth.begin(),fifth.begin()+2);
    vector<int> other2(fifth.begin()+2,fifth.end());
    
    for (std::vector<int>::iterator it = other.begin(); it != other.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    
    for (std::vector<int>::iterator it = other2.begin(); it != other2.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    vector<int> other3(other2.begin(),other2.begin()+1);
    vector<int> other4(other2.begin()+1,other2.end());
    
    for (std::vector<int>::iterator it = other3.begin(); it != other3.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    
    for (std::vector<int>::iterator it = other4.begin(); it != other4.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    
	return 0;
}
