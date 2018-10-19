/*
Programmer: Corey Carrington
net id: cac844

*/
#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <list>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;
/*-------------------------------------------------------
				From pervious Homework
---------------------------------------------------------
*/
class trainStopData {
public:
    trainStopData(const string& id, const string& name, double lat, double lon)
                  : stop_id(id), stop_name(name), stop_lat(lat), stop_lon(lon) {}
    string get_id()         const { return stop_id; }
    string get_stop_name()  const { return stop_name; }
    double get_latitude()   const { return stop_lat; }
    double get_longitude()  const { return stop_lon; }
private:
    string stop_id;
    string stop_name;
    double stop_lat;
    double stop_lon;
};
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

//--------------------New Code---------------------------
const int DEFAULT_VAL =  -1;      // must be less than 0
//update
typedef unordered_map< string, list<string> > Graph;        // The graph is given in an adjacency list.


struct vertexInf{                   // Stores information for a vertex
    vertexInf (int d = DEFAULT_VAL, string p = "") : dist(d), prev(p) {}                              
    int dist;  // distance to vertex from the source
    string prev;  // update
};
void printpath(const string& begin,const string& end, const unordered_map<string, vertexInf>& vinfo){
    cout <<"Start of the stop_id: " << begin << endl;
    cout <<"End of the stop_id:   " << end << endl;
    cout <<"distance:             " << vinfo.find(end)->second.dist << endl;



    stack<string> t;
	
    string current = end;
    while (current != begin){
		t.push(current);
		current = vinfo.find(current)->second.prev;
    }
    cout << begin;

    while (!t.empty())
    {
		cout <<"-> " << t.top();
		t.pop();
    }
    cout << endl;
}



 

void shortestpaths(const Graph & g, const string& begin, const string& end){
    if (g.find(begin) == g.end()) {
        cout << "The start train ID does not exist!" << endl;
        return;
    }

    if (g.find(end) == g.end()) {
        cout << "The end train ID does not exist!" << endl;
        return;
    }

   
    unordered_map<string, vertexInf> vertex;

    
    for (Graph::const_iterator itr = g.begin(); itr != g.end(); itr++) {
        vertex.insert( {itr->first, vertexInf()} );
    }

   
    vertex[begin].dist = 0;

    
    
    queue<string> q;


    q.push(begin);

    while (!q.empty() ) {

         
        string v = q.front();
        
        q.pop();

        for (list<string>::const_iterator w = g.find(v)->second.begin(); w != g.find(v)->second.end(); w++) {
            
            string adjacentStop = *w;
            if (vertex[adjacentStop].dist == DEFAULT_VAL) {
                vertex[adjacentStop].dist = vertex[v].dist + 1;
                vertex[adjacentStop].prev = v;
                q.push(adjacentStop);
            }
        }
    }

    
    printpath(begin, end, vertex);
}








int main(){
	//Test code
    unordered_map < string, list<string> > adjList;
     

	vector<string> stops;
    createVectorOfStops(stops);
    mapAdjStops(adjList);

    
    cout << "Adjacency listings:\n";
    cout << "112: ";
    displayList(adjList.find("112")->second);
    
    cout << endl;

    shortestpaths(adjList, "112", "125");

    cout << endl;

}