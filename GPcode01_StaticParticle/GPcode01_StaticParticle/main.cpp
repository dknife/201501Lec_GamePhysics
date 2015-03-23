#include <stdio.h>
#include <stdlib.h>
#include <GLUT/GLUT.h>

#include "StopWatch.h"

#include <stdlib.h>

GLfloat angle = 0.0;	/*Rotationsvinkel*/

void createMenu(void);
void menu(int value);
void disp(void);

static int win;
static int menu_id;
static int animeringsmeny;
static int springmeny;
static int val = 0;
static int fyrkantRoed = 1;
static int fyrkantGroen = 0;
static int fyrkantBla = 0;
static int trekantRoed = 1;
static int trekantGroen = 0;
static int trekantBla = 0;

int main(int argc, char **argv){
    
    // normal initialisation
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    
    win = glutCreateWindow("GLUT MENU");
    
    // put all the menu functions in one nice procedure
    createMenu();
    
    // set the clearcolor and the callback
    glClearColor(0.0,0.0,0.0,0.0);
    
    glutDisplayFunc(disp);
    
    // enter the main loop
    glutMainLoop();
    
}
void createMenu(void){
    //////////
    // MENU //
    //////////
    
    // Create a submenu, this has to be done first.
    animeringsmeny = glutCreateMenu(menu);
    
    // Add sub menu entry
    glutAddMenuEntry("På", 1);
    glutAddMenuEntry("Av", 2);
    
    springmeny = glutCreateMenu(menu);
    
    glutAddMenuEntry("Gå", 3);
    glutAddMenuEntry("Galopp", 4);
    
    // Create the menu, this menu becomes the current menu
    menu_id = glutCreateMenu(menu);
    
    // Create an entry
    glutAddSubMenu("Animering", animeringsmeny);
    glutAddSubMenu("Löpstil", springmeny);
    // Create an entry
    glutAddMenuEntry("Avluta", 0);
    
    // Let the menu respond on the right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    
}

void disp(void){
    // Just clean the screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_QUADS);
    glColor3f(fyrkantRoed, fyrkantGroen, fyrkantBla);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-0.75f, -1.0f);
    glVertex2f(-0.75f, -0.75f);
    glVertex2f (-1.0f, -0.75f);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glColor3f(trekantRoed, trekantGroen, trekantBla);
    glVertex2f(-0.6f, -1.0f);
    glVertex2f(-0.4f, -1.0f);
    glVertex2f(-0.6f, -0.6f);
    glEnd();
    
    // ändra färg beroende på menyval
    if(val == 1){
        trekantBla = 1;
        trekantRoed = 0;
        trekantGroen = 0;
    }
    else if(val == 2){
        trekantBla = 0;
        trekantRoed = 1;
        trekantGroen = 0;
    }
    else if(val == 3){
        fyrkantRoed = 0;
        fyrkantGroen = 0;
        fyrkantBla = 1;
    }
    else if(val == 4){
        fyrkantRoed = 1;
        fyrkantGroen = 0;	
        fyrkantBla = 0;
    }
    glFlush();
}



void menu(int value){
    if(value == 0){
        glutDestroyWindow(win);
        exit(0);
    }else{
        val=value;
    }
    
    // you would want to redraw now
    glutPostRedisplay();
}