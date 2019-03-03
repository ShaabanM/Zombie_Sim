
#include "solver.h"
#include "append_netcdf.h"


// even if there is no explicit t dependence, one has to define t as a function parameter.
void rhs(const state_type &x, state_type &dxdt, const double /*t*/)
{
    dxdt[0] = -B * x[0] * x[2] - E * x[0] * x[1];
    dxdt[1] = -C * x[1] * x[2] + E * x[0] * x[1];
    dxdt[2] = B * x[0] * x[2] + C * x[1] * x[2] - A * x[1] * x[2];
}

void solve_and_report(size_t steps, int dat_count, std::vector<state_type> x_vec, std::vector<double> times)
{
    rarray<double, 2> data(steps + 1, 4);

    for (size_t i = 0; i <= steps; i++)
    {
        data[i][0] = times[i];
        data[i][1] = x_vec[i][0];
        data[i][2] = x_vec[i][1];
        data[i][3] = x_vec[i][2];
    }
    append_netcdf(data, dat_count);
}
