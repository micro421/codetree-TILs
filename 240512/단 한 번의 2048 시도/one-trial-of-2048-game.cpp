#include <iostream>
#include <cstring> /* memset*/

#define BLANK 0
#define CUT_SHIFT 500 /* 해당 자리 CUT 하고 shift하는 것도 폭탄 원리다!*/

using namespace std;
char dir;
int grid[4][4] = { 0,0 };
int nextgrid[4][4] = { 0, 0 };

int gravity[4] = { 0,0 }; /* 0 is not appied*/
/*gravity management - from 2D array to 1D array skill apply*/
void Copy()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
        {
            grid[i][j] = nextgrid[i][j];
        }
    }
}
void CutArrayRight(int i, int cut_idx) /*CutArrayRight(i,j-1)*/
{
    memset(nextgrid, 0, sizeof(nextgrid));

    grid[i][cut_idx] = CUT_SHIFT; /* 해당 부분 자르고 SHIFT 해준다. */
    int end_of_array = 3;
    for (int j = 3; j >= 0; j--) {
        if (grid[i][j] != CUT_SHIFT) { /*CUT_SHIFT도 폭탄 원리를 쓴다.*/
            nextgrid[i][end_of_array] = grid[i][j];
            end_of_array--;
        }
    }
    /*Above Copy*/
    for (int j = 3; j >= 0; j--)
    {
        grid[i][j] = nextgrid[i][j];
    }
}

void CutArrayDown(int j, int cut_idx)
{
    memset(nextgrid, 0, sizeof(nextgrid));

    grid[cut_idx][j] = CUT_SHIFT; /* 해당 부분 자르고 SHIFT 해준다. */
    int end_of_array = 3;
    for (int i = 3; i >= 0; i--) {
        if (grid[i][j] != CUT_SHIFT) { /*CUT_SHIFT도 폭탄 원리를 쓴다.*/
            nextgrid[end_of_array][j] = grid[i][j];
            end_of_array--;
        }
    }
    /*Above Copy*/
    for (int i = 3; i >= 0; i--)
    {
        grid[i][j] = nextgrid[i][j];
    }

}
void CutArrayLeft(int i, int cut_idx) /*CutArrayLeft(i, j)*/
{/*4 2 2 4 => 4 4 cut 4 => 4 4 4 0*/
    memset(nextgrid, 0, sizeof(nextgrid));

    grid[i][cut_idx] = CUT_SHIFT; /* 해당 부분 자르고 SHIFT 해준다. */
    int end_of_array = 0;
    for (int j = 0; j < 4; j++) {
        if (grid[i][j] != CUT_SHIFT) { /*CUT_SHIFT도 폭탄 원리를 쓴다.*/
            nextgrid[i][end_of_array] = grid[i][j];
            end_of_array++;
        }
    }
    /*Above Copy*/
    for (int j = 0; j < 4; j++)
    {
        grid[i][j] = nextgrid[i][j];
    }
}

void CutArrayUp(int j, int cut_idx)
{
    memset(nextgrid, 0, sizeof(nextgrid));

    grid[cut_idx][j] = CUT_SHIFT; /* 해당 부분 자르고 SHIFT 해준다. */
    int end_of_array = 0;
    for (int i = 0; i < 4; i++) {
        if (grid[i][j] != CUT_SHIFT) { /*CUT_SHIFT도 폭탄 원리를 쓴다.*/
            nextgrid[end_of_array][j] = grid[i][j];
            end_of_array++;
        }
    }
    /*Above Copy*/
    for (int i = 0; i < 4; i++)
    {
        grid[i][j] = nextgrid[i][j];
    }
}

