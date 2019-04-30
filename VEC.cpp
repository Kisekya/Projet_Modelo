#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

string vec_to_string( vector<double> s1 ,  string c1 ){
    string data;
    for (unsigned i=0; i< s1.size() ; i++ ){
        string tmp=to_string(s1.at(i));
        data += c1+" "+tmp+"\n";
    } return data;
    }

int main(){
    vector<double> test { 0,0.25,0.5 };
    vector<double> test2 { 1, 2 , 3 };
    string v =" test";
	cout << vec_to_string( test,v  ) ;
    return 0;
}