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

class QLearningAgent : public Agent {
public:
    QLearningAgent(int xsize, int ysize);
    Point next_accel(const Point& pos, const Point& vel, const int reward, const bool terminate);
private:
    
};

#endif /* QLEARN_H */

