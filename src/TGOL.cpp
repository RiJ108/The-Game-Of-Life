#include "TGOL.h"

void update(int** m,int i,int j)
{
    int** mp=Matrix2Di(i,j);
    int n=0,c=0,d=0,e=0,f=0;
    for(int x=0;x<i;x++)
    {
        for(int y=0;y<j;y++)
        {
            if(x==0)
            {
                if(y==0)
                {
                    c=0;                    d=2;
                    e=0;                    f=2;
                }
                else if(y==j-1)
                {
                    c=0;                    d=2;
                    e=-1;                    f=1;
                }
                else
                {
                    c=0;                    d=2;
                    e=-1;                    f=2;
                }
            }
            else if(x==i-1)
            {
                if(y==0)
                {
                    c=-1;                    d=1;
                    e=0;                    f=2;
                }
                else if(y==j-1)
                {
                    c=-1;                    d=1;
                    e=-1;                    f=1;
                }
                else
                {
                    c=-1;                    d=1;
                    e=-1;                    f=2;
                }
            }
            else
            {
                if(y==0)
                {
                    c=-1;                    d=2;
                    e=0;                    f=2;
                }
                else if(y==j-1)
                {
                    c=-1;                    d=2;
                    e=-1;                    f=1;
                }
                else
                {
                    c=-1;                    d=2;
                    e=-1;                    f=2;
                }
            }
            n=0;
            for(int a=c;a<d;a++)
            {
                for(int b=e;b<f;b++)
                {
                    //cout<<" "<<m[x+a][y+b];
                    if(!(a==0 && b==0))
                        n+=m[x+a][y+b];
                    //else
                        //cout<<"<-NULL";
                }
            }
            //cout<<"["<<x<<"|"<<y<<"]="<<n<<endl;
            if(m[x][y])
            {
                if(n<2)
                    mp[x][y]=0;
                else if(n==2 || n==3)
                    mp[x][y]=1;
                else if(n<3)
                    mp[x][y]=0;
            }
            else
            {
                if(n==3)
                    mp[x][y]=1;
                else
                    mp[x][y]=0;
            }
        }
    }
    for(int x=0;x<i;x++)
    {
        for(int y=0;y<j;y++)
        {
            m[x][y]=mp[x][y];
        }
    }
    free(mp);
}

void draw(int** m,int w,int h,int state)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawGrid(m,w,h);
    drawButton(state);
    drawCell(m,w,h);
}

void drawGrid(int** m,int w,int h)
{
    glColor3ub(150,150,150);
    glBegin(GL_LINES);
    for(int x=0;x<=h;x++)
    {
        glVertex3i(10,((20*h)+50)-(20*x),0);
        glVertex3i(((20*w)+10),((20*h)+50)-(20*x),0);
    }
    for(int x=0;x<=w;x++)
    {
        glVertex3i(((20*w)+10)-(20*x),((20*h)+50),0);
        glVertex3i(((20*w)+10)-(20*x),50,0);
    }
    glEnd();
}

void drawButton(int state)
{
    glBegin(GL_QUADS);
        glColor3ub(state*255,!state*255,0);
        glVertex3i(10,15,0);
        glVertex3i(100,15,0);
        glVertex3i(100,35,0);
        glVertex3i(10,35,0);
    if(state)
        return;
    for(int i=1;i<3;i++)
    {
        if(i==1)
            glColor3ub(255,106,0);
        else
            glColor3ub(255,216,0);
        glVertex3i(10+(100*i),15,0);
        glVertex3i(100+(100*i),15,0);
        glVertex3i(100+(100*i),35,0);
        glVertex3i(10+(100*i),35,0);
    }
    for(int i=3;i<5;i++)
    {
        if(i==3)
            glColor3ub(0,148,255);
        else
            glColor3ub(178,0,255);
        glVertex3i(310+(60*(i-3)),15,0);
        glVertex3i(360+(60*(i-3)),15,0);
        glVertex3i(360+(60*(i-3)),35,0);
        glVertex3i(310+(60*(i-3)),35,0);
    }
    glEnd();
}

void drawCell(int** m,int w,int h)
{
     glColor3ub(100,255,150);
     glBegin(GL_QUADS);
     for(int i=0;i<h;i++)
     {
        for(int j=0;j<w;j++)
        {
            if(m[i][j])
            {
                glVertex3i(10+(20*j),(20*h)+50-(20*i),0);
                glVertex3i(10+20+(20*j),(20*h)+50-(20*i),0);
                glVertex3i(10+20+(20*j),(20*h)+30-(20*i),0);
                glVertex3i(10+(20*j),(20*h)+30-(20*i),0);
            }
        }
    }
    glEnd();
}

void clearMatrix(int** m,int width,int height)
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
            m[i][j]=0;
    }
}

void resetMatrix(int** m,int** ms,int width,int height)
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
            m[i][j]=ms[i][j];
    }
}

void saveMatrix(int** m,int** ms,int width,int height)
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
            ms[i][j]=m[i][j];
    }
}

void updateCell(int** m,float mx,float my)
{
    cout<<(int)(mx-10)/20<<"|";
    cout<<(int)(my-10)/20<<"]";
    if(m[(int)(my-10)/20][(int)(mx-10)/20])
    {
        m[(int)(my-10)/20][(int)(mx-10)/20]=0;
        cout<<" clear."<<endl;
    }
    else
    {
        m[(int)(my-10)/20][(int)(mx-10)/20]=1;
        cout<<" set."<<endl;
    }
}
