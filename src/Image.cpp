#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
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
//Add
GWRBRA001::Image GWRBRA001::Image::operator+(const Image & rhs)
{
  if(GWRBRA001::Image::width * GWRBRA001::Image::height != rhs.width * rhs.height)
  {
    return GWRBRA001::Image();
  }
  GWRBRA001::Image temp(rhs.width,rhs.height);
  GWRBRA001::Image::iterator beg = this->begin(), end = this->end();
  GWRBRA001::Image::iterator rhsBeg = rhs.begin();
  GWRBRA001::Image::iterator tempBeg = temp.begin();

  while(beg != end)
  {
    *tempBeg = *beg + *rhsBeg;
    *tempBeg = GWRBRA001::Image::clamp(*tempBeg);
    ++tempBeg;
    ++beg;
    ++rhsBeg;
  }
  return temp;
}
//Sub
GWRBRA001::Image GWRBRA001::Image::operator-(const Image & rhs)
{
  if(GWRBRA001::Image::width * GWRBRA001::Image::height != rhs.width * rhs.height)
  {
    return GWRBRA001::Image();
  }
  GWRBRA001::Image temp(rhs.width,rhs.height);
  GWRBRA001::Image::iterator beg = this->begin(), end = this->end();
  GWRBRA001::Image::iterator rhsBeg = rhs.begin();
  GWRBRA001::Image::iterator tempBeg = temp.begin();

  while(beg != end)
  {
    *tempBeg = *beg - *rhsBeg;
    *tempBeg = GWRBRA001::Image::clamp(*tempBeg);
    ++tempBeg;
    ++beg;
    ++rhsBeg;
  }
  return temp;
}

GWRBRA001::Image GWRBRA001::Image::operator!() //Invert
{
  GWRBRA001::Image temp(GWRBRA001::Image::width,GWRBRA001::Image::height);
  GWRBRA001::Image::iterator beg = this->begin(), end = this->end();
  GWRBRA001::Image::iterator tempBeg = temp.begin();
  while(beg != end)
  {
    *tempBeg = 255 - *beg; //No need to clamp
    ++tempBeg;
    ++beg;
  }
  return temp;
}

GWRBRA001::Image GWRBRA001::Image::operator/(const Image & rhs)
{
  if(GWRBRA001::Image::width * GWRBRA001::Image::height != rhs.width * rhs.height)
  {
    return GWRBRA001::Image();
  }
  GWRBRA001::Image temp(rhs.width,rhs.height);
  GWRBRA001::Image::iterator beg = this->begin(), end = this->end();
  GWRBRA001::Image::iterator rhsBeg = rhs.begin();
  GWRBRA001::Image::iterator tempBeg = temp.begin();

  while(beg != end)
  {
    if(*rhsBeg == 255)
    {
      *tempBeg = *beg;
    }
    else
    {
      *tempBeg = 0;
    }
    ++tempBeg;
    ++beg;
    ++rhsBeg;
  }
  return temp;
}

GWRBRA001::Image GWRBRA001::Image::operator*(int threshold)
{
  GWRBRA001::Image temp(GWRBRA001::Image::width,GWRBRA001::Image::height);
  GWRBRA001::Image::iterator beg = this->begin(), end = this->end();
  GWRBRA001::Image::iterator tempBeg = temp.begin();

  while(beg != end)
  {
    if(*beg > threshold)
    {
      *tempBeg = 255;
    }
    else
    {
      *tempBeg = 0;
    }
    ++tempBeg;
    ++beg;
  }
  return temp;
}

unsigned char GWRBRA001::Image::clamp(const unsigned char & val)
{
  if(val > 255) return 255;
  if(val < 0) return 0;
  return val;
}
void GWRBRA001::Image::load(std::string filePath)
{
  std::ifstream in(filePath,std::ios::binary);
  if(!in)
  {
    std::cout << "File does not exist: " << filePath << '\n';
    return;
  }
  std::string placeHolder;
  std::getline(in,placeHolder,'\n');
  if(placeHolder != "P5")
  {
    std::cout << "Image not PGM: " << placeHolder << '\n';
    return;
  }
  int rows,cols;
  while(std::getline(in,placeHolder,'\n'))
  {
    if(placeHolder[0] != '#')
    {
      std::stringstream strStream(placeHolder);
      strStream >> rows;
      strStream >> cols;
      break;
    }
    else
      std::cout << "Comment:" << '\n' << placeHolder << '\n';
  }
  int threshold;
  in >> threshold;
  GWRBRA001::Image::width = cols;
  GWRBRA001::Image::height = rows;
  std::cout << "Rows: "<< rows << " Cols: " << cols << '\n';
  std::cout << "Threshold Value: " << threshold << '\n';

  GWRBRA001::Image::imageBuffer = std::unique_ptr<unsigned char[]>(new unsigned char[cols * rows]);
  /*GWRBRA001::Image::iterator beg = this->begin(), end = this->end();
  while(beg != end)
  {
    in >> *beg;
    ++beg;
  }*/
  in >> *this;
}

void GWRBRA001::Image::save(std::string filePath)
{
  std::ofstream out(filePath,std::ios::binary);
  if(!out)
  {
    std::cout << "File does not exist: " << filePath << '\n';
    return;
  }
  out << "P5" << '\n';
  out << "# Created by the GWRBRA001 image processeor!" << '\n';
  out << GWRBRA001::Image::height << ' ' << GWRBRA001::Image::width << '\n';
  out << 255 << '\n';
  /*GWRBRA001::Image::iterator beg = this->begin(), end = this->end();
  while(beg != end)
  {
    out << *beg;
    ++beg;
  }*/
  out << *this;
}

std::ostream& GWRBRA001::operator<<(std::ostream & os, const GWRBRA001::Image& img)
{
  GWRBRA001::Image::iterator beg = img.begin(), end = img.end();
  while (beg != end)
  {
    os << *beg;
    ++beg;
  }
  return os;
}

//Input
//If it throws an error it means that not enough binary values exist and the image size is wrong
std::istream & GWRBRA001::operator>>(std::istream & is, GWRBRA001::Image & img)
{

  GWRBRA001::Image::iterator beg = img.begin(), end = img.end();
  while (beg != end)
  {
    is >> *beg;
    ++beg;
  }
  return is;
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
  return !GWRBRA001::Image::iterator::operator==(rhs);
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
