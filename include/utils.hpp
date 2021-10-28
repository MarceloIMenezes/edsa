#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

bool stringTok(const std::string& s, std::string& dest, char delim, size_t *position = nullptr);

bool csvFieldParser(const std::string& line, std::string& field, size_t *position = nullptr);

#endif // UTILS_HPP
