#include "index.hpp"

Index::Index() {}

Index::Index(tuple<int, int, int> index) {
  this->index = index;
}

Index::Index(int indexOne, int indexTwo, int indexThree) {
  this->index = make_tuple(indexOne, indexTwo, indexThree);
}

int Index::get_first_index() { 
    return get<0>(this->index); 
}

int Index::get_second_index() { 
    return get<1>(this->index); 
}

int Index::get_third_index() { 
    return get<2>(this->index); 
    }

string Index::index_to_string() {
  return to_string(this->get_first_index()) + " " +
         to_string(this->get_second_index()) + " " +
         to_string(this->get_third_index());
}