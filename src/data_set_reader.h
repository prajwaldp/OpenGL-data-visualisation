#ifndef DATA_SET_READER_H
#define DATA_SET_READER_H

#include "../lib/csv.h"

class DataSetReader
{
public:
  Dataset read();
};

Dataset DataSetReader::read() {
  int i;
  Data item;
  Dataset tester;

  io::CSVReader<4> in("data.json");
  in.read_header(io::ignore_extra_column, "label", "x", "y", "z");
  std::string label; GLfloat x, y, z;
  while(in.read_row(item.label, item.x, item.y, item.z)){
    tester.push_back(item);
  }

  return tester;
}

#endif
