#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <math.h>
using namespace std;


/*
Programmer: Corey Carrington
net ID: cac844
*/

class trainStopData{
public:
    trainStopData(const string& id, const string& n,const double lat,
                  const double lon): stop_id(id), stop_name(n), stop_lat(lat),stop_lon(lon){}
    string get_id()const{return stop_id;}
    string get_stop_name()const{return stop_name;}
    double get_latitude()const{return stop_lat;}
    double get_longitude()const{return stop_lon;}
    friend ostream& operator<<(ostream& os, trainStopData& tsd);
    
    
private:
    string stop_id;
    string stop_name;
    double stop_lat;
    double stop_lon;
};
ostream& operator<<(ostream& os, trainStopData& tsd){
    cout << "Station: \n";
    cout << "ID: " << tsd.get_id() << ", Name: "
    << tsd.get_stop_name() << ", Latitude: " << tsd.get_latitude()
    << ", Longitude " << tsd.get_longitude()<< endl;
    return os;
}
void readFile(vector<string>& vec_of_str, ifstream& ifs){
    string line;
    getline(ifs, line);
    while(getline(ifs, line))
        vec_of_str.push_back(line );
    
}
void convertToTrainData(vector<string>& vec_of_str, vector<trainStopData>& trainData){
    for (size_t i = 0; i < vec_of_str.size(); ++i) {
        long pos1 = vec_of_str[i].find_first_of(',');
        string s1 = vec_of_str[i].substr(0, pos1);
        
        
        long pos2 = vec_of_str[i].find_first_of(',',pos1+2);
        string s2 = vec_of_str[i].substr(pos1+2, pos2-pos1-2);
        
        long pos3 = vec_of_str[i].find_first_of(',',pos2+2);
        string s3 = vec_of_str[i].substr(pos2+2,pos3-pos2-2);
        
        long pos4 = vec_of_str[i].find_first_of(',',pos3+1);
        string s4 = vec_of_str[i].substr(pos3+1, pos4-pos3-1);
        
        trainStopData stop(s1, s2,stod(s3),stod(s4));
        trainData.push_back(stop);
        
        
    }
    
}
double degrad(double d) {
   return d * M_PI / 180;
}


// Code below is adapted from http://www.movable-type.co.uk/scripts/latlong.html
// FYI: That website has an applet that computes the haversine distance. 
// It also has a link that will show the locations on a map,
// with a line between them.
double haverdist(double lat1, double longit1, double lat2, double longit2)
{
     double r = 6371;
     double dlat = degrad(lat2 - lat1);
     double dlongit = degrad(longit2 - longit1);
     double a = sin(dlat/2)*sin(dlat/2)+
        cos(degrad(lat1))*cos(degrad(lat2))*sin(dlongit/2)*sin(dlongit/2);
     double c = 2*atan2(sqrt(a),sqrt(1-a));
     return r*c;
}
/*
functor to determine stops along a trains route.
*/
class isStopOnRoute{
private:
    char route;
public:
    isStopOnRoute(const char& r):route(r){}
    bool operator()(const trainStopData& tsd){
        string stop = tsd.get_id();
        return stop[0] == route;
    }
};

//functor for checking the equality of the train 
//stop id 
class isSubwayStop{
private:
    string stopId;
public:
    isSubwayStop(const string& id):stopId(id){}
    bool operator()(const trainStopData& tsd){
        return tsd.get_id() == stopId;
    }

};


/*
Check distance from the longitude and latitude to 
see if it is near the train stop.
*/
class isSubwayStopNearX{
private:
    double longitude;
    double latitude;
    double d;
public:
    isSubwayStopNearX(const double longi, const double lat, const double d): 
    longitude(longi), latitude(lat),d(d){}
    bool operator()(const trainStopData& tsd){
        double distance = haverdist(longitude, latitude, 
            tsd.get_longitude(), tsd.get_latitude());
      return distance <= d;

    }
};
/*
printTrainStopInfo output the 
information of a single train stop
*/
class printTrainStopInfo{
public:
    void operator()(const trainStopData& tsd){
        cout << "Station: \n";
        cout << "ID: " << tsd.get_id() << ", Name: "
        << tsd.get_stop_name() << ", Latitude: " << tsd.get_latitude()
        << ", Longitude " << tsd.get_longitude()<< endl;
    }

};


