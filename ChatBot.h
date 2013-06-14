#ifndef CHATBOT_H
#define CHATBOT_H

#include <vector>
#include <algorithm>
#include <sstream>

#include <sqlite3.h>

#include "IrcConnect.h"
#include "DatabaseLogger.h"
#include "BufParse.h"

class ChatBot
{
public:
    ChatBot(string nickname, string password);
    ~ChatBot();

    void            ChatBotLoop();

    IrcConnect      *connect;

    string          nickname;
    string          password;
    bool            bLogging;

    void    LoginBot(string host, int port, string channel);

    void    Logging(bool bLogging);
    void    ClearLog();
    void    LogMsg(string name, string msg);
    void    ShowLog();
    void    ShowLastSeen(string nickname);

    int     ChatBotFunctions(string buffer);
    void    Nick(string nickname);
    void    User(string username);
    void    Join(string channel);
    void    Leave(string channel);
    void    ChangeTopic(string topic);
};

#endif
