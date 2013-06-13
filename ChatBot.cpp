#include "ChatBot.h"

// Konstruktor
ChatBot::ChatBot()
{

}
// Destruktor
ChatBot::~ChatBot()
{

}

// Verbindung zum Server aufbauen
void ChatBot::connectToServer(const char *host, int port)
{
    // Socket wird erstellt
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Fehler Socket");
        disconnect();
        exit(1);
    }

    // Host wird ueberprueft
    hostent *hp = gethostbyname(host);
    if (!hp)
    {
        perror("Host nicht gefunden...");
        disconnect();
        exit(1);
    }

    // Serverinformation wird festgelegt
    sockaddr_in sin;
    memset((char*)&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    memcpy((char*)&sin.sin_addr, hp->h_addr, hp->h_length);
    sin.sin_port = htons(port);
    memset(&(sin.sin_zero), 0, 8*sizeof(char));

    // Verbindung mit dem Server
    if (connect(sock, (sockaddr*) &sin, sizeof(sin)) == -1)
    {
        perror("Verbindung fehlgeschlagen...");
        disconnect();
        exit(1);
    }
}

// Verbindung trennen
void ChatBot::disconnect()
{
    close(sock);
}

// Funktion um Nachrichten an den Server zu schicken
void ChatBot::sendToServer(string m)
{
    send(sock, m.c_str(), m.length(), 0);
}

void ChatBot::pingpong(string m)
{

}
void ChatBot::botIdentify(string nick, string user, string pw)
{

}

void ChatBot::botSkills(string m)
{

}

void ChatBot::botLoop()
{

}
