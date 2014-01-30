#ifndef PIXUTIL_H
#define PIXUTIL_H

#include <string>

class PixUtil {

public: 
  static bool bothAreSpaces(char lhs, char rhs);
  static void replaceAll(std::string& str, const std::string& from, const std::string& to);

};

#endif

