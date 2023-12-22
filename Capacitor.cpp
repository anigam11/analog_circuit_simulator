// Capacitor.cpp
// Capacitor class represents a passive electronic component in a circuit.
// It models the behavior of a capacitor, including its capacitance, voltage, and visual representation.
// The class is used in an analog circuit simulation. 

#include "Capacitor.h"
#include <GL/glut.h>
#include <cmath>
#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif


Capacitor::Capacitor(double _capacitance, float R, float G, float B, const std::string& _name) {
    // Parameters:
    // _capacitance: The capacitance value in Farads.
    //  R, G, B: Red, Green, and Blue color components for visualization.
    // _name: The name or identifier for the capacitor.
    capacitance = _capacitance;
    Red = R;
    Green = G;
    Blue = B;
    name = _name;
    voltage = 0.0; // Initialize voltage
    prevVoltage = 0.0; // Initialize prevVoltage
}

std::string Capacitor::GetName() const {     
    // Get the name of the capacitor.
    return name;
}

void Capacitor::Update() {
    // Updating the capacitor's internal state.
    // Typically called during a simulation time step to update the voltage across the capacitor.
    prevVoltage = voltage; 

}

double Capacitor::GetVoltage(double _current, double timestep) {
    // Calculating the voltage across the capacitor based on the current and time step.
    // Using the capacitor's properties to calculate voltage
    voltage = prevVoltage + _current * timestep / capacitance;
    return voltage;
}

void Capacitor::Display(double xpos, double ypos) {
    // Displaying the visual representation of the capacitor.
    // Parameters:
    // xpos: X-coordinate for rendering.
    // ypos: Y-coordinate for rendering.
    glColor3f(Red, Green, Blue);//RGB
    glBegin(GL_POINTS);
    glVertex2f(xpos, ypos);
    glEnd();
    glFlush();
}
