#ifndef BUFPARSE_H
#define BUFPARSE_H

#include <vector>
#include <ctime>
#include <sstream>
#include <stdio.h>
#include <string>

using namespace std;

class BufParse {
public:
    BufParse(string msg);
    ~BufParse() {};

    string          sender;
    vector<string>  message;

    int atPosition(string msgVar);
};

#endif
