#ifndef AOC2022_DAY1_H
#define AOC2022_DAY1_H

#include <fstream>
#include <string>

class Day1 {
  public:
    Day1(const std::string &filename) : data(filename) {};
  private:
    std::ifstream data;
};

#endif /* AOC2022_DAY!_H */
