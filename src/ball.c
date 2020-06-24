#include "../include/ball.h"

static void ball_draw(WINDOW *win, struct Ball *this) {
	mvwprintw(win, (int)this->m_y, (int)this->m_x, BALL);
}
static void ball_reset(WINDOW *win, struct Ball *this) {
    int max_x = 0, max_y = 0;
    getmaxyx(win, max_y, max_x);
    this->m_v_x = 1;
    this->m_v_y = 0;
    this->m_x = max_x / 2;
    this->m_y = max_y / 2;
}
static struct Ball ball_new() {
    return (struct Ball){.draw=&ball_draw, .reset=&ball_reset};
}

const struct BallClass Ball={.new=&ball_new};
