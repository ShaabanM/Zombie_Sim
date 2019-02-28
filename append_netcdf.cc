
#include "append_netcdf.h"

void append_netcdf(rarray<double, 4> arr, int dat_count)
{

    // if this is the first time the function is called run this block to create or replace file
    if (dat_count == 0)
    {
        std::vector<NcDim> dims;
        // Create or replace exisiting outout.nc file
        NcFile dataFile("output.nc", NcFile::replace);

        // Create netCDF dimensions
        NcDim SDim = dataFile.addDim("S", arr.shape()[0]);
        NcDim KDim = dataFile.addDim("K", arr.shape()[1]);
        NcDim ZDim = dataFile.addDim("Z", arr.shape()[2]);
        NcDim tDim = dataFile.addDim("t", arr.shape()[3]);
        NcDim recDim = dataFile.addDim("Z0"); //adds an unlimited dimension

        // set up dims vector array
        dims.push_back(recDim);
        dims.push_back(SDim);
        dims.push_back(KDim);
        dims.push_back(ZDim);
        // add variable to file
        NcVar data = dataFile.addVar("data", ncInt, dims);
    }

    // open existing file to write
    NcFile dataFile("output.nc", NcFile::write);
    // get existing data variable
    NcVar data = dataFile.getVar("data");

    // write array to the dat_count entry in the rec dimension
    data.putVar({dat_count, 0, 0, 0}, {1, arr.shape()[0], arr.shape()[1], arr.shape([2])},
                arr.data());
}