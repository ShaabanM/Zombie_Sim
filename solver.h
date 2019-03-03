#ifndef SOLVER
#define SOLVER
// zh3X4dJqkR

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
const double TOTAL = 500;
const double A = 0.03;
const double B = 0.02;
const double C = 0.01;
const double E = 0.015;

void rhs(const state_type &x, state_type &dxdt, const double /*t*/);

void solve_and_report(size_t steps, int dat_count, std::vector<state_type> x_vec, std::vector<double> times);

struct push_back_state_and_time
{
    std::vector<state_type> &m_states;
    std::vector<double> &m_times;

    push_back_state_and_time(std::vector<state_type> &states, std::vector<double> &times)
        : m_states(states), m_times(times) {}

    void operator()(const state_type &x, double t)
    {
        m_states.push_back(x);
        m_times.push_back(t);
    }
};

#endif