

int main(int argc, char const *argv[])
{

  if(arc  < 4 || argc > 5)
  {
    std::cout << "Error!!: Function not recognized." << '\n';
    return 1;
  }
  if(argc == 4)
  {
    std::cout << "Image invert called" << '\n';
  }
  else if(argc == 5)
  {
    std::cout << "Other function" << '\n';
  }

  return 0;
}
