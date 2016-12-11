/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rand_agent.h
 * Author: girish
 *
 * Created on December 11, 2016, 4:27 PM
 */

#ifndef RAND_AGENT_H
#define RAND_AGENT_H
#include <climits>
#include <float.h>

#define QNULL INT_MAX
#define MAX_FREQ 3
#define MAX_UTILITY 1.0
class RandAgent;

#include "agent.h"
#include "engine.h"

class RandAgent : public Agent {
public:
    RandAgent();
    Point next_accel(const Point& pos, const Point& vel, const double rwd, const bool terminate, bool debug);
    void soft_reset();
private:
  
    uint a2i(int a);
    uint v2i(int v);
    int i2a(uint i);
    int i2v(uint i);
};




#endif /* RAND_AGENT_H */

