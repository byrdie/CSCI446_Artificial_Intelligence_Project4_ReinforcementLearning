/**
 * 
 * @param this_world
 */


#include "engine.h"
#include "typedef.h"
#include <cmath>

Engine::Engine(World& world, Agent& agent, bool crash_restart) {
   
    restart = crash_restart;
    rt = world;
    car = agent;
         
}

/**/
void Engine::move(Point accel, Point& pos, Point& vel) {

    /* restrict acceleration */
    accel.x = range(accel.x, 1, -1);
    accel.y = range(accel.y, 1, -1);
    
    /* Apply probabilistic acceleration */
    if(rand() % 5 == 0){
        accel.x = 0;
        accel.y = 0;
    }

    /* Calculate new velocity */
    vel.x = range(vel.x + accel.x, 5, -5);
    vel.y = range(vel.y + accel.y, 5, -5);

    /* Calculate new position */
    pos.x = pos.x + vel.x;
    pos.y = pos.y + vel.y;

}

int range(int arg, int n1, int n2) {

    int n_max = max(n1, n2);
    int n_min = min(n1, n2);

    return max(min(arg, n_max), n_min);

}

