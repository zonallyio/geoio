#pragma once
#ifndef GEOIO_DRIVER_H_
#define GEOIO_DRIVER_H_
#include <string>
#include "model.hpp"

using std::string;

namespace {
class custom_exception : public std::exception
{
  private:
    char* errmsg;

  public:
    custom_exception(char* msg)
      : errmsg(msg)
      , std::exception(){};

    custom_exception(string msg)
      : errmsg(const_cast<char*>(msg.c_str()))
      , std::exception(){};

    char* what() { return this->errmsg; }
};

} // namespace

namespace geoio {

struct driver
{
    string short_name;
    string long_name;
    string extension;

    driver()
      : short_name("")
      , long_name("")
      , extension(""){};

    driver(string s, string l, string e)
      : short_name(s)
      , long_name(l)
      , extension(e){};

    virtual void info() const
    {
        throw custom_exception(
          "this virtual driver class does not implement the info() method."
        );
    };

    virtual model& read() const
    {
        throw custom_exception(
          "this virtual driver class does not implement the read() method."
        );
    };

    virtual void write(model&) const
    {
        throw custom_exception(
          "this virtual driver class does not implement the write() method."
        );
    };
};

struct vector_driver : driver
{
    virtual void    info() const;
    virtual vector& read() const;
    virtual void    write(vector&) const;
};

struct raster_driver : driver
{
    virtual void    info() const;
    virtual raster& read() const;
    virtual void    write(raster&) const;
};

} // namespace geoio
#endif