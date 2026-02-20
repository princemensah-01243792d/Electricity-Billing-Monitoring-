#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

// Appliance Class
class Appliance {
private:
    string name;
    double powerRating;  // in watts
    double dailyHours;   // hours used per day

public:
    // Constructor
    Appliance() : name(""), powerRating(0), dailyHours(0) {}
    
    Appliance(string n, double p, double h) {
        setName(n);
        setPowerRating(p);
        setDailyHours(h);
    }

    // Setters with validation
    void setName(string n) {
        if (!n.empty()) {
            name = n;
        } else {
            name = "Unknown Appliance";
        }
    }

    void setPowerRating(double p) {
        if (p > 0) {
            powerRating = p;
        } else {
            powerRating = 0;
            cout << "Warning: Power rating must be greater than 0. Set to 0 temporarily.\n";
        }
    }

    void setDailyHours(double h) {
        if (h >= 0 && h <= 24) {
            dailyHours = h;
        } else {
            dailyHours = 0;
            cout << "Warning: Daily hours must be between 0 and 24. Set to 0 temporarily.\n";
        }
    }

    // Getters
    string getName() const { return name; }
    double getPowerRating() const { return powerRating; }
    double getDailyHours() const { return dailyHours; }

    // Display appliance information
    void display() const {
        cout << left << setw(20) << name 
             << right << setw(10) << fixed << setprecision(0) << powerRating << " W"
             << setw(10) << fixed << setprecision(1) << dailyHours << " hrs/day\n";
    }
};

// Function prototypes
void displayMenu();
void registerAppliance(vector<Appliance>& appliances);
void viewAllAppliances(const vector<Appliance>& appliances);
void searchAppliance(const vector<Appliance>& appliances);
void clearInputBuffer();
void pressAnyKeyToContinue();

int main() {
    vector<Appliance> appliances;
    int choice;

    cout << "=========================================\n";
    cout << "  ELECTRICAL LOAD MONITORING SIMULATOR  \n";
    cout << "=========================================\n";
    cout << "           Week 1 - Basic Setup         \n";
    cout << "=========================================\n\n";

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        // Check if input failed
        if (cin.fail()) {
            cin.clear();
            clearInputBuffer();
            cout << "\nInvalid input! Please enter a number.\n";
            pressAnyKeyToContinue();
            continue;
        }

        clearInputBuffer(); // Clear any remaining input

        switch (choice) {
            case 1:
                registerAppliance(appliances);
                break;
            case 2:
                viewAllAppliances(appliances);
                break;
            case 3:
                searchAppliance(appliances);
                break;
            case 4:
                cout << "\nExiting program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please enter 1-4.\n";
                pressAnyKeyToContinue();
        }
    } while (choice != 4);

    return 0;
}

void displayMenu() {
    cout << "\n" << string(40, '-') << "\n";
    cout << "MAIN MENU\n";
    cout << string(40, '-') << "\n";
    cout << "1. Register Appliance\n";
    cout << "2. View All Appliances\n";
    cout << "3. Search Appliance by Name\n";
    cout << "4. Exit\n";
    cout << string(40, '-') << "\n";
}

void registerAppliance(vector<Appliance>& appliances) {
    cout << "\n" << string(40, '=') << "\n";
    cout << "REGISTER NEW APPLIANCE\n";
    cout << string(40, '=') << "\n\n";

    string name;
    double power, hours;

    // Get appliance name
    cout << "Enter appliance name: ";
    getline(cin, name);

    // Get power rating with validation
    do {
        cout << "Enter power rating (watts, > 0): ";
        cin >> power;
        
        if (cin.fail() || power <= 0) {
            cin.clear();
            clearInputBuffer();
            cout << "Invalid input! Power rating must be a positive number.\n";
        } else {
            break;
        }
    } while (true);

    // Get daily usage hours with validation
    do {
        cout << "Enter daily usage hours (0-24): ";
        cin >> hours;
        
        if (cin.fail() || hours < 0 || hours > 24) {
            cin.clear();
            clearInputBuffer();
            cout << "Invalid input! Hours must be between 0 and 24.\n";
        } else {
            break;
        }
    } while (true);

    clearInputBuffer(); // Clear any remaining input

    // Create and add appliance
    Appliance newAppliance(name, power, hours);
    appliances.push_back(newAppliance);

    cout << "\n✓ Appliance registered successfully!\n";
    cout << "\nAppliance Details:\n";
    cout << string(30, '-') << "\n";
    newAppliance.display();
    
    pressAnyKeyToContinue();
}

void viewAllAppliances(const vector<Appliance>& appliances) {
    cout << "\n" << string(40, '=') << "\n";
    cout << "REGISTERED APPLIANCES\n";
    cout << string(40, '=') << "\n\n";

    if (appliances.empty()) {
        cout << "No appliances registered yet.\n";
    } else {
        cout << left << setw(20) << "Appliance Name" 
             << right << setw(12) << "Power (W)"
             << setw(15) << "Daily Hours\n";
        cout << string(47, '-') << "\n";
        
        for (size_t i = 0; i < appliances.size(); i++) {
            cout << i + 1 << ". ";
            appliances[i].display();
        }
        
        cout << "\nTotal appliances: " << appliances.size() << "\n";
    }
    
    pressAnyKeyToContinue();
}

void searchAppliance(const vector<Appliance>& appliances) {
    cout << "\n" << string(40, '=') << "\n";
    cout << "SEARCH APPLIANCE\n";
    cout << string(40, '=') << "\n\n";

    if (appliances.empty()) {
        cout << "No appliances registered yet.\n";
        pressAnyKeyToContinue();
        return;
    }

    string searchName;
    cout << "Enter appliance name to search: ";
    getline(cin, searchName);

    // Convert search term to lowercase for case-insensitive search
    string searchLower = searchName;
    for (char &c : searchLower) {
        c = tolower(c);
    }

    vector<const Appliance*> found;
    
    // Search for matching appliances
    for (const auto& appliance : appliances) {
        string appName = appliance.getName();
        string appLower = appName;
        for (char &c : appLower) {
            c = tolower(c);
        }
        
        if (appLower.find(searchLower) != string::npos) {
            found.push_back(&appliance);
        }
    }

    if (found.empty()) {
        cout << "\nNo appliances found with name containing \"" << searchName << "\".\n";
    } else {
        cout << "\nFound " << found.size() << " matching appliance(s):\n\n";
        cout << left << setw(20) << "Appliance Name" 
             << right << setw(12) << "Power (W)"
             << setw(15) << "Daily Hours\n";
        cout << string(47, '-') << "\n";
        
        for (size_t i = 0; i < found.size(); i++) {
            cout << i + 1 << ". ";
            found[i]->display();
        }
    }
    
    pressAnyKeyToContinue();
}

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pressAnyKeyToContinue() {
    cout << "\nPress Enter to continue...";
    cin.get();
}
