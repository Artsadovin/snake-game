#include <ncurses.h>
#define SNAKE_SYM 'o'
#define FIELD_SYM '#'

struct snake_struct
{
    int hx, hy; //h - head
    int direction; //1 - up, 2 - right, 3 - down, 4 - left
};

struct field_struct
{
    int x, y; //coordinates of up left corner of field
    int w, h; // width and height of field
};

struct snake_struct snake;
struct field_struct field;
int row, col, game_end;
//const char SNAKE_SYM = 'o';

void swap(int *a, int *b);
void welcome_screen(int row, int col);
int get_key_pressed();
void on_key_pressed(int *key_pressed);
void init_field();
void init_snake();
void draw_field();
void draw_snake();
void move_snake();

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

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

void init_field()
{
    field.w = 50;
    field.h = 25;
    field.x = (col - field.w) / 2;
    field.y = (row - field.h) / 2;
    return;
}

void init_snake()
{
    snake.hx = 0;
    snake.hy = row / 2;
    snake.direction = 2;
    return;
}

void draw_field()
{
    int i;
    move(field.y, field.x);
    for (i = field.x; i < field.x + field.w; ++i)
    {
        move(field.y, i);
        addch(FIELD_SYM);
    }
    for (i = field.y; i < field.y + field.h; ++i)
    {
        move(i, field.x);
        addch(FIELD_SYM);
    }
    for (i = field.x; i < field.x + field.w; ++i)
    {
        move(field.y + field.h - 1, i);
        addch(FIELD_SYM);
    }
    for (i = field.y; i < field.y + field.h; ++i)
    {
        move(i, field.x + field.w - 1);
        addch(FIELD_SYM);
    }
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

    init_snake();
    init_field();
    draw_field();
    getch();
    halfdelay(1);
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