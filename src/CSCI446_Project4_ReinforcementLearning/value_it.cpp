
#include "value_it.h"


Value_ItAgent::Value_ItAgent(uint xsize, uint ysize, double delt, double gam, double eps) : Agent(),
U(xsize, vector<vector<vector<vector<vector<double>>>>>(ysize, vector<vector<vector<vector<double>>>>(NUM_VEL, vector<vector<vector<double>>>(NUM_VEL, vector<vector<double>>(NUM_ACC, vector<double>(NUM_ACC, 0.0)))))),
UP(xsize, vector<vector<vector<vector<vector<double>>>>>(ysize, vector<vector<vector<vector<double>>>>(NUM_VEL, vector<vector<vector<double>>>(NUM_VEL, vector<vector<double>>(NUM_ACC, vector<double>(NUM_ACC, 0.0)))))),
opos(QNULL, QNULL), ovel(QNULL, QNULL), oacc(QNULL, QNULL) {

    delta = delt;
    gamma = gam;
    epsilon = eps;

}

Point Value_ItAgent::next_accel(const Point& pos, const Point& vel, const double reward, const bool terminate, bool debug) {
//    if (iter == 0) {
//        out << "_________________________________\n__________________\n\n";
//        out << "Running:\n\n";
//    }
//    iter++;



//    out << "\n";
//
//    out << "MOVE: " << iter << "\n";
//    out << "    x = " << pos.x << ", y = " << pos.y << "\n";
//    out << "    vel_x = " << vel.x << ", vel_y = " << vel.y << "\n";
    Point accel(0, 0);
    vector<vector < int>> choices;
    double max_ut;
    for (uint i = 0; i < NUM_ACC; i++) {
        for (uint j = 0; j < NUM_ACC; j++) {
//            out << "Accelleration = " << i2a(i) << ", " << i2a(j) << " ";
//            out << "Utility = " << U[pos.x][pos.y][v2i(vel.x)][v2i(vel.y)][i][j] << "\n";
            if (U[pos.x][pos.y][v2i(vel.x)][v2i(vel.y)][i][j] > U[pos.x][pos.y][v2i(vel.x)][v2i(vel.y)][accel.x][accel.y]) {
                choices.clear();
                vector<int> temp;
                temp.push_back(i);
                temp.push_back(j);
                choices.push_back(temp);
                max_ut = U[pos.x][pos.y][v2i(vel.x)][v2i(vel.y)][i][j];
                accel.x = i;
                accel.y = j;

            } else if (U[pos.x][pos.y][v2i(vel.x)][v2i(vel.y)][i][j] == U[pos.x][pos.y][v2i(vel.x)][v2i(vel.y)][accel.x][accel.y]) {
                vector<int> temp;
                temp.push_back(i);
                temp.push_back(j);
                choices.push_back(temp);
            }
        }
    }
    vector<int> accels = choices[rand() % choices.size()];
    accel.x = i2a(accels[0]);
    accel.y = i2a(accels[1]);

//    out << "    Max_Utility = " << max_ut << "\n";
//    out << "    Chosen Acceleration = " << accel.x << ", " << accel.y << "\n";
    iter++;
    return accel;



}

