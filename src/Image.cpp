

#include "../include/Image.h"
/********************Define Image********************/
GWRBRA001::Image::Image(){}

GWRBRA001::Image::~Image(){}

GWRBRA001::Image::Image(int width,int height) : width(width), height(height)
{}

GWRBRA001::Image::Image(const Image & copy) : width(copy.width), height(copy.height)
{
  //Create new space on stack for copy data
  GWRBRA001::Image::imageBuffer = std::unique_ptr<unsigned char[]>(new unsigned char[copy.width*copy.height]);
  GWRBRA001::Image::iterator beg = this->begin(), end = this->end();
  GWRBRA001::Image::iterator copyBeg = copy.begin(), copyEnd = copy.end();

  while(copyBeg != copyEnd)
  {
    *beg = *copyBeg;
    ++beg;
    ++copyBeg;
  }
}

GWRBRA001::Image::Image(Image && move) : width(move.width), height(move.height)
{
  move.width = 0;
  move.height = 0;
  GWRBRA001::Image::imageBuffer = std::move(move.imageBuffer);
}

GWRBRA001::Image & GWRBRA001::Image::operator=(const Image & copy)
{
  GWRBRA001::Image::width = copy.width;
  GWRBRA001::Image::height = copy.height;

  GWRBRA001::Image::imageBuffer = std::unique_ptr<unsigned char[]>(new unsigned char[copy.width*copy.height]);
  GWRBRA001::Image::iterator beg = this->begin(), end = this->end();
  GWRBRA001::Image::iterator copyBeg = copy.begin(), copyEnd = copy.end();

  while(copyBeg != copyEnd)
  {
    *beg = *copyBeg;
    ++beg;
    ++copyBeg;
  }

  return *this;

}

GWRBRA001::Image & GWRBRA001::Image::operator=(Image && move)
{

  GWRBRA001::Image::width = move.width;
  GWRBRA001::Image::height = move.height;
  move.width = 0;
  move.height = 0;
  GWRBRA001::Image::imageBuffer = std::move(move.imageBuffer);

  return *this;
}
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
unsigned char & GWRBRA001::Image::iterator::operator*() const
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

GWRBRA001::Image::iterator GWRBRA001::Image::begin(void) const
{
  return GWRBRA001::Image::iterator(GWRBRA001::Image::imageBuffer.get());
}
GWRBRA001::Image::iterator GWRBRA001::Image::end(void) const
{
  int endPos = GWRBRA001::Image::width * GWRBRA001::Image::height;
  return GWRBRA001::Image::iterator(GWRBRA001::Image::imageBuffer.get() + endPos);
}
