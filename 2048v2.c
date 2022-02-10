#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct tile {
    int pos_x;
    int pos_y;
    int val;
};

typedef struct tile Tile;

Tile array[16];
const int count_row = 4;
const int count_col = 4;
const int size = 16;

int get_idx(int x, int y) {
    int i;
    int temp = 0;
    int ret;

    for (i = 0; i < size && !temp; i++)
    {
        if (array[i].pos_x == x && array[i].pos_y == y) {
            temp = 1;
        }
    }
    i--;
    if (i < size) {
        ret = i;
    } else {
        ret = -1;
        printf("element with coordinates (x[%d], y[%d]) is not in field\n", x, y);
    }
    
    return ret;
}

static void print_field_debug() 
{
    for (int y = count_row - 1; y >= 0; y--) {
        for (int x = 0; x < count_col; x++) {
            Tile t = array[get_idx(x, y)];
            printf("[x: %d, y: %d, v: %d] ", t.pos_x, t.pos_y, t.val);
        }
        printf("\n");
    }
    printf("\n");
}

static void print_field() 
{
    for (int y = count_col - 1; y >= 0; y--) {
        for (int x = 0; x < count_row; x++) {
            printf("%d ", array[get_idx(x, y)].val);
        }
        printf("\n");
    }
    printf("\n");
}

static int count_free_tiles() 
{
    int ret = 0;

    for (int i = 0; i < size; i++) {
        if (!array[i].val) {
            ret++;
        } 
    }

    return ret;
}

static int spawn()
{
    int counter = 0;
    int rndm_tile = rand() % count_free_tiles(size);
    int rndm = rand() % 10;

    switch (rndm)  {
    case 0:
        rndm = 4;
        break;
    default:
        rndm = 2;
        break;
    }

    for (int i = 0; i < size; i++) {
        if (!array[i].val && counter == rndm_tile) {
            printf("spawn idx: %d\n\n", i);
            array[i].val = rndm;
            return rndm;
        } else if (!array[i].val) {
            counter++;
        }
    }
}

static void move_right() {
    for (int y = count_row - 1; y >= 0; y--) {
        int counter = 0;
        Tile last;

        last.val = -1;

        for (int x = count_col - 1; x >= 0; x--) {
            Tile current = array[get_idx(x, y)];

            if (!current.val) {
                counter++;
            } else if (last.val == current.val) {
                array[get_idx(last.pos_x, last.pos_y)].val = array[get_idx(last.pos_x, last.pos_y)].val * 2;
                array[get_idx(current.pos_x, current.pos_y)].val = 0;

                counter++;
                last.val = -1;
            } else if (counter) {
                int temp = current.val;

                array[get_idx(x, y)].val = 0;
                array[get_idx(x + counter, y)].val = temp;

                last = array[get_idx(x + counter, y)];
            } else {
                last = array[get_idx(x, y)];
            }
        }
    }
}

static void move_left() {
    for (int y = count_row - 1; y >= 0; y--) {
        int counter = 0;
        Tile last;

        last.val = -1;
        for (int x = 0; x < count_col; x++) {
            Tile current = array[get_idx(x, y)];

            if (!current.val) {
                counter++;
            } else if (last.val == current.val) {
                array[get_idx(last.pos_x, last.pos_y)].val = array[get_idx(last.pos_x, last.pos_y)].val * 2;
                array[get_idx(current.pos_x, current.pos_y)].val = 0;

                counter++;
                last.val = -1;
            } else if (counter) {
                int temp = current.val;

                array[get_idx(x, y)].val = 0;
                array[get_idx(x - counter, y)].val = temp;

                last = array[get_idx(x - counter, y)];
            } else {
                last = array[get_idx(x, y)];
            }
        }
    }
}

static void move_up() {
    for (int x = 0; x < count_col; x++) {
        int counter = 0;
        Tile last;

        last.val = -1;
        for (int y = count_row - 1; y >= 0; y--) {
            Tile current = array[get_idx(x, y)];

            if (!current.val) {
                counter++;
            } else if (last.val == current.val) {
                array[get_idx(last.pos_x, last.pos_y)].val = array[get_idx(last.pos_x, last.pos_y)].val * 2;
                array[get_idx(current.pos_x, current.pos_y)].val = 0;

                counter++;
                last.val = -1;
            } else if (counter) {
                int temp = current.val;

                array[get_idx(x, y)].val = 0;
                array[get_idx(x, y + counter)].val = temp;

                last = array[get_idx(x, y + counter)];
            } else {
                last = array[get_idx(x, y)];
            }
        }
    }
}

static void move_down() {
    for (int x = 0; x < count_col; x++) {
        int counter = 0;
        Tile last;

        last.val = -1;
        for (int y = 0; y < count_row; y++) {
            Tile current = array[get_idx(x, y)];

            if (!current.val) {
                counter++;
            } else if (last.val == current.val) {
                array[get_idx(last.pos_x, last.pos_y)].val = array[get_idx(last.pos_x, last.pos_y)].val * 2;
                array[get_idx(current.pos_x, current.pos_y)].val = 0;

                counter++;
                last.val = -1;
            } else if (counter) {
                int temp = current.val;

                array[get_idx(x, y)].val = 0;
                array[get_idx(x, y - counter)].val = temp;

                last = array[get_idx(x, y - counter)];
            } else {
                last = array[get_idx(x, y)];
            }
        }
    }
}

int main (int argc, char *argv[]) 
{
    int right = 0;
    int left = 0;
    int up = 0;
    int down = 0;
    int score = 0;

    for (int i = 0; i < count_row; i++) {
        for (int j = 0; j < count_col; j++) {
            Tile temp;
            temp.pos_x = j;
            temp.pos_y = count_row - i - 1;
            temp.val = 0;
            array[i * count_row + j] = temp;
        }
    }

    print_field();

    while (count_free_tiles() > 0) {
        int rndm;

        score += spawn(size);
        print_field();

        rndm = rand() % 4;
        switch (rndm)
        {
        case 0:
            move_right();
            right++;
            break;
        case 1:
            move_left();
            left++;
            break;
        case 2:
            move_up();
            up++;
            break;
        case 3:
            move_down();
            down++;
            break;
        default:
            break;
        }
        
        print_field();
    }
    printf("r: %d, l: %d, u: %d, d: %d\n", right, left, up, down);
    printf("score: %d", score);
}