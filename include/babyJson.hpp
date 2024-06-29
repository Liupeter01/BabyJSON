#pragma once
#ifndef _BABYJSON_HPP_
#define _BABYJSON_HPP_
#include<iostream>
#include<string>
#include<variant>
#include<regex>
#include<optional>
#include<charconv>
#include<unordered_map>

namespace json {
          struct JSONType {
                    using argument_type = std::variant<
                              std::nullptr_t,                                                             //nothing
                              bool,                                                                           //true, false
                              int,                                                                              //18
                              double,                                                                       //100.5;
                              std::string,                                                                  //"female"
                              std::vector<JSONType>,                                           //[18, "female"]
                              std::unordered_map<std::string, JSONType>>;       //{"name":"alice", "info": [18, "female"]}

                    argument_type inner_type;
          };

          class BabyJSON{
          public:
                    JSONType parse(std::string_view json);

                    template<typename _Ty>
                    std::optional<_Ty> get_value(std::string_view value);
          };
};

#endif // !_BABYJSON_HPP_
