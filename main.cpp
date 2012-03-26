#include "GL/freeglut.h"
#include "GL/gl.h"
#include "math.h"
#include "time.h"
#include "vector"

using namespace std;

class Circle {
public:
    float x, y, r, alpha;
    Circle(float _x = 0.0, float _y = 0.0, float _r = 10.0):x(_x), y(_y), r(_r), alpha(1.0) {};
    void draw();
};

void Circle::draw() {
    glColor4f(1.0, 0.0, 0.0, this->alpha);
    glBegin(GL_LINE_LOOP);
    for (float i = 0.0; i < 2 * 3.14; i+= 3.14 / 18) {
        glVertex2f(this->x + this->r * sin (i), this->y + this->r * cos(i) );
    }
    glEnd();
}

vector<Circle> circ;

float WinWid = 400.0;
float WinHei = 400.0;

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_ALPHA);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    vector<Circle>::iterator i = circ.begin();
    while(i != circ.end()) {
        i->draw();
        if(i->alpha <= 0.1f) {
            i = circ.erase(i);
        } else {
             i++;
        }
    }
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA);
    glutSwapBuffers();
}

void Timer(int value) {
    for(vector<Circle>::iterator i = circ.begin(); i != circ.end(); i++ ) {
        i->r++;
        i->alpha/=1.05;
    }
    glutPostRedisplay();
    glutTimerFunc(50, Timer, 0);
}

void Timer2(int value) {
    Circle c(rand() % int(WinWid) - WinWid / 2, rand() % int(WinHei) - WinHei / 2, rand() % 20 + 2);
    circ.push_back(c);
    glutPostRedisplay();
    glutTimerFunc(1000, Timer2, 0);
}

void Initsialaize() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WinWid/2, WinWid/2, -WinHei/2, WinHei/2, -200.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {

    srand(time(0));
    for(int i = 2; i < 2 + rand() % 5; i++) {
        Circle c(rand() % int(WinWid) - WinWid / 2, rand() % int(WinHei) - WinHei / 2, rand() % 20 + 2);
        circ.push_back(c);
    }
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(WinWid, WinHei);
    glutInitWindowPosition(100, 200);
    glutCreateWindow("Lesson 07");
    
    glutDisplayFunc(Draw);
    glutTimerFunc(50, Timer, 0);
    glutTimerFunc(1000, Timer2, 0);
    Initsialaize();
    glutMainLoop();
    
    return 0;
}

