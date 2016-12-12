
#include "value_it.h"

Value_ItAgent::Value_ItAgent(uint xsize, uint ysize, double delt, double gam, double eps) : Agent(),
U(xsize, vector<vector<vector<vector<vector<double>>>>>(ysize, vector<vector<vector<vector<double>>>>(NUM_VEL, vector<vector<vector<double>>>(NUM_VEL, vector<vector<double>>(NUM_ACC, vector<double>(NUM_ACC, 0.0)))))),
UP(xsize, vector<vector<vector<vector<vector<uint>>>>>(ysize, vector<vector<vector<vector<uint>>>>(NUM_VEL, vector<vector<vector<uint>>>(NUM_VEL, vector<vector<uint>>(NUM_ACC, vector<uint>(NUM_ACC, 0.0)))))),
opos(QNULL, QNULL), ovel(QNULL, QNULL), oacc(QNULL, QNULL) {

    delta = delt;
    gamma = gam;
    epsilon = eps;

}
        
        
Point Value_ItAgent::next_accel(const Point& pos, const Point& vel, const double reward, const bool terminate){
    
    
    do {
        
        
        U = UP;
        delta = 0;
        
        double max_a = -1e6;
        for (uint i = 0; i < NUM_ACC; i++) {
            for (uint j = 0; j < NUM_ACC; j++) {
                
                
                double test = U[pos.x][pos.y][v2i(vel.x)][v2i(vel.y)][i][j];
                // Utility Equation
                // U'(s) = R(s) + gamma max a in A(s) * sum of (P(s'|s,a)*U(s') for all s'
                // NEEDS UBER ATTENTION!
                
                UP[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][a2i(oacc.x)][a2i(oacc.y)]
                         = reward + (gamma * .9 * max_a );
                
                
                if (test > max_a) {
                    max_a = test;
                }
                
                double diff = UP[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][i][j] - U[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][i][j];
                
                // if absolute value of the difference between U and U'
                //   is > delta, then delta = that difference
                // else, delta remains the same
                
                if (diff < 0) {
                    diff = diff * (-1);
                }
                if (diff > delta) {
                    delta = diff;
                }
                
                
            }
        
        }
    // repeat until delta < epsilon(1-gamma)/gamma    
    
    } while (delta < (epsilon * ((1 - gamma) / gamma)));
    
    opos = pos;
    ovel = vel;
    orwd = reward;
    
    // return U Vector
    return U;
    
    
}

uint Value_ItAgent::a2i(int a) {
    return a - MIN_ACC;
}

uint Value_ItAgent::v2i(int v) {
    return v - MIN_VEL;
}

int Value_ItAgent::i2a(uint i) {
    return i + MIN_ACC;
}

int Value_ItAgent::i2v(uint i) {
    return i + MIN_VEL;
}
