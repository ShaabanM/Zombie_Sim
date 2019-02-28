
#include "append_netcdf.h"

void append_netcdf(rarray<double, 2> arr, int dat_count)
{

    // if this is the first time the function is called run this block to create or replace file
    if (dat_count == 0)
    {
        std::vector<NcDim> dims;
        // Create or replace exisiting outout.nc file
        NcFile dataFile("output.nc", NcFile::replace);

        // Create netCDF dimensions
        NcDim xDim = dataFile.addDim("x", arr.shape()[0]);
        NcDim yDim = dataFile.addDim("y", arr.shape()[1]);
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