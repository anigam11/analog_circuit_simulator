// Capacitor.h
#ifndef _CAPACITOR_H_
#define _CAPACITOR_H_

#include "Component.h"

class Capacitor : public Component {
private:
    double capacitance;     // The capacitance of the capacitor.
    double voltage;         // The current voltage across the capacitor.
    double prevVoltage;     // The previous voltage for simulation updates.

public:
    Capacitor(double capacitance, float R, float G, float B, const std::string& name);
    std::string GetName() const override;
    void Update() override;
    double GetVoltage(double current, double timestep) override;
    void Display(double xpos, double ypos) override;
};

#endif // _CAPACITOR_H_
