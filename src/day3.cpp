#include "day3.hpp"

#include <string>
#include <thread>

#include "channels.hpp"

using std::string;

static void producer(std::ifstream *data, channel<string> *ch, channel<string> *ch2) {
  string s;

  while(getline(*data, s)) {
    ch->send(s);
    ch2->send(s);
  }

  ch->close();
  ch2->close();
}

static int priority(char c) {
  if(c >= 'a') {
    return c - 'a' + 1;
  }
  return c - 'A' + 27;
}

static void consumer(channel<string> *ch, int *result) {
  int acc = 0;
  while(true) {
    auto n = ch->receive();
    if(n) {
      auto s = *n;
      auto second = s.substr(s.length()/2);
      s.resize(s.length()/2);
      for(auto it = s.begin(); it != s.end(); it++) {
	if(second.find(*it) != string::npos) {
	  acc += priority(*it);
	  break;
	}
      }
    } else {
      *result = acc;
      return;
    }
  }
}

static void consumer2(channel<string> *ch, int *result) {
  int acc = 0;
  while(true) {
    auto n = ch->receive();
    if(!n) break;
    auto string1 = *n;
    n = ch->receive();
    if(!n) break;
    auto string2 = *n;
    n = ch->receive();
    if(!n) break;
    auto string3 = *n;

    for(auto it = string1.begin(); it != string1.end(); it++) {
      if((string2.find(*it) != string::npos) && (string3.find(*it) != string::npos)) {
	acc += priority(*it);
	break;
      }
    }
  }

  *result = acc;
}

Day3::Day3(const string &filename) : data(filename), priority(0), badgePriority(0) {
  channel<string> ch;
  channel<string> ch2;

  std::thread p(producer, &data, &ch, &ch2);
  std::thread c(consumer, &ch, &priority);
  std::thread c2(consumer2, &ch2, &badgePriority);

  p.join();
  c.join();
  c2.join();
}

int Day3::part1(void) const {
  return priority;
}

int Day3::part2(void) const {
  return badgePriority;
}
