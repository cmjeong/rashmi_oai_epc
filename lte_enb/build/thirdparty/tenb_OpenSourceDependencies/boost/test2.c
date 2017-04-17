#include <iostream.h>
#include <string>
#include <fstream>
#include "filesystem.hpp"
using namespace std;
int main()
{
   namespace fs = boost::filesystem;
   fs::path p("~/test.txt");
   fs::path full_p = fs::complete(p); // complete == absolute
   //std::cout << "The absolute path: " << full_p;
   return 0;
}
