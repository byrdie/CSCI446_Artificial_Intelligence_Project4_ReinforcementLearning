
#include <vector>
#include <fstream>

#include "world_gen.h"
#include "qt_world.h"

// Create a black world (world covered in fog of war)

World::World(string dir, string filename) {
    ifstream attr_file(dir + filename);
    string value;
    getline(attr_file, value);
    while (attr_file.good()) {
        getline(attr_file, value);
        vector<int> row;
        for (char& c : value) {
            if (c == '#') {
                row.push_back(WALL);
            } else if (c == 'S') {
                row.push_back(START);
            } else if (c == 'F') {
                row.push_back(FINISH);
            } else if (c == '.') {
                row.push_back(TRACK);
            } else if (c == 'X') {
                row.push_back(CAR);
            }
        }
        
        world_vec.push_back(row);
    }
    
    attr_file.close();
    qt_world = new Qt_world(world_vec.size());
    
    for(uint i = 0; i < world_vec.size(); i++){
        for(uint j = 0; j < world_vec[0].size(); j++){
            qt_world->set_tile(i, j, world_vec[i][j]);
        }
    }
  
    //    N = side_length;
    //    qt_world = new Qt_world(N, agent);
    //
    //    // Fill empty board with fog of war
    //    for (int i = 0; i < N + 2; i++) {
    //        vector<int> world_vec_row;
    //        for (int j = 0; j < N + 2; j++) {
    //            world_vec_row.push_back(FOG);
    //            qt_world->set_tile(i, j, FOG);
    //        }
    //        world_vec.push_back(world_vec_row);
    //    }
    //
    //    qt_world->view->show();
}

/**
 * Adds the desired effect about a point, taking care to not appy it to walls
 * @param 
 * @return 
 */
void World::add_effect(Point * center, int effect_bits) {

    // Construct a vector of the four points surrounding the center

            world_vec[center->x][center->y] = effect_bits;
            qt_world->set_tile(center->x, center->y, effect_bits);
      
    

}

