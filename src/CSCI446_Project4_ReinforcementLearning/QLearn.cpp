
/* 
 * File:   QLearn.h
 * Author: byrdie
 *
 * Created on December 8, 2016, 2:19 PM
 */

#include "QLearn.h"

QLearningAgent::QLearningAgent(uint xsize, uint ysize, double alp, double gam) : Agent(),
Q(xsize, vector<vector<vector<vector<vector<double>>>>>(ysize, vector<vector<vector<vector<double>>>>(NUM_VEL, vector<vector<vector<double>>>(NUM_VEL, vector<vector<double>>(NUM_ACC, vector<double>(NUM_ACC)))))),
N(xsize, vector<vector<vector<vector<vector<uint>>>>>(ysize, vector<vector<vector<vector<uint>>>>(NUM_VEL, vector<vector<vector<uint>>>(NUM_VEL, vector<vector<uint>>(NUM_ACC, vector<uint>(NUM_ACC)))))),
opos(QNULL, QNULL), ovel(QNULL, QNULL), oacc(QNULL, QNULL) {

    alpha = alp;
    gamma = gam;


}

Point QLearningAgent::next_accel(const Point& pos, const Point& vel, const int reward, const bool terminate) {

    if (terminate) {

    }

}

Point QLearningAgent::exploration_function(const Point& pos, const Point& vel, const Point& act){
    if(N[pos.x][pos.y][vel.x][vel.y][act.x][act.y] > MAX_FREQ ){
        
    }
}
