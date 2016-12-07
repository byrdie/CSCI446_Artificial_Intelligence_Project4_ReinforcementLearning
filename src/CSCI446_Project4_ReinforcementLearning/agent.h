/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   agent.h
 * Author: byrdie
 *
 * Created on December 6, 2016, 10:47 PM
 */

#ifndef AGENT_H
#define AGENT_H

class Agent {
public:
    Point pos;
    Point vel;
    Agent(Point& start_pos, Point& start_vel);
    virtual int next_move() = 0;
    
};

#endif /* AGENT_H */

