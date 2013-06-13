#include "ChatBot.h"

/* Programm braucht drei Argumente:
*   host
*   port
*   channel
* Beispiel: irc.freenode.net    6667    DavesChannel
*/
int main(int argc, char **argv)
{
    if (argc != 4)
    {
        perror("erwarte drei Argumente");
        exit(1);
    }
    ChatBot *chatBot = new ChatBot("Banane22w", "Ananas84");
    chatBot->LoginBot(string(argv[1]), atoi(argv[2]), argv[3]);

    delete chatBot;
    return 0;
}
