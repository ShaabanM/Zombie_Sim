
#include "solver.h"
#include "append_netcdf.h"


void solve(const state_type &x0, int dat_count)
{
    vector<state_type> x_vec;
    vector<double> times;
    rarray<double, 2> data(steps + 1, 4);

    size_t steps = integrate(rhs, x0, 0.0, 100.0, 0.1, push_back_state_and_time(x_vec, times));
    for (size_t i = 0; i <= steps; i++)
    {
        data[i][0] = times[i];
        data[i][1] = x_vec[i][0];
        data[i][2] = x_vec[i][1];
        data[i][3] = x_vec[i][2];
    }
    append_netcdf(data, dat_count);
}

// Helper Function

// even if there is no explicit t dependence, one has to define t as a function parameter.
void rhs(const state_type &x, state_type &dxdt, const double /*t*/)
{
    dxdt[0] = -B * x[0] * x[2] - E * x[0] * x[1];
    dxdt[1] = -C * x[1] * x[2] + E * x[0] * x[1];
    dxdt[2] = B * x[0] * x[2] + C * x[1] * x[2] - A * x[1] * x[2];
}