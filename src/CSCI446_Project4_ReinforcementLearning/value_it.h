
#ifndef VALUE_IT_H
#define VALUE_IT_H

#include <climits>

#define QNULL INT_MAX
#define MAX_FREQ 1
#define MAX_UTILITY 1.0
class Value_ItAgent;

#include "agent.h"
#include "engine.h"

class Value_ItAgent : public Agent {
public:
    Value_ItAgent(uint xsize, uint ysize, double delt, double gam, double eps);
    Point next_accel(const Point& pos, const Point& vel, const double rwd, const bool terminate);
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
    
    uint a2i(int a);
    uint v2i(int v);
    int i2a(uint i);
    int i2v(uint i);
    void val_iteration(World * world);
    vector<vector<double>> get_reward(vector<vector<uint>> track);
    vector<vector<uint>> track_val(vector<vector<uint>> track);
    double utility(uint x, uint y, uint vel_x, uint vel_y, uint act_x, uint act_y);
    vector<int> calc_vel(int vel_x, int vel_y, int act_x, int act_y);
    vector<vector<uint>> affected_squares(int x, int y, int acc_x, int acc_y);
};
#endif /* VALUE_IT_H */

