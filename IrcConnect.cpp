#include "IrcConnect.h"

// Konstruktor
IrcConnect::IrcConnect(string host, int port, string channel)
{
    this->host = host;
    this->port = port;
    this->channel = channel;
}

// Destruktor
IrcConnect::~IrcConnect()
{
}

void IrcConnect::Connect() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Failed to create socket...");
        Disconnect();
        return;
    }
    hostent *hp = gethostbyname(host.c_str());
    if (!hp)
    {
        perror("Failed to get hostname...");
        Disconnect();
        return;
    }

    sockaddr_in sin;
    memset((char*)&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    memcpy((char*)&sin.sin_addr, hp->h_addr, hp->h_length);
    sin.sin_port = htons(port);
    memset(&(sin.sin_zero), 0, 8*sizeof(char));

    if (connect(sock, (sockaddr*) &sin, sizeof(sin)) == -1)
    {
        perror("Failed to connect socket...");
        Disconnect();
        return;
    }
}
void IrcConnect::Disconnect()
{
    close(sock);
}
void IrcConnect::Send(string msg) {
    send(sock, msg.c_str(), msg.length(), 0);
}
bool IrcConnect::Receive(string &buf) {
    char buffer[BUFSIZE+1] = {0};
    if (recv(sock, buffer, BUFSIZE*sizeof(char), 0) < 0) {
        perror("Failed to receive message...");
        return false;
    }
    buf = ParseIrc(string(buffer));
    return true;
}
void IrcConnect::Identify(string name, string pw, string channel)
{
    Send("NICK " + name + "\r\n");
    Send("USER " + name + " 0 0  :" + name + "\r\n");
    Send("PRIVMSG NickServ IDENTIFY " + pw + "\r\n");
    SetChannel(channel);
    Send("PRIVMSG #" + channel + " :Hallo!\r\n");
}
void IrcConnect::PingPong(string buffer)
{
    size_t pos = buffer.find("PING");
    if (pos != string::npos) {
        string pong("PONG" + buffer.substr(pos + 4)+"\r\n");
        cout << pong << endl;
        Send(pong);
    }
}
string IrcConnect::ParseIrc(string buffer) {
    if (buffer.find("\r\n") == buffer.length()-2)
        buffer.erase(buffer.length()-2);
    return buffer;
}
void IrcConnect::SetChannel(string channel)
{
    Send("JOIN #" + channel + "\r\n");
    this->channel = channel;
}
string IrcConnect::GetChannel()
{
    return channel;
}
