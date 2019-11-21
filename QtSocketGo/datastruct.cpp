#include "datastruct.h"

//===================== DataStruct ===============

DataStruct::DataStruct(){}

//====================== SimpleStr =================


string simpleStr::toString(){
    return data;
}

void simpleStr::init(string jstr){
    this->data= jstr;
}
