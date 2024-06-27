#pragma once
#ifndef _BABYJSON_HPP_
#define _BABYJSON_HPP_
#include<iostream>
#include<string>
#include<variant>
#include<regex>
#include<unordered_map>

struct JSONType {
          using argument_type = std::variant<bool, int, double, std::string, std::vector<JSONType>, std::unordered_map<std::string, JSONType>>;
          argument_type inner_type;
};

JSONType parse(std::string_view json);

#endif // !_BABYJSON_HPP_
