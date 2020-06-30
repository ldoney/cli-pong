
struct Bot {
    struct Racket m_racket;
};
extern const struct BotClass {
    struct Bot (*new)();
} Bot;
