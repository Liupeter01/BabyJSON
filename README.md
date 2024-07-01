# BabyJson

## Description

C++17 Toy JSON parser. using std::variant, std::optional and std::regex(C++11)

## Example

```C++
#include<babyJson.hpp>

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
```

## Developer Quick Start

### Platform Support

Windows, Linux, MacOS(Intel and M Serious Chip)

### Building BabyJson

```bash
git clone https://github.com/Liupeter01/BabyJSON
cd BabyJSON
cmake -B build
cmake --build build
```