void Value_ItAgent::val_iteration(World * world) {
//    out << "______TRAINING______:" << "\n";
//    out << "To condense the output we only show the max utility and preferred acceleration\n for zero velocities\n\n";
    //gamma, epsilon, and delta are class variables
    //initialize rewards
    reward = get_reward(world->world_vec);
    //get list of states that contain track
    wd = world;
    vector <vector < uint>>track_vals = track_val(world->world_vec);
    int count = 0;
    //x == 25 && y == 2 && i2v(vel_x) == 0 && i2v(vel_y) == 0 && i2a(act_x) == -1 && i2a(act_y) == -1
        vector<vector<int>> test = affected_squares(25,2,5,0);
//        out<<test.size()<<"\n";
        for(uint i = 0; i<test.size(); i++){
//            out << test[i][0]<<", "<<test[i][1]<<"\n";
        }
    do {
        //out << "GENERATION: _________________________________________________________________________" << count << "\n";
        //update u and set delta back to zero
        U = UP;
        delta = 0;
        //iterate over every state that is part of the track
        for (uint i = 0; i < track_vals.size(); i++) {
            // out << "x_pos = " << track_vals[i][0] << ", y_pos = " << track_vals[i][1] << "\n";

            //iterate over each velocity
            for (uint j = 0; j < NUM_VEL; j++) {
                for (uint k = 0; k < NUM_VEL; k++) {
                    if (i2v(j) == 0 && i2v(k) == 0) {
                        //       out << "    vel_x = " << i2v(j) << ", vel_y = " << i2v(k) << "\n";
                    }
                    //iterate over  each accelleration. Note we save all utilities rather than just the max one
                    vector<int> max_acc(2, 0);
                    double max_ut = 0;
                    for (uint l = 0; l < NUM_ACC; l++) {
                        for (uint m = 0; m < NUM_ACC; m++) {
                            //calculate if acceleration works
                            double works = .8 * (utility(track_vals[i][0], track_vals[i][1], j, k, l, m));
                            //calculate if acceleration does not work
                            double d_work = .2 * (utility(track_vals[i][0], track_vals[i][1], j, k, 0, 0));
                            //set utility using bellman equation
                            UP[track_vals[i][0]][track_vals[i][1]][j][k][l][m] = reward[track_vals[i][0]][track_vals[i][1]] + (gamma * (works + d_work));
                            //update delta

                            if ((UP[track_vals[i][0]][track_vals[i][1]][j][k][l][m] - U[track_vals[i][0]][track_vals[i][1]][j][k][l][m]) > delta) {
                                delta = UP[track_vals[i][0]][track_vals[i][1]][j][k][l][m] - U[track_vals[i][0]][track_vals[i][1]][j][k][l][m];

                            }
                            if (UP[track_vals[i][0]][track_vals[i][1]][j][k][l][m] > max_ut) {
                                max_acc[0] = i2a(l);
                                max_acc[1] = i2a(m);
                                max_ut = UP[track_vals[i][0]][track_vals[i][1]][j][k][l][m];
                            }
                            //                            if ((i2v(j) == 0)&& (i2v(k) == 0)) {
                            //                                cout << "accel " << i2a(l) << "," << i2a(m) << endl;
                            //                                cout << "point " << track_vals[i][0] << "," << track_vals[i][1] << endl;
                            //                                cout << works << endl << endl;
                            //                            }
                        }
                    }
                    if (i2v(j) == 0 && i2v(k) == 0) {
                        //   out << "        Max Utility = " << max_ut << "\n";
                        //  out << "        Acceleration = " << max_acc[0] << ", " << max_acc[1] << "\n";
                    }

                }
            }
        }
        U = UP;
        count++;
        //out << delta << "\n";

    } while (delta > (epsilon * (1 - gamma) / gamma));

}

double Value_ItAgent::utility(uint x, uint y, uint vel_x, uint vel_y, uint act_x, uint act_y) {
    //return utility for given state, velocity, and accellerations
    vector<int> vels = calc_vel(i2v(vel_x), i2v(vel_y), i2a(act_x), i2a(act_y));
    int i_vel_x = vels[0];
    int i_vel_y = vels[1];
    int i_x = x + i_vel_x;
    int i_y = y + i_vel_y;
    //if out of bounds
    if (i_x >= U.size() || i_y >= U[0].size() || i_x < 0 || i_y < 0) {
        if (did_finish(affected_squares(x, y, i_vel_x, i_vel_y))) {
            //return 1.0;
            return 0;
        } else {
            vel_x = 0;
            vel_y = 0;

            double max_util = U[x][y][vel_x][vel_y][0][0];

            for (uint i = 0; i < NUM_ACC; i++) {
                for (uint j = 0; j < NUM_ACC; j++) {


                    if (max_util < U[x][y][vel_x][vel_y][i][j]) {
                        max_util = U[x][y][vel_x][vel_y][i][j];
                    }
                }
            }
            return 0;
        }

    } else {

        //if (did_finish(affected_squares(x, y, i_vel_x, i_vel_y)) || wd->world_vec[i_x][i_y] == FINISH) {
                    if ( wd->world_vec[i_x][i_y] == FINISH) {
//            if (x == 25 && y == 2 && i2v(vel_x) == 0 && i2v(vel_y) == 0 && i2a(act_x) == -1 && i2a(act_y) == -1) {
//                out << "finish\n";
//            }
            return 1.0;

        } else if (hit_wall(affected_squares(x, y, i_vel_x, i_vel_y)) || wd->world_vec[i_x][i_y] == WALL) {
//            if (x == 5 && y == 25 && i2v(vel_x) == 0 && i2v(vel_y) == 0 && i2a(act_x) == 1 && i2a(act_y) == 1) {
//                out << "wall\n";
//            }
            double max_util = U[x][y][vel_x][vel_y][0][0];
            for (uint i = 0; i < NUM_ACC; i++) {
                for (uint j = 0; j < NUM_ACC; j++) {
                    if (max_util < U[x][y][vel_x][vel_y][i][j]) {
                        max_util = U[x][y][vel_x][vel_y][i][j];
                    }
                }
            }
            return 0;
        } else {
            x = uint(i_x);
            y = uint(i_y);
            vel_x = v2i(i_vel_x);
            vel_y = v2i(i_vel_y);
            //cout << U.size() << endl;
            //cout <<  x << ", " << y << ", " << i_vel_x << ", " << i_vel_y <<endl;
            double max_util = U[x][y][vel_x][vel_y][0][0];
            for (uint i = 0; i < NUM_ACC; i++) {
                for (uint j = 0; j < NUM_ACC; j++) {
                    if (max_util < U[x][y][vel_x][vel_y][i][j]) {
                        max_util = U[x][y][vel_x][vel_y][i][j];
                    }
                }
            }
            //out << max_util << "\n";
            return max_util;
        }
    }


}

