#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// ------------------- ABSTRACT CLASS (Milestone 4: Interface) -------------------
class RiskStrategy {
public:
    virtual float calculateRisk() = 0;
};

// ------------------- BASE CLASS (Inheritance) -------------------
class SensorData {
public:
    float temperature, humidity, rainfall, soilMoisture;

    void input() {
        cout << "\nEnter temperature: ";
        cin >> temperature;

        cout << "Enter humidity: ";
        cin >> humidity;

        cout << "Enter rainfall: ";
        cin >> rainfall;

        cout << "Enter soil moisture: ";
        cin >> soilMoisture;

        // Exception handling
        if (temperature < 0 || humidity < 0 || rainfall < 0 || soilMoisture < 0) {
            throw "Invalid input! Values must be positive.";
        }
    }
};

// ------------------- DERIVED CLASS -------------------
class Crop {
public:
    string type;

    void input() {
        cout << "Enter crop type (maize/beans/rice): ";
        cin >> type;
    }

    float getCropScore() {
        if (type == "maize") return 10;
        else if (type == "beans") return 7;
        else if (type == "rice") return 12;
        else return 5;
    }
};

// ------------------- POLYMORPHISM -------------------
class PestRiskCalculator : public RiskStrategy {
public:
    float calculateRisk(SensorData s, Crop c) {
        float risk = (s.temperature * 0.25) +
                     (s.humidity * 0.30) +
                     (s.rainfall * 0.20) +
                     (s.soilMoisture * 0.15) +
                     c.getCropScore();
        return risk;
    }
};

// ------------------- ALERT SYSTEM -------------------
class AlertSystem {
public:
    void showAlert(float risk) {
        cout << "\nTotal Pest Risk: " << risk << endl;

        if (risk > 70)
            cout << "HIGH Pest Risk\n";
        else if (risk > 40)
            cout << "MODERATE Pest Risk\n";
        else
            cout << "LOW Pest Risk\n";
    }
};

// ------------------- FILE HANDLING -------------------
class FileHandler {
public:
    void saveToFile(SensorData s, Crop c, float risk) {
        ofstream file("pest_log.txt", ios::app);

        file << "Temp: " << s.temperature
             << ", Humidity: " << s.humidity
             << ", Rainfall: " << s.rainfall
             << ", Soil: " << s.soilMoisture
             << ", Crop: " << c.type
             << ", Risk: " << risk << endl;

        file.close();
    }
};

// ------------------- MAIN SYSTEM -------------------
int main() {
    vector<SensorData> records; // Milestone 3: array/structured dataset
    PestRiskcalculator calculator;
    AlertSystem alert;
    FileHandler file;

    int choice;

    do {
        SensorData sensor;
        Crop crop;

        try {
            sensor.input();
            crop.input();

            float risk = calculator.calculateRisk(sensor, crop);

            alert.showAlert(risk);

            file.saveToFile(sensor, crop, risk);

            records.push_back(sensor); // store multiple entries

        } catch (const char* msg) {
            cout << msg << endl;
            continue;
        }

        cout << "\nRun again? (1 = Yes, 0 = No): ";
        cin >> choice;

    } while (choice == 1);

    // Display stored records count
    cout << "\nTotal records stored: " << records.size() << endl;

    return 0;
}
