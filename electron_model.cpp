#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Constants
const double ELECTRON_CHARGE = -1.60219e-19; // Elementary charge in coulombs
const double ELECTRON_MASS = 9.10938356e-31; // Electron mass in kilograms
const double ELECTRON_RADIUS = 2.81794e-15; // Classical electron radius in meters

// Electron structure
struct Electron {
    double x, y; // Position in meters
    double vx, vy; // Velocity in meters per second

    // Constructor
    Electron(double initialX, double initialY, double initialVx, double initialVy)
        : x(initialX), y(initialY), vx(initialVx), vy(initialVy) {}
};

// Function to calculate the electrostatic force between two charges
double calculateElectrostaticForce(double q1, double q2, double distance) {
    const double COULOMB_CONSTANT = 8.9875e9; // Coulomb's constant in N·m^2/C^2
    return (COULOMB_CONSTANT * q1 * q2) / (distance * distance);
}

// Function to update the electron's position and velocity based on electrostatic forces
void updateElectron(Electron &electron, double timeStep, double externalField = 0.0) {
    // Update position using current velocity
    electron.x += electron.vx * timeStep;
    electron.y += electron.vy * timeStep;

    // Calculate the distance from the origin (0, 0)
    double distance = std::sqrt(electron.x * electron.x + electron.y * electron.y);

    // Calculate the electrostatic force between the electron and the origin (nucleus)
    double force = calculateElectrostaticForce(ELECTRON_CHARGE, ELECTRON_CHARGE, distance);

    // Apply the external electric field force
    force += externalField * ELECTRON_CHARGE;

    // Calculate the acceleration using Newton's second law (F = ma)
    double acceleration = force / ELECTRON_MASS;

    // Update velocity based on acceleration
    electron.vx += acceleration * (electron.x / distance) * timeStep;
    electron.vy += acceleration * (electron.y / distance) * timeStep;
}

int main() {
    // Seed the random number generator
    std::srand(std::time(0));

    // Create an electron at a random initial position with a random initial velocity
    Electron electron(std::rand() % 10 - 5, std::rand() % 10 - 5,
                      std::rand() % 1000 - 500, std::rand() % 1000 - 500);

    // Simulation parameters
    const double TIME_STEP = 1.0e-15; // Time step in seconds
    const double SIMULATION_TIME = 1.0e-12; // Total simulation time in seconds

    // Simulation loop
    for (double t = 0; t < SIMULATION_TIME; t += TIME_STEP) {
        // Update the electron's position and velocity
        updateElectron(electron, TIME_STEP);

        // Print the electron's position at each time step
        std::cout << "Time: " << t << " seconds, Position: (" << electron.x << ", " << electron.y << ")\n";
    }

    return 0;
}
