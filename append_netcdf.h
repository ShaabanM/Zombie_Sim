#ifndef NETAPP
#define NETAPP

#include <netcdf>
#include "antsontable.h"
using namespace netCDF;

void append_netcdf(rarray<int, 2> arr, int dat_count);

#endif