#include <iostream>
#include <GLFW/glfw3.h>
#include "fonction.h"

using namespace std;

void update(int** m,int w,int h);
void draw(int** m,int w,int h,int state);
void drawGrid(int** m,int w,int h);
void drawButton(int state);
void drawCell(int** m,int w,int h);

void clearMatrix(int** m,int width,int height);
void resetMatrix(int** m,int** ms,int width,int height);
void saveMatrix(int** m,int** ms,int width,int height);

void updateCell(int** m,float mx,float my);
