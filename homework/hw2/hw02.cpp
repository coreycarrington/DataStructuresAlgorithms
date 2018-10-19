#include <iostream>
using namespace std;




class IntArray{
public:
    IntArray(int n = 0): size(n), array(new int[n ]){}
    // add your methods here
    void put (int  i, int value);
    int get( int i);
    ~IntArray();//destructor
    IntArray(const IntArray& rhs);//Copy Constructor
    IntArray(IntArray && rhs);//Move Constructor
    IntArray& operator=(IntArray&& rhs);//Move Assignment operator
    IntArray& operator=(IntArray& rhs);//Copy Assignment operator
    
    
private:
    int * array;
    int size;
};

void IntArray::put(int i, int value){
    if(i >= 0 && i < size )
        array[i]= value;
}
int IntArray::get(int i){
    if (i >= 0 && i < size)
        return array[i];
    return -1;
}

//Destructor
IntArray::~IntArray(){delete[] array;}

//Copy Constructor
IntArray::IntArray(const IntArray& rhs):size(rhs.size){
        cout<< "Copy Constructor\n";
    array = new int(rhs.size);
    for(size_t i = 0; i < size; ++i)
        array[i] = rhs.array[i];
}
//Copy Assignment Operator
IntArray& IntArray::operator=(IntArray& rhs){
    
    if(this != &rhs){
        cout<< "Copy assign\n";
        for (size_t i = 0; i < size; ++i) {
            array[i] = rhs.array[i];
        }
    }
    return *this;
}

//Move Constructor
IntArray::IntArray(IntArray&& rhs): size(rhs.size),array(rhs.array){
    cout<< "Move Constructor\n";
    rhs.array = nullptr;
}

//Move assignment operator
IntArray& IntArray::operator=(IntArray&& rhs){
    cout<< "Move assign\n";
//    int * tmpA = array;
//    int tmpS = size;
//    size = rhs.size;
//    array = rhs.array;
//    rhs.array = tmpA;
//    rhs.size= tmpS;
    swap(size, rhs.size);
    swap(array, rhs.array);
    return *this;
}

int main(){
    
//    IntArray a(3);
//    a.put(0,2);
//    a.put(2,78);
//    
//    cout << a.get(0) << endl;
//    cout << a.get(2) << endl;
//
//    
//    
//    IntArray b(3);
//    
//    b.put(0,56);
//    b.put(2,45);
//    cout << b.get(0) << endl;
//    cout << b.get(2) << endl;
//    b = move(a);
//    
//    cout << b.get(0) << endl;
//    cout << b.get(2) << endl;
//    IntArray c(3);
//    c.put(0,56);
//    c.put(2,45);
//    cout << c.get(0) << endl;
//    cout << c.get(2) << endl;
//    c= b ;
//    cout << c.get(0) << endl;
//    cout << c.get(2) << endl;
//    
//    
//    IntArray s(b);
//    
//    IntArray f(move(s));
//    
    
    return 1;
    
}
















