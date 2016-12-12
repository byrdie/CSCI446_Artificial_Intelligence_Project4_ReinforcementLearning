
#include "value_it.h"

Value_ItAgent::Value_ItAgent(uint xsize, uint ysize, double delt, double gam, double eps) : Agent(),
U(xsize, vector<vector<vector<vector<vector<double>>>>>(ysize, vector<vector<vector<vector<double>>>>(NUM_VEL, vector<vector<vector<double>>>(NUM_VEL, vector<vector<double>>(NUM_ACC, vector<double>(NUM_ACC, 0.0)))))),
UP(xsize, vector<vector<vector<vector<vector<double>>>>>(ysize, vector<vector<vector<vector<double>>>>(NUM_VEL, vector<vector<vector<double>>>(NUM_VEL, vector<vector<double>>(NUM_ACC, vector<double>(NUM_ACC, 0.0)))))),
opos(QNULL, QNULL), ovel(QNULL, QNULL), oacc(QNULL, QNULL) {

    delta = delt;
    gamma = gam;
    epsilon = eps;

}

Point Value_ItAgent::next_accel(const Point& pos, const Point& vel, const double reward, const bool terminate) {


    //    do {


    //        U = UP;
    //        delta = 0;
    //        
    //        double max_a = -1e6;
    //        for (uint i = 0; i < NUM_ACC; i++) {
    //            for (uint j = 0; j < NUM_ACC; j++) {
    //                
    //                
    //                double test = U[pos.x][pos.y][v2i(vel.x)][v2i(vel.y)][i][j];
    //                // Utility Equation
    //                // U'(s) = R(s) + gamma max a in A(s) * sum of (P(s'|s,a)*U(s') for all s'
    //                // NEEDS UBER ATTENTION!
    //                
    //                UP[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][a2i(oacc.x)][a2i(oacc.y)]
    //                         = reward + (gamma * .9 * max_a );
    //                
    //                
    //                if (test > max_a) {
    //                    max_a = test;
    //                }
    //                
    //                double diff = UP[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][i][j] - U[opos.x][opos.y][v2i(ovel.x)][v2i(ovel.y)][i][j];
    //                
    //                // if absolute value of the difference between U and U'
    //                //   is > delta, then delta = that difference
    //                // else, delta remains the same
    //                
    //                if (diff < 0) {
    //                    diff = diff * (-1);
    //                }
    //                if (diff > delta) {
    //                    delta = diff;
    //                }
    //                
    //                
    //            }
    //        
    //        }
    //    // repeat until delta < epsilon(1-gamma)/gamma    
    //    
    //    } while (delta < (epsilon * ((1 - gamma) / gamma)));
    //    
    //    opos = pos;
    //    ovel = vel;
    //    orwd = reward;
    //    
    //    // return U Vector
    //    return U;
    //    

}

void Value_ItAgent::val_iteration(World * world) {
    
    //gamma, epsilon, and delta are class variables
    //initialize rewards
    reward = get_reward(world->world_vec);
    //get list of states that contain track
    vector <vector < uint>>track_vals = track_val(world->world_vec);
    

    do {
        //update u and set delta back to zero
        U = UP;
        delta = 0;
        //iterate over every state that is part of the track
        for (uint i = 0; i < track_vals.size(); i++) {

            //iterate over each velocity
            for (uint j = 0; j < NUM_VEL; j++) {
                for (uint k = 0; k < NUM_VEL; k++) {
                    //iterate over each accelleration. Note we save all utilities rather than just the max one
                    for (uint l = 0; l < NUM_ACC; l++) {
                        for (uint m = 0; m < NUM_ACC; m++) {
                            //calculate if acceleration works
                            double works = .8 *(utility(track_vals[i][0], track_vals[i][1], j, k, l, m));
                            //calculate if acceleration does not work
                            double d_work = .2 * (utility(track_vals[i][0], track_vals[i][1], j, k, 0, 0));
                            //set utility using bellman equation
                            UP[track_vals[i][0]][track_vals[i][1]][j][k][l][m] = reward[track_vals[i][0]][track_vals[i][1]] + (gamma *(works + d_work));
                            //update delta
                            if((UP[track_vals[i][0]][track_vals[i][1]][j][k][l][m] - U[track_vals[i][0]][track_vals[i][1]][j][k][l][m]) > delta){
                                delta = UP[track_vals[i][0]][track_vals[i][1]][j][k][l][m] - U[track_vals[i][0]][track_vals[i][1]][j][k][l][m];
                            }
                        }
                    }



                }
            }
        }
    } while (delta < (epsilon*(1-gamma)/gamma));

}

double Value_ItAgent::utility(uint x, uint y, uint vel_x, uint vel_y, uint act_x, uint act_y) {
    //return utility for given state, velocity, and accellerations
    vector<uint> vels = calc_vel(vel_x, vel_y, act_x, act_y);
    vel_x = vels[0];
    vel_y = vels[1];
    
    x = x + vel_x;
    y = x + vel_y;
    if(x > U.size() || y > U.size() || x < 0 || y < 0){
        
    }else{
        double max_util = U[x][y][vel_x][vel_y][0][0];
        for(uint i = 0; i < NUM_ACC; i++){
            for(uint j = 0; j < NUM_ACC; i++){
                if (max_util < U[x][y][vel_x][vel_y][i][j]){
                    max_util = U[x][y][vel_x][vel_y][i][j];
                }
            }
        }
        return max_util;
    }
    

}

vector<uint> Value_ItAgent::calc_vel(uint vel_x, uint vel_y, uint act_x, uint act_y) {
    //calculate x and y velocities given an acceleration
    vector<uint> n_vel;
    if (((vel_x + act_x) < MAX_VEL) && ((vel_x + act_x) > MIN_VEL)) {
        vel_x = vel_x + act_x;
    }

    if (((vel_y + act_y) < MAX_VEL) && ((vel_y + act_y) > MIN_VEL)) {
        vel_y = vel_y + act_y;
    }
    n_vel.push_back(vel_x);
    n_vel.push_back(vel_y);
}

vector<vector<uint>> Value_ItAgent::track_val(vector<vector<uint>> track) {
    //find and return list of states that are part of the track
    vector<vector < uint>> track_vals;
    for (uint i = 0; i < track.size(); i++) {
        for (uint j = 0; j < track[0].size(); j++) {
            if (track[i][j] == TRACK || track[i][j] == START) {
                vector<uint> temp;
                temp.push_back(i);
                temp.push_back(j);
                track_vals.push_back(temp);
            }
        }
    }
    return track_vals;
}

vector<vector<double>> Value_ItAgent::get_reward(vector<vector<uint>> track) {
    //update rewards for all cells
    vector<vector<double>> reward;
    for (uint i = 0; i < track.size(); i++) {
        vector<double> temp;
        reward.push_back(temp);
        for (uint j = 0; j < track[0].size(); j++) {
            if ((track[i][j] == TRACK)||(track[i][j] == WALL)||(track[i][j] == START)) {
                reward[i].push_back(-.04);
            } else if (track[i][j] == FINISH) {
                reward[i].push_back(1.0);
            }
        }
    }
    return reward;
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
