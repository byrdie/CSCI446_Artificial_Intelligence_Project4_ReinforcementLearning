/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   record.h
 * Author: girish
 *
 * Created on December 12, 2016, 4:07 PM
 */

#ifndef RECORD_H
#define RECORD_H

#include <fstream>
#include <iostream>

struct record;

extern record out;

struct record : std::ofstream {

    record(const std::string& fileName)
    : std::ofstream(fileName)
    , fileName(fileName) {
    };

    const std::string fileName;
};

template <typename T>
record& operator<<(record& strm, const T& var) {
    std::cout << var;
    static_cast<std::ofstream&> (strm) << var;
    return strm;
};

#endif /* RECORD_H */
