/* 
 * File:   main.h
 * Author: byrdie
 *
 * Created on December 6, 2016, 10:30 PM
 */

#ifndef MAIN_H
#define MAIN_H

#include "world_gen.h"
#include "engine.h"
#include "QLearn.h"
#include "rand_agent.h"
#include "value_it.h"
#include "record.h"

void init_rand(unsigned long int seed);
unsigned long int init_rand();
void q_sample_runs();

#endif /* MAIN_H */

