/*
* Brandon Gower - Winter
* Assignment 4
*/

#ifndef _IMAGE
#define _IMAGE

#include <string>
#include <memory>
#include <iostream>

namespace GWRBRA001
{
  class Image
  {
    private:
      int width, height;
      std::unique_ptr<unsigned char[]> imageBuffer;
    public:
      //Constructors

      Image(void);
      ~Image(void);

      Image(int width,int height);

      Image(const Image & copy);
      Image(Image && move);

      //Operator Overloads
      Image & operator=(const Image & copy);
      Image & operator=(Image && move);

      //Make sure they are the same size
      Image operator+(const Image & rhs); //Add
      Image operator-(const Image & rhs); //Sub

      Image operator!(); //Invert
      Image operator/(const Image & rhs);//Mask
      Image operator*(int threshold);

      //Functions
      void load(std::string filePath);
      void save(std::string filePath);

      //Friends
      friend std::ostream& operator<<(std::ostream & os, const Image& img); //Output
      friend std::istream & operator>>(std::istream & is, Image & img); //Input

      unsigned char clamp(const unsigned char & val);
      //Iterator
      class iterator
      {
        private:
          unsigned char *ptr;
          iterator(u_char *p);
        public:
          iterator( const iterator & rhs);
          // define overloaded ops: *, ++, --, =
          iterator & operator=(const iterator & rhs);
          // other methods for iterator
          void operator++();
          void operator--();
          bool operator==(iterator rhs);
          bool operator!=(iterator rhs);
          unsigned char & operator*() const;
          friend Image;
        };
      // define begin()/end() to get iterator to start and
      // "one-past" end.
      iterator begin(void) const;
      iterator end(void) const;
  };

  std::ostream& operator<<(std::ostream & os, const Image& img); //Output
  std::istream & operator>>(std::istream & is, Image & img); //Input

}

#endif
