#ifndef AOC2022_DAY3_HPP
#define AOC2022_DAY3_HPP

#include <fstream>
#include <string>

class Day3 {
  public:
    Day3(const std::string &filename);
    int part1(void) const;
    int part2(void) const;
  private:
    std::ifstream data;
    int priority;
    int badgePriority;
};

#endif /* AOC2022_DAY3_HPP */
