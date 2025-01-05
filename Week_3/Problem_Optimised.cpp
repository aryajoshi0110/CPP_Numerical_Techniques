#include <iostream>
#include <vector>
#include <Eigen/Sparse>
#include <fstream>
using namespace std;
using namespace Eigen;

void flatten(const vector<vector<double>>& grid, VectorXd& flat) {
    int n = grid.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            flat[i * n + j] = grid[i][j];
        }
    }
}

void flat2grid(const VectorXd& flat, vector<vector<double>>& grid) {
    int n = grid.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = flat[i * n + j];
        }
    }
}

void make_laplacian_operator(SparseMatrix<double>& M, int n) {
    vector<Triplet<double>> triplets;

    int N = n * n; // Total number of elements in the flattened grid
    for (int i = 0; i < N; i++) {
        triplets.emplace_back(i, i, -4); // Diagonal element
        
        if (i % n != 0) // Left neighbor
            triplets.emplace_back(i, i - 1, 1);
        
        if (i % n != n - 1) // Right neighbor
            triplets.emplace_back(i, i + 1, 1);
        
        if (i - n >= 0) // Top neighbor
            triplets.emplace_back(i, i - n, 1);
        
        if (i + n < N) // Bottom neighbor
            triplets.emplace_back(i, i + n, 1);
    }

    M.setFromTriplets(triplets.begin(), triplets.end());
}

int main() {
    int n = 100; // Grid size
    vector<vector<double>> cd_grid(n, vector<double>(n, 0.0));
    cd_grid[n / 2 ][n / 2 + 20] = 1.0;
    cd_grid[n / 2 ][n / 2 - 20] = -1.0;

    for (int i = 0; i < n; i++){
        cd_grid[0][i] = 1.0;
        cd_grid[n - 1][i] = -1.0;
    }

    // Flatten the grid
    VectorXd cd_flat(n * n);
    flatten(cd_grid, cd_flat);

    // Create the sparse Laplacian matrix
    SparseMatrix<double> M(n * n, n * n);
    make_laplacian_operator(M, n);

    // Solve the system using Conjugate Gradient
    SparseLU<SparseMatrix<double>> solver;
    solver.compute(M);
    if (solver.info() != Success) {
        cout << "Decomposition failed!" << endl;
        return -1;
    }

    VectorXd U_flat = solver.solve(cd_flat);
    if (solver.info() != Success) {
        cout << "Solving failed!" << endl;
        return -1;
    }

    // Convert flat solution back to grid
    vector<vector<double>> U(n, vector<double>(n, 0.0));
    flat2grid(U_flat, U);

    // Output results to file
    ofstream field_file("Week_3/field.txt");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            field_file << U[i][j] << " ";
        }
	    field_file << "\n";
    }
    field_file.close();

    // ofstream field_file("Week_3/field.txt");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //     field_file << i << " " << j << " " << U[i][j] << '\n' ;
    //     }
    // }
    // field_file.close();

    return 0;
}
