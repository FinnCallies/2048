#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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

static void cp_field(Tile src[16], Tile dest[16]) {
    for (int i = 0; i < 16; i++) {
        dest[i].pos_x = src[i].pos_x;
        dest[i].pos_y = src[i].pos_y;
        dest[i].val = src[i].val;
    }
}

static void print_field_debug() {
    for (int y = count_row - 1; y >= 0; y--) {
        for (int x = 0; x < count_col; x++) {
            Tile t = array[get_idx(x, y)];
            printf("[x: %d, y: %d, v: %d] ", t.pos_x, t.pos_y, t.val);
        }
        printf("\n");
    }
    printf("\n");
}

static void print_field() {
    for (int y = count_col - 1; y >= 0; y--) {
        for (int x = 0; x < count_row; x++) {
            printf("%d ", array[get_idx(x, y)].val);
        }
        printf("\n");
    }
    printf("\n");
}

static int count_free_tiles() {
    int ret = 0;

    for (int i = 0; i < size; i++) {
        if (!array[i].val) {
            ret++;
        } 
    }

    return ret;
}

static void spawn() {
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
            array[i].val = rndm;
            return;
        } else if (!array[i].val) {
            counter++;
        }
    }
}

static int move_right() {
    int moves = 0;
    for (int y = 0; y < count_row; y++) {
        int counter = 0;
        Tile last;

        last.val = -1;

        for (int x = count_col - 1; x >= 0; x--) {
            Tile current = array[get_idx(x, y)];

            if (!current.val) {
                counter++;
                for (int i = 0; i < current.pos_x; i++) {
                    if (array[get_idx(i, y)].val) {
                        moves++;
                        break;
                    }
                }
            } else if (last.val == current.val) {
                array[get_idx(last.pos_x, last.pos_y)].val = array[get_idx(last.pos_x, last.pos_y)].val * 2;
                array[get_idx(current.pos_x, current.pos_y)].val = 0;

                counter++;
                last.val = -1;
                moves++;
            } else if (counter) {
                int temp = current.val;

                array[get_idx(x, y)].val = 0;
                array[get_idx(x + counter, y)].val = temp;

                last = array[get_idx(x + counter, y)];
                moves++; 
            } else {
                last = array[get_idx(x, y)];
            }
        }
    }
    return moves;
}

static int move_left() {
    int moves = 0;
    for (int y = count_row - 1; y >= 0; y--) {
        int counter = 0;
        Tile last;

        last.val = -1;
        for (int x = 0; x < count_col; x++) {
            Tile current = array[get_idx(x, y)];

            if (!current.val) {
                counter++;
                for (int i = current.pos_x; i < count_col; i++) {
                    if (array[get_idx(i, y)].val) {
                        moves++;
                        break;
                    }
                }
            } else if (last.val == current.val) {
                array[get_idx(last.pos_x, last.pos_y)].val = array[get_idx(last.pos_x, last.pos_y)].val * 2;
                array[get_idx(current.pos_x, current.pos_y)].val = 0;

                counter++;
                last.val = -1;
                moves++;
            } else if (counter) {
                int temp = current.val;

                array[get_idx(x, y)].val = 0;
                array[get_idx(x - counter, y)].val = temp;

                last = array[get_idx(x - counter, y)];
                moves++;
            } else {
                last = array[get_idx(x, y)];
            }
        }
    }
    return moves;
}

static int move_up() {
    int moves = 0;
    for (int x = 0; x < count_col; x++) {
        int counter = 0;
        Tile last;

        last.val = -1;
        for (int y = count_row - 1; y >= 0; y--) {
            Tile current = array[get_idx(x, y)];

            if (!current.val) {
                counter++;
                for (int i = 0; i < current.pos_y; i++) {
                    if (array[get_idx(x, i)].val) {
                        moves++;
                        break;
                    }
                }
            } else if (last.val == current.val) {
                array[get_idx(last.pos_x, last.pos_y)].val = array[get_idx(last.pos_x, last.pos_y)].val * 2;
                array[get_idx(current.pos_x, current.pos_y)].val = 0;

                counter++;
                last.val = -1;
                moves++;
            } else if (counter) {
                int temp = current.val;

                array[get_idx(x, y)].val = 0;
                array[get_idx(x, y + counter)].val = temp;

                last = array[get_idx(x, y + counter)];
                moves++;
            } else {
                last = array[get_idx(x, y)];
            }
        }
    }
    return moves;
}

