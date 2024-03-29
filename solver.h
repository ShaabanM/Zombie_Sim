#ifndef SOLVER
#define SOLVER

// odeint is a header-only library, no linking against pre-compiled code is required
#include <boost/numeric/odeint.hpp>
// All functions and classes from odeint live in the namespace
using namespace boost::numeric::odeint;
/* The type of container used to hold the state vector */
typedef std::vector<double> state_type;

// Constants as provided in the homework problem
/* 
    S:x[0]: number of regular people, who can't kill zombies
    K:x[1]: number of zombie killers
    Z:x[2]: number of zombies
    A: rate at which zombies are killed, by K
    B: rate at which regular people are turned into zombies
    C: rate at which zombie killers are turned into zombies
    E: rate at which zombie killers teach regular people how to kill zombies 
*/
const double TOTAL = 500;
const double A = 0.03;
const double B = 0.02;
const double C = 0.01;
const double E = 0.015;

// Function to set the up the right hand side of the ODE
//
// Parameters:
//   x          The ODE variables
//   dxdt       the LHS of the equation i.e. the time derivative of variable
//   t          even if there is no explicit t dependence, one has to define t as a function parameter.
//
void rhs(const state_type &x, state_type &dxdt, const double /*t*/);

// Function for reporting the results of the integration, returns netcdf file called output as well as cmd print out with who won
//
// Parameters:
//   steps          Number of time steps in the integration
//   dat_count      value of Z0 and also position along the rec dimension in the netcdf file
//   x_vec/times    Vectors for data storage during integration.
//
void report(size_t steps, int dat_count, std::vector<state_type> x_vec, std::vector<double> times);

// Struct used to keep track of the values during the integration
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