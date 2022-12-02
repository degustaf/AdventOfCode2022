#ifndef AOC2022_DAY1_HPP
#define AOC2022_DAY1_HPP

#include <array>
#include <fstream>
#include <string>

class Day1 {
  public:
    Day1(const std::string &filename);
    int part1(void) const;
    int part2(void) const;
  private:
    std::ifstream data;
    std::array<int, 3> best;

    void better(int);
};

#endif /* AOC2022_DAY1_HPP */