/*
Generic Funtion
*/
template<class Iteration, class UnaryPred, class UnaryOp>
int perform_if(Iteration& itrStart, Iteration& itrEnd, 
    UnaryPred pred, UnaryOp op){
    int how_many = 0;
    Iteration itr = itrStart;

    while(itr!= itrEnd)
        if(pred(*itr)){
            op(*itr);
            how_many++;
            ++itr;

        }
    return how_many;
}

//Menu function to run the 
// template<class Iteration,class UnaryPred, class UnaryOp>
void menu(vector<trainStopData>& vec_stops){
    
    while(true){//infinite loop to run the loop
        char num;
        cout << "Enter 0 through 3 for perform a task:\n";
        cout << "0: Quit the program\n";
        cout << "1: Print out information about all the train stops on a specific route\n";
        cout << "2: Print out the information about a specific train stop\n";
        cout << "3: Print out all the train stops with a certain distance\n";
        
        cin >> num;
        

        vector<trainStopData>::iterator itrStart = vec_stops.begin();
        vector<trainStopData>::iterator itrEnd = vec_stops.end();
        printTrainStopInfo op;

        if(num == '0')
            break;
        else if (num == '1'){
            cout << " Enter Subway route name";
            char r;
            cin >> r;
            

            isStopOnRoute pred(r);

            int how_many = perform_if(itrStart, itrEnd, pred, op );
            // cout << how_many << endl;
            if(how_many == 0)
                cout <<" No route found\n";
        }
        else if (num == '2'){
            cout <<"Enter id for stop:";
            string identification;
            cin >> identification;
            isSubwayStop pred(identification);
            int how_many = perform_if(itrStart, itrEnd, pred, op);
            if (how_many == 0)
                cout << "No subway stop was found\n";
            
        }
        else if(num == '3'){
            double lon, lat,d;
            cout << "Longitude:";
            cin >> lon;

            cout << "Latitude:";
            cin >> lat;

            cout << "Enter distance:";
            cin >> d;
            isSubwayStopNearX pred(lon, lat, d);
            int how_many = perform_if(itrStart, itrEnd, pred, op);
            if(how_many == 0)
                cout <<"There were NO Stops found in distance you entered\n";

        }
        else
            cout << "You entered a wrong value. Please try again\n";

    }

}
//Question 2
int GCD(int a, int b){
    if(b == 0) return GCD(a, b);
    else if(a < b) return GCD(a, b);
    else return GCD(b, a % b);
}

//Question 3
//Driver Function
template<class Object>
Object sumVector(typename vector<Object>::iterator start,typename vector<Object>::iterator end){
    if(start+1 == end)return *start;
    typename vector<Object>::iterator middle = start + (end - start)/2;
    return sumVector<Object>(start, middle) + sumVector<Object>(middle, end);
    
    
}
template<class  Object>
Object sumVector( vector<Object>& vec_obj){
    if(vec_obj.size()== 0)return 0;
    return sumVector<Object>(vec_obj.begin(),vec_obj.end());
}

int main(){
    
    vector<string> train_strings;

    vector<trainStopData> train_stops;


    ifstream ifs("MTA_train_stop_data.txt");
    if(!ifs){
        cerr << "File didn't open\n";
        exit(1);
    }


    readFile(train_strings,ifs);
    ifs.close();

    convertToTrainData(train_strings, train_stops);
    menu(train_stops);

    //cout << train_stops.size();
    vector<trainStopData>::iterator itr = train_stops.begin();
    // while(itr!= train_stops.end()){
    //     cout<< *itr << endl;
    //     itr++;
    // }

    
	return 0;
}



































