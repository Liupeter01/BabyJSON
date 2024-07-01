#include<babyJson.hpp>

int main() 
{          
          json::BabyJSON json;
          std::string_view str = R"JSON([42, [2,3,"hello0"],4,5])JSON";
          auto type = json.parse(str);
          return 0;
}