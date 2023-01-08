#pragma once
#ifndef GEOIO_INTERFACE_H_
#define GEOIO_INTERFACE_H_
#include <algorithm>
#include <cctype>
#include "driver.hpp"

namespace { // private
// super simple constexpr hash from: https://stackoverflow.com/a/46711735
constexpr inline unsigned int hash(const char* s, int off = 0)
{
    return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}

// define a custom constexpr user literal for strings for switch-case
constexpr inline unsigned int operator""_(const char* s, size_t)
{
    return hash(s);
}
} // namespace

namespace geoio {

inline driver get_driver(string drv)
{
    // convert drv to lowercase
    std::transform(drv.begin(), drv.end(), drv.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    driver new_driver = driver();
    switch (hash(drv.c_str())) {
        // raster
        case "geotiff"_:
        case "zarr"_:
        case "raster-gpkg"_:
        // vector
        case "shp"_:
        case "flatgeobuf"_:
        case "geojson"_:
        case "gpkg"_:
        default:
            // fail if no matching driver
            // TODO: customize this exception to provide better output to user
            throw std::exception();
    }

    return new_driver;
}

} // namespace geoio
#endif