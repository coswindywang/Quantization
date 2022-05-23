#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <ctime>
#include <cmath>
#define nan 1e-9
using namespace std; 
const int N = 1001;
float A[N][N] , B[N][N] , Q[N][N] , res[N][N];
int8_t q_a[N][N] , q_b[N][N] ;
short P[N][N];
int m , n , k;

float val_min , val_max;



int main(){
    int seeda , seedb ;
    cout << "please input m , k , n (as the dimension of mat A and B) :" ;
    cin >> m >> k >> n;
    cout << endl << "plese input val_min and val_max as the value of the two mats : ";
    cin >> val_min >> val_max;
    cout << endl;
    cout << "please input the seeds to generate mat A and B: ";
    cin >> seeda >> seedb;
    cout << endl;

    ofstream ofa , ofb;
    ofa.open("a.txt");
    ofb.open("b.txt");
    ofstream qa , qb ;
    qa.open("a_q.txt");
    qb.open("b_q.txt");
    // generate mat
    std::default_random_engine rea(seeda);
    uniform_real_distribution<float> disa(val_min , val_max);
    for (int i = 0 ; i < m ; i ++)
    {
        for (int j = 0 ; j < k ; j ++)
        {
            A[i][j] = disa(rea) ;
            ofa << fixed << setprecision(20) << A[i][j] << " ";
            q_a[i][j] = int8_t(((255)/(val_max - val_min)) * A[i][j]);
            qa << int(q_a[i][j]) << " " ;
        }
        ofa << endl;
        qa << endl;
    }
   
    std::default_random_engine reb(seedb);
    uniform_real_distribution<float> disb(val_min , val_max);
    for (int i = 0 ; i < k ; i ++)
    {
        for (int j = 0 ; j < n ; j ++)
        {
            B[i][j] = disb(reb) ;
            ofb << fixed << setprecision(20) << B[i][j] << " ";
            q_b[i][j] = int8_t(((255)/(val_max - val_min)) * B[i][j]);
            qb << int(q_b[i][j]) << " ";
        }
        ofb << endl;
        qb << endl;
    }
    ofa.close();
    ofb.close();
    qa.close();
    qb.close();
    // matmul
    for (int i = 0 ; i < m ; i ++){
        for (int j = 0 ; j < n ; j ++){
            float ans = 0;
            short wyh = 0;
            for (int x = 0 ; x < k ; x ++){
                ans += A[i][x] * B[x][j];
                wyh +=q_a[i][x] * q_b[x][j];
            }
            res[i][j] = ans;
            P[i][j] = wyh;
        }
    }
    
    ofstream output , op;
    op.open("p.txt");
    output.open("output.txt");
    for (int i = 0 ; i < m ; i ++)
    {
        for (int j = 0 ; j < n; j++){
            output << fixed << setprecision(20) << res[i][j] << " ";
            op << P[i][j] << " ";
        }
        output << endl;
        op << endl;
    }
    output.close();
    op.close();
    //requantify
   
    ofstream oq;
    oq.open("output_q.txt");
    for (int i = 0 ; i < m ; i ++){
        for (int j = 0; j < n ; j ++){
            Q[i][j] = float(P[i][j]*(val_max - val_min) * (val_max - val_min)/65505.0);
            oq << fixed << setprecision(20) << Q[i][j] << " ";
            //cout << fixed << setprecision(20) << Q[i][j] << " ";
           
        }
        oq << endl;
        
    }
    
    oq.close();

 
    // calculate the diff between Q[][] and res[][]
    double diff1 , diff2 ,diff3;
    double up = 0 , down = nan;
    double up_ = 0 , down_ = nan;
    diff3 = 0;
    for (int i = 0 ; i < m ; i ++){
        for (int j = 0 ; j < n ; j ++){
            up += abs(Q[i][j] - res[i][j]);
            down += abs(res[i][j]);
            up_ += (Q[i][j] - res[i][j]) * (Q[i][j] - res[i][j]);
            down_ += res[i][j] * res[i][j];
            diff3 = max(diff3 , abs(Q[i][j]-res[i][j]) / abs(res[i][j] + nan));
        }
    }
    diff1 = double(up / down);
    diff2 = double(sqrt(up / down));
    cout << fixed << setprecision(20) << " the diff1 of matmul quantization is : " << diff1 << endl;
    cout << fixed << setprecision(20) << " the diff2 of matmul quantization is : " << diff2 << endl;
    cout << fixed << setprecision(20) << " the diff3 of matmul quantization is : " << diff3 << endl;





    return 0;

}