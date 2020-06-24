#define BALL "o"

struct Ball {
    double m_v_x, m_v_y;
    double m_x, m_y;
    void (*draw)(WINDOW *win, struct Ball *this);
    void (*reset)(WINDOW *win, struct Ball *this);
};
extern const struct BallClass {
    struct Ball (*new)();
} Ball;
