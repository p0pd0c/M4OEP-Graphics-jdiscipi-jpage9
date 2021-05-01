#include "graphics.h"
#include <iostream>
#include <vector>
#include "circle.h"
#include "diceRoller.h"
#include "Button.h"
#include "cstdlib"
#include "ctime"

using namespace std;



// Function declarations for drawing each scene type
void drawWelcome();
void drawInstructions();
void drawRoll();
void drawEnd();

// Components
vector<Button> leftMenu;
vector<Button> rightMenu;
vector<Button> interactables;
vector<Quad> menuOutlines;

// State
int sides;
int modifier;
int roll;

GLdouble width, height;
int wd;

enum {WELCOME, INSTRUCTIONS, ROLL, END} screen;


void init() {
    width = 800;
    height = 800;
    roll = 0;
    sides = 20;
    modifier = 0;
    screen = WELCOME;

    // initialize roll and end buttons
    interactables.push_back(Button({150/255.0,10/255.0,1}, {405, 180}, 350, 350, "Roll"));
    interactables.push_back(Button({0,1,0},{405, 800-175-25},350,350, "Reveal Roll"));
    // initialize leftMenu
    leftMenu.push_back(Button({0,0,1},{90, 95},130, 130, "20"));
    leftMenu.push_back(Button({0,0,1},{90, 95 + 150},130, 130, "12"));
    leftMenu.push_back(Button({0,0,1},{90, 95 + 2*150},130, 130, "8"));
    leftMenu.push_back(Button({0,0,1},{90, 95 + 3*150},130, 130, "6"));
    leftMenu.push_back(Button({0,0,1},{90, 95 + 4*150},130, 130, "4"));
    menuOutlines.push_back(Quad({0,0,0},{85 + 5, 385 + 5},170, 770));
    // initialize right menu
    rightMenu.push_back(Button({0,0,1},{800 - 90, 95},130, 130, "-2"));
    rightMenu.push_back(Button({0,0,1},{800 - 90, 95 + 150},130, 130, "-1"));
    rightMenu.push_back(Button({0,0,1},{800 - 90, 95 + 2*150},130, 130, "0"));
    rightMenu.push_back(Button({0,0,1},{800 - 90, 95 + 3*150},130, 130, "+1"));
    rightMenu.push_back(Button({0,0,1},{800 - 90, 95 + 4*150},130, 130, "+2"));
    menuOutlines.push_back(Quad({0,0,0},{800 - 85 - 5, 385 + 5},170, 770));

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
    glViewport(0, 0, width*2, height*2); // DO NOT CHANGE THIS LINE (unless you're on a Mac running Catalina)

    
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

    if(key == 32) {
        if(screen == END) {
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
    for(Button& b : rightMenu) {
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
            // 4 8 6 12 20
            for(int i = 0; i < leftMenu.size(); i++) {
                if(leftMenu[i].isOverlapping(x,y)) {
                    leftMenu[i].pressDown();
                    switch(i) {
                        case 0:
                            sides = 20;
                            break;
                        case 1:
                            sides = 12;
                            break;
                        case 2:
                            sides = 8;
                            break;
                        case 3:
                            sides = 6;
                            break;
                        case 4:
                            sides = 4;
                            break;
                        default:
                            break;
                    }
                    cout << "User set sides to " + to_string(sides) << endl;
                }
            }

            for(int i = 0; i < rightMenu.size(); i++) {
                if(rightMenu[i].isOverlapping(x,y)) {
                    rightMenu[i].pressDown();
                    switch(i) {
                        case 0:
                            modifier = -2;
                            break;
                        case 1:
                            modifier = -1;
                            break;
                        case 2:
                            modifier = 0;
                            break;
                        case 3:
                            modifier = 1;
                            break;
                        case 4:
                            modifier = 2;
                            break;
                        default:
                            break;
                    }
                    cout << "User set modifier to " + to_string(modifier) << endl;
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
            for(Button& b : rightMenu) {
                if(b.isOverlapping(x,y)) {
                    b.release();
                }
            }

            // Handle flow to the end screen from roll screen
            for(int i = 0; i < interactables.size(); i++) {
                interactables[i].release();

                if(i == 1 && interactables[i].isOverlapping(x, y) && screen == ROLL) {
                    // User pressed the roll result button
                    screen = END;
                } else if(i == 0 && interactables[i].isOverlapping(x, y) && screen == ROLL) {
                    // User releases roll button
                    cout << "User released the roll button with " + to_string(sides) + " sides and a " + to_string(modifier) + " modifier!" << endl;
                    // Need to use the sides and modifier to call the correct method and then set total
                    switch(sides) {
                        case 20:
                            roll = DiceRoller::d20(modifier);
                            break;
                        case 12:
                            roll = DiceRoller::d12(modifier);
                            break;
                        case 8:
                            roll = DiceRoller::d8(modifier);
                            break;
                        case 6:
                            roll = DiceRoller::d6(modifier);
                            break;
                        case 4:
                            roll = DiceRoller::d4(modifier);
                            break;
                        default:
                            break;

                    }
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
    glRasterPos2i(width/2.0 - (5.210347565892984769 * title.length()), height/2.0 + 3*7); // the definition of center
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
    glRasterPos2i(width/2.0 - (5.210347565892984769 * title.length()), height/2.0 + 3*7);
    for (const char &letter : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
    title = "Press r to go to the dice roller!";
    glRasterPos2i(width/2.0 - (5.210347565892984769 * title.length()), height/2.0 + 5*7);
    for (const char &letter : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
}

void drawRoll() {
    // Draw menu outlines
    for(Quad& q: menuOutlines) {
        q.draw();
    }

    // Fill menus with content
    for(Button& b: leftMenu) {
        b.draw();
    }

    for(Button& b : rightMenu) {
        b.draw();
    }

    // Add center content
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
    title = "Press space to go back to the roller!";
    glColor3f(0, 0, 0);
    glRasterPos2i(width/2.0 - (5.210347565892984769 * title.length()), height/2.0 + 3*7); // the definition of center
    for (const char &letter : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    srand(time(0));

    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("DND Dice Roller!" /* title */ );
    
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