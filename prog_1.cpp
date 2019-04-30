#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;


// implémentation du modèle Hindmash-Rose

vector<double> sim(double duration, double dt) {
    // initialisation des variables
    int a =3; int b = 4; int d = 5;
    double xC = -0.5*(1+sqrt(5)); double epsilon = 0.008; double I = 3.25;
    double x0 = 0; double y0 = 0; double z0 = 0;
    double x_tmp; // nécessaire pour calculer y et z à un instant donné
    double x = x0; double y = y0; double z = z0;
    vector<double> time, x_values, y_values, z_values;

    // méthode d'Euler
    for (double t=0; t < duration; t+=dt) {
        time.push_back(t);
        x_values.push_back(x);
        y_values.push_back(y);
        z_values.push_back(z);
        x_tmp = x;
        x = (y + a*x*x - x*x*x - z + I) * dt + x;
        y = (1 - d*x_tmp*x_tmp - y) * dt + y;
        z = (epsilon * (b * (x_tmp - xC)) - z) * dt + z;
    }

    return x_values;
}


int main(int argc, char** argv) {
    if (argc == 1) {
        cerr << "Usage : comute <duration> <dt> <target_file>\nduration : simulation duration(ms)\ndt : bin (ms)\ntarget_file : output file name" << endl;
    } else {
        vector<double> x_values = sim(argv[1], argv[2]);
        vector<double> V_values;
        .... // calculer V(t) pour x(t) du vecteur x_values
        cout << argv[3] << " written" << endl;
    }
    return 0;
}