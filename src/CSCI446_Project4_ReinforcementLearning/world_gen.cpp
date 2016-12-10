
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
        vector<uint> row;
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
    world_vec.pop_back();

    vector<vector < uint>> temp;

    //rotate 90 degrees
    for (uint i = 0; i < world_vec[0].size(); i++) {
        vector<uint> t;
        temp.push_back(t);
        for (uint j = 0; j < world_vec.size(); j++) {
            temp[i].push_back(world_vec[j][i]);
        }
    }
    world_vec = temp;

    attr_file.close();
    qt_world = new Qt_world(max(world_vec.size(), world_vec[0].size()));
    for (uint i = 0; i < world_vec.size(); i++) {
        for (uint j = 0; j < world_vec[0].size(); j++) {
            qt_world->set_tile(i, j, world_vec[i][j]);
        }
    }
    generate_train_track();
    qt_world->view->show();

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

void World::generate_train_track() {
    uint layer = 20;
    vector<vector < uint>> level;
    bool train = true;
    train_vec = world_vec;
    for (uint i = 0; i < world_vec.size(); i++) {
        for (uint j = 0; j < world_vec[0].size(); j++) {
            if (world_vec[i][j] == START) {
                vector<uint> temp;
                temp.push_back(i);
                temp.push_back(j);
                level.push_back(temp);
                train_vec[i][j] = layer;
            }
        }
    }
    while (train) {
        cout<<"Crap\n";
        train = false;
        vector<vector <uint>> new_level;
        layer++;
        
        for (uint i = 0; i < level.size(); i++) {
            if (train_vec[level[i][0] + 1][level[i][1]] == TRACK) {
                train_vec[level[i][0] + 1][level[i][1]] == layer;
                vector<uint> temp;
                temp.push_back(level[i][0] + 1);
                temp.push_back(level[i][1]);
                new_level.push_back(temp);
                train = true;
                cout<<level.size()<<endl;
            }
            if (train_vec[level[i][0] - 1][level[i][1]] == TRACK) {
                train_vec[level[i][0] - 1][level[i][1]] == layer;
                vector<uint> temp;
                temp.push_back(level[i][0] - 1);
                temp.push_back(level[i][1]);
                new_level.push_back(temp);
                train = true;
                cout<<level.size()<<endl;
            }
            if (train_vec[level[i][0]][level[i][1]+1] == TRACK) {
                train_vec[level[i][0]][level[i][1]+1] == layer;
                vector<uint> temp;
                temp.push_back(level[i][0]);
                temp.push_back(level[i][1]+1);
                new_level.push_back(temp);
                train = true;
                cout<<level.size()<<endl;
            }
            if (train_vec[level[i][0]][level[i][1]-1] == TRACK) {
                train_vec[level[i][0]][level[i][1]-1] == layer;
                vector<uint> temp;
                temp.push_back(level[i][0]);
                temp.push_back(level[i][1]-1);
                new_level.push_back(temp);
                train = true;
                cout<<level.size()<<endl;
            }
        }
        level = new_level;
    }
}
