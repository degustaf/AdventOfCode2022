#include "day1.hpp"

#include <chrono>
#include <iostream>

// int main(int argc, char* argv[]) {
int main(void) {

  auto start = std::chrono::high_resolution_clock::now();
  Day1 testProb("data/sampleDay1.txt");
  Day1 prob("data/Day1.txt");
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << testProb.part1() << "\n";
  std::cout << testProb.part2() << "\n";

  std::cout << prob.part1() << "\n";
  std::cout << prob.part2() << "\n";

  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
    << "μs\n";

  return 0;
}
