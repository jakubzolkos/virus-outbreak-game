#include "View.h"
using namespace std;

View::View() : size(16), scale(2), origin(Point2D(0, 0)) {}

View::~View() {}

void View::Clear()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            grid[i][j][0] = '.';
            grid[i][j][1] = ' ';
        }
    }
}

bool View::GetSubscripts(int &out_x, int &out_y, Point2D location)
{
    Vector2D res = (location - origin) / scale;
    out_x = static_cast<int>(res.x);
    out_y = static_cast<int>(res.y);

    if ((out_x >= 0 && out_x < view_maxsize) && (out_y >= 0 && out_y < view_maxsize))
    {
        return true;
    }

    else
    {
        cout << endl << "An object is outside the display" << endl << endl;
        return false;
    }
}

void View::Draw() 
{
    for (int j = size - 1; j >= -1; j--)
    {
        for (int i = -1; i <= size - 1; i++)
        {
            if (i == -1 && j%2 == 0)
            {
                cout << j*2 << " ";

                if (j / 5 == 0)
                {
                    cout << " ";
                }
            }

            else if (i == -1 && j%2 != 0)
            {
                cout << "   ";
            }
            
            else if (j == -1 && i%2 == 0)
            {
                cout << i*2;
                if (i / 5 == 0)
                {
                    cout << " ";
                }
                cout << "  ";
            }   
            if (i >= 0 && j >= 0)
            {
                cout << grid[i][j][0] << grid[i][j][1];
            }

        }
    
    cout << endl;

    }
}

void View::Plot(GameObject *ptr)
{
    Point2D location = (*ptr).GetLocation();
    char *id_code = new char[2];
    (*ptr).DrawSelf(id_code);
    int i,j;
    View::GetSubscripts(i, j, location);
    
    if (grid[i][j][0] == '.' && grid[i][j][1] == ' ')
    {
        grid[i][j][0] = *(id_code);
        grid[i][j][1] = *(id_code + 1);
    }

    else if (grid[i][j][0] != '.' && *(id_code) != '.')
    {
        grid[i][j][0] = '*';
        grid[i][j][1] = ' ';
    }

    delete [] id_code;
}