/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   engine.h
 * Author: byrdie
 *
 * Created on October 2, 2016, 6:38 PM
 */

#ifndef ENGINE_H
#define ENGINE_H

class Engine;

#include "world_gen.h"

class Engine {
    
public: 
    
    Engine(World * this_world);
    void move(Point accel , Point * pos, Point * vel);
private:
    World * world;
    
    
};

#endif /* ENGINE_H */

