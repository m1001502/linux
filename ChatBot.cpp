#include "ChatBot.h"

// Konstruktor
ChatBot::ChatBot(string nickname, string password)
{
    this->nickname = nickname;
    this->password = password;
    this->bLogging = false;
    connect = NULL;

}

// Destruktor
ChatBot::~ChatBot()
{
    delete connect;
}

void ChatBot::ChatBotLoop()
{
    string message;
    for (;;) {
        if (!connect->Receive(message))
            break;
        cout << message << endl;
        connect->PingPong(message);
        if (ChatBotFunctions(message) == -1)
            break;
    }
}

void ChatBot::LoginBot(string host, int port, string channel)
{
    connect = new IrcConnect(host, port, channel);
    connect->Connect();
    connect->Identify(nickname, password, channel);
    ChatBotLoop();
    connect->Disconnect();
}


void ChatBot::ChangeTopic(string topic)
{
    connect->Send("TOPIC #" + connect->GetChannel() + " " + topic + "\r\n");
}
void ChatBot::Nick(string nickname)
{
    connect->Send("NICK " + nickname + "\r\n");
}
void ChatBot::User(string username)
{
    connect->Send("USER " + username + " 0 0  :" + username + "\r\n");
}
void ChatBot::Join(string channel)
{
    connect->SetChannel(channel);
}
void ChatBot::Leave(string channel)
{
    connect->Send("PART #" + channel + "\r\n");
}

int ChatBot::ChatBotFunctions(string buffer)
{
    BufParse data(buffer);
    int pos=0;

    if (bLogging)
    {
        stringstream buf;
        for(int i=0;i<(int)data.message.size();i++)
            buf << data.message[i] << " ";
        if (data.message.size() > 0)
            LogMsg(data.sender, buf.str());
    }

    if( (pos=data.atPosition("-topic")) != -1 && (int)data.message.size() > pos+1)
    {
        ChangeTopic(data.message[pos+1]);
        connect->Send("PRIVMSG #" + connect->GetChannel() + " :topic changed\r\n");
    }
    if( (pos=data.atPosition("-nick")) != -1 && (int)data.message.size() > pos+1 )
    {
        Nick(data.message[pos+1]);
        connect->Send("PRIVMSG #" + connect->GetChannel() + " :name changed\r\n");
    }
    if( (pos=data.atPosition("-join")) != -1 && (int)data.message.size() > pos+1 )
    {
        Join( data.message[pos+1] );
    }
    if( (pos=data.atPosition("-leave")) != -1 && (int)data.message.size() > pos+1 )
    {
        connect->Send("PRIVMSG #" + connect->GetChannel() + " :ciao!\r\n");
        Leave( data.message[pos+1] );
    }
    if((pos=data.atPosition("-show_log")) != -1 )
    {
        //ShowLog();
    }
    if ((pos=data.atPosition("-last_seen")) != -1 && data.message.size() > pos+1)
    {
        //ShowLastSeen(data.message[pos+1]);
    }
    if ((pos=data.atPosition("-exit")) != -1 )
    {
        connect->Send("PRIVMSG #" + connect->GetChannel() + " :cya!\r\n");
        connect->Send("QUIT cya\r\n");
        return -1;
    }
    if ((pos=data.atPosition("-log")) != -1 && (int)data.message.size() > pos+1 ) {
        if (data.message[pos+1] == "on" )
        {
            bLogging = true;
            connect->Send("PRIVMSG #" + connect->GetChannel() + " :chat logging on\r\n");
        } else if( data.message[pos+1] == "off" )
        {
            bLogging = false;
            connect->Send("PRIVMSG #" + connect->GetChannel() + " :chat logging on\r\n");
        }
    }

    return 0;
}
