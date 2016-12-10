
/* 
 * File:   QLearn.h
 * Author: byrdie
 *
 * Created on December 8, 2016, 2:19 PM
 */

#include "QLearn.h"

QLearningAgent::QLearningAgent(uint xsize, uint ysize, double alp, double gam) : Agent(),
Q(xsize, vector<vector<vector<vector<vector<double>>>>>(ysize, vector<vector<vector<vector<double>>>>(NUM_VEL, vector<vector<vector<double>>>(NUM_VEL, vector<vector<double>>(NUM_ACC, vector<double>(NUM_ACC, 0.0)))))),
N(xsize, vector<vector<vector<vector<vector<uint>>>>>(ysize, vector<vector<vector<vector<uint>>>>(NUM_VEL, vector<vector<vector<uint>>>(NUM_VEL, vector<vector<uint>>(NUM_ACC, vector<uint>(NUM_ACC,0.0)))))),
opos(QNULL, QNULL), ovel(QNULL, QNULL), oacc(QNULL, QNULL) {

    alpha = alp;
    gamma = gam;


}

Point QLearningAgent::next_accel(const Point& pos, const Point& vel, const double rwd, const bool terminate) {

    /* if Terminal?(s) then */
    if (terminate) {

        /* Q[s, None] <- r' */
        Q[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][a2i(0)][a2i(0)] = rwd;
    }

    /* if s is not null then */
    if (opos.x != QNULL) {

        /* increment N[s,a] */
        N[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][a2i(oacc.x)][a2i(oacc.y)]++;

        /* Compute max_a' Q[s',a'] */
        cout << "Compute max_a' Q[s',a']\n";
        double max_a_Q = 0.0;
        for (uint i = 0; i < NUM_ACC; i++) {
            for (uint j = 0; j < NUM_ACC; j++) {
                double test = Q[pos.x][pos.y][v2i(vel.x)][v2i(vel.y)][i][j];
                cout << "    Testing Q[" << pos.x << "][" << pos.y << "][" << vel.x << "][" << vel.y << "][" << i2a(i) << "][" << i2a(j) << "] = " << test<< "\n";
                if (test > max_a_Q) {
                    max_a_Q = test;
                } else if(test = max_a_Q){
                    
                }
            }
        }

        /* Evaluate the update rule */
        /* Q[s,a] <- Q[s,a] + alpha (N[s,a])(r + gamma max_a' Q[s',a'] - Q[s,a]) */
        Q[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][a2i(oacc.x)][a2i(oacc.y)]
                = Q[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][a2i(oacc.x)][a2i(oacc.y)]
                + alpha * N[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][a2i(oacc.x)][a2i(oacc.y)]
                * (orwd + gamma * max_a_Q - Q[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][a2i(oacc.x)][a2i(oacc.y)]);
        
        cout << "Updated Q[" << opos.x << "][" << opos.y << "][" << ovel.x << "][" << ovel.y << "][" << oacc.x << "][" << oacc.y << "] = " 
                << Q[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][a2i(oacc.x)][a2i(oacc.y)] << "\n";
        
    }

    /* Compute argmax_a' f(Q[s',a'], N[s',a']) */
    cout << "Compute argmax_a' f(Q[s',a'], N[s',a'])\n";
    double max_a_f = -1e6;
    vector<Point> acc_lst;
    for (uint i = 0; i < NUM_ACC; i++) {
        for (uint j = 0; j < NUM_ACC; j++) {
            double test = exploration_function(Q[pos.x][pos.y][v2i(vel.x)][v2i(vel.y)][i][j], N[pos.x][pos.y][v2i(vel.x)][v2i(vel.y)][i][j]);
            
            cout << "    Testing f(Q[" << pos.x << "][" << pos.y << "][" << vel.x << "][" << vel.y << "][" << i2a(i) << "][" << i2a(j) << "], " << "N[" << pos.x << "][" << pos.y << "][" << vel.x << "][" << vel.y << "][" << i2a(i) << "][" << i2a(j) << "]) = " << test<< "\n";
            
            if (test > max_a_f) {
                max_a_f = test;
                acc_lst.clear();
                acc_lst.push_back(Point(i2a(i),i2a(j)));
            } else if(test = max_a_f){
                acc_lst.push_back(Point(i2a(i),i2a(j)));
            }
        }
    }

    /* select a ranom acceleration from the argmax'es */
    cout << acc_lst.size() << endl;
    Point acc = acc_lst[rand() % acc_lst.size()];

    /* update variables */
    opos = pos;
    ovel = vel;
    oacc = acc;
    orwd = rwd;
    
    cout << "Requested ax = " << acc.x << ", ay = " << acc.y << endl;
    cout << "______________________________________________________\n";

    return acc;

}

double QLearningAgent::exploration_function(double q_val, uint freq) {
    if (freq < MAX_FREQ) {
        return MAX_UTILITY;
    } else {
        return q_val;
    }
}

uint QLearningAgent::a2i(int a) {
    return a - MIN_ACC;
}

uint QLearningAgent::v2i(int v) {
    return v - MIN_VEL;
}

int QLearningAgent::i2a(uint i){
    return i + MIN_ACC;
}

int QLearningAgent::i2v(uint i){
    return i + MIN_VEL;
}