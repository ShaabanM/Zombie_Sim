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

// Function for writing the data in a 2D rarray to a netCDF file
void append_netcdf(rarray<double, 2> arr, int dat_count);

#endif