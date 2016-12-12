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
#include "record.h"

#define MAX_VEL 5
#define MIN_VEL -5
#define MAX_ACC 1
#define MIN_ACC -1
#define NUM_VEL MAX_VEL - MIN_VEL + 1
#define NUM_ACC MAX_ACC - MIN_ACC + 1

class Engine;

class Engine {
public:
    Engine(World * world, Agent * agent, bool crash_restart);
    uint run(bool gui, uint slp_t, bool debug);
    void update_start();
private:
    bool restart;
    World * rt;
    Agent * car;
    QGraphicsPixmapItem * car_tile;
    vector<Point> start_pos;
    vector<Point> pos_lst;
    vector<Point> vel_lst;
    void move(const double reward, const bool terminal);
    int range(int arg, int n1, int n2);
    
};

#endif /* ENGINE_H */

