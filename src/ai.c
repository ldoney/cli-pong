#include "../include/ai.h"

static struct Bot bot_new(struct Racket rack) {
    return (struct Bot){.m_racket=rack, .respond=&bot_respond};
}


const struct BotClass Bot={.new=&bot_new};
