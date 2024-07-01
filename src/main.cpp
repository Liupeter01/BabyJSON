#include<babyJson.hpp>

int main() 
{          
          json::BabyJSON json;
          std::string_view str = R"(
                    {
                        "sites": [
                        { "name":"youtube" , "url":"www.youtube.com" }, 
                        { "name":"google" , "url":"www.google.com" }, 
                        { "name":"ins" , "url":"www.instagram.com" }
                        ]
                    }
          )";

          auto [value, counter] = json.parse(str);
          return 0;
}