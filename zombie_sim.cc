#include "append_netcdf.h"
#include "solver.h"



int main()
{

    for (size_t z = 0; z <= 10; z++)
    {
        state_type x0(3);
        x0[1] = 9.0;                   // K0
        x0[2] = z;                     // Z0
        x0[0] = TOTAL - x0[1] - x0[2]; // S0

        vector<state_type> x_vec;
        vector<double> times;

        size_t steps = integrate(rhs, x0, 0.0, 100.0, 0.1, push_back_state_and_time(x_vec, times));
        solve_and_report(steps, z, x_vec, times);
    }
}