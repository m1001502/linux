#ifndef DATABASELOGGER_H
#define DATABASELOGGER_H

#include <cstring>
#include <fstream>
#include <sstream>
#include <time.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <sqlite3.h>

using namespace std;

class DatabaseLogger {
public:
    static void     init(const char *path);

    static void     open();
    static void     close();
    static void     createTable();
    static void     clearTable();

    static void     insertLog(const char *date, const char *name, const char *bLogging);
    static string   getLastSeen(const char *name);
    static string   getChatLog();

    static sqlite3      *db;
    static const char   *filepath;

};

#endif
