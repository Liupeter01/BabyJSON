#include<babyJson.hpp>

template<typename _Ty>
std::optional<_Ty> json::BabyJSON::get_value(std::string_view value)
{
          _Ty _temp_res{};
          std::from_chars_result res = std::from_chars(value.data(), value.data() + value.size(), _temp_res);
          if (res.ec == std::errc() && res.ptr == value.data() + value.size()) {
                    return _temp_res;
          }
          return std::nullopt;
}

json::JSONType json::BabyJSON::parse(std::string_view json) 
{
          /*nothing inside json parameter, then returned*/
          if (json.empty()) {
                    return json::JSONType{ std::nullptr_t{} };
          }

          if (std::isdigit(json[0]) || json[0] == '+' || json[0] == '-') {
                    std::regex regex("[+-]?[0-9]+(\\.[0-9]*)?([eE][+-]?[0-9]+)?");
                    std::cmatch match;
                    
                    if (std::regex_search(json.data(), json.data() + json.size(), match, regex)) {
                              std::string str = match.str();

                              /*try to use optional int to parse the value*/
                              std::optional<int> value_int = get_value<int>(str);
                              if (value_int.has_value()) {
                                        return json::JSONType{ value_int.value() };
                              }

                              /*if using int to parse string failed, then try to use optional double to parse the value*/
                              std::optional<double> value_double = get_value<double>(str);
                              if (value_double.has_value()) {
                                        return json::JSONType{ value_double.value() };
                              }

                    }
          }

          return json::JSONType{ std::nullptr_t{} };
}