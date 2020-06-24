#define RACKET "H"
#define BASE_RACKET_SIZE 9

struct Racket {
    char* m_player;
    int m_x, m_y, m_size;
    void (*draw)(WINDOW *win, struct Racket *this);
};
extern const struct RacketClass {
    struct Racket (*new)(char* player, int x, int y);
} Racket;
