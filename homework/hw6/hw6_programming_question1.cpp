/*  
Programmer: Corey Carrington
netid: cac844
Product:
    Homework 6 programming part 1 a-f.
    Topic(s):
        Linked List
        Iterators
*/

#include <iostream>
#include <algorithm>

using namespace std;

template <typename Object>
class List
{
private:

    struct Node
    {
        Object  data;
        Node   *next;
        
        Node( const Object & d = Object{ },  Node * n = nullptr )
        : data{ d },  next{ n } { }
        
        Node( Object && d, Node * n = nullptr )
        : data{ std::move( d ) }, next{ n } { }
    };
    
public:
    class iterator
    {
    public:
        
        iterator( ): current( nullptr )
        { }
        
        Object & operator* ( )
        { return current->data; }
        
        const Object & operator* ( ) const
        { return  current->data; }
        
        iterator & operator++ ( )
        {
            this->current = this->current->next;
            return *this;
        }
        
        iterator operator++ ( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        }
        
        bool operator== ( const iterator & rhs ) const
        { return current == rhs.current; }
        
        bool operator!= ( const iterator & rhs ) const
        { return !( *this == rhs ); }
        
    private:
        Node * current;

        iterator( Node *p ) : current{ p }
        { }
        
        friend class List<Object>;
    };
    
public:
    List( )
    { header = new Node; }
    
    ~List( )
    {
        clear( );
        delete header;
    }
    
    List( const List & rhs ); 

    List & operator= ( const List & rhs )
    {
        List copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    List( List && rhs ):header{ new Node }
    {
        header->next = rhs.header->next;
        rhs.header->next = nullptr;
    }
    
    List & operator= ( List && rhs )
    {
        std::swap( header, rhs.header );
        return *this;
    }
    
    iterator begin( ) const
    { return iterator( header->next ); }
    
    iterator end( ) const
    { return iterator( nullptr ); }
    
    iterator before_begin( ) const
    { return iterator( header ); }
    
    bool empty( ) const
    { return header->next == nullptr; }
    
    void clear( )
    {
        while( !empty( ) )
            pop_front( );
    }
   
    
    void pop_front( )
    { erase_after( before_begin( ) ); }
    
    iterator insert_after( iterator itr, const Object & x )
    {
        Node *p = itr.current;
        p->next = new Node{ x, p->next };
        
        return iterator(p->next);
    }
    
    void remove( const Object & x )
    {
        Node * prev = header;
        
        while ( prev->next != nullptr )
        {
            if ( prev->next->data == x )
                erase_after( iterator(prev) );
            else
                prev = prev->next;
        }
    }
    
    iterator erase_after( iterator itr )
    {
        Node *p = itr.current;
        Node *oldNode = p->next;
        
        p->next = oldNode->next;
        delete oldNode;    
        return iterator( p->next );
    }
    
    Object & front( );
    
    const Object & front( ) const;
    
    void merge( List & alist );
    
    void reverse( );
    void remove_adjacent_duplicates();

    // Part F in question 1.
    template<class Predicate>
    void remove_if( Predicate& pred ){
        iterator current = begin();
        iterator before = before_begin();
        while(current != end()){
            if(pred(*current))
                current = erase_after(before);
            else{
                ++before;
                ++current;
            }
        }

    }
    
    //Part E: Question 1
    iterator insert_after( iterator itr, Object && x ){
        Node *p = itr.current;
        p->next = new Node{ move(x), p->next };
        
        return iterator(p->next);
    }
    

    
private:
    Node *header;
    
};
//Part A Copy Constructor
template<class Object>
List<Object>::List(const List& rhs):header(new Node){
    Node* currentNode = header;
    iterator tmp = rhs.begin();
    while(tmp != rhs.end()){
        currentNode->next = new Node(*tmp, nullptr);
        currentNode = currentNode->next;
        ++tmp;
    }
}

//Part B: front function
template<class Object>
const Object & List<Object>::front()const{
    return header->next->data;
}

//Part C: merge function
template<class Object>
void List<Object>::merge(List& alist){
    Node* left_previous = header;
    Node* left_current = header->next;
    Node* right_current = alist.header->next;
    while (left_current  != nullptr && right_current != nullptr){
        if (left_current->data < right_current->data) {
            left_current  = left_current->next;
            left_previous = left_previous->next;
        } 
        else{
            Node* tmp = right_current->next;
            right_current->next = left_current ;
            left_previous->next = right_current;
            right_current= tmp;
            left_previous = left_previous->next;
        }
    }
    while (right_current != nullptr) {
        Node* tmp = right_current->next;
        right_current->next = nullptr;
        left_previous->next = right_current;
        right_current = tmp;
    }
    alist.header->next = nullptr;
}

//Part D remove_adjacent_duplicates function
template<class Object>
void List<Object>::remove_adjacent_duplicates(){
    iterator first = begin();
    iterator second = ++begin();
    while(second != end()){
        if(first.current->data == second.current->data){
           Node* tmp = second.current;
           first.current->next = tmp->next;
           delete tmp;
           tmp = nullptr;

            // ++first;
            ++second;
        }
        else{
            ++first;
            ++second;
        }
    }

}



int main( ) {


}

