#include <ncurses.h>

struct snake_struct
{
    int hx, hy; //h - head
    int direction; //1 - up, 2 - right, 3 - down, 4 - left
};

struct snake_struct snake;
int row, col, game_end;
const char SNAKE_SYM = 'o';

void welcome_screen(int row, int col);
int get_key_pressed();
void on_key_pressed(int *key_pressed);
void move_snake();
void draw_snake();

void welcome_screen(int row, int col)
{
    move(row / 2, col / 2 - 5);
    printw("Welcome to snake game!");

    move(row / 2 + 1, col / 2 - 7);
    printw("Press any key to continue..");
    refresh();
    getch();
}

int get_key_pressed()
{
    int ch = getch();
    if (ch == ERR) 
        return 0;
    return ch;
}

void on_key_pressed(int *key_pressed)
{
    if (*key_pressed == 27)
    {
        game_end = 1;
        return;
    }
    if (*key_pressed == 'w')
        if (snake.direction != 3) snake.direction = 1;
    if (*key_pressed == 'a')
        if (snake.direction != 2) snake.direction = 4;
    if (*key_pressed == 's')
        if (snake.direction != 1) snake.direction = 3;
    if (*key_pressed == 'd')
        if (snake.direction != 4) snake.direction = 2;
    *key_pressed = 0;
    return;
}

void draw_snake()
{
    move(snake.hy, snake.hx);
    addch(SNAKE_SYM);
    return;
}

void move_snake()
{
    move(snake.hy, snake.hx);
    addch(' ');
    if (snake.direction == 1) --snake.hy;
    else if (snake.direction == 2) ++snake.hx;
    else if (snake.direction == 3) ++snake.hy;
    else if (snake.direction == 4) --snake.hx;
    return;
}

int main()
{
    int key_pressed;
    initscr();
    noecho();
    
    getmaxyx(stdscr, row, col);

    welcome_screen(row, col);

    clear();
    refresh();
    halfdelay(1);

    snake.hx = 0;
    snake.hy = row / 2;
    snake.direction = 2;
    game_end = 0;

    while (!game_end)
    {
        draw_snake();

        key_pressed = get_key_pressed();
        if (key_pressed)
        {
            on_key_pressed(&key_pressed);
        }
        move_snake();
        refresh();
    }
    
    getch();
    endwin();
}