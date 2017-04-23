/**
 * fifteen.c
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

// board's permitted dimension
#define D_MIN 3
#define D_MAX 9

// board, array with i columns and j lines
int board[D_MAX][D_MAX];

// dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < D_MIN || d > D_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            D_MIN, D_MIN, D_MAX, D_MAX);
        return 2;
    }
    
    // open log
    FILE *file = fopen("log.txt", "w");
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
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // fill the array with tiles in descending order
    int c = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
        board[i][j] = d * d - c;
        c++;
        }
    }
    //let the last tile blank
    board[d-1][d-1] = 0;
    // if d is even and the tiles on board odd, swap 1 and 2 so game can be won
    if ((d * d)%2 == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++) 
        {
            if (board[i][j] == 0)
            // print the blank tile
                printf(" _ ");
            else
            // the tiles in descending order
                printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // set algorithm for checking bordering tiles
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            //Checking if the blank space is around the tile
            {
                if (j+1 <= d-1 && board[i][j+1] == 0)
                {
                    board[i][j+1] = tile;
                    board[i][j] = 0;
                    return true;
                }
                else if (j-1 >= 0 && board[i][j-1] == 0)
                {
                    board[i][j-1] = tile;
                    board[i][j] = 0;
                    return true;
                }
                else if (i-1 >= 0 && board[i-1][j] == 0)
                {
                    board[i-1][j] = tile;
                    board[i][j] = 0;
                    return true;
                }
                else if (i+1 <= d-1 && board[i+1][j] == 0)
                {
                    board[i+1][j] = tile;
                    board[i][j] = 0;
                    return true;
                }
            
            }
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
    // initializes variable
    int n = 1;
    
    // checking if the last tile is blank, isn't return false
    if (board[d-1][d-1] != 0)
        return false;
    
    // checking the ascending order of the numbers
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (i == d - 1 && j == d - 1)
                return true;
                
            // check the numbers of the tiles
            if (n != board[i][j])
                return false;
            n++;                        
        }
    }
    return false;
}