#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/gl.h>
#include <unistd.h>
#include "fonction.h"
#include "TGOL.h"


GLFWwindow* Init_();
using namespace std;
float   time;
double pMouse[2];
int run=0,launched=0;
int **m,**ms;
int FPS=20.0;
int width=63,height=33;
string title;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    glfwGetCursorPos(window,&pMouse[0],&pMouse[1]);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if(run)
        {
            if(pMouse[0]<100 && pMouse[0]>=10 && pMouse[1]<((20*height)+45) && pMouse[1]>=((20*height)+24))
            {
                run=0;
                cout<<"STOP"<<endl;
            }
        }
        else if(!run)
        {
            if(pMouse[0]<100 && pMouse[0]>=10 && pMouse[1]<((20*height)+45) && pMouse[1]>=((20*height)+24))
            {
                run=1;
                cout<<"PLAY"<<endl;
                if(!launched)
                {
                    launched=1;
                    saveMatrix(m,ms,width,height);
                }
            }
            else if(pMouse[0]<200 && pMouse[0]>=110 && pMouse[1]<((20*height)+45) && pMouse[1]>=((20*height)+24))
            {
                cout<<"RESET"<<endl;
                resetMatrix(m,ms,width,height);
                launched=0;
            }
            else if(pMouse[0]<300 && pMouse[0]>=210 && pMouse[1]<((20*height)+45) && pMouse[1]>=((20*height)+24))
            {
                cout<<"CLEAR"<<endl;
                clearMatrix(m,width,height);
                launched=0;
            }
            else if(pMouse[0]<360 && pMouse[0]>=310 && pMouse[1]<((20*height)+45) && pMouse[1]>=((20*height)+24))
            {
                cout<<"MORE"<<endl;
                if(height<44)
                {
                    width+=2;
                    height+=1;
                    free(m);
                    free(ms);
                    m=Matrix2Di(height,width);
                    ms=Matrix2Di(height,width);
                    glfwSetWindowSizeLimits(window,(width*20)+20,(height*20)+60,(width*20)+20,(height*20)+60);
                    glViewport( 0, 0, (width*20)+20, (height*20)+60 );
                    glMatrixMode( GL_PROJECTION );
                    glLoadIdentity();
                    glOrtho(0.0,(width*20)+20,0.0,(height*20)+60,0.0,1.0);
                }
            }
            else if(pMouse[0]<420 && pMouse[0]>=370 && pMouse[1]<((20*height)+45) && pMouse[1]>=((20*height)+24))
            {
                cout<<"LESS"<<endl;
                if(height>12)
                {
                    width-=2;
                    height-=1;
                    free(m);
                    free(ms);
                    m=Matrix2Di(height,width);
                    ms=Matrix2Di(height,width);
                    glfwSetWindowSizeLimits(window,(width*20)+20,(height*20)+60,(width*20)+20,(height*20)+60);
                    glViewport( 0, 0, (width*20)+20, (height*20)+60 );
                    glMatrixMode( GL_PROJECTION );
                    glLoadIdentity();
                    glOrtho(0.0,(width*20)+20,0.0,(height*20)+60,0.0,1.0);
                }
            }
            else if(pMouse[0]<((20*width)+10) && pMouse[0]>=10 && pMouse[1]<((20*height)+9) && pMouse[1]>=10)
            {
            cout<<"cell [";
            updateCell(m,pMouse[0],pMouse[1]);
            }
        }
        //cout<<pMouse[0]<<"|"<<pMouse[1]<<endl;
    }

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    FPS+=yoffset;
    if(FPS<10)
        FPS=10;
    else if(FPS>60)
        FPS=60;
}

int main(void)
{
    if (!glfwInit())
        return -1;
    GLFWwindow* window=Init_();
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glViewport( 0, 0, (width*20)+20, (height*20)+60 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0.0,(width*20)+20,0.0,(height*20)+60,0.0,1.0);
    m=Matrix2Di(height,width);
    ms=Matrix2Di(height,width);
    m[16][2]=m[15][2]=m[15][3]=m[15][4]=m[17][2]=m[17][3]=m[17][4]=m[16][5]=m[16][6]=m[16][7]=1;
    m[16][60]=m[15][60]=m[15][59]=m[15][58]=m[16][57]=m[16][56]=m[17][58]=m[17][59]=m[17][60]=m[16][55]=1;
    m[7][31]=m[6][31]=m[5][31]=m[4][30]=m[3][30]=m[2][30]=m[2][31]=m[2][32]=m[3][32]=m[4][32]=1;
    m[28][30]=m[29][30]=m[30][30]=m[30][31]=m[30][32]=m[29][32]=m[28][32]=m[27][31]=m[26][31]=m[25][31]=1;
    saveMatrix(m,ms,width,height);
    //______________________________________
    while (!glfwWindowShouldClose(window)  && !glfwGetKey(window,GLFW_KEY_ESCAPE))
    {
        time=glfwGetTime();
        title="The Game Of Life    ";title+=to_string(FPS-20).c_str();
        draw(m,width,height,run);
        if(run)
            update(m,height,width);
        glfwSetWindowTitle(window,title.c_str());
        glfwSwapBuffers(window);
        glfwPollEvents();
        if(glfwGetTime()-time<(1.0/FPS))
            usleep(((1.0/FPS)-(glfwGetTime()-time))*1000000);
    }
    glfwTerminate();
    return 0;
}

GLFWwindow* Init_()
{
    GLFWwindow* window;
    int x=(width*20)+20,y=(height*20)+60;
    window = glfwCreateWindow(x,y,"The Game Of Life",NULL,NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetWindowSizeLimits(window,x,y,x,y);
    return window;
}


