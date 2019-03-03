
#include "solver.h"
#include "append_netcdf.h"

// Implementaiton of the RHS of the ODE as provided in the assignment
void rhs(const state_type &x, state_type &dxdt, const double /*t*/)
{
    dxdt[0] = -B * x[0] * x[2] - E * x[0] * x[1];
    dxdt[1] = -C * x[1] * x[2] + E * x[0] * x[1];
    dxdt[2] = B * x[0] * x[2] + C * x[1] * x[2] - A * x[1] * x[2];
}

// Implementation of the report function to report and store the data of integration.
void report(size_t steps, int dat_count, std::vector<state_type> x_vec, std::vector<double> times)
{
    // data array set up like a table, |times|S|K|Z| note there is a redundancy required in order to display the non integer time value.
    rarray<double, 2> data(steps + 1, 4);

    // fill the rarray with the data provided by the integration
    for (size_t i = 0; i <= steps; i++)
    {
        data[i][0] = times[i];
        data[i][1] = x_vec[i][0];
        data[i][2] = x_vec[i][1];
        data[i][3] = x_vec[i][2];
    }
    // append the data to the output netcdf file.
    append_netcdf(data, dat_count);

    // report the winner on the cmd line
    if (x_vec[steps][0] + x_vec[steps][1] < 1)
    {
        cout <<  "Humanity Loses for Z0 = " << dat_count << endl;
    }

    if (x_vec[steps][2] < 1)
    {
        cout <<  "Humanity Wins for Z0 = " << dat_count << endl;
    }
}
