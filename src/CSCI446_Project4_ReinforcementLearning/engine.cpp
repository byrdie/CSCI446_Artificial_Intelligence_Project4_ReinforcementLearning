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
    /* add car to the board */

    car_tile = rt->qt_world->set_tile(0, 0, CAR);
    qApp->processEvents();



}

void Engine::run(bool gui, uint slp_t) {



    /* Select starting position and velocity */
    pos_lst.push_back(start_pos[rand() % start_pos.size()]);
    Point start_vel(0, 0);
    vel_lst.push_back(start_vel);

    rt->qt_world->move_tile(car_tile, vel_lst.back().x, vel_lst.back().y);
    qApp->processEvents();
    qApp->processEvents();
    usleep(slp_t);





    /* Main control loop */
    while (true) {

        /* Have the agent carry out the next move */
        move(-1.0, false);
        Point pos = pos_lst.back(); // Update the current position
        Point vel = vel_lst.back();
        if (gui) {
            rt->qt_world->move_tile(car_tile, pos.x, pos.y);
            qApp->processEvents();
            qApp->processEvents();
            usleep(slp_t);
        }

        if (rt->world_vec[pos.x][pos.y] == FINISH) {
            move(1.0, true);
            pos_lst.clear();
            vel_lst.clear();
            return; // If so, break out of the loop
        } else {
            Point opos = pos_lst[pos_lst.size() - 2];
            //        Point ovel = vel_lst[vel_lst.size() - 2];

            int dx = (vel.x > 0) - (vel.x < 0);
            int dy = (vel.y > 0) - (vel.y < 0);
            cout << "dx = " << dx << ", dy = " << dy << endl;
            cout << "pos.x = " << pos.x << ", pos.y = " << pos.y << endl;
            cout << "opos.x = " << opos.x << ", opos.y = " << opos.y << endl;
            while ((opos.x != pos.x) and (opos.y != pos.y)) {


                if (rt->world_vec[opos.x][opos.y] == FINISH) {
                    move(1.0, true);
                    pos_lst.clear();
                    vel_lst.clear();
                    return; // If so, break out of the loop
                }

                opos.x += dx;
                opos.y += dy;

            }
        }




        //        do {
        //
        //            if (fr_x != 0) {
        //                opos.x += (fr_x > 0) - (fr_x < 0);
        //            }
        //
        //            do {
        //
        //                if (fr_y != 0) {
        //                    opos.y += (fr_y > 0) - (fr_y < 0);
        //                }
        //
        //                if (rt->world_vec[opos.x][opos.y] == FINISH) {
        //                    move(1.0, true);
        //                    pos_lst.clear();
        //                    vel_lst.clear();
        //                    return; // If so, break out of the loop
        //                }
        //
        //
        //            } while (opos.y != pos.y);
        //
        //
        //        } while (opos.x != pos.x);


        /* Check if the agent has reached the finish line */



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
            if (gui) {
                rt->qt_world->move_tile(car_tile, pos.x, pos.y);
                qApp->processEvents();
                qApp->processEvents();
                usleep(slp_t);
            }

        }





    }



}

/**
 * Have the update the position and velocity based on the agent's requested
 * acceleration
 */
void Engine::move(const double reward, const bool terminal) {

    Point pos = pos_lst.back();
    Point vel = vel_lst.back();
    Point accel = car->next_accel(pos, vel, reward, terminal);


    /* restrict acceleration */
    accel.x = range(accel.x, MAX_ACC, MIN_ACC);
    accel.y = range(accel.y, MAX_ACC, MIN_ACC);

    /* Apply probabilistic acceleration */
    if (rand() % 5 == 0) {
        accel.x = 0;
        accel.y = 0;
    }

    /* Calculate new velocity */
    vel.x = range(vel.x + accel.x, MAX_VEL, MIN_VEL);
    vel.y = range(vel.y + accel.y, MAX_VEL, MIN_VEL);

    /* Calculate new position */
    pos.x = range(pos.x + vel.x, 0, rt->world_vec.size() - 1);
    pos.y = range(pos.y + vel.y, 0, rt->world_vec[0].size() - 1);

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

