#ifndef SOLVER
#define SOLVER

// odeint is a header-only library, no linking against pre-compiled code is required
#include <boost/numeric/odeint.hpp>
// All functions and classes from odeint live in the namespace
using namespace boost::numeric::odeint;
/* The type of container used to hold the state vector */
typedef std::vector<double> state_type;

/* 
    S:x[0]: number of regular people, who can't kill zombies
    K:x[1]: number of zombie killers
    Z:x[2]: number of zombies
    A: rate at which zombies are killed, by K
    B: rate at which regular people are turned into zombies
    C: rate at which zombie killers are turned into zombies
    E: rate at which zombie killers teach regular people how to kill zombies 
*/

// Constants
#define TOTAL 500
#define A 0.03
#define B 0.02
#define C 0.01
#define E 0.015

void rhs(const state_type &x, state_type &dxdt, const double /*t*/); 
void solve(const state_type &x0, int dat_count);

#endif