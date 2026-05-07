#include <iostream>
using namespace std;

class PestSystem {
private:
    float temperature, humidity, rainfall, soilMoisture;
    string cropType;

    float tempScore, humidityScore, rainfallScore, soilScore, cropScore;
    float pestRisk;

public:
    // Input all parameters
    void inputData() {
        cout << "\nEnter temperature: ";
        cin >> temperature;

        cout << "Enter humidity: ";
        cin >> humidity;

        cout << "Enter rainfall: ";
        cin >> rainfall;

        cout << "Enter soil moisture: ";
        cin >> soilMoisture;

        cout << "Enter crop type (maize/beans/rice): ";
        cin >> cropType;

        // Validation
        if (temperature < 0 || humidity < 0 || rainfall < 0 || soilMoisture < 0) {
            cout << "Invalid input! Values must be positive.\n";
            inputData();
        }
    }

    // Compute each parameter separately
    void computeTemperatureEffect() {
        tempScore = temperature * 0.25;
    }

    void computeHumidityEffect() {
        humidityScore = humidity * 0.30;
    }

    void computeRainfallEffect() {
        rainfallScore = rainfall * 0.20;
    }

    void computeSoilEffect() {
        soilScore = soilMoisture * 0.15;
    }

    void computeCropEffect() {
        // Assign crop-based risk factor
        if (cropType == "maize") {
            cropScore = 10;
        }
        else if (cropType == "beans") {
            cropScore = 7;
        }
        else if (cropType == "rice") {
            cropScore = 12;
        }
        else {
            cropScore = 5; // default
        }
    }

    // Final pest risk calculation
    void calculatePestRisk() {
        pestRisk = tempScore + humidityScore + rainfallScore + soilScore + cropScore;
    }

    // Output results
    void displayResult() {
        cout << "\n--- Pest Risk Breakdown ---\n";
        cout << "Temperature Effect: " << tempScore << endl;
        cout << "Humidity Effect: " << humidityScore << endl;
        cout << "Rainfall Effect: " << rainfallScore << endl;
        cout << "Soil Moisture Effect: " << soilScore << endl;
        cout << "Crop Effect: " << cropScore << endl;

        cout << "\nTotal Pest Risk: " << pestRisk << endl;

        if (pestRisk > 70) {
            cout << "HIGH Pest Risk\n";
        }
        else if (pestRisk > 40) {
            cout << "MODERATE Pest Risk\n";
        }
        else {
            cout << "LOW Pest Risk\n";
        }
    }
};

int main() {
    PestSystem system;
    int choice;

    do {
        system.inputData();

        // Compute each parameter
        system.computeTemperatureEffect();
        system.computeHumidityEffect();
        system.computeRainfallEffect();
        system.computeSoilEffect();
        system.computeCropEffect();

        system.calculatePestRisk();
        system.displayResult();

        cout << "\nRun again? (1 = Yes, 0 = No): ";
        cin >> choice;

    } while (choice == 1);

    return 0;
}
