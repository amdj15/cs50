/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 2
#define DIM_MAX 9
#define EMPTY -1

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

int empty_i;
int empty_j;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void print_item(int item);
bool check_can_move(int i, int j);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    empty_i = d - 1;
    empty_j = d - 1;

    int number = d * d;

    for (int i = 0; i < d; ++i)
    {
        for (int j = 0; j < d; ++j)
        {
            board[i][j] = --number == 0 ? EMPTY : number;
        }
    }

    if (number % 2 == 0) {
        int swaped = board[number - 1][number - 1];

        board[number - 1][number - 1] = board[number - 2][number - 2];
        board[number - 2][number - 2] = swaped;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; ++i)
    {
        printf("%s", "| ");

        for (int j = 0; j < d; ++j)
        {
            print_item(board[i][j]);
            printf("%s", " | ");
        }

        printf("\n");
    }
}

void print_item(int item)
{
     if (item < 10) {
        printf("%s", " ");
    }

    if (item > 0) {
        printf("%d", item);
    } else {
        printf("_");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    for (int i = 0; i < d; ++i)
    {
        for (int j = 0; j < d; ++j)
        {
            if (board[i][j] == tile && check_can_move(i, j)) {
                board[empty_i][empty_j] = board[i][j];
                board[i][j] = EMPTY;

                empty_i = i;
                empty_j = j;

                return true;
            }
        }
    }

    return false;
}

bool check_can_move(int x, int y) {
    int delta[4][2] = {
        { -1, 0 }, // up
        { 0, 1 }, // right
        { 1, 0 }, // down
        { 0, -1 } // left
    };

    for (int i = 0; i < 4; ++i)
    {
        int suspect_x = x + delta[i][0];
        int suspect_y = y + delta[i][1];

        if (board[suspect_x][suspect_y] == EMPTY) {
            return true;
        }
    }

    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    int start = 1;

    for (int i = 0; i < d; ++i)
    {
        for (int j = 0; j < d; ++j)
        {
            if (board[i][j] > 0 && start++ != board[i][j]) {
                return false;
            }
        }
    }

    return board[d - 1][d - 1] == EMPTY;
}
