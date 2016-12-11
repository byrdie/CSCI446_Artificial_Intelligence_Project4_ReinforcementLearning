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
#include <fstream>

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    init_rand();

    string dir = "Tracks/";
    string filename = "R-track.txt";
    QApplication app(argc, argv);
    World * world = new World(dir, filename);

    bool restart = false;
    bool gui = true;
    uint n_steps = 5e5;

    QLearningAgent * da = new QLearningAgent(world->world_vec.size(), world->world_vec[0].size(), 1e-6, 0.99);
    Engine engine(world, da, restart);
    ofstream data;
    data.open("qlearn.dat");

    //following for loop incrementally makes larger tracks
    uint step_size = 4;
    while (world->max_layer - step_size > 16) {
        world->world_vec = world->get_train_set(world->world_vec, world->max_layer - step_size);
        engine.update_start();
        for (uint i = 0; i < 100; i++) {
            
            data << engine.run(gui, 0) << endl;
        }
        step_size += 4;
    }


    filename = "R-track_longer.txt";
    world = new World(dir, filename);
    Engine engine2(world, da, restart);


    for (uint i = 0; i < 2 * n_steps; i++) {
        data << engine2.run(gui, 0) << endl;
    }

    cout << "finished" << endl;

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
