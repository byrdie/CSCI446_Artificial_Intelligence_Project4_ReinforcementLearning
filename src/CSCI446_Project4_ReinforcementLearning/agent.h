
/* 
 * File:   agent.h
 * Author: byrdie
 *
 * Created on December 6, 2016, 10:47 PM
 */

#ifndef AGENT_H
#define AGENT_H

#include "typedef.h"

class Agent {
public:
    Agent();
    virtual Point next_accel(const Point& pos, const Point& vel) = 0;
    
};

class DumbAgent : public Agent{
public:
    DumbAgent();
    Point next_accel(const Point& pos, const Point& vel);
    
};

#endif /* AGENT_H */

