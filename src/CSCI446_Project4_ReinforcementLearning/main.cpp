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

record out("../output/output.tex");

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    init_rand();

    string dir = "Tracks/";
    string filename = "R-track.txt";
    QApplication app(argc, argv);

    //    q_sample_runs();
    string dir = "Tracks/";
    //    string filename = "R-track_short.txt";
    string filename = "R-track.txt";
    World * world = new World(dir, filename);

    bool restart = true;
    bool gui = false;
    uint n_steps = 5e6;
    uint n_ave = 2e3;
    bool debug = false;

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
        double older_ave = 0.0;
        double oldest_ave = 0.0;
        while (true) {
            //        for (uint i = 0; i < n_steps / n_ave; i++) {

            double ave = 0.0;
            for (uint j = 0; j < n_ave; j++) {
                ave += engine.run(gui, 0, debug);
            }
            ave = ave / n_ave;
            data << ave << endl;

            /* convergence test */
            if (abs(ave - (old_ave + older_ave + oldest_ave) / 3) < 1e-3) {
                break;
            }
            oldest_ave = older_ave;
            older_ave = old_ave;
            old_ave = ave;

        }
        step_size += 2;

        if (step_size == 26 or step_size == 36) {
            step_size++;
        } else if (step_size == 35) {
            step_size += 2;
        }

        cout << "The step size is: " << step_size << "\n";
    }


    while (true) {
        cout << engine.run(true, 200000, debug) << "\n";
    }
    

    bool restart = false;
    bool gui = false;
    uint n_steps = 5e5;
    out << .00000000000001 << "\n";
    //    Value_ItAgent * va = new Value_ItAgent(world->world_vec.size(), world->world_vec[0].size(), 0, 0.5, .00000000000001);
    //    Engine engine1(world, va, restart);
    //    //world->world_vec = world->get_train_set(world->world_vec, world->max_layer-10);
    //    //engine1.update_start();
    //    va->val_iteration(world);
    uint average = 0;
  
        World * world = new World(dir, filename);
        Value_ItAgent * va = new Value_ItAgent(world->world_vec.size(), world->world_vec[0].size(), 0, 0.5, .00000000000001);
        Engine engine1(world, va, restart);
        //world->world_vec = world->get_train_set(world->world_vec, world->max_layer-10);
        //engine1.update_start();
        va->val_iteration(world);
        for(uint i = 0; i < 1; i++){
        average += engine1.run(gui, 0);
        }
    cout << average <<"\n";
    average = 0;
    

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

void q_sample_runs() {

    string dir = "Tracks/";
    //    string filename = "R-track_short.txt";
    string filename = "R-track_short.txt";

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


    for (uint i = 0; i < 10; i++) {
        engine.run(gui, 100000, debug);
    }

    out.close();

}
