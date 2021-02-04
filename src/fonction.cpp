#include "fonction.h"

int** Matrix2Di(int i,int j)
{
    int** m=(int**)malloc(i*sizeof(int*));
    for(int x=0;x<i;x++)
        m[x]=(int*)malloc(j*sizeof(int));
    for(int x=0;x<i;x++)
    {
        for(int y=0;y<j;y++)
            m[x][y]=0;
    }
    return m;
}
