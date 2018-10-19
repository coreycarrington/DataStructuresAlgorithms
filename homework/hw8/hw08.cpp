/*
Programmer: Corey Carrington
net id: cac844
Homework 8 Topic:
	Recursion
*/

//
//  Binary Search Tree Class
//
//  Modified code from Weiss
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <queue>
using namespace std;

template<class Comparable>
struct BinaryNode
{
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ theElement }, left{ lt }, right{ rt }{ }

    BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
};


// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// bool contains( x )     --> Return true if x is present
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************


template <typename Comparable>
class BinarySearchTree
{
public:
    typedef BinaryNode<Comparable> Node;

    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }


    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
    	if(root == nullptr) return false;

        return contains( x, root );
    }

    //Homework 8 question 2a
    bool contains(const Comparable& x, Node* t)const{
    	if(x < t->element)
    		return contains(x, t->left);
    	else if(t->element < x)
    		return contains(x, t->right);
    	else
    		return true;

    	return false;
    }
    //Question 2b
    void printElementRange(const Comparable& low, const Comparable& high)const{
    	// if(root == nullptr) return;
    	printElementRange(low, high, root);
    }
      void printElementRange(const Comparable& low, const Comparable& high, Node* t)const{
    	if (t == nullptr) return;
        if(t->element < low)
            printElementRange(low, high, t->right);
        else if(t->element > high)
            printElementRange(low, high, t->left);
        else if(t->element == low || t->element == high)
            cout << t->element << ", ";

    	if(t->element > low && t->element < high){
    		cout << t->element << ", ";
    		printElementRange(low, high, t->left);
    		printElementRange(low, high, t->right);
        }
    }

    //Question 2c




    //Question 2d
    double average_node_depth()const{
        if(isEmpty()) return -1;

        return average_node_depth(root, 0)/size();

    }
    double average_node_depth(Node* t, int dep)const{
        if(t == nullptr) return 0;
        return average_node_depth(t->right, dep +1) + average_node_depth(t->left, dep+1) + dep;
    }

    //Question 3
    void OutputLevelOrder()const{
        if(root == nullptr) return;

        OutputLevelOrder(root);
    }

    //Question 3
    void OutputLevelOrder(Node* t)const{
        queue<Node*> q;
        Node* tmp = root;
        while(tmp){
            cout<<tmp->element<< ", ";

            if(tmp->left)
                q.push(tmp->left);

            if(tmp->right)
                q.push(tmp->right);

            if(!q.empty()){
                tmp = q.front();
                q.pop();
            }
            else
                tmp= nullptr;
        }
        cout << endl;
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }


    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }

    int size()const{
        if(isEmpty()) return 0;

        return size(root);
    }
    int size(Node* t)const{
        if(t == nullptr)
            return 0;

        return size(t->left) + size(t->right) + 1 ;

    }

private:

    BinaryNode<Comparable> *root;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, Node * & t )
    {
        if( t == nullptr )
            t = new Node{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, Node * & t )
    {
        if( t == nullptr )
            t = new Node{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing

    }


    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( Node * & t ){
        if( t != nullptr ){
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    

    /**
     * Internal method to clone subtree.
     */
    Node * clone( Node *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new Node{ t->element, clone( t->left ), clone( t->right ) };
    }



};
//Calculates the value a string has from the numbers in the vec_of_values
int calculateValue(string& str, vector<int>& vec_of_values){
    int number=0;
    char ch;
    for(size_t i = 0; i < str.size(); ++i){
        ch = toupper(str[i]);
        number += vec_of_values[ch - 65];

    }
    return number;
}


/*
Reads file calls the calculateValue function
to store the string and value into a map
*/
void readEnableFile(ifstream& ifs,map<string, int>& map_of_string_values,
    vector<int>& vec_of_values){
    string str;
    while(ifs >> str){
        int num = calculateValue(str, vec_of_values);
        map_of_string_values[str]= num;
    }


}
//Reads file and stores the string and it's number value in a map
void fileStoreLetterValues(ifstream& ifs, vector<int>& vec_of_values){
    char ch;
    int num, pos;
    while(ifs >> num >> ch){
        pos = ch - 65;
        vec_of_values[pos] = num;
    }
}

int main(){
	BinarySearchTree<int> bs;

	bs.insert(5);
	bs.insert(89);
	bs.insert(54);
	bs.insert(35);
	bs.insert(15);
	bs.insert(45);
	bs.insert(34);
	bs.insert(27);
    bs.insert(3);
    bs.insert(2);
    bs.insert(4);
    cout << bs.size() << endl;
    cout << bs.isEmpty() << endl;
    cout << bs.average_node_depth() << endl;
    BinarySearchTree<int> ba;

    // bs.OutputLevelOrder();

	// bs.printElementRange(1, 40);
	// int x = 5;
	// cout << bs.contains(x) << endl;
    // ba.printElementRange(14, 40);
    vector<int> vec_of_values(26);
    ifstream ifs;
    ifs.open("Letter_point_value.txt");
    if(!ifs){//test to see if file is open
        cerr << "File doesn't open \n";
        exit(1);
    }

    fileStoreLetterValues(ifs, vec_of_values);
    ifs.close();

    ifs.open("ENABLE.txt");
    if(!ifs){//test to see if file is open
        cerr << "File doesn't open \n";
        exit(1);
    }

    map<string, int> map_of_string_values;



    readEnableFile(ifs, map_of_string_values, vec_of_values);
    ifs.close();
    for(map<string, int>::iterator itr = map_of_string_values.begin(); itr != map_of_string_values.end(); ++itr)
        cout << itr->first << " = " << itr->second << endl;
}
