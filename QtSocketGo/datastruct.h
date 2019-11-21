#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>
#include <QDialog>
#include <string.h>
#include <string>
using namespace std;

/*
 DataStruct is a pure virtual class to produce other class that
 translate different type of data between qt and go
*/
class DataStruct {
public:
    DataStruct();
    virtual ~DataStruct()=0;
    virtual string toString()=0;
    virtual void init(string)=0;
};

//====================== SimpleStr =================

class simpleStr : public DataStruct {
public:
    string data;
public:
    ~simpleStr();
    string toString();
    void init(string jstr);
};


#endif // DATASTRUCT_H