bool Value_ItAgent::did_finish(vector<vector<int>> crossed_states) {
    for (uint i = 0; i < crossed_states.size(); i++) {
        //cout <<crossed_states.size() << endl;
        if (crossed_states[i][0] > 0 && crossed_states[i][1] > 0 && crossed_states[i][0] < wd->world_vec.size() && crossed_states[i][1] < wd->world_vec[0].size()) {
            if (wd->world_vec[crossed_states[i][0]][crossed_states[i][1]] == FINISH) {

                return true;

            }
        }
    }
    return false;
}

bool Value_ItAgent::hit_wall(vector<vector<int>> crossed_states) {
    for (uint i = 0; i < crossed_states.size(); i++) {
        if (crossed_states[i][0] > 0 && crossed_states[i][1] > 0 && crossed_states[i][0] < wd->world_vec.size() && crossed_states[i][1] < wd->world_vec[0].size()) {
            if (wd->world_vec[crossed_states[i][0]][crossed_states[i][1]] == WALL) {
                return true;
            }
        }
    }
    return false;
}

vector<vector<int>> Value_ItAgent::affected_squares(int x, int y, int acc_x, int acc_y) {
    vector<vector<int>> aff_sqrs;
    
    if (acc_x > 0) {
        for (int i = 1; i < acc_x + 1; i++) {
            int t_y;
            if (acc_y == 0) {
                t_y = 0;
            } else {
                t_y = floor((double) (acc_y / acc_x) * (double) (i));
            }
            vector<int> temp;
            temp.push_back(x + i);
            temp.push_back(y + t_y);
            aff_sqrs.push_back(temp);
        }
    } else if(acc_x < 0) {
        for (int i = -1; i > acc_x - 1; i--) {
            int t_y;
            if (acc_y == 0) {
                t_y = 0;
            } else {
                t_y = floor((double) (acc_y / acc_x) * (double) ( i));
            }
            vector<int> temp;
            temp.push_back(x + i);
            temp.push_back(y + t_y);
            aff_sqrs.push_back(temp);
        }
    }

    if (acc_y > 0) {
        for (int i = 1; i < acc_y + 1; i++) {
            int t_x;
            if (acc_x == 0) {
                t_x = 0;
            } else {

                t_x = floor((double) (1 / (double) ((double) acc_y / acc_x)) * (double) (i));
            }
            vector<int> temp;
            temp.push_back(x + t_x);
            temp.push_back(y + i);
            aff_sqrs.push_back(temp);

        }
    } else if(acc_y < 0) {
        for (int i = -1; i > acc_y - 1; i--) {
            int t_x;
            if (acc_x == 0) {
                t_x = 0;
            } else {
                t_x = floor((double) ((double) acc_y / acc_x) * (double) (i));
            }
            vector<int> temp;
            temp.push_back(x + t_x);
            temp.push_back(y + i);
            aff_sqrs.push_back(temp);
        }

    }
    return aff_sqrs;

}

vector<int> Value_ItAgent::calc_vel(int vel_x, int vel_y, int act_x, int act_y) {
    //calculate x and y velocities given an acceleration
    vector<int> n_vel;
    if (((vel_x + act_x) < MAX_VEL) && ((vel_x + act_x) > MIN_VEL)) {
        vel_x = vel_x + act_x;
    }

    if (((vel_y + act_y) < MAX_VEL) && ((vel_y + act_y) > MIN_VEL)) {
        vel_y = vel_y + act_y;
    }
    n_vel.push_back(vel_x);
    n_vel.push_back(vel_y);
    return n_vel;
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
            if ((track[i][j] == TRACK) || (track[i][j] == WALL) || (track[i][j] == START)) {
                reward[i].push_back(0);
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

void Value_ItAgent::print_max_util(uint x, uint y, uint x_vel, uint y_vel) {
    Point accel(0, 0);
    for (uint i = 0; i < NUM_ACC; i++) {
        for (uint j = 0; j < NUM_ACC; j++) {
            cout << "Accell: " << i2a(i) << ", " << i2a(j) << endl << endl;
            cout << "Utility = " << U[x][y][x_vel][y_vel][i][j] << endl;
            if (U[x][y][x_vel][y_vel][i][j] > U[x][y][x_vel][y_vel][accel.x][accel.y]) {
                accel.x = i;
                accel.y = j;
            }
        }
    }
    //max utility
    cout << "Points:  " << x << ", " << y << endl;
    cout << "Utility = " << U[x][y][x_vel][y_vel][accel.x][accel.y] << endl;
    cout << "Accell: " << i2a(accel.x) << ", " << i2a(accel.y) << endl << endl;


}

void Value_ItAgent::soft_reset() {



}
