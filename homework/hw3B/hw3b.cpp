//
//  hw3b.cpp
//  HW3B
//  Net ID: cac844
//  Created by Corey Carrington on 2/21/16.
//  Copyright © 2016 Corey Carrington. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <functional>

//#include <boost/algorithm/string.hpp>
using namespace std;
//using namespace boost;

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
void displayTrainData(vector<trainStopData>& trainData){
    for(size_t i = 0; i < trainData.size();++i)
        cout << trainData[i];
}
int main() {
    vector<string > fields;

    ifstream ifs("MTA_train_stop_data.txt");
    if(!ifs){
        cerr << "file not opened \n";
        exit(1);
    }
    
    readFile(fields, ifs);
    ifs.close();
    
    vector<trainStopData> trainData;
    convertToTrainData(fields, trainData);
    //displayTrainData(trainData);//Use if want to see File was read and stored.
    
  
    return 0;
}





























