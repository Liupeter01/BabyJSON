# BabyJson

## Description

C++17 Toy JSON parser. using std::variant, std::optional and std::regex(C++11)

## Example

```C++
#include<babyJson.hpp>

int main() 
{          
          json::BabyJSON json;
          std::string_view str = R"JSON([42, [2,3,"hello0"],4,5])JSON";
          auto type = json.parse(str);
          return 0;
}
```



## Developer Quick Start

### Platform Support

Windows, Linux, MacOS(Intel and M Serious Chip)

### Building BabyJson





