/**
 * 
 * @param this_world
 */


#include "engine.h"
#include <cmath>

Engine::Engine(World * this_world) {
    world = this_world;
    orientation = NORTH;
    score = 0;
}

int Engine::move(int direction, Point * cur_pos) {
    orient_to_direction(direction, orientation);
    score--;
    vector<Point *> neighbors = world->find_neighbors(cur_pos);

    Point * test_pt = neighbors[direction];

    int test_tile = world->world_vec[test_pt->x][test_pt->y];

    if ((test_tile & WALL) > 0){
        return test_tile;
    } else {
        cur_pos->x = test_pt->x;
        cur_pos->y = test_pt->y;
    }
    return test_tile;

}

int Engine:: orient_to_direction(int direction, int orientation){
    
    //Moves player orientation to direction and increments score correctly
    if(orientation == direction){
        score = score;
    }else if(abs(orientation - direction) % 2 == 0){
        orientation = (orientation + 2) % 4;
        score -= 2;
    }else {
        orientation = direction;
        score--;
    }

    
    return orientation;
    
    
}
int Engine::num_obstacles(){
    return world->num_pits;
}