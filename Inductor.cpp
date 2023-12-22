//Inductor.cpp

#include "Inductor.h"
#include <GL/glut.h>
#include <cmath>
#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif


// Constructor for creating an Inductor object.
// Parameters:
// _inductance: The inductance value in Henries.
// R, G, B: Red, Green, and Blue color components for visualization.
// _name: The name or identifier for the inductor.
Inductor::Inductor(double _inductance, float R, float G, float B, const std::string& _name) {
    inductance = _inductance;
    Red = R;
    Green = G;
    Blue = B;
    name = _name;
    current = 0.0; // Initialize current
    prevCurrent = 0.0; // Initialize prevCurrent
}

// Getting the name of the inductor.
std::string Inductor::GetName() const {
    return name;
}

void Inductor::Update() {
    prevCurrent = current; // Updating prevCurrent with the current value
}

double Inductor::GetVoltage(double _current, double timestep) {
    // Using the inductor's properties to calculate voltage
    double voltage = inductance * (_current - prevCurrent) / timestep;
    current = _current;
    return voltage;
}

void Inductor::Display(double xpos, double ypos) {
    glColor3f(Red, Green, Blue);  // Setting RGB color
    glBegin(GL_POINTS);           // Beginning rendering as points
    glVertex2f(xpos, ypos);       // Rendering a point at the specified coordinates
    glEnd();                      // Ending rendering
    glFlush();                    // displaying the rendering pipeline

}