void MoveAsLeft()
{
    for (int i = 0; i < 4; i++) {
        int end_of_array = 0; /*can be used as index or length*/
        /* if new row, initialize end_of_array needed! */
        for (int j = 0; j < 4; j++) {
            if (grid[i][j] != BLANK)
            {
                nextgrid[i][end_of_array] = grid[i][j];
                end_of_array++;
            }
        }
    }
    Copy();
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if ((grid[i][j - 1] == grid[i][j]) && (gravity[i] == 0))
            {
                grid[i][j - 1] = 2 * grid[i][j-1]; /* 앞쪽 인덱스로 밀어주니 grid[i][j-1] = 2*grid[i][j-1]*/
                CutArrayLeft(i, j); /*cut index는 j-1과 j 중에 j : because 앞 쪽으로 밀어줌*/
                /*CutArray as start_idx  = j and 1kan*/
                gravity[i] = 1; /* i번째 줄 gravity 이미 작용 꿑*/
            }

        }
    }
}

void MoveAsUp() /* check idx*/
{
    for (int j = 0; j < 4; j++) { /*column*/
        int end_of_array = 0;
        for (int i = 0; i < 4; i++) {
            if (grid[i][j] != BLANK) {
                nextgrid[end_of_array][j] = grid[i][j];
                end_of_array++;
            }
        }
    }
    Copy();
    for (int j = 0; j < 4; j++) {
        for (int i = 1; i < 4; i++) {
            if ((grid[i - 1][j] == grid[i][j]) && (gravity[j] == 0))
            {
                grid[i - 1][j] = 2 * grid[i-1][j]; /* 앞쪽 인덱스로 밀어주니 grid[i-1][j] = 2*grid[i-1][j]*/
                CutArrayUp(j/*row*/, i/*cut_idx*/); /*cut index는 i-1과 i중에 i : because 앞 쪽으로 밀어줌*/
                gravity[j] = 1; /* j번째 열 gravity 이미 작용 꿑*/
            }

        }
    }
}

void MoveAsDown() /* check idx*/
{
    for (int j = 0; j < 4; j++) { /*column1 - 2 - 3 - 4*/
        int end_of_array = 3;
        for (int i = 3; i >= 0; i--) {
            if (grid[i][j] != BLANK) {
                nextgrid[end_of_array][j] = grid[i][j];
                end_of_array--;
            }
        }
    }
    Copy();
    for (int j = 0; j < 4; j++) {
        for (int i = 3; i >= 1; i--) {
            if ((grid[i - 1][j] == grid[i][j]) && (gravity[j] == 0))
            {
                grid[i][j] = 2 * grid[i][j]; /*뒷쪽 인덱스로 밀어주니 grid[i][j] = 2*grid[i][j]; */
                CutArrayDown(j, i - 1); /* 뒷쪽으로 밀어주니 CUT_SHIFT index는 i-1 */
                gravity[j] = 1; /* i번째 줄 gravity 이미 작용 꿑*/
            }
        }
    }
}

void MoveAsRight()
{
    for (int i = 0; i < 4; i++) { /*row*/
        int end_of_array = 3;
        for (int j = 3; j >= 0; j--) { /*column*/
            if (grid[i][j] != BLANK)
            {
                nextgrid[i][end_of_array] = grid[i][j];
                end_of_array--;
            }
        }
    }
    Copy();
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 1; j--) {
            if ((grid[i][j - 1] == grid[i][j]) && (gravity[i] == 0))
            {
                grid[i][j] = 2 * grid[i][j];/*뒷쪽 인덱스로 밀어주니 grid[i][j] = 2*grid[i][j]; */
                CutArrayRight(i, j - 1);/* 뒷쪽으로 밀어주니 CUT_SHIFT index는 j-1 */
                gravity[i] = 1; /* i번째 줄 gravity 이미 작용 꿑*/
            }
        }
    }
}

void MoveDueToZero() /*Move if zero*/
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grid[i][j] != BLANK) {
                if (dir == 'L') {
                    MoveAsLeft();
                }
                if (dir == 'R')
                {
                    MoveAsRight();
                }
                if (dir == 'U')
                {
                    MoveAsUp();
                }
                if (dir == 'D')
                {
                    MoveAsDown();
                }
            }
        }
    }
}


int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> grid[i][j];
        }
    }
    cin >> dir;

    MoveDueToZero();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << grid[i][j];
            if (j != 3)
                cout << " ";
        }
        if (i != 3)
            cout << "\n";
    }

    return 0;
}