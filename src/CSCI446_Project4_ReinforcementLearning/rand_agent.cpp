
/* 
 * File:   QLearn.h
 * Author: byrdie
 *
 * Created on December 8, 2016, 2:19 PM
 */

#include "rand_agent.h"

RandAgent::RandAgent() : Agent() {

}

Point RandAgent::next_accel(const Point& pos, const Point& vel, const double rwd, const bool terminate, bool debug) {

    int x = 0;
    int y = 0;
    while((x==0) && (y == 0)){
        x = (rand() % 3) - 1;
        y = (rand() % 3) - 1;
        
    }
    Point acc(x,y);

    return acc;

}

void RandAgent::soft_reset(){
    
}


uint RandAgent::a2i(int a) {
    return a - MIN_ACC;
}

uint RandAgent::v2i(int v) {
    return v - MIN_VEL;
}

int RandAgent::i2a(uint i) {
    return i + MIN_ACC;
}

int RandAgent::i2v(uint i) {
    return i + MIN_VEL;
}