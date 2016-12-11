
/* 
 * File:   agent.cpp
 * Author: byrdie
 *
 * Created on December 6, 2016, 10:47 PM
 */

#include "agent.h"

Agent::Agent(){
    
}

DumbAgent::DumbAgent() : Agent() {
    
}

Point DumbAgent::next_accel(const Point& pos, const Point& vel, const double reward, const bool terminate, bool debug){
    
    return Point(0,-1);
    
}

void DumbAgent::soft_reset(){
    
}