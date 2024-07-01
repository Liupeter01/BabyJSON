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

json::BabyJSON::ret_value json::BabyJSON::parse(std::string_view json)
{
          std::size_t i = 1;

          /*nothing inside json parameter, then returned*/
          if (json.empty()) {
                    return ret_value{ json::JSONType{ std::nullptr_t{} }, 0 };
          }

          /*processing rubbish character in the front(space tab \n\r\t\v\f\0)*/
          std::size_t pos = json.find_first_not_of(" \n\r\f\v\t\0");
          if (pos!=0 && pos!=std::string::npos) {
                    auto [value, processed] = parse(json.substr(pos));
                    return ret_value{ json::JSONType{std::move(value)}, pos + processed };
          }

          /*try to parse integer and floating point value*/
          else  if (std::isdigit(json[0]) || json[0] == '+' || json[0] == '-') 
          {
                    std::regex regex("[+-]?[0-9]+(\\.[0-9]*)?([eE][+-]?[0-9]+)?");
                    std::cmatch match;

                    if (std::regex_search(json.data(), json.data() + json.size(), match, regex)) {
                              std::string value_extracted = match.str();

                              /*try to use optional int to parse the value*/
                              std::optional<int> value_int = get_value<int>(value_extracted);
                              if (value_int.has_value()) {
                                        return ret_value{ json::JSONType{value_int.value()}, value_extracted.size()};
                              }

                              /*if using int to parse string failed, then try to use optional double to parse the value*/
                              std::optional<double> value_double = get_value<double>(value_extracted);
                              if (value_double.has_value()) {
                                        return ret_value{ json::JSONType{value_double.value()}, value_extracted.size() };
                              }
                    }
          }

          /*try to parse string type from json */
          else if (json[0] == '\"') {
                    //is there any escape character in the string
                    Escape status{ OFF };

                    std::string result{};

                    for (i = 1; i < json.size(); ++i) {
                              //Currently, there is no escape ch detected!
                              if (status == Escape::OFF) {
                                        if (json[i] == '\"') {
                                                  break;
                                        }
                                        else if (json[i] == '\\') {
                                                  status = Escape::ON;
                                        }
                                        else {
                                                  result += json[i];
                                        }
                              }
                              else {    //status == Escape::ON
                                        result += handle_escape(json[i]);
                                        status = Escape::OFF;
                              }
                    }
                    /*DO NOT forget the last ch(") */
                    return ret_value{ json::JSONType{ std::move(result)}, i + 1 };  
          }

          /*try to parse data inside [] to std::vector*/
          else if (json[0] == '[') {
                    std::vector<JSONType> result;
                    for (i = 1; i < json.size(); ) {
                              /*DO NOT forget the last ch(]) */
                              if (json[i] == ']') {
                                        i += 1;   
                                        break;
                              }

                              auto [extracted_json, already_processed] = parse(json.substr(i));

                              /*Error Occured! Reset the size to zero*/
                              if (!already_processed) {
                                        i = 0;
                                        break;
                              }
                              result.push_back(std::move(extracted_json));
                              i += already_processed;

                              //there is one comma seperate each value, so using i+=1 to skip it([1,2,3,"hello"])
                              if (json[i] == ',') {
                                        i += 1;
                              }
                    }
                    return  ret_value{ json::JSONType{ std::move(result)}, i };
          }

          /* try to parse data inside {} to std::unordered_map*/
          else if (json[0] == '{') {
                    std::unordered_map<std::string, JSONType> result;
                    for (i = 1; i < json.size(); ) {
                              /*end of }*/
                              if (json[i] == '}') {
                                        i += 1;
                                        break;
                              }

                              /*parse json key*/
                              auto [json_key, processed_key_size] = parse(json.substr(i));

                              /*Key Size =0, so Error Occured! Reset the size to zero*/
                              if (!processed_key_size) {
                                        i = 0;
                                        break;
                              }
                              else {
                                        i += processed_key_size;
                              }
                              //the json key MUST be a string Datatype
                              if (!std::holds_alternative<std::string>(json_key.inner_type)) {
                                        i = 0;
                                        break;
                              }

                              //there is one : seperate each value, so using i+=1 to skip it({"name":"alice", "info": [18, "female"]})
                              if (json[i] == ':') {
                                        i += 1;
                              }

                              /*parse json value(which is after ch : )*/
                              auto [json_value, processed_value_size] = parse(json.substr(i));

                              /*Error Occured! Reset the size to zero*/
                              if (!processed_value_size) {
                                        i = 0;
                                        break;
                              }
                              else {
                                        i += processed_value_size;
                              }

                              result.insert_or_assign(
                                        std::move(std::get<std::string>(json_key.inner_type)),
                                        std::move(json_value)
                              );

                              //there is one comma seperate each value, so using i+=1 to skip it({"name":"alice", "info": [18, "female"]})
                              if (json[i] == ',') {
                                        i += 1;
                              }
                    }
                    return  ret_value{ json::JSONType{ std::move(result)}, i };
          }
          return  ret_value{ json::JSONType{ std::nullptr_t{} }, 0 };
}

const char  json::BabyJSON::handle_escape(const char escape)
{
          switch (escape) {
                    case 'n':return '\n';
                    case 'a':return '\a';
                    case 'b':return '\b';
                    case 't':return '\t';
                    case 'f':return '\f';
                    case 'v':return '\v';
                    case 'r':return '\r';
                    case '0':return '\0';
                    default:return escape;
          }
}