#include "graphics.h"
#include <iostream>
#include <vector>
#include "circle.h"
#include "Button.h"

using namespace std;

int roll;

// Function declarations for drawing each scene type
void drawWelcome();
void drawInstructions();
void drawRoll();
void drawEnd();

// Components
vector<Button> leftMenu;
vector<Button> rightMenu;
vector<Button> interactables;
Quad leftMenuOutLine;
Quad rightMenuOutLine;

GLdouble width, height;
int wd;

enum {WELCOME, INSTRUCTIONS, ROLL, END} screen;

void init() {
    width = 800;
    height = 800;
    roll = 0;
    screen = WELCOME;

    // initialize roll and end buttons
    interactables.push_back(Button({1,0,0}, {static_cast<int>(width/2), static_cast<int>(height/2)}, 150, 150, "Roll"));
    interactables.push_back(Button({0,1,0},{static_cast<int>(width/2), static_cast<int>(height/2 + 200)},150,150, "Total = NaN"));
    // initialize leftMenu
    leftMenu.push_back(Button({0,0,1},{static_cast<int>(width/2) - 200, static_cast<int>(height/2)},100, 100, "20"));
    leftMenu.push_back(Button({0,0,1},{static_cast<int>(width/2) - 200, static_cast<int>(height/2) + 200},100, 100, "20"));
    leftMenu.push_back(Button({0,0,1},{static_cast<int>(width/2) - 200, static_cast<int>(height/2) + 400},100, 100, "20"));
    leftMenu.push_back(Button({0,0,1},{static_cast<int>(width/2) - 200, static_cast<int>(height/2) + 600},100, 100, "20"));
    leftMenu.push_back(Button({0,0,1},{static_cast<int>(width/2) - 200, static_cast<int>(height/2) + 800},100, 100, "20"));
    leftMenuOutLine = Quad({1,1,1},{100, 400},200, 800);

}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    if(__APPLE__) {
        glViewport(0, 0, width*2, height*2); // DO NOT CHANGE THIS LINE (unless you're on a Mac running Catalina)
    } else {
        glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you're on a Mac running Catalina)
    }

    
    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE
    
    /*
     * Draw here
     */

    switch(screen) {
        case WELCOME:
            drawWelcome();
            break;
        case INSTRUCTIONS:
            drawInstructions();
            break;
        case ROLL:
            drawRoll();
            break;
        case END:
            drawEnd();
            break;
    }
    
    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    if(key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    if(key == 105) {
        screen = INSTRUCTIONS;
    }

    if(key == 114) {
        if(screen == INSTRUCTIONS) {
            screen = ROLL;
        }
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            
            break;
        case GLUT_KEY_LEFT:
            
            break;
        case GLUT_KEY_RIGHT:
            
            break;
        case GLUT_KEY_UP:
            
            break;
    }
    
    glutPostRedisplay();
}

// Mouse movement
void cursor(int x, int y) {
    for(Button& b : leftMenu) {
        if(b.isOverlapping(x,y)) {
            b.hover();
        } else {
            b.release();
        }
    }

    for(Button& b : interactables) {
        if(b.isOverlapping(x,y)) {
            b.hover();
        } else {
            b.release();
        }
    }
    glutPostRedisplay();
}

// Mouse interaction
// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_DOWN) {
            for(Button& b : leftMenu) {
                if(b.isOverlapping(x,y)) {
                    b.pressDown();
                }
            }

            for(Button& b : interactables) {
                if(b.isOverlapping(x,y)) {
                    b.pressDown();
                }
            }
        } else {
            for(Button& b : leftMenu) {
                if(b.isOverlapping(x,y)) {
                    b.release();
                }
            }

            for(Button& b : interactables) {
                if(b.isOverlapping(x,y)) {
                    b.release();
                }
            }
        }
    }
    glutPostRedisplay();
}

void timer(int dummy) {
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

void drawWelcome() {
    string title = "Welcome to DND Dice Roller!";
    glColor3f(0, 0, 0);
    glRasterPos2i(width/2.0 - (5.210347565892984769 * title.length()), height/2.0 + 7); // the definition of center
    for (const char &letter : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
    title = "Press i at any time to see the instructions!";
    glRasterPos2i(width/2.0 - (5.210347565892984769 * title.length()), height/2.0 + 7 + 7); // the definition of center
    for (const char &letter : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
}

void drawInstructions() {
    string title = "Use the left menu to select the number of faces on the die!";
    glColor3f(0, 0, 0);
    glRasterPos2i(width/2.0 - (5.210347565892984769 * title.length()), height/2.0 + 7); // the definition of center
    for (const char &letter : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
    title = "Use the right menu to select modifier!";
    glRasterPos2i(width/2.0 - (5.210347565892984769 * title.length()), height/2.0 + 7 + 7);
    for (const char &letter : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
    title = "Press r to go to the dice roller!";
    glRasterPos2i(width/2.0 - (5.210347565892984769 * title.length()), height/2.0 + 7 + 7 + 7);
    for (const char &letter : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
}

void drawRoll() {
    leftMenuOutLine.draw();
    for(Button& b: leftMenu) {
        b.draw();
    }

    rightMenuOutLine.draw();
    for(Button& b : rightMenu) {
        b.draw();
    }

    for(Button& b : interactables) {
        b.draw();
    }

}

void drawEnd() {
    string title = "You rolled a " + to_string(roll);
    glColor3f(0, 0, 0);
    glRasterPos2i(width/2.0 - (5.210347565892984769 * title.length()), height/2.0 + 7); // the definition of center
    for (const char &letter : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Fun with Drawing!" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}