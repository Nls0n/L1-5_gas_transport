#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void float_input(float& var) {
    while (!(cin >> var) || var <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter positive number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void int_input(int& var) {
    while (!(cin >> var) || var <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter positive number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


class Pipe {
public:
    string km_mark;
    float length; // km
    int diameter; // mm
    bool is_in_repair;

    void read_from_console() {
        string input;

        cout << "Input kilometers mark (name): ";
        getline(cin, km_mark);
        cout << "Input pipe length: ";
        float_input(length);
        cout << "Input pipe diameter: ";
        int_input(diameter);
        cout << "Input is_in_repair status: ";
        while (!(cin >> is_in_repair || (is_in_repair < 0 && is_in_repair > 1))) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter 1 or 0: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void write_to_console() {
        cout << "Pipe km_mark: " << km_mark << endl;
        cout << "Pipe length (km): " << length << endl;
        cout << "Pipe diameter (mm): " << diameter << endl;
        cout << "Pipe is_in_repair: " << is_in_repair << endl;
    }

    void change_status() {
        is_in_repair = !is_in_repair;
        cout << "Current status: " << is_in_repair << endl;
    }

    void save_to_file() {
        ofstream out;
        out.open("pipe.txt");
        if (out.is_open()) {
            out << km_mark << endl;
            out << length << endl;
            out << diameter << endl;
            out << is_in_repair << endl; 
        }
        out.close();
        cout << "Pipe data saved to file" << endl;
    }

    void load_from_file(string filename) {
        ifstream file(filename);
        getline(file, km_mark);
        file >> length;
        file >> diameter;
        file >> is_in_repair;
        file.close();
        cout << "Pipe data loaded from " << filename << endl;
    }
};

class CompressorStation {
public:
    string name;
    int workshop_count;
    int current_working_workshop_count;
    float station_cls;

    void read_from_console() {
        string input;

        cout << "Input CS name: ";
        getline(cin, name);
        cout << "Input workshop_count: ";
        int_input(workshop_count);
        cout << "Input current_working_workshop_count: ";
        while (true) {
            int_input(current_working_workshop_count);
            if (current_working_workshop_count > workshop_count) {
                cout << "current_working_workshop_count must be less or equal to workshop_count, try again" << endl;
                cout << "Input current_working_workshop_count: ";
                continue;
            }
            else {
                break;
            }
        }
        cout << "Input station_cls ";
        float_input(station_cls);
    }

    void write_to_console() {
        cout << "CS name: " << name << endl;
        cout << "CS workshop_count: " << workshop_count << endl;
        cout << "CS current_working_workshop_count: " << current_working_workshop_count << endl;
        cout << "CS station_cls: " << station_cls << endl;
    }

    void start_workshop() {
        if (current_working_workshop_count < workshop_count) {
            current_working_workshop_count++;
            cout << "Workshop started. Current working: " << current_working_workshop_count << endl;
        }
        else {
            cout << "Cannot start more workshops. All " << workshop_count << " workshops are already working." << endl;
        }
    }

    void stop_workshop() {
        if (current_working_workshop_count > 0) {
            current_working_workshop_count--;
            cout << "Workshop stopped. Current working: " << current_working_workshop_count << endl;
        }
        else {
            cout << "There are no available workshops to stop." << endl;
        }
    }

    void save_to_file() {
        ofstream out;
        out.open("CS.txt");
        if (out.is_open()) {
            out << name << endl;
            out << workshop_count << endl;
            out << current_working_workshop_count << endl;
            out << station_cls << endl;
        }
        out.close();
        cout << "CS data saved to file" << endl;
    }

    void load_from_file(string filename) {
        ifstream file(filename);
        getline(file, name);
        file >> workshop_count;
        file >> current_working_workshop_count;
        file >> station_cls;
        file.close();
        cout << "Data loaded from file " << filename << endl;
    }
};

int main() {
    Pipe pipe;
    CompressorStation cs;
    int user_input;

    while (true) {
        cout << "1. Add Pipe" << endl;
        cout << "2. Add Compressor Station" << endl;
        cout << "3. View All Objects" << endl;
        cout << "4. Change Pipe Status" << endl;
        cout << "5. Manage Compressor Station Workshops" << endl;
        cout << "6. Save Data to Files" << endl;
        cout << "7. Load Data from Files" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter command [0-7]: ";

        if (!(cin >> user_input)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (user_input) {
        case 1:
            cout << "\n=== Adding New Pipe ===" << endl;
            pipe.read_from_console();
            break;

        case 2:
            cout << "\n=== Adding New Compressor Station ===" << endl;
            cs.read_from_console();
            break;

        case 3:
            cout << "\n=== All Objects ===" << endl;
            if (pipe.km_mark != "") {
                cout << "\n--- Pipe ---" << endl;
                pipe.write_to_console();
            }
            else {
                cout << "No pipe data available" << endl;
            }

            if (cs.name != "") {
                cout << "\n--- Compressor Station ---" << endl;
                cs.write_to_console();
            }
            else {
                cout << "No compressor station data available" << endl << endl;
            }
            break;

        case 4:
            if (pipe.km_mark != "") {
                pipe.change_status();
                cout << "Pipe status changed successfully!" << endl;
            }
            else {
                cout << "No pipe available to modify. Please add a pipe first." << endl;
            }
            break;

        case 5:
            if (cs.name != "") {
                cout << "Current working workshops: " << cs.current_working_workshop_count
                    << " / " << cs.workshop_count << endl;
                cout << "1. Start workshop" << endl;
                cout << "2. Stop workshop" << endl;

                int cs_action;
                cout << "Choose action: ";
                if (cin >> cs_action) {
                    if (cs_action == 1) {
                        cs.start_workshop();
                    }
                    else if (cs_action == 2) {
                        cs.stop_workshop();
                    }
                    else {
                        cout << "Invalid action!" << endl;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                }
                else {
                    cout << "Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            else {
                cout << "No compressor station available to modify. Please add a CS first." << endl;
            }
            break;

        case 6:
            cout << "\n=== Saving Data ===" << endl;
            if (pipe.km_mark != "") {
                pipe.save_to_file();
            }
            else {
                cout << "No pipe data to save" << endl;
            }

            if (cs.name != "") {
                cs.save_to_file();
            }
            else {
                cout << "No compressor station data to save" << endl;
            }
            break;

        case 7:
            cout << "\n=== Loading Data ===" << endl;
            pipe.load_from_file("pipe.txt");
            cs.load_from_file("CS.txt");
            cout << "Data loaded successfully!" << endl;
            break;

        case 0:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;

        default:
            cout << "Input is incorrect. Please try digits in range [0-7]" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
    return 0;
}