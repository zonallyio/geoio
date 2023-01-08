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

class driver
{
  protected:
    string _short;
    string _long;
    string _ext;

  public:
    driver()
      : _short("")
      , _long("")
      , _ext(""){};

    driver(string s, string l, string e)
      : _short(s)
      , _long(l)
      , _ext(e){};

    string       short_name() { return this->_short; }
    string       long_name() { return this->_long; }
    string       extension() { return this->_ext; }

    virtual void info() const
    {
        throw custom_exception(
          "this virtual driver class does not implement the info() method."
        );
    };

    virtual bool read(string, model&) const
    {
        throw custom_exception(
          "this virtual driver class does not implement the read() method."
        );
    };

    virtual bool write(string, model&) const
    {
        throw custom_exception(
          "this virtual driver class does not implement the write() method."
        );
    };
};

class driver_vector : public driver
{
    virtual void info() const;
    virtual bool read(string, vector&) const;
    virtual bool write(string, vector&) const;
};

class driver_raster : public driver
{
    virtual void info() const;
    virtual bool read(string, raster&) const;
    virtual bool write(string, raster&) const;
};

} // namespace geoio
#endif