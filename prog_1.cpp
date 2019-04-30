#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

/////   Fonction Read

string read_file(string file){
    ifstream fichier (file);
    string data;
    string line;
    if (fichier) {
        while(getline(fichier , line)){
            data+=line+"\n"; 
        }
        fichier.close();
    } else cerr << "Impossible d'ouvrir le fichier !" << endl;	
        cout << data;
    }


///////  Fonction Write

void write_file(string file, string content){
	ofstream fichier(file);
	if(fichier){
		fichier << content;
		fichier.close();
	} else cerr << "Impossible d'ouvrir le fichier !" << endl;
}


//////// Affichage en colonne 

string cbind( vector<double> s1 , vector<double> s2 , string c1 , string c2){
    string data;
    data = c1+" "+c2+"\n";
    for (unsigned i=0; i< s1.size() ; i++ ){
        string tmpst1=to_string(s1.at(i));
        string tmpst2=to_string(s2.at(i));
        data+= tmpst1+" "+tmpst2+"\n";
    } 
    return data;
}

/////// Stocker les vitesses calculées: 


// vector<double> GetV( vector<double> x_val){
//     vector<double> V_values; 
//     for (unsigned i=0 ; i< x_val.size() ; i ++){
//         double tmp = 40*(x_val.at(i)-0.5);
//         V_values.push_back(tmp);
//     }
//     return V_values;
    
// }

// implémentation du modèle Hindmash-Rose

double GetV(double x){
    double V = 40*(x-0.5);
    return V;
    
}

vector<double> sim(double duration, double dt) {
    // initialisation des variables
    double a = 3; double b = 4; double d = 5;
    double xC = -0.5*(1+sqrt(5)); double epsilon = 0.008; double I = 3.25;
    double x0 = 0; double y0 = 0; double z0 = 0;
    double x = x0; double y = y0; double z = z0;
    vector<double> time, x_values, y_values, z_values;

    // méthode d'Euler
    for (double t=0; t < duration; t+=dt) {
        time.push_back(t);
        x_values.push_back(GetV(x));
        x = (y + a*x*x - x*x*x - z + I) * dt + x;
        y = (1 - d*x*x - y) * dt + y;
        z = (epsilon * (b * (x - xC) - z)) * dt + z;
    }

    return x_values;
}


///////  Stocker les temps incrémenté à 0.1

vector<double> GetTime ( double duration , double dt){
    vector<double> time_values;
    for (double i=0 ; i < duration ; i+=dt){
        time_values.push_back(i);
    }
    return time_values;
}

int main(int argc, char** argv) {
    if (argc != 4) {
        cerr << "Usage : comute <duration> <dt> <target_file>\nduration : simulation duration(ms)\ndt : bin (ms)\ntarget_file : output file name" << endl;
    } else if ( argc == 4) {
        string t = " Time ";
        string v = " V(t)";
        string::size_type st;
        double duration = stod( argv[1],&st);
        double dt = stod( argv[2],&st);
        vector<double> V_values = sim(duration, dt);
        vector<double> Time = GetTime( duration, dt );
        string data = cbind(Time,V_values,t,v);
        write_file ( argv[3], data);
        cout << argv[3] << " written" << endl;
    }
    return 0;
}