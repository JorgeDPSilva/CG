#ifndef INDEX_H
#define INDEX_H

#include <vector>
#include <iostream>
#include <tuple>
#include <string>

using namespace std;

class Index {
private:
  tuple<int, int, int> index;

public:
  Index();

  Index(tuple<int, int, int> index);

  Index(int indexOne, int indexTwo, int indexThree);

  int get_first_index();

  int get_second_index();

  int get_third_index();

  string index_to_string();
};

#endif