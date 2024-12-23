#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
using namespace std;

double x_(double t, double x, double y, double z, double s) {
    return s*(y - x);
}

double y_(double t, double x, double y, double z, double r) {
    return x*(r - z) - y;
}

double z_(double t, double x, double y, double z, double b) {
    return x*y - b*z;
}

void Euler(vector<double>& t, vector<double>& x, vector<double>& y, vector<double>& z, double r , double s , double b , int n, double h) {
    for (int i = 0; i < n - 1; i++) {
        x[i + 1] = x[i] + x_(t[i], x[i], y[i], z[i] , s) * h;
        y[i + 1] = y[i] + y_(t[i], x[i], y[i], z[i] , r) * h;
        z[i + 1] = z[i] + z_(t[i], x[i], y[i], z[i], b) * h;
    }
}

void RK4(vector<double>& t, vector<double>& x, vector<double>& y, vector<double>& z, double r , double s , double b , int n, double h) {
    for (int i = 0; i < n - 1; i++) {
        t[i + 1] = t[i] + h;
        double x1 = x_(t[i], x[i], y[i], z[i], s);
        double y1 = y_(t[i], x[i], y[i], z[i], r);
        double z1 = z_(t[i], x[i], y[i], z[i], b);
        double x2 = x_(t[i] + h / 2, x[i] + h * x1 / 2, y[i] + h * y1 / 2, z[i] + h * z1/2, s);
        double y2 = y_(t[i] + h / 2, x[i] + h * x1 / 2, y[i] + h * y1 / 2, z[i] + h * z1/2, r);
        double z2 = z_(t[i] + h / 2, x[i] + h * x1 / 2, y[i] + h * y1 / 2, z[i] + h * z1/2, b);
        double x3 = x_(t[i] + h / 2, x[i] + h * x2 / 2, y[i] + h * y2 / 2, z[i] + h * z2/2, s);
        double y3 = y_(t[i] + h / 2, x[i] + h * x2 / 2, y[i] + h * y2 / 2, z[i] + h * z2/2, r);
        double z3 = z_(t[i] + h / 2, x[i] + h * x2 / 2, y[i] + h * y2 / 2, z[i] + h * z2/2, b);
        double x4 = x_(t[i] + h, x[i] + h * x3, y[i] + h * y3, z[i] + h * z3, s);
        double y4 = y_(t[i] + h, x[i] + h * x3, y[i] + h * y3, z[i] + h * z3, r);
        double z4 = z_(t[i] + h, x[i] + h * x3, y[i] + h * y3, z[i] + h * z3, b);

        x[i + 1] = x[i] + h * (x1 + 2 * x2 + 2 * x3 + x4) / 6;
        y[i + 1] = y[i] + h * (y1 + 2 * y2 + 2 * y3 + y4) / 6;
        z[i + 1] = z[i] + h * (z1 + 2 * z2 + 2 * z3 + z4) / 6;
    }
}

void Time_Series(const vector<double>& t, const vector<double>& x, const vector<double>& y, const vector<double>& z, int n) {
    // Open a pipe to Gnuplot
    FILE* gnuplotPipe = popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error: Could not open pipe to Gnuplot.\n";
        return;
    }

    // Send commands to Gnuplot
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Van der Pol Oscillator'\n");
    fprintf(gnuplotPipe, "set xlabel 'Time'\n");
    fprintf(gnuplotPipe, "set ylabel 'Values'\n");
    // fprintf(gnuplotPipe, "set yrange [-3:3]\n") ;
    fprintf(gnuplotPipe, "plot '-' title 'x(t)' with lines, '-' title 'y(t)' with lines, '-' title 'z(t)' with lines\n");

    // Send data for x(t)
    for (int i = 0; i < n; i++) {
        fprintf(gnuplotPipe, "%f %f\n", t[i], x[i]);
    }
    fprintf(gnuplotPipe, "e\n");  // End of x data

    // Send data for y(t)
    for (int i = 0; i < n; i++) {
        fprintf(gnuplotPipe, "%f %f\n", t[i], y[i]);
    }
    fprintf(gnuplotPipe, "e\n");  // End of y data

    // Send data for z(t)
    for (int i = 0; i < n; i++) {
        fprintf(gnuplotPipe, "%f %f\n", t[i], z[i]);
    }
    fprintf(gnuplotPipe, "e\n");  // End of z data

    // Close the pipe
    pclose(gnuplotPipe);
}


void State_Space(const vector<double>& x, const vector<double>& y, const vector<double>& z, int n) {
    // Open a pipe to Gnuplot
    FILE* gnuplotPipe = popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error: Could not open pipe to Gnuplot.\n";
        return;
    }

    // Send commands to Gnuplot
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Lorenz Attractor'\n");
    fprintf(gnuplotPipe, "set xlabel 'X position'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y Position'\n");
    fprintf(gnuplotPipe, "set zlabel 'Z position'\n");

    for (int frame = 0; frame < n; frame++)
    {
        fprintf(gnuplotPipe, "splot '-' using 1:2:3 with lines title 'State Space'\n");
        for (int i = 0; i <= frame; i++) {
        fprintf(gnuplotPipe, "%f %f %f\n", x[i], y[i], z[i]);
        }
        fprintf(gnuplotPipe, "e\n");
    }
    
     
}

int main() {
    // Lorenz System
    // x' = s(y - x)
    // y' = x(r - z) - y
    // z' = xy - bz


    double h = 0.01, r = 28, s = 10, b = 8/3;
    int n = static_cast<int>(50 / h) + 1;

    vector<double> t(n, 0.0), x_euler(n, 0.0), y_euler(n, 0.0), z_euler(n, 0.0), x_rk4(n, 0.0), y_rk4(n, 0.0), z_rk4(n, 0.0) ;

    // Initial conditions
    t[0] = 0;
    x_euler[0] = 0.1;
    y_euler[0] = 0.1;
    z_euler[0] = 0.1;
    x_rk4[0] = 0.1 ;
    y_rk4[0] = 0.1 ;
    z_rk4[0] = 0.1 ;

    for (int i = 0 ; i < n-1 ; i++) t[i+1] = t[i] + h ;

    // Euler method
    Euler(t, x_euler, y_euler, z_euler, r, s, b, n, h);
    RK4(t , x_rk4 , y_rk4 , z_rk4, r, s, b, n, h) ;
    
    // Plot results
    // Time_Series(t, x_euler, y_euler, z_euler, n);
    Time_Series(t , x_rk4 , y_rk4 , z_rk4, n) ;
    // State_Space(x_euler , y_euler , z_euler , n) ;
    State_Space(x_rk4 , y_rk4 , z_rk4, n) ;

    return 0;
}
