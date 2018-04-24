

#include "../include/Image.h"




/********************Define Iterator********************/
GWRBRA001::Image::iterator::iterator(u_char *p) : ptr(p) {}

GWRBRA001::Image::iterator::iterator( const iterator & rhs) : ptr(rhs.ptr) {}

GWRBRA001::Image::iterator & GWRBRA001::Image::iterator::operator=(const iterator & rhs)
{
  GWRBRA001::Image::iterator::ptr = rhs.ptr;
  return *this;
}
