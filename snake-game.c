#include <ncurses.h>
#include <stdlib.h>
#define SNAKE_SYM "o"
#define FIELD_SYM '#'

struct node
{
    int x, y;
    struct node *next; //pointer to the next part of snake
};

struct field_struct
{
    int x, y; //coordinates of up left corner of field
    int w, h; // width and height of field
};

struct game_state
{
    struct node* head;
    int grow;
    int direction;
    int game_end;
};

struct field_struct field;
int row, col, game_end;

void welcome_screen(int row, int col);
int get_key_pressed();
void on_key_pressed(int* key_pressed, struct game_state* state);
void init_field();
struct node* create_node(int x, int y);
void draw_field();
void draw_snake(struct game_state* state);
void move_snake(struct node** head, int direction, int grow);

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

void on_key_pressed(int* key_pressed, struct game_state* state)
{
    if (*key_pressed == 27)
    {
        (*state).game_end = 1;
        return;
    }
    if (*key_pressed == 'w' && (*state).direction != 3) (*state).direction = 1;
    if (*key_pressed == 'a' && (*state).direction != 2) (*state).direction = 4;
    if (*key_pressed == 's' && (*state).direction != 1) (*state).direction = 3;
    if (*key_pressed == 'd' && (*state).direction != 4) (*state).direction = 2;
    if (*key_pressed == 'n') (*state).grow = 1;
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

struct node* create_node(int x, int y)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->x = x;
    new_node->y = y;
    new_node->next = NULL;
    return new_node;
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

void draw_snake(struct game_state* state)
{
    struct node* current = state->head;
    while (current != NULL)
    {
        mvprintw(current->y, current->x, SNAKE_SYM);
        current = current->next;
    }
    return;
}

void move_snake(struct node** head, int direction, int grow)
{
    int new_x = (*head)->x;
    int new_y = (*head)->y;
    if (direction == 1) --new_y;
    else if (direction == 2) ++new_x;
    else if (direction == 3) ++new_y;
    else if (direction == 4) --new_x;

    //redefine snake head
    struct node* new_head = create_node(new_x, new_y);
    new_head->next = *head;
    *head = new_head;

    //delete tail (last element) if necessary
    if (!grow)
    {
        struct node* tmp = *head;
        while (tmp->next->next != NULL)
            tmp = tmp->next;
        free(tmp->next);
        tmp->next = NULL;
    }
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
    struct game_state state;
    state.head = create_node(0, row / 2);
    state.direction = 2;
    state.grow = 0;
    init_field();
    draw_field();

    while (!state.game_end)
    {
        clear();
        //draw_field();
        state.grow = 0;
        draw_snake(&state);

        key_pressed = get_key_pressed();
        if (key_pressed)
        {
            on_key_pressed(&key_pressed, &state);
        }
        move_snake(&(state.head), state.direction, state.grow);
        
        refresh();
    }    
    getch();
    endwin();
}