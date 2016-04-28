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

  for (i = 1; i <= 10; i++) {
    item.x = i;
    item.y = i;
    item.z = i;

    tester.push_back(item);
  }

  return tester;
}

#endif
