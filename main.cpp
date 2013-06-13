#include "ChatBot.h"

int main() {
    ChatBot bot;
    bot.connectToServer("irc.freenode.net", 6667);
    bot.disconnect();

    return 0;
}
