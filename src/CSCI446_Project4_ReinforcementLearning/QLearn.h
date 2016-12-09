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

class QLearningAgent;

#include "agent.h"
#include "engine.h"

class QLearningAgent : public Agent {
public:
    QLearningAgent(uint xsize, uint ysize, double alp, double gam);
    Point next_accel(const Point& pos, const Point& vel, const int reward, const bool terminate);
private:
    double alpha;
    double gamma;
    Point opos;     // The old position, a component of s
    Point ovel;     // The old velocity, a component of s
    Point oacc;     // The old acceleration, redefinition of a
    int orwd;       // The old reward, a redefinition of r
    vector<vector<vector<vector<vector<vector<double>>>>>> Q;   // Table of Q-values, Q[s,a]
    vector<vector<vector<vector<vector<vector<uint>>>>>> N;     // Table of frequencies for state-action pairs, N[s,a]
    uint a2i(int a);
    uint v2i(int v);
};

#endif /* QLEARN_H */

