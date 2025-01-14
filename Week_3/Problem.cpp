#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
using namespace std;

void flatten (const vector<vector<double>>& grid , vector<double>& flat){
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[i].size(); j++){
            flat[grid.size()*i + j] = grid[i][j];
        }
    }
}

void flat2grid (const vector<double>& flat , vector<vector<double>>& grid){
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[i].size(); j++){
            grid[i][j] = flat[grid.size()*i + j] ;
        }
    }
}

void make_laplacian_operator (vector<vector<double>>& M){
    // vector<double> M_flat (M.size()*M.size(),0.0) ;
    int n = pow(M.size(),0.5);
    for (int i = 0; i < M.size(); i++){
            M[i][i] = 4;

            if (i%n == 0){
                M[i][i+1] = -1;
            }
            else if (i%n == n-1){
                M[i][i-1] = -1;
            }
            else{
                M[i][i-1] = -1;
                M[i][i+1] = -1;
            }
            

            if (i-n >= 0 and i+n < M[i].size()){
            M[i][i-n] = -1;
            M[i][i+n] = -1;
            }
            else if (i-n >= 0){
                M[i][i-n] = -1;
            }
            else{
                M[i][i+n] = -1;
        }
    }
}

float diff_btw_vectors ( const vector<double>& a , const vector<double>& b )
{
    float sum_of_sq = 0 ;
    for (int i = 0; i < a.size(); i++)
    {
        sum_of_sq += pow(a[i]-b[i],2) ;
    }
    return pow(sum_of_sq,0.5) ;
}

void Gauss_Siedel ( const vector<vector <double>>& M , vector<double>& U_flat, const vector<double>& rho_flat ){
    cout << "Gauss-Siedel Method" << endl ;
    int k=0;
    float tolerance = pow(10,-6) ;

    vector<double> xk(U_flat.size(),0.0), xk1(U_flat.size(),0.0) ;
    // for (int i = 0; i < n; i++) xk[i] = U[i] ;

    for (int i = 0; i < M.size(); i++){
            float sum = 0;
            for (int j = 0; j < i; j++){
                sum += M[i][j]*xk1[j] ;
            }
            for (int j = i+1; j < M[i].size(); j++){
                sum += M[i][j]*xk[j] ;
            }
            
            xk1[i] = ( rho_flat[i] - sum )/M[i][i] ;
        }

    while ( diff_btw_vectors( xk , xk1) >= tolerance ){   
        // cout << k << endl ;
        for (int i = 0; i < xk.size(); i++) xk[i] = xk1[i] ; 
        for (int i = 0; i < xk.size(); i++){
            float sum = 0;
            for (int j = 0; j < i; j++){
                sum += M[i][j]*xk1[j] ;
            }
            for (int j = i+1; j < xk.size(); j++){
                sum += M[i][j]*xk[j] ;
            }
            
            xk1[i] = ( rho_flat[i] - sum )/M[i][i] ;
        }
        // k++ ;
        // cout << k << " " ;
    }

    for (int i = 0; i < xk.size(); i++) U_flat[i] = xk1[i] ; 

}

int main(){

    int n = 100 ;
    vector<vector<double>> cd_grid (n , vector<double> (n,0.0)), different (n , vector<double> (n,0.0)) ;
    cd_grid[n/2 + 10][n/2] = 1.0;
    cd_grid[n/2 - 10][n/2] = -1.0;

    for (int i = 0; i < n; i++){
        cd_grid[0][i] = 1.0;
        cd_grid[n - 1][i] = -1.0;
    }

    // for (int i = 0; i < n; i++){
    //     for (int j = 0; j < n; j++){
    //         cout << " " << cd_grid[i][j] << " " ; 
    //     }
    //     cout << "\n" ;
    // }
    vector<double> cd_flat (n*n, 0.0);

    // // cout << cd_grid[0].size();

    flatten(cd_grid, cd_flat) ;

    // cout << endl ;

    // for (int i = 0; i < flat.size(); i++){
        // cout << flat[i] << " " ;
    // }

    // cout << endl;
    
    vector<vector<double>> M(n*n , vector<double> (n*n,0.0));
    make_laplacian_operator(M);

    // for (int i = 0; i < M.size(); i++){
    //     for (int j = 0; j < M[i].size(); j++){
    //         cout << M[i][j] << " " ; 
    //     }
    //     cout << "\n" ;
    // }

    vector<double> U_flat(n*n,0.0);
    vector<vector <double>> U(n , vector<double> (n,0.0)) ;

    Gauss_Siedel(M , U_flat , cd_flat) ;
    
    flat2grid(U_flat , U) ;

    // ofstream field_file("Week_3/field.txt");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //     field_file << i << " " << j << " " << U[i][j] << '\n' ;
    //     }
    // }
    // field_file.close();

    ofstream field_file("Week_3/field.txt");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            field_file << U[i][j] << " ";
        }
	    field_file << "\n";
    }
    field_file.close();

    return 0;
}