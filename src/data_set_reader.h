#ifndef DATA_SET_READER_H
#define DATA_SET_READER_H

#include "../lib/csv.h"

using namespace io;

string get_data_set()
{
  switch (current_data_set) {
  case 0:
    return "data/co2_budget.csv";
  case 1:
    return "data/co2_emmissions.csv";
  case 2:
    return "data/access_to_electricity.csv";
  default:
    return "data/co2_budget.csv";
  }
}

class DataSetReader
{
  int degree;
public:
  DataSetReader(int);
  Dataset read();
};

DataSetReader::DataSetReader(int degree=3): degree(degree) {}

Dataset DataSetReader::read() {
  int i;
  Data item1, item2, item3;
  Dataset tester1, tester2, tester3;

  CSVReader<2> in1(get_data_set());
  CSVReader<3> in2(get_data_set());
  CSVReader<4> in3(get_data_set());

  in1.read_header(ignore_extra_column, "label", "x");
  while(in1.read_row(item1.label, item1.x)){
    tester1.push_back(item1);
  }

  in2.read_header(ignore_extra_column, "label", "x", "y");
  while(in2.read_row(item2.label, item2.x, item2.y)){
    tester2.push_back(item2);
  }

  in3.read_header(ignore_extra_column, "label", "x", "y", "z");
  while(in3.read_row(item3.label, item3.x, item3.y, item3.z)){
    tester3.push_back(item3);
  }

  if (degree == 1) {
    return tester1;
  } else if (degree == 2) {
    return tester2;
  } else if (degree == 3) {
    return tester3;
  }

}

#endif
