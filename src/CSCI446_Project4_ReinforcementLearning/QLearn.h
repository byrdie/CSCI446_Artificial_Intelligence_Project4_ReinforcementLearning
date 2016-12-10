/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QLearn.h
 * Author: byrdie
 *
 * Created on December 8, 2016, 2:19 PM
 */

#ifndef QLEARN_H
#define QLEARN_H

#include <climits>

#define QNULL INT_MAX
#define MAX_FREQ 1
#define MAX_UTILITY 1.0
class QLearningAgent;

#include "agent.h"
#include "engine.h"

class QLearningAgent : public Agent {
public:
    QLearningAgent(uint xsize, uint ysize, double alp, double gam);
    Point next_accel(const Point& pos, const Point& vel, const double rwd, const bool terminate);
    void soft_reset();
private:
    double alpha;
    double gamma;
    Point opos;     // The old position, a component of s
    Point ovel;     // The old velocity, a component of s
    Point oacc;     // The old acceleration, redefinition of a
    double orwd;       // The old reward, a redefinition of r
    vector<vector<vector<vector<vector<vector<double>>>>>> Q;   // Table of Q-values, Q[s,a]
    vector<vector<vector<vector<vector<vector<uint>>>>>> N;     // Table of frequencies for state-action pairs, N[s,a]

    
    double exploration_function(double q_val, uint freq);
    uint a2i(int a);
    uint v2i(int v);
    int i2a(uint i);
    int i2v(uint i);
};


#endif /* QLEARN_H */

