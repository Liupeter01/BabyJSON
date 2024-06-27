#include<babyJson.hpp>

int main() 
{
          std::string s_data = "42";
          auto res = parse(s_data);

          const char* c_data = "42";
          auto res = parse(c_data);
          return 0;
}