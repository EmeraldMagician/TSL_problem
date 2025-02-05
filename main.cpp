#include <iostream>
//#include "funcs.hpp"
#include "solvers.hpp"

#include <ctime>
#include <random>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(0));
    // generate_country();
    /*glutInit(&argc, argv);
    glutInitWindowSize(window_traits::width, window_traits::height);
    glutInitWindowPosition(window_traits::position.x, window_traits::position.y);
    glutInitDisplayMode(GLUT_RGB);
    glMatrixMode(GL_PROJECTION);
    glutCreateWindow("TSL");
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(mutate);
    glutMainLoop();*/
    // while (mutate());
    /*for (int i = 1; i <= 13; ++i){
        cities_n = i;
        test_sequence(1000);
    }*/
    // cities_n = 17;
    // test_sequence(100);
    Tester tester(dynamic | genetic | research);
    tester.test();
    return 0;
}
