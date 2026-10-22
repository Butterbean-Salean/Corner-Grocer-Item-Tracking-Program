#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// Class to manage item tracking and frequency analysis for Corner Grocer
class ItemTracker {
private:
    map<string, int> itemFrequencyMap;

    // Helper method to load data from the input file and populate the map
    void loadData(const string& inputFilename) {
        ifstream inputFile(inputFilename);
        if (!inputFile.is_open()) {
            cout << "Error: Could not open input file " << inputFilename << endl;
            return;
        }

        string item;
        // Read file word by word (each line/word represents a purchased item)
        while (inputFile >> item) {
            itemFrequencyMap[item]++;
        }
        inputFile.close();
    }

    // Helper method to write the accumulated frequency data to frequency.dat backup file
    void exportData(const string& outputFilename) {
        ofstream outputFile(outputFilename);
        if (!outputFile.is_open()) {
            cout << "Error: Could not create backup file " << outputFilename << endl;
            return;
        }

        for (auto const& [item, frequency] : itemFrequencyMap) {
            outputFile << item << " " << frequency << endl;
        }
        outputFile.close();
    }

public:
    // Constructor initializes the tracker by reading the input file and creating frequency.dat
    ItemTracker(const string& inputFilename, const string& outputFilename) {
        loadData(inputFilename);
        exportData(outputFilename);
    }

    // Menu Option 1: Prompt user for an item and return its frequency
    void searchItem() const {
        string searchItem;
        cout << "Enter the item you wish to look for: ";
        cin >> searchItem;

        auto it = itemFrequencyMap.find(searchItem);
        if (it != itemFrequencyMap.end()) {
            cout << endl << it->first << " was purchased " << it->second << " time(s)." << endl;
        }
        else {
            cout << endl << "Item not found in the records." << endl;
        }
    }

    // Menu Option 2: Print the list of all items and their purchase frequencies
    void printFrequencyList() const {
        cout << "\n--- Item Purchase Frequencies ---" << endl;
        for (auto const& [item, frequency] : itemFrequencyMap) {
            cout << left << setw(15) << item << " " << frequency << endl;
        }
        cout << "----------------------------------" << endl;
    }

    // Menu Option 3: Print a text-based histogram using asterisks
    void printHistogram() const {
        cout << "\n--- Item Purchase Histogram ---" << endl;
        for (auto const& [item, frequency] : itemFrequencyMap) {
            cout << left << setw(15) << item << " ";
            for (int i = 0; i < frequency; ++i) {
                cout << "*";
            }
            cout << endl;
        }
        cout << "-------------------------------" << endl;
    }
};

int main() {
    string inputFile = "CS210_Project_Three_Input_File.txt";
    string backupFile = "frequency.dat";

    // Automatically generate frequency.dat backup file upon program startup
    ItemTracker tracker(inputFile, backupFile);

    int choice = 0;
    do {
        cout << "\n=== Corner Grocer Item Tracker ===" << endl;
        cout << "1. Look up an item frequency" << endl;
        cout << "2. Print all item frequencies" << endl;
        cout << "3. Print histogram of item frequencies" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";

        // Input validation for menu selection (handles non-integer inputs gracefully)
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            cin.clear();
            cin.ignore(10000, '\n'); // Fixed typo from 'ignoring' to 'ignore'
            continue;
        }

        switch (choice) {
        case 1:
            tracker.searchItem();
            break;
        case 2:
            tracker.printFrequencyList();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            cout << "Exiting program. Thank you!" << endl; // Removed accidental 'int()'
            break;
        default:
            cout << "Invalid choice. Please select a valid option between 1 and 4." << endl;
        }
    } while (choice != 4);

    return 0;
}
