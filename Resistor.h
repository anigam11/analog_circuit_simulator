//Resistor.h 

#ifndef _RESISTOR_H_
#define _RESISTOR_H_

#include "Component.h"

class Resistor : public Component {
private: 
    double resistance;         // The resistance of the resistor.
public:
    // Constructor for creating a Resistor object.
    Resistor(double resistance, float R, float G, float B, const std::string& name);
    // Getting the name of the resistor.
    std::string GetName() const override;
    // Updating the internal state of the resistor.
    void Update() override;
    // Calculating the voltage across the resistor based on the current and time step.
    double GetVoltage(double current, double timestep) override;
    void Display(double xpos, double ypos) override;
};

#endif // _RESISTOR_H_
