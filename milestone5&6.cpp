#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

// ------------------- SENSOR DATA CLASS -------------------
class SensorData {
private:
    float temperature;
    float humidity;
    float rainfall;
    float soilMoisture;

public:

    // Constructor
    SensorData(float t = 0, float h = 0,
               float r = 0, float s = 0) {

        temperature = t;
        humidity = h;
        rainfall = r;
        soilMoisture = s;
    }

    // Input Function
    void inputData() {

        cout << "\nEnter temperature: ";
        cin >> temperature;

        cout << "Enter humidity: ";
        cin >> humidity;

        cout << "Enter rainfall: ";
        cin >> rainfall;

        cout << "Enter soil moisture: ";
        cin >> soilMoisture;

        // Exception handling
        if (temperature < 0 || humidity < 0 ||
            rainfall < 0 || soilMoisture < 0) {

            throw "Invalid input! Values cannot be negative.";
        }
    }

    // Getter Functions
    float getTemperature() {
        return temperature;
    }

    float getHumidity() {
        return humidity;
    }

    float getRainfall() {
        return rainfall;
    }

    float getSoilMoisture() {
        return soilMoisture;
    }
};

// ------------------- CROP CLASS -------------------
class Crop {
private:
    string cropType;

public:

    // Constructor
    Crop(string type = "Unknown") {
        cropType = type;
    }

    void inputCrop() {
        cout << "Enter crop type (maize/beans/rice): ";
        cin >> cropType;
    }

    string getCropType() {
        return cropType;
    }

    float getCropScore() {

        if (cropType == "maize")
            return 10;

        else if (cropType == "beans")
            return 7;

        else if (cropType == "rice")
            return 12;

        else
            return 5;
    }
};

// ------------------- ABSTRACT CLASS -------------------
class RiskStrategy {
public:
    virtual float calculateRisk(SensorData s, Crop c) = 0;
};

// ------------------- DERIVED CLASS -------------------
class PestRiskCalculator : public RiskStrategy {
public:

    float calculateRisk(SensorData s, Crop c) override {

        float risk =
            (s.getTemperature() * 0.25) +
            (s.getHumidity() * 0.30) +
            (s.getRainfall() * 0.20) +
            (s.getSoilMoisture() * 0.15) +
            c.getCropScore();

        return risk;
    }
};

// ------------------- ALERT SYSTEM -------------------
class AlertSystem {
public:

    void displayAlert(float risk) {

        cout << fixed << setprecision(2);

        cout << "\nTotal Pest Risk: " << risk << endl;

        if (risk > 70)
            cout << "HIGH Pest Risk" << endl;

        else if (risk > 40)
            cout << "MODERATE Pest Risk" << endl;

        else
            cout << "LOW Pest Risk" << endl;
    }
};

// ------------------- FILE HANDLER -------------------
class FileHandler {
public:

    void saveReport(SensorData s, Crop c, float risk) {

        ofstream file("pest_report.txt", ios::app);

        file << "Temperature: " << s.getTemperature()
             << ", Humidity: " << s.getHumidity()
             << ", Rainfall: " << s.getRainfall()
             << ", Soil Moisture: " << s.getSoilMoisture()
             << ", Crop: " << c.getCropType()
             << ", Risk: " << risk << endl;

        file.close();
    }
};

// ------------------- MAIN PROGRAM -------------------
int main() {

    vector<SensorData> sensorRecords;

    PestRiskCalculator calculator;
    AlertSystem alert;
    FileHandler file;

    int choice;

    do {

        cout << "\n========== PEST RISK PREDICTION SYSTEM ==========";
        cout << "\n1. Enter Sensor Data";
        cout << "\n2. Exit";
        cout << "\nChoose option: ";
        cin >> choice;

        switch (choice) {

        case 1: {

            // Dynamic memory allocation
            SensorData* sensor = new SensorData();
            Crop* crop = new Crop();

            try {

                // Input data
                sensor->inputData();
                crop->inputCrop();

                // Calculate risk
                float risk =
                    calculator.calculateRisk(*sensor, *crop);

                // Display alert
                alert.displayAlert(risk);

                // Save to file
                file.saveReport(*sensor, *crop, risk);

                // Store records in vector
                sensorRecords.push_back(*sensor);

                cout << "\nData saved successfully!" << endl;
            }

            catch (const char* msg) {
                cout << msg << endl;
            }

            // Free memory
            delete sensor;
            delete crop;

            break;
        }

        case 2:
            cout << "\nExiting system..." << endl;
            break;

        default:
            cout << "\nInvalid option!" << endl;
        }

    } while (choice != 2);

    cout << "\nTotal Records Stored: "
         << sensorRecords.size() << endl;

    return 0;
}
