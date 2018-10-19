/*
Programmer: Corey Carrington
net id: cac844
Homework 5:
	Topics:
		Recursion 
		Sorting: MergeSort, QuickSort, & InsertionSort
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;



/*
Program Question 1 rewrite recursive part of merge sort
*/
// mergerSort function generic to any containers
template <class RandItr>
void mergeSort(RandItr start, RandItr end, RandItr result) {
  // base case
  if (end == start+1 )return;

  // Gives me the center of the container
  RandItr center = start + (end - start) / 2;
  int x = end - start; // gives the size of the contain once it's split.
  //cout << x << endl;
  // Recursively call function for both sides.
  mergeSort(start, center, result);
  mergeSort(center, end, result+1/2);

  merge(start, center, center, end, result);

  copy(result, result+x, start);
}

// mergeSort Driver Function
template <class RandItr> 
void mergeSort(RandItr start, RandItr end) {
  int sz = end - start; // or use auto sz = end-start;
  typedef typename iterator_traits<RandItr>::value_type Object; // Xcode
  // typedef typename iterator_traits<RandItr>::value_type Object; // Other
  // compilers
  // Don’t worry about this line of code
  vector<Object> tmp(sz);
  mergeSort(start, end, tmp.begin());
}

//---------------------End of Programming Question 1---------------------

//Student class that was used in Homework 3A
class Student {
public:
    Student (const string& who) : name(who) {}
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

/*
Pogramming Question 2 create a Functor with a private member 
variable (me) type string. Overload operator() takes two argument
of type Student.
*/
ostream& operator<<(ostream& os, const Student& stu){
	cout << "Student Name: " << stu.getName() << endl;
	return os;
}
//Functor to compare names
class meFirst{
private:
  string me;
public:
  meFirst(const string& m):me(m){}
  bool operator()(const Student& first, const Student& second){
    if(me == first.getName()) return true;
    else if (me == second.getName()) return false;
    else
    	return first.getName() <= second.getName();

    }

};

//------------End of Programming Question 2----------------

/*
Programming Question 3:
Create an Algorithm that sorts a vector with true and false values.
False values must appear before all the true values. 
*/
void sortBool(vector<bool>& vec_of_bools){
	if(vec_of_bools.size() == 0) return;

	for(size_t i=0, j=0; i < vec_of_bools.size(); ++i){
		if(vec_of_bools[i]== false && vec_of_bools[j] ==true){
			swap(vec_of_bools[i],vec_of_bools[j]);
			j++;
		}
	}

}
//-----------End of Programming Question 3-------------



int main(){




	//Test Code for programming Question 3
	vector<bool> v;
	v.push_back(true);
	v.push_back(false);
	v.push_back(false);
	v.push_back(true);
	v.push_back(true);
	v.push_back(false);
	v.push_back(true);
	cout << "Unsorted\n";
	for(int i = 0; i < v.size(); ++i){
		cout << v[i] << endl;
	}
	sortBool(v);
//--End of Programming Question 3


//Test of for programming Question 2
	cout << "Sorted\n";
	for(int i = 0; i < v.size(); ++i){
		cout << v[i] << endl;
	}
  vector<Student> vec_of_students;
  vec_of_students.push_back(Student("Corey"));
  vec_of_students.push_back(Student("Mike"));
  vec_of_students.push_back(Student("Tommy"));
  vec_of_students.push_back(Student("Billy"));
  vec_of_students.push_back(Student("Latasha"));
  vec_of_students.push_back(Student("Johnny"));
  vec_of_students.push_back(Student("Jesus"));
  
  cout << "Unsorted vector of Student\n";
  for (size_t i = 0; i < vec_of_students.size(); i++)
        cout << "Name: " << vec_of_students[i].getName() << endl;
  
  meFirst me = meFirst("Corey");
  
  sort(vec_of_students.begin(), vec_of_students.end(),me);

  cout << "Sorted vector of Student\n";
  for (size_t i = 0; i < vec_of_students.size(); i++)
        cout << "Name: " << vec_of_students[i].getName() << endl;
//---End of Programming Question 2


//Test code for programming Question 1
      vector<int> a{14,6,34,-53,23,-9};
      cout << "-----Unsorted:\n";
      vector<int>::iterator itr = a.begin();
      while(itr!= a.end()){
        cout <<*itr << ',';
        itr++; 
      }
      mergeSort(a.begin(),a.end());

      
      cout <<"Sorted\n";
      for(int i =0; i < a.size(); ++i)
        cout << a[i] << ',';
      //End of programming question 1

	return 0;
}






