static int move_down() {
    int moves = 0;
    for (int x = 0; x < count_col; x++) {
        int counter = 0;
        Tile last;

        last.val = -1;
        for (int y = 0; y < count_row; y++) {
            Tile current = array[get_idx(x, y)];

            if (!current.val) {
                counter++;
                for (int i = current.pos_y; i < count_row; i++) {
                    if (array[get_idx(x, i)].val) {
                        moves++;
                        break;
                    }
                }
            } else if (last.val == current.val) {
                array[get_idx(last.pos_x, last.pos_y)].val = array[get_idx(last.pos_x, last.pos_y)].val * 2;
                array[get_idx(current.pos_x, current.pos_y)].val = 0;

                counter++;
                last.val = -1;
                moves++;
            } else if (counter) {
                int temp = current.val;

                array[get_idx(x, y)].val = 0;
                array[get_idx(x, y - counter)].val = temp;

                last = array[get_idx(x, y - counter)];
                moves++;
            } else {
                last = array[get_idx(x, y)];
            }
        }
    }
    return moves;
}

static int calc_score() {
    int ret = 0;

    for (int i = 0; i < 16; i++) {
        ret += array[i].val;
    }

    ret = count_free_tiles();

    return ret;
}

static int calculate_move(int depth) {
    int score = 0;
    int moved;
    int current_score = 0;
    if (depth) {
        spawn();
        Tile temp_state[16];
        cp_field(array, temp_state);
        for (int i = 0; i < 4; i++) {
            moved = 0;

            switch (i) {
            case 0:
                moved = move_right();
                break;
            case 1:
                moved = move_left();
                break;
            case 2:
                moved = move_up();
                break;
            case 3:
                moved = move_down();
                break;
            default:
                break;
            }

            if (moved) {
                current_score = calculate_move(depth - 1);
            
                if (current_score && current_score > score) {
                    score = current_score;
                }
            } else {
                cp_field(temp_state, array);
                return calc_score();
            }

            cp_field(temp_state, array);
        }
        if (score) {
            return score;
        }
    }
    return calc_score();
}

static int calc_wrapper(int depth) {
    if (depth) {
        int score = 0;
        int move = -1;
        int moved;
        Tile state[16];

        cp_field(array, state);
        
        for (int i = 0; i < 4; i++) {
            moved = 0;
            int current_score = 0;

            switch (i) {
            case 0:
                moved = move_right();
                break;
            case 1:
                moved = move_left();
                break;
            case 2:
                moved = move_up();
                break;
            case 3:
                moved = move_down();
                break;
            default:
                break;
            }

            if (moved) {
                current_score = calculate_move(depth - 1);
                if (current_score && current_score > score) {
                    score = current_score;
                    move = i;
                }
            }
            cp_field(state, array);
        }
        return move;
    } else {
        Tile state[16];
        int moved;
        int counter = 0;
        int temp[4] = {0, 0, 0, 0};
        cp_field(array, state);
        
        for (int i = 0; i < 4; i++) {
            moved = 0;
            int current_score = 0;

            switch (i) {
            case 0:
                moved = move_right();
                break;
            case 1:
                moved = move_left();
                break;
            case 2:
                moved = move_up();
                break;
            case 3:
                moved = move_down();
                break;
            default:
                break;
            }

            if (moved) {
                temp[counter] = i;
                counter++;
            } 
            cp_field(state, array);
        }
        if (counter)
            return temp[rand() % counter];
    }
    return -1;
}

static int play_game() {
    int right = 0;
    int left = 0;
    int up = 0;
    int down = 0;
    int valid_moves = 1;

    srand(time(0));

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
    while (count_free_tiles() > 0 && valid_moves) {
        int rndm = 0;
        spawn();
        // print_field();
        rndm = calc_wrapper(11);
        switch (rndm) {
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
            valid_moves = 0;
            break;
        }
        
        print_field(array);
    }
    printf("r: %d, l: %d, u: %d, d: %d\n", right, left, up, down);

    int score;
    for (int i = 0; i < 16; i++) {
        score += array[i].val;
    }
    printf("score: %d\n", score);
    
    return calc_score();
}

int main (int argc, char *argv[])  {
    int score = 0;
    for (int i = 0; i < 1; i++) {
        score += play_game();
    }
    // printf("Average: %f\n", (double)score / (double)100); 
}