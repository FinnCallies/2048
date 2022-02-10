#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static void print_field(char **array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s ", array[i]);
        if (((i + 1) % ((int) sqrt(size))) == 0 )
            printf("\n");
    }
    printf("\n\n");
}

static void move_right(char **array, int size) {
    int index_self = 0, index_neigh = 0;
    int sqrt_size = ((int) sqrt(size));
    // For every row ...
    for (int i = 0; i < sqrt_size; i++)
    {
        int move = 0;
        int index_end = (sqrt_size * (i + 1)) - 1;
        int index_current;

        // ... shift to right, ...
        for (int j = 0; j < sqrt_size; j++) {
            index_current = index_end - j;
            if (strcmp(array[index_current], "0") == 0) {
                move++;
            } else if (move != 0) {
                array[index_current + move] = array[index_current];
                array[index_current] = "0";
            }
        }

        while (index_end > (i * sqrt_size) && strcmp(array[index_end], "0") != 0) {
            move = 0;
            // add
            if (strcmp(array[index_end], array[index_end - 1]) == 0)
            {
                int temp = (atoi(array[index_end]) + atoi(array[index_end - 1]));
                printf("strlen: %d\n", ((int) strlen(array[index_end])));
                printf("%d\n", atoi(array[index_end]) + atoi(array[index_end - 1]));
                printf("%s\n", itoa(atoi(array[index_end]) + atoi(array[index_end - 1]), array[index_end], 10));
                // array[index_end] = "4";
                array[index_end - 1] = "0";
            }

            // shift
            for (int j = 0; j < (index_end - i * sqrt_size) && strcmp(array[index_end - 2], "0") != 0; j++) {
                printf("shift\n");
                index_current = index_end - j;
                if (strcmp(array[index_current], "0") == 0) {
                    move++;
                } else if (move != 0) {
                    array[index_current + move] = array[index_current];
                    array[index_current] = "0";
                }
            }
            index_end--;
        }
        
    }
}

int main (int argc, char *argv[]) {
    // initialize field
    char **array = (char**)malloc(16*sizeof(char*));
    int temp = 0;
    //allocate space for each string
    // here allocate 50 bytes, which is more than enough for the strings
    for(temp = 0; temp < 16; temp++) {
        array[temp] = (char*) malloc(50 * sizeof(char));
        array[temp][49] = '\0';
    }
    printf("strlen: %d\n", ((int) strlen(array[0])));
    // char *array[16] = {'\0'};
    
    for (int i = 0; i < 16; i++) {
        array[i] = "0";
    } 
    printf("\n");
    
    // init field print
    print_field(array, 16);

    int r = 0;
    while (r < 17) {
        int new = rand() % 16;
        while (strcmp(array[new], "0") != 0) {
            new = rand() % 16;  // Fixme
        }
        printf("new: %d, array[new]: %s\n", new, array[new]);
        
        array[new] = "2";
        print_field(array, 16);

        move_right(array, 16);

        print_field(array, 16);
        r++;
    } 
}