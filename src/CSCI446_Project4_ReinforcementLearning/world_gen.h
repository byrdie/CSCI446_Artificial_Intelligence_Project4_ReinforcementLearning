/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   world_gen.h
 * Author: byrdie
 *
 * Created on October 2, 2016, 11:31 AM
 */

#ifndef WORLD_GEN_H
#define WORLD_GEN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

class World;



#include "qt_world.h"

#include "typedef.h"

using namespace std;

class World {
public:
    uint x_size;
    uint y_size;
    vector<vector<uint> > world_vec;
    vector<vector<uint>> train_vec;
    Qt_world * qt_world;


    World(string dir, string filename); // Load a world from a file
    void add_effect(Point * center, int effect_bits);
    void generate_train_track();


};

#endif /* WORLD_GEN_H */

