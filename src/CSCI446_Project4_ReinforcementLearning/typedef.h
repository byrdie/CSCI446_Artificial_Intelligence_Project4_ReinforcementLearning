/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   typedef.h
 * Author: byrdie
 *
 * Created on October 1, 2016, 10:26 PM
 */

#ifndef TYPEDEF_H
#define TYPEDEF_H




#define WALL     0x00000000
#define START    0x00000001
#define FINISH  0x00000002
#define TRACK  0x00000004
#define CAR     0x00000008


// Definite move types
#define EAST    0
#define NORTH   1
#define WEST    2
#define SOUTH   3

#include <vector>
#include <tuple>

using namespace std;






class Point {
public:
    int x;
    int y;
    ;

    Point(int xpos, int ypos) {
        x = xpos;
        y = ypos;
    }
};

#endif /* TYPEDEF_H */

