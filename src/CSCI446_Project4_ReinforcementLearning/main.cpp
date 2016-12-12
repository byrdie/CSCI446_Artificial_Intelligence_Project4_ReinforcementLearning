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

record out("../output.tex");

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    init_rand();

    string dir = "Tracks/";
    //    string filename = "R-track_short.txt";
    string filename = "R-track_short.txt";

    QApplication app(argc, argv);
    World * world = new World(dir, filename);

    bool restart = false;
    bool gui = true;
    uint n_steps = 5e6;
    uint n_ave = 1e3;
    bool debug = true;

    ofstream data;
    data.open("qlearn.dat");

    QLearningAgent * da = new QLearningAgent(world->world_vec.size(), world->world_vec[0].size(), 1e-8, 0.9);
    Engine engine(world, da, restart);

    //following for loop incrementally makes larger tracks
    uint step_size = 3;
    while (world->max_layer - step_size > 16) {
        world->world_vec = world->get_train_set(world->world_vec, world->max_layer - step_size);
        engine.update_start();
        double old_ave = 0.0;
        while (true) {
            //        for (uint i = 0; i < n_steps / n_ave; i++) {

            double ave = 0.0;
            for (uint j = 0; j < n_ave; j++) {
                ave += engine.run(gui, 0, debug);
            }
            ave = ave / n_ave;
            data << ave << endl;

            /* convergence test */
            if (abs(ave - old_ave) < 1e-1) {
                break;
            }
            old_ave = ave;

        }
        step_size += 1;

        if (step_size == 26 or step_size == 35 or step_size == 36) {
            step_size += 2;
        }

        cout << "The step size is: " << step_size << "\n";
    }

    //    uint n_check = 10;
    //
    //    for (uint i = 0; i < n_check; i++) {
    //        cout << engine.run(true, 200000,debug) << "\n";
    //    }


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
