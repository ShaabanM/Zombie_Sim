#ifndef NETAPP
#define NETAPP

#include <netcdf>
#include <algorithm>
#include <rarray>
#include <iostream>
#include <vector>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

void append_netcdf(rarray<double, 2> arr, int dat_count);

#endif