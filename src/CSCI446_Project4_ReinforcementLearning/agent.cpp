
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

Point DumbAgent::next_accel(const Point& pos, const Point& vel, const int reward, const bool terminate){
    
    return Point(0,-1);
    
}