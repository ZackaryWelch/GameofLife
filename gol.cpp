#include "termmanip.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fstream>

using namespace std;

//The cell object that rests in the grid
//Contains set_state(bool state), set_nextstate(bool state)
//get_state(void), and get_nextstate(void)
class Cell
{
    public:
    Cell()
    {
        life = false;
        future = false;
    }
    void set_state(bool state)
    {
        life = state;
    }
    void set_nextstate(bool state)
    {
        future = state;
    }
    bool get_state()
    {
        return life;
    }
    bool get_nextstate()
    {
        return future;
    }
    private:
    bool life;
    bool future;
};

//The Grid object that contains all the cells and is the core of the program
//Contains get_cell(int i, int j), get_cellstate(int i, int j), print_grid(void)
//check_neighbors(int i, int j), check_state(void), void generate_grid(void)
//set_cell(int i, int j, bool state)
class Grid
{
    public:

    //Initalizes the grid by initalizing 24*80 null pointers and setting them
    //to be the location of dynamically allocated cell objects
    Grid()
    : _grid(24, vector<Cell*>(80))
    {
        for(int i=0; i < 24; i++)
        {
            for(int j = 0; j < 80; j++)
            {
                Cell *cell = new Cell();
                _grid[i][j] = cell;
            }
        }
        srand(time(0));
    }

    Cell* get_cell(int i, int j)
    {
        return _grid[i][j];
    }

    //a shorthand created to simplify code
    bool get_cellstate(int i, int j)
    {
        return _grid[i][j]->get_state();
    }

    //Begins by moving clearing the screen and setting the cursor to the upper lefthand corner.
    //Then it prints * if the cell is alive, and sets to green if it will be alive next turn, and red
    //If it is to die. After each cell is printed, it's current state is set to the state to be.
    void print_grid()
    {
        cout << clearScreen << cursorPosition(1, 1);
        for(int i = 0; i < 24; i++)
        {
            for(int j = 0; j < 80; j++)
            {
                 if(get_cellstate(i,j))
                 {
                    cout << (get_cell(i, j)->get_nextstate() ? green : red) << '*';
                 }else
                 {
                     cout << ' ';
                 }
                 set_cell(i, j, (get_cell(i, j)->get_nextstate()));
            }
            cout << endl;
        }
    }

    //Performs checks on the neighboring cells, 8 for most, 5 for the edges, and 3 for the four corners.
    int check_neighbors(int i, int j)
    {
        bool top = (i==0);
        bool right = (j==79);
        bool bottom = (i==23);
        bool left = (j==0);
        if (top+right+bottom+left > 1) //corners
        {
            if(top and left) return get_cellstate(1, 1) + get_cellstate(1, 0) + get_cellstate(0, 1);
            if(top and right) return get_cellstate(1, 79) + get_cellstate(1, 78) + get_cellstate(0, 78);
            if(bottom and right) return get_cellstate(22, 78) + get_cellstate(23, 78) + get_cellstate(22, 79);
            if(bottom and left) return get_cellstate(22, 0) + get_cellstate(22, 1) + get_cellstate(23, 1);
        }else if (top+right+bottom+left == 1) //edges
        {
            if(top) return get_cellstate(i, j+1) + get_cellstate(i, j-1) + get_cellstate(i+1, j)
                          + get_cellstate(i+1, j+1) + get_cellstate(i+1, j-1);
            if(right) return get_cellstate(i-1, j) + get_cellstate(i-1, j-1) + get_cellstate(i, j-1)
                            + get_cellstate(i+1, j-1) + get_cellstate(i+1, j);
            if(bottom) return get_cellstate(i, j+1) + get_cellstate(i-1, j+1) + get_cellstate(i-1, j)
                             + get_cellstate(i-1, j-1) + get_cellstate(i, j-1);
            if(left) return get_cellstate(i-1, j) + get_cellstate(i-1, j+1) + get_cellstate(i, j+1)
                           + get_cellstate(i+1, j+1) + get_cellstate(i+1, j);
        }else //interior cells
        {
            return get_cellstate(i, j+1) + get_cellstate(i, j-1) + get_cellstate(i+1, j)
                          + get_cellstate(i+1, j+1) + get_cellstate(i+1, j-1) + get_cellstate(i-1, j-1)
                          + get_cellstate(i-1, j) + get_cellstate(i-1, j+1);
        }
    }

    //Calls the check_neighbor function for each cell and then sets the next state based on the state of the neighbors.
    void check_state()
    {
        for(int i = 0; i < 24; i++)
        {
            for(int j = 0; j < 80; j++)
            {
                int state = check_neighbors(i, j);
                bool starving = state < 2;
                bool overpopulated = state > 3;
                bool stable = (state == 2 or state ==3 );
                bool resurection = state == 3;
                if(get_cellstate(i, j))
                {
                    if(starving or overpopulated)
                    {
                        get_cell(i, j)->set_nextstate(false);
                    }else if(stable)
                    {
                        get_cell(i, j)->set_nextstate(true);
                    }
                }else if(resurection)
                {
                    get_cell(i, j)->set_nextstate(true);
                }
            }
        }
    }

    //Creates a random grid and then sets the future states of the grid based on the randomly generated states
    void generate_grid()
    {
        for(int i = 0; i < 24; i++)
        {
            for(int j = 0; j < 80; j++)
            {
                bool state = rand() % 2;
                set_cell(i, j, state);
            }
        }
        check_state();
    }

    void set_cell(int i, int j, bool state)
    {
        _grid[i][j]->set_state(state);
    }

    //Destroys the cells inside the grid
    ~Grid()
    {
        for(int i = 0; i < 24; i++)
        {
            for(int j = 0; j < 80; j++)
            {
                delete _grid[i][j];
            }
        }
    }

    private:
    vector<vector<Cell*> > _grid;
};

int main(int argc, char **argv)
{
    Grid *grid = new Grid();
    string l;
    if(argc == 1) //If the program is ran without arguments
    {
        grid->generate_grid();
    }else //If the command includes a file
    {
        ifstream file(argv[1]);
        while(file.good())
        {
            getline(file, l);
            static int i = 0;
            for(int j = 0; j < 80; j++)
            {
                bool state = (l[j]== '*'); //* indicate alive cells in the files, other wise the cells are dead
                grid->set_cell(i, j, state);
            }
            if(++i == 24)
            {
                break;
            }
        }
        grid->check_state(); //Sets the future states based on the current states in the file
    }
    
    //The cycle. Prints the grid, sets the future states based on the neighbors, sleeps for 0.25 seconds, and then reprints, with new neighbors
    while(true)
    {
        grid->print_grid();
        grid->check_state();
        usleep(250000);
    }
    
    //Clears the screen when terminated and sets the cursor position back to the start
    cout << clearScreen << cursorPosition(1, 1) << normal;
    delete grid;
    return 0;
}