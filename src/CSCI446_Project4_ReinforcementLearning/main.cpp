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
    //    string filename = "R-track_short.txt";
    string filename = "L-track.txt";

    QApplication app(argc, argv);
    World * world = new World(dir, filename);

    bool restart = false;
    bool gui = false;
    uint n_steps = 1e7;

    ofstream data;
    data.open("qlearn.dat");

    QLearningAgent * da = new QLearningAgent(world->world_vec.size(), world->world_vec[0].size(), 1e-6, 0.99);

    //    Engine engine(world, da, restart);
    //    for (uint i = 0; i < n_steps; i++) {
    //        data << engine.run(gui, 0) << endl;
    //    }

//    filename = "R-track_longer.txt";
    world = new World(dir, filename);
    Engine engine2(world, da, restart);
    for (uint i = 0; i < n_steps; i++) {
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