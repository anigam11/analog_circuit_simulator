//AnalogCircuit.cpp - function definitions for the analog circuit
//
// 20-May-22  M. Watler         Created.
// 27-May-22  M. Watler         Added graphical display.
// 30-Oct-23  Tanish Naresh Kalathiya, Arnav Nigam, Smeet Patel        Modified.

#include <iomanip>//setw
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>//M_PI
#include <stdlib.h>//abs

#include "AnalogCircuit.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Resistor.h"

using namespace std;

int xpos, ypos;
int windowWidth, windowHeight;
double scalingFactor;

void start() {
	cout << "BEGIN" << endl;
	AnalogCircuit circuit("RLC.dat");
	circuit.run();
	cout << "Press any key + ENTER to end..." << endl;
	char key;
	cin >> key;
	glutLeaveMainLoop();
	cout << "DONE!" << endl;
}

void AnalogCircuit::display(float R, float G, float B) { //drawing a point on the screen
	//	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R, G, B);//RGB
	glBegin(GL_POINTS);
	glVertex2f(xpos, ypos);
	glEnd();
	glFlush();
}

AnalogCircuit::AnalogCircuit(string filename) {
	fout.open(filename);

	if (!fout.is_open()) {
		cerr << "Error opening output file." << endl;
		exit(1);  // Exit the program if there was an error opening the file
	}

}


void AnalogCircuit::run() {
	component.push_back(new Capacitor(0.000100, 0.0, 1.0, 0.0, "C1"));//100uF, Green
	component.push_back(new Inductor(0.020, 0.0, 0.0, 1.0, "L1"));//20mH, Blue
	component.push_back(new Resistor(10, 1.0, 0.0, 0.0, "R1"));//10ohm, Red

	//Horizontal line
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);  // White color for the line
	glVertex2f(xoffset, (windowHeight*scalingFactor)/2);      // Starting point of the line (x, y)
	glVertex2f(windowWidth, (windowHeight * scalingFactor) / 2 );      // Ending point of the line (x, y)
	glEnd();
	glFlush();

	//Vertical line
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);  // White color for the line
	glVertex2f(xoffset, 0.0);     // Starting point of the line (x, y)
	glVertex2f(xoffset, scalingFactor*windowHeight);   // Ending point of the line (x, y)
	glEnd();
	glFlush();

	//Horizontal line markers
	glColor3f(1.0, 1.0, 1.0);  // White color for the markers
	glBegin(GL_LINES);
	double xMarker = 50;
	for (double x = 1.0; x <= 11.0; x++) { // Adjusting the marker position
		glVertex2f((xoffset - 10),xMarker); // Drawing a small line below the horizontal line
		glVertex2f((xoffset + 10),xMarker);
		xMarker = xMarker + 50;

	}
	glEnd();
	glFlush();
	
	//Vertical line markers
	glColor3f(1.0, 1.0, 1.0);  // White color for the markers
	glBegin(GL_LINES);
	double yMarker = xoffset + 80;
	for (double y = 1.0; y <= 11.0; y++) {
		// Adjust the marker position
		glVertex2f(yMarker, (windowHeight*scalingFactor/2) - 10); // Drawing a small line to the left of the vertical line
		glVertex2f(yMarker, (windowHeight * scalingFactor / 2) + 10);
		yMarker = yMarker + 80;
	}
	glEnd();
	glFlush();


	//Displaying each component's name and colour
	glFlush();


	//Runn the simulation for the first 0.06 seconds (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen
	for (double time = 0.0; time < 0.6 * timeMax; time += T) {
		double V = Vpeak * sin(2.0 * M_PI * freq * time);

		//...
		ypos = (windowHeight * V / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;
		xpos = ((time / ( timeMax)) * windowWidth)+45;

		// Assuming time is in seconds
		display(1.0,1.0,1.0);

		CostFunctionV(I, V);
	}

	//Run the simulation to the end (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen
	for (double time = 0.6 * timeMax; time < timeMax; time += T) {
		double V = 0.0;

		//...

		ypos = (windowHeight * V / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;
		xpos = ((time / (timeMax)) * windowWidth)+45;
		display(1.0, 1.0, 1.0);

		CostFunctionV(I, V);
	}
}

void AnalogCircuit::CostFunctionV(double& current, double voltage) {
	double I1 = current;
	double J1 = 0.0;
	double J0 = 0.0;
	double alpha = 1.0;

	do {
		double sumVoltage = 0.0;
		list<Component*>::iterator it;
		for (it = component.begin(); it != component.end(); ++it) {
			double Vcomponent = (*it)->GetVoltage(I1, T);
			sumVoltage += Vcomponent;
		}
		J1 = sumVoltage - voltage;
		if ((abs(J0 - J1) != (J0 - J1)) || J0 == J1)alpha /= 2.0;

		if (abs(J1) > tolerance) {
			if (J1 < 0) {//increase the current
				I1 += alpha;
			}
			else {
				I1 -= alpha;
			}
			J0 = J1;
		}
		if (alpha < tolerance / 1000000.0) {
			alpha = ((double)rand() / (RAND_MAX)) + 0.5;
		}
	} while (abs(J1) > tolerance);

	fout << setw(12) << I1;
	list<Component*>::iterator it;
	for (it = component.begin(); it != component.end(); ++it) {
		fout << setw(12) << (*it)->GetVoltage(I1, T);
		ypos = (windowHeight * (*it)->GetVoltage(I1, T) / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;
		(*it)->Display(xpos, ypos);
		(*it)->Update();
	}
	fout << endl;

	current = I1;
}

AnalogCircuit::~AnalogCircuit() {//perform cleanup
}