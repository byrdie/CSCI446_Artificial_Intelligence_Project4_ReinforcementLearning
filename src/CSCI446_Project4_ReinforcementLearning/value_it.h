
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
    vector<vector<vector<vector<vector<vector<uint>>>>>> UP;    // Utility prime Vector
    
    uint a2i(int a);
    uint v2i(int v);
    int i2a(uint i);
    int i2v(uint i);
    
};
#endif /* VALUE_IT_H */

