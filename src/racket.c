#include "../include/racket.h"

static void racket_draw(WINDOW *win, struct Racket *this) {
    for(int i = 0; i < BASE_RACKET_SIZE; i++)
    {
        mvwprintw(win, (this->m_y-(BASE_RACKET_SIZE / 2)) + i, this->m_x, RACKET);
    }
}
static struct Racket new(char* player, int x, int y) {
    return (struct Racket){.m_player=player, .m_size=BASE_RACKET_SIZE, .m_x=x, .m_y=y, .draw=&racket_draw};
}

const struct RacketClass Racket={.new=&new};
