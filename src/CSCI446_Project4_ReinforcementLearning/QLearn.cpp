
/* 
 * File:   QLearn.h
 * Author: byrdie
 *
 * Created on December 8, 2016, 2:19 PM
 */

#include "QLearn.h"

QLearningAgent::QLearningAgent(uint xsize, uint ysize) : Agent(),
Q(xsize, vector<vector<double>>(ysize, vector<double>(NUM_ACTIONS))),
N(xsize, vector<vector<uint>>(ysize, vector<uint>(NUM_ACTIONS))) {

}

Point QLearningAgent::next_accel(const Point& pos, const Point& vel, const int reward, const bool terminate){
    
    return Point(1,1);
    
}