/**
 * 
 * @param this_world
 */


#include "engine.h"

Engine::Engine(World * world, Agent * agent, bool crash_restart) {

    restart = crash_restart;
    rt = world;
    car = agent;

    /* Find the starting positions */
    
    for (uint i = 0; i < rt->world_vec.size(); i++) {
        for (uint j = 0; j < rt->world_vec[i].size(); j++) {
            if (rt->world_vec[i][j] == START) {
                Point spos(i, j);
                start_pos.push_back(spos);
            }
        }
    }
    

}

void Engine::run() {



    /* Select starting position and velocity */
    pos_lst.push_back(start_pos[rand() % start_pos.size()]);
    Point start_vel(0, 0);
    vel_lst.push_back(start_vel);
    
    /* add car to the board */
    car_tile = rt->qt_world->set_tile(pos_lst.back().x, pos_lst.back().y, CAR);
    qApp->processEvents();


    /* Main control loop */
    while (true) {

        /* Have the agent carry out the next move */
        move();
        Point pos = pos_lst.back(); // Update the current position
        Point vel = vel_lst.back();
        rt->qt_world->move_tile(car_tile, pos.x, pos.y);
        qApp->processEvents();
        qApp->processEvents();

        /* Check that the agent didn't hit a wall */
        if (rt->world_vec[pos.x][pos.y] == WALL) {

            /* If so, reset the car to the appropriate position */
            if (restart) {
                pos = pos_lst[0];
            } else {
                pos = pos_lst[pos_lst.size() - 2];
            }
            vel = start_vel;
            pos_lst.push_back(pos);
            vel_lst.push_back(vel);
            rt->qt_world->move_tile(car_tile, pos.x, pos.y);
            qApp->processEvents();
            qApp->processEvents();

        }

        /* Check if the agent has reached the finish line */
        if (rt->world_vec[pos.x][pos.y] == FINISH) {
            break; // If so, break out of the loop
        }

        usleep(500000);

    }

}

/**
 * Have the update the position and velocity based on the agent's requested
 * acceleration
 */
void Engine::move() {

    Point pos = pos_lst.back();
    Point vel = vel_lst.back();
    Point accel = car->next_accel(pos, vel);


    /* restrict acceleration */
    accel.x = range(accel.x, 1, -1);
    accel.y = range(accel.y, 1, -1);

    /* Apply probabilistic acceleration */
    if (rand() % 5 == 0) {
        accel.x = 0;
        accel.y = 0;
    }

    /* Calculate new velocity */
    vel.x = range(vel.x + accel.x, 5, -5);
    vel.y = range(vel.y + accel.y, 5, -5);

    /* Calculate new position */
    pos.x = pos.x + vel.x;
    pos.y = pos.y + vel.y;

    /* Update list of positions and velocities */
    pos_lst.push_back(pos);
    vel_lst.push_back(vel);

}

/**
 * restricts arg between the numbers n1 and n2 
 * @param arg
 * @param n1
 * @param n2
 * @return 
 */
int Engine::range(int arg, int n1, int n2) {

    int n_max = max(n1, n2);
    int n_min = min(n1, n2);

    return max(min(arg, n_max), n_min);

}

