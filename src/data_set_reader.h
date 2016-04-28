#ifndef DATA_SET_READER_H
#define DATA_SET_READER_H

class DataSetReader
{
public:
  Dataset read();
};

Dataset DataSetReader::read() {
  int i;

  Data item;
  Dataset tester;

  ifstream infile("data.json");

  if (infile.is_open()) {
    while (infile >> item.label >> item.y >> item.x >> item.z) {
      tester.push_back(item);
    }
  } else {
    cout << "File not found\n";
  }

  return tester;
}

#endif
