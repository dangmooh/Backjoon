
#include <iostream>
#include <vector>


using namespace std;

int N, M, F;

pair<int,int> dd[4] = {{1,0}, {-1,0},{0,1},{0,-1}};
int timeBoard[4][10][10] = {0,};
int spaceBoard[20][20] = {0,};

int eC, eR;

int main()
{
    cin >> N >> M >> F;

    for(int i=0; i< N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cin >> spaceBoard[i][j];
            if(spaceBoard[i][j] == 4)
            {
                eC = j;
                eR = i;
            } 
            else if(spaceBoard[i][j] == 3)
            {
                
            }
        }
    }

    for(int i=0; i < 4; i++)
    {
        for(int j=0; j<M; j++)
        {
            for(int k=0; k<M; k++)
            {
                cin >> timeBoard[i][j][k];
            }
        }
    }



    return 0;
}