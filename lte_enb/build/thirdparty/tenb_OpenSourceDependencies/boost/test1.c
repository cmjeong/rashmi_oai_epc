#include <stdlib.h>
#include <iostream.h>
#include <string>


int main()
{
   string array;
   realpath("test.txt",array);
   std::cout<<"path:"<<array;
   return 0;
}
