#include <iostream>
using namespace std;
/*
Programmer: Corey Carrington
netid: cac844
Program: 
	Create a model of a Queue class
*/
//Queue are first in first out
template<class Object>
class Queue{
private:
	struct Node {
        Object data;
        Node *next;
        Node (const Object& d = Object(), Node* n = nullptr):data(d),next(n){}
    };

	Node * first;

public:
	Queue(Node* f = nullptr):first(f){}
	Object& front(){ return first->data;}
	Object& back(){
		Node* tmp = first;
		while(tmp->next != nullptr)
			tmp = tmp->next;
		return tmp->data;
		
	}
	bool empty(){return first == nullptr;}
	void dequeue(){
		if(first != nullptr){
			Node* tmp = first;
			first = tmp->next;
			delete tmp;
		}
	}
	void enqueue(const Object& x){
		if(first == nullptr){
			first = new Node(x);
		
		}
		else{
			Node * tmp = first;
			while(tmp->next != nullptr)
				tmp = tmp->next;
		
			tmp->next = new Node(x);
		}

	}

};



int main(){

	

}