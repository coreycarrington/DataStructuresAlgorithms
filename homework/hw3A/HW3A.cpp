/*
 Programmer:Corey Carrington
 NetID:cac844
 */
#include <iostream>
using namespace std;

template <typename Object>
class Vector
{
public:
    explicit Vector( int initSize = 0 )
    : theSize( initSize ), theCapacity(initSize + SPARE_CAPACITY )
    { objects = new Object[ theCapacity ]; }

    Vector( const Vector & rhs ):theSize( rhs.theSize ),
    theCapacity(rhs.theCapacity),objects(nullptr )
    {
        objects = new Object[ theCapacity ];
        for( int k = 0; k < theSize; ++k )
            objects[ k ] = rhs.objects[ k ];
    }
    
    Vector & operator= ( const Vector & rhs )
    {
        Vector copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    ~Vector( )
    { delete [ ] objects; }
    
    Vector( Vector && rhs )
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }
    
    Vector & operator= ( Vector && rhs )
    {
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );
        
        return *this;
    }
    
    bool empty( ) const
    { return size( ) == 0; }
    int size( ) const
    { return theSize; }
    int capacity( ) const
    { return theCapacity; }
    
    Object & operator[]( int index )
    {
        return objects[ index ];
    }
    
    const Object & operator[]( int index ) const
    {
        return objects[ index ];
    }
    
    void resize( int newSize )
    {
        if( newSize > theCapacity )
            reserve( newSize * 2 );
        theSize = newSize;
    }
    
    void reserve( int newCapacity )
    {
        if( newCapacity < theSize )
            return;
        
        Object *newArray = new Object[ newCapacity ];
        for( int k = 0; k < theSize; ++k )
            newArray[ k ] = std::move( objects[ k ] );
        
        theCapacity = newCapacity;
        std::swap( objects, newArray );
        delete [ ] newArray;
    }
    
    // Stacky stuff
    void push_back( const Object & x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = x;
    }
    // Stacky stuff
    void push_back( Object && x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = std::move( x );
    }
    
    
    // Iterator stuff: not bounds checked
    typedef Object * iterator;
    typedef const Object * const_iterator;
    
    iterator begin( )
    { return &objects[ 0 ]; }
    const_iterator begin( ) const
    { return &objects[ 0 ]; }
    iterator end( )
    { return &objects[ size( ) ]; }
    const_iterator end( ) const
    { return &objects[ size( ) ]; }
    iterator erase(iterator vItr);//erase method
    
    
    static const int SPARE_CAPACITY = 2;
    
private:
    int theSize;
    int theCapacity;
    Object * objects;
};
template<class Object>
typename Vector<Object>::iterator Vector<Object>::erase(Vector<Object>::iterator Ivtr){
    if(Ivtr < begin() || Ivtr >= end()){return Ivtr;}
    
    for (Vector<Object>::iterator itr = Ivtr; itr != end()-1  ; ++itr) {
       
        *itr = move(*(itr+1));
        
    }
    --theSize;
    return Ivtr;
}


class Student {
public:
    Student (const string& who, double grade) : name(who), gpa(grade) {}
    Student(){}
    string getName () const { return name; }
    double getGPA () const { return gpa; }
    friend ostream& operator<<(ostream&, const Student&);
private:
    string name;
    double gpa;
};
class GPA_in_range{
public:
    GPA_in_range(double l, double h):low(l),high(h){}
    bool operator()(const Student stu){
        return stu.getGPA() >= low && stu.getGPA() <= high;
    }
private:
    double low;
    double high;
};
ostream& operator<<(ostream& os, const Student& stu){
    cout << stu.getGPA() << endl;
    cout << stu.getName() << endl;
    return os;
}
template<class iterator , class UnaryPred>
void print_if( iterator start, iterator end, UnaryPred pred){
    if(start >= end){return;}
    for(iterator it = start; it != end; ++it){
        if (pred(*it)) {
            cout << *it;
            
        }
    }
}

int main(){
    
    Vector<Student> vec_of_student;
    Student stu1("Billy", 3.5);
    Student stu2("Sindy", 2.5);
    Student stu3("Carl", 3.6);
    Student stu4("Joe", 4.0);
    Student stu5("Mike", 3.0);
    vec_of_student.push_back(stu1);
    vec_of_student.push_back(stu2);
    vec_of_student.push_back(stu3);
    vec_of_student.push_back(stu4);
    vec_of_student.push_back(stu5);
    
    Vector<Student>::iterator start = vec_of_student.begin();
    Vector<Student>::iterator end = vec_of_student.end();
    
    print_if(start, end, GPA_in_range(3.0,4.0));
    
    
    
    
    return 1;
}






















