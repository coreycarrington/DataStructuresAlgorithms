/*
Programmer: Corey Carrington
net id: cac844
Topic(s): Hash function
Homework 09
*/
#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

 template< class HashedObj >
     class HashTable
     {
       public:
          explicit HashTable( int size = 101 ):currentSize(0){ array.resize(size); }
          std::hash<HashedObj> hf; // create a hash function object
          bool find( const HashedObj & x ) const;
          void makeEmpty( );
          bool insert( const HashedObj & x );
          bool remove( const HashedObj & x);
          enum EntryType { ACTIVE, EMPTY, DELETED };
      private:
          struct HashEntry
          {
               HashedObj element;
               EntryType info;
               HashEntry( const HashedObj & e = HashedObj(), EntryType i = EMPTY )
               : element( e), info(i) {}
          };
          vector<HashEntry> array;
          int currentSize;
          void rehash();
};



/*
Question 1 of the Homework create a find, 
insert, and remove function.
*/

//find element inside hash table
template<class HashedObj>
bool HashTable<HashedObj>::find(const HashedObj& obj)const{
     int hashIndex = hf(obj) % array.size();
     while(true){
          if(array[hashIndex].info == EMPTY)
               return false;
          else if(array[hashIndex].info == DELETED)
               hashIndex = (hashIndex+1) % array.size();
          else if(array[hashIndex].element == obj)
               return true;
          

          hashIndex = (hashIndex+1) % array.size();
     }
};




//inserts objects into hash table
template<class HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj& obj){
     int hashIndex = hf(obj) % array.size();

     if(find(obj))return false;

     while(array[hashIndex].info == ACTIVE)
          hashIndex = (hashIndex+1) % array.size();

     array[hashIndex].element = obj;
     array[hashIndex].info = ACTIVE;
     ++currentSize;

     if (currentSize >= array.size()* 0.5)
          rehash();

     return true;
};


//creates a new Hash table and rehash old items into new table
template<class HashedObj>
void HashTable<HashedObj>::rehash(){
     vector<HashEntry> prevArray = array;

     array.clear();
     currentSize = 0;
     array.resize(prevArray.size()*2 + 1);

     for(int i = 0; i < prevArray.size(); ++i){
          if(prevArray[i].info == ACTIVE)
               insert(prevArray[i].element);
     }
};


/*
-------------------------------------------------------------------
                    QUESTION 2 
-------------------------------------------------------------------
*/

//stores the train stop in a sorted vector
void createVectorOfStops(vector<string>& stops){
     ifstream ifs("MTA_train_stop_data.txt");
     if(!ifs){//checks to see if the file is not open
          cerr << "File didn't open\n";
          exit(1);
     }

     string line;
     getline(ifs, line);//gets the first line in the file

     while(getline(ifs, line)){
     //Stores all element in vector without duplicates
          stringstream separateLine(line);

          string x;

          getline(separateLine, x, ',');

          if(x[x.size()-1] != 'N' && x[x.size()-1] != 'S')
               stops.push_back(x);

     }
     ifs.close();
     sort(stops.begin(), stops.end());//sorts all elements in the vector
}



/*
Creates a map from the train stops in a vector. 
Also, store the element in the previous and next element
as long as it has the same first character. The vector is already sorted
*/
void createMapInitialStops(unordered_map<string, list<string>>& trainMap, 
     vector<string>& stops){
     for(size_t i = 0; i < stops.size(); ++i){
          list<string> listAdj;
          if(i == 0 && stops[i][0] == stops[i][0])
               listAdj.push_back(stops[i+1]);
          else if(i == stops.size()-1  && stops[i][0] == stops[i-1][0])
               listAdj.push_back(stops[i-1]);
          else{
               listAdj.push_back(stops[i-1]);
               listAdj.push_back(stops[i+1]);
          }

          trainMap.insert({stops[i], listAdj});

     }
}

/*
Read transfer file and find all adjancent locations
*/
void mapAdjStops(unordered_map<string, list<string>>& trainMap){
     ifstream ifs("transfers.txt");
     if(!ifs){
          cerr << "File did not open \n";
          exit(1);
     }

     string line;
     getline(ifs, line);
     while(getline(ifs,line)){
          stringstream separateLine(line);

          string from_stop;
          string to_stop;

          getline(separateLine, from_stop, ',');

          // to_stop = line.substr(4, line.size());
          getline(separateLine, to_stop, ',');

          if(from_stop != to_stop)
               trainMap[from_stop].push_back(to_stop);

     }



     ifs.close();
}

void displayList(const list<string>& adj){
     for(list<string>::const_iterator itr = adj.begin();  itr != adj.end(); itr++){
          cout << *itr << ',';
     }
     cout << endl;
}



int main(){
     
     

     vector<string> stops;
     createVectorOfStops(stops);

     unordered_map<string, list<string>> trainMap;

     createMapInitialStops(trainMap, stops);
     mapAdjStops(trainMap);
     displayList(trainMap.find("112")->second);
          
     HashTable<string> bostonGeneral;
     bostonGeneral.insert("emergency");
     bool truthValue = bostonGeneral.find("emergency");
     if(truthValue)
          cout << "emergency is inserted \n";
     
}


