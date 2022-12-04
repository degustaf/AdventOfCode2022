#ifndef AOC2022_DAY2_HPP
#define AOC2022_DAY2_HPP

#include <fstream>
#include <string>

class Day2 {
  public:
    Day2(const std::string &filename);
    int part1(void) const;
    int part2(void) const;
  private:
    std::ifstream data;
    int acc;
    int acc2;
};

#endif /* AOC2022_DAY2_HPP */
