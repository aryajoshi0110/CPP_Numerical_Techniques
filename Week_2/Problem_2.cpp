#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
using namespace std;

double x_(double t, double x, double y, double mu) {
    return mu * (x - pow(x, 3) / 3 - y);
}

double y_(double t, double x, double y, double mu) {
    return x / mu;
}

void Euler(vector<double>& t, vector<double>& x, vector<double>& y, int n, double h, double mu) {
    for (int i = 0; i < n - 1; i++) {
        x[i + 1] = x[i] + x_(t[i], x[i], y[i], mu) * h;
        y[i + 1] = y[i] + y_(t[i], x[i], y[i], mu) * h;
    }
}

void RK4(vector<double>& t, vector<double>& x, vector<double>& y, int n, double h, double mu) {
    for (int i = 0; i < n - 1; i++) {
        t[i + 1] = t[i] + h;
        double x1 = x_(t[i], x[i], y[i], mu);
        double y1 = y_(t[i], x[i], y[i], mu);
        double x2 = x_(t[i] + h / 2, x[i] + h * x1 / 2, y[i] + h * y1 / 2, mu);
        double y2 = y_(t[i] + h / 2, x[i] + h * x1 / 2, y[i] + h * y1 / 2, mu);
        double x3 = x_(t[i] + h / 2, x[i] + h * x2 / 2, y[i] + h * y2 / 2, mu);
        double y3 = y_(t[i] + h / 2, x[i] + h * x2 / 2, y[i] + h * y2 / 2, mu);
        double x4 = x_(t[i] + h, x[i] + h * x3, y[i] + h * y3, mu);
        double y4 = y_(t[i] + h, x[i] + h * x3, y[i] + h * y3, mu);

        x[i + 1] = x[i] + h * (x1 + 2 * x2 + 2 * x3 + x4) / 6;
        y[i + 1] = y[i] + h * (y1 + 2 * y2 + 2 * y3 + y4) / 6;
    }
}

void Time_Series(const vector<double>& t, const vector<double>& x, const vector<double>& y, int n) {
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
    fprintf(gnuplotPipe, "set yrange [-3:3]\n") ;
    fprintf(gnuplotPipe, "plot '-' title 'x(t)' with lines, '-' title 'y(t)' with lines\n");

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

    // Close the pipe
    pclose(gnuplotPipe);
}

void State_Space(const vector<double>& x, const vector<double>& y, int n) {
    // Open a pipe to Gnuplot
    FILE* gnuplotPipe = popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error: Could not open pipe to Gnuplot.\n";
        return;
    }

    // Send commands to Gnuplot
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Van der Pol Oscillator'\n");
    fprintf(gnuplotPipe, "set xlabel 'X position'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y Position'\n");
    fprintf(gnuplotPipe, "plot '-' title 'State Space' with lines\n");

    // Send data for x(t)
    for (int i = 0; i < n; i++) {
        fprintf(gnuplotPipe, "%f %f\n", x[i], y[i]);
    }
    fprintf(gnuplotPipe, "e\n");  // End of x data
}

int main() {
    double h = 0.1, mu = 7;
    int n = static_cast<int>(500 / h) + 1;

    vector<double> t(n, 0.0), x_euler(n, 0.0), y_euler(n, 0.0), x_rk4(n, 0.0), y_rk4(n, 0.0);

    // Initial conditions
    t[0] = 0;
    x_euler[0] = 0.1;
    y_euler[0] = 0.1;
    x_rk4[0] = 0.5 ;
    x_rk4[0] = 0.5 ;

    for (int i = 0 ; i < n-1 ; i++) t[i+1] = t[i] + h ;

    // Euler method
    Euler(t, x_euler, y_euler, n, h, mu);
    RK4(t , x_rk4 , y_rk4 , n , h , mu) ;

    // Plot results
    // Time_Series(t, x_euler, y_euler, n);
    Time_Series(t , x_rk4 , y_rk4 , n) ;
    // State_Space(x_euler , y_euler , n) ;
    State_Space(x_rk4 , y_rk4 , n) ;

    return 0;
}
