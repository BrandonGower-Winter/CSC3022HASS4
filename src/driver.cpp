#include <string>
#include <iostream>
#include "../include/Image.h"

int main(int argc, char const *argv[])
{
  if(argc  < 4 || argc > 5)
  {
    std::cout << "Error!!: Function not recognized." << '\n';
    return 1;
  }
  if(argc == 4)
  {
    //outputFileName = argv[3];
    std::cout << "Image invert called" << '\n';
    GWRBRA001::Image img;
    img.load(argv[2]);
    img.save(argv[3]);
  }
  else if(argc == 5)
  {
    //Function id = argv[1]
    if(argv[1] == "-t")
    {
      std::cout << "Threshold function called" << '\n';
    }
    else if(argv[1] == "-a")
    {
      std::cout << "Add function called" << '\n';
    }
    else if(argv[1] == "-s")
    {
      std::cout << "Subtract function called" << '\n';
    }
    else if(argv[1] == "-l")
    {
      std::cout << "Mask function called" << '\n';
    }
    else
    {
      std::cout << "Error!!: Function not recognized." << '\n';
      return 1;
    }
  }
  return 0;
}
