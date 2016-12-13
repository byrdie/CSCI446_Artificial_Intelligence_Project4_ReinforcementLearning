
#ifndef VALUE_IT_H
#define VALUE_IT_H

#include <climits>

#define QNULL INT_MAX

class Value_ItAgent;

#include "agent.h"
#include "engine.h"
#include "record.h"
//#include "main.h"

class Value_ItAgent : public Agent {
public:
    Value_ItAgent(uint xsize, uint ysize, double delt, double gam, double eps);
    Point next_accel(const Point& pos, const Point& vel, const double reward, const bool terminate, bool debug);
    void val_iteration(World * world);
    void soft_reset();
    void print_max_util(uint x, uint y, uint x_vel, uint y_vel);
        
    uint a2i(int a);
    uint v2i(int v);
    int i2a(uint i);
    int i2v(uint i);
    
    uint iter = 0;
private:
    double delta;
    double gamma;
    double epsilon;
    Point opos;     // The old position, a component of s
    Point ovel;     // The old velocity, a component of s
    Point oacc;     // The old acceleration, redefinition of a
    double orwd;
    vector<vector<vector<vector<vector<vector<double>>>>>> U;   // Utility Vector
    vector<vector<vector<vector<vector<vector<double>>>>>> UP;    // Utility prime Vector
    bool crash_prot = false;
    vector<vector<double>> reward;
    World * wd;


    vector<vector<double>> get_reward(vector<vector<uint>> track);
    vector<vector<uint>> track_val(vector<vector<uint>> track);
    double utility(uint x, uint y, uint vel_x, uint vel_y, uint act_x, uint act_y);
    vector<int> calc_vel(int vel_x, int vel_y, int act_x, int act_y);
    vector<vector<int>> affected_squares(int x, int y, int acc_x, int acc_y);
    bool did_finish(vector<vector<int>> crossed_states);
    bool hit_wall(vector<vector<int>> crossed_states);
};
#endif /* VALUE_IT_H */

