//Inductor.h
//30-Oct-23  Tanish Naresh Kalathiya, Arnav Nigam, Smeet Patel        Created.

#ifndef _INDUCTOR_H_
#define _INDUCTOR_H_

#include "Component.h"

class Inductor : public Component {
private:
    double inductance;   // The inductance of the inductor.
    double current;      // The current flowing through the inductor.
    double prevCurrent;  // The previous current for simulation updates.

public:
    // Constructor for creating an Inductor object.
    Inductor(double inductance, float R, float G, float B, const std::string& name);
    std::string GetName() const override;
    void Update() override;
    double GetVoltage(double current, double timestep) override;
    void Display(double xpos, double ypos) override;
};

#endif // _INDUCTOR_H_
