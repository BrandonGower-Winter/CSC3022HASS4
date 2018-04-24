

#include "../include/Image.h"




/********************Define Iterator********************/
GWRBRA001::Image::iterator::iterator(u_char *p) : ptr(p) {}

GWRBRA001::Image::iterator::iterator( const iterator & rhs) : ptr(rhs.ptr) {}

GWRBRA001::Image::iterator & GWRBRA001::Image::iterator::operator=(const iterator & rhs)
{
  GWRBRA001::Image::iterator::ptr = rhs.ptr;
  return *this;
}

void GWRBRA001::Image::iterator::operator++()
{
  ++GWRBRA001::Image::iterator::ptr;
}
void GWRBRA001::Image::iterator::operator--()
{
  --GWRBRA001::Image::iterator::ptr; //Add check here
}
unsigned char GWRBRA001::Image::iterator::operator*()
{
  return *GWRBRA001::Image::iterator::ptr;
}

bool GWRBRA001::Image::iterator::operator==(iterator rhs)
{
  return GWRBRA001::Image::iterator::ptr == rhs.ptr;
}

bool GWRBRA001::Image::iterator::operator!=(iterator rhs)
{
  return !GWRBRA001::Image::iterator::operator!=(rhs);
}

GWRBRA001::Image::iterator GWRBRA001::Image::begin(void)
{
  return GWRBRA001::Image::iterator(GWRBRA001::Image::imageBuffer.get());
}
GWRBRA001::Image::iterator GWRBRA001::Image::end(void)
{
  int endPos = GWRBRA001::Image::width * GWRBRA001::Image::height;
  return GWRBRA001::Image::iterator(GWRBRA001::Image::imageBuffer.get() + endPos);
}
