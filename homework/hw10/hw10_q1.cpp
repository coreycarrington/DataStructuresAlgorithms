/*
Programmer: Corey Carrington
netid: cac844
Homework 10
Topic: Priority Queue

*/

#include <vector>
#include <iostream>
#include <queue>
using namespace std;


template<class Comparable>
void print_kth_largest(const vector<Comparable>& a, int k){
	if(a.size() == 0) return;//test: make sure vector isn't empty

	priority_queue<Comparable> print_que;

	//loads all the elements into the priority queue
	for(Comparable x: a)
		print_que.push(x);


	for(int i = 1; i < k; ++i)
		print_que.pop();

	cout << "The kth (k = " << k << ") largest item: " 
	<< print_que.top() << endl;
}




int main(){
	//test code for function 
	vector<int> a = {12, 54, 87, 1, 34, 56, 23};
	
	priority_queue<int> print_que;
	
	cout << "priority_queue \n";

	print_kth_largest(a, 5);



}