/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: byrdie
 *
 * Created on December 6, 2016, 8:52 PM
 */

#include "main.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    string dir = "Tracks/";
    string filename = "R-track.txt";
    QApplication app(argc, argv);
    World * world = new World(dir, filename);

    sleep(1);

    QLearningAgent * da = new QLearningAgent(world->world_vec.size(), world->world_vec[0].size(), 0.5, 0.99);
    world->world_vec = world->get_train_set(world->world_vec, world->max_layer-5);
    Engine engine(world, da, false);
//    while(true){
//       engine.run(true, 100000) ;
//    }

    for(uint i = 0; i < 1; i++){
        engine.run(true, 100000);
    }
    world->world_vec = world->get_train_set(world->world_vec, world->max_layer-40);
    engine.update_start();
    for(uint i = 0; i < 1; i++){
        engine.run(true, 100000);
    }
    // create and show your widgets here

    return app.exec();
}

/* Prepare random number generation */
void init_rand(unsigned long int seed) {
    srand(seed);
    printf("Seed: %lu\n", seed);
}

unsigned long int init_rand() {
    unsigned int seed = time(NULL);
    srand(seed);
    printf("Seed: %u\n", seed);
    return seed;
}
