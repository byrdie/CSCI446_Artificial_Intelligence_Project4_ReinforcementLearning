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

#include "world_gen.h"
#include "agent.h"

class Engine;

class Engine {
public:
    Engine(World * world, Agent * agent, bool crash_restart);
    void run();
private:
    bool restart;
    World * rt;
    Agent * car;
    QGraphicsPixmapItem * car_tile;
    vector<Point> start_pos;
    vector<Point> pos_lst;
    vector<Point> vel_lst;
    void move();
    int range(int arg, int n1, int n2);
};

#endif /* ENGINE_H */

