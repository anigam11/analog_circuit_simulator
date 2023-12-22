//Resistor.cpp 

#include "Resistor.h"
#include <GL/glut.h>
#include <cmath>
#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

Resistor::Resistor(double _resistance, float R, float G, float B, const std::string& _name) {
    // Constructor for creating a Resistor object.
    // Parameters:
    // _resistance: The resistance value of the resistor in Ohms.
    // R, G, B: Red, Green, and Blue color components for visualization.
    // _name: The name or identifier for the resistor.
    resistance = _resistance;
    Red = R;
    Green = G;
    Blue = B;
    name = _name;
}

std::string Resistor::GetName() const {
    // Getting the name of the resistor.
    return name;
}

void Resistor::Update() {

}

double Resistor::GetVoltage(double current, double timestep) {

    return current * resistance;
}

void Resistor::Display(double xpos, double ypos) {
    glColor3f(Red, Green, Blue);//RGB
    glBegin(GL_POINTS);
    glVertex2f(xpos, ypos);
    glEnd();
    glFlush();
}

