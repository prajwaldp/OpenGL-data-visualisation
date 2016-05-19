#ifndef DATA_SET_READER_H
#define DATA_SET_READER_H

#include "../lib/csv.h"

string DATA_FILE = "data/co2_budget.csv";

using namespace io;

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

  CSVReader<2> in1(DATA_FILE);
  CSVReader<3> in2(DATA_FILE);
  CSVReader<4> in3(DATA_FILE);

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
