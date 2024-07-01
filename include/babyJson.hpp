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
          enum Escape { OFF, ON };

          struct JSONType {
                    using JSONList = std::vector<JSONType>;
                    using JSONDictonary = std::unordered_map<std::string, JSONType>;

                    std::variant<
                              std::nullptr_t,                //nothing
                              bool,                            //true, false
                              int,                                 //18
                              double,                         //100.5;
                              std::string,                   //"female"
                              JSONList,                   //[18, "female"]
                              JSONDictonary           //{"name":"alice", "info": [18, "female"]}
                    > inner_type;
          };

          class BabyJSON {
                    using ret_value = std::pair<json::JSONType, std::size_t>;

          public:
                    ret_value parse(std::string_view json);

          private:
                    const char handle_escape(const char escape);

                    template<typename _Ty>
                    std::optional<_Ty> get_value(std::string_view value);
          };
};

#endif // !_BABYJSON_HPP_
