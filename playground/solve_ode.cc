
// odeint is a header-only library, no linking against pre-compiled code is required
#include <boost/numeric/odeint.hpp>
#include <iostream>
#include <vector>
#include <netcdf>
#include <algorithm>
#include <rarray>
using namespace netCDF;
using namespace netCDF::exceptions;
// All functions and classes from odeint live in the namespace
using namespace std;
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

// even if there is no explicit t dependence, one has to define t as a function parameter.
void rhs(const state_type &x, state_type &dxdt, const double /*t*/)
{
    dxdt[0] = -B * x[0] * x[2] - E * x[0] * x[1];
    dxdt[1] = -C * x[1] * x[2] + E * x[0] * x[1];
    dxdt[2] = B * x[0] * x[2] + C * x[1] * x[2] - A * x[1] * x[2];
}

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

void append_netcdf(rarray<double, 2> arr, int dat_count)
{

    // if this is the first time the function is called run this block to create or replace file
    if (dat_count == 0)
    {
        std::vector<NcDim> dims;
        // Create or replace exisiting outout.nc file
        NcFile dataFile("output.nc", NcFile::replace);

        // Create netCDF dimensions
        NcDim xDim = dataFile.addDim("x");
        NcDim yDim = dataFile.addDim("y",arr.shape()[1]);
        NcDim recDim = dataFile.addDim("t"); //adds an unlimited dimension

        // set up dims vector array
        dims.push_back(recDim);
        dims.push_back(xDim);
        dims.push_back(yDim);
        // add variable to file
        NcVar data = dataFile.addVar("data", ncDouble, dims);
    }

    // open existing file to write
    NcFile dataFile("output.nc", NcFile::write);
    // get existing data variable
    NcVar data = dataFile.getVar("data");

    // write array to the dat_count entry in the rec dimension
    data.putVar({dat_count, 0, 0}, {1, arr.shape()[0], arr.shape()[1]}, arr.data());
}

int main()
{
    for (size_t z = 5; z < 11; z++)
    {
        /* code */

        vector<state_type> x_vec;
        vector<double> times;

        state_type x(3);
        x[1] = 9.0; // S0
        x[2] = z;
        x[0] = 491 - x[2];

        size_t steps = integrate(rhs, x, 0.0, 100.0, 0.1, push_back_state_and_time(x_vec, times));

        rarray<double, 2> data(steps + 1, 4);


        /* output */
        for (size_t i = 0; i <= steps; i++)
        {
            // cout << times[i] << '\t' << x_vec[i][0] << '\t'
            //<< x_vec[i][1] << '\t' << x_vec[i][2] << '\n';

            data[i][0] = times[i];
            data[i][1] = x_vec[i][0];
            data[i][2] = x_vec[i][1];
            data[i][3] = x_vec[i][2];
        }

        append_netcdf(data, z-5);
    }
}