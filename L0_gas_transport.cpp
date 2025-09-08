#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

bool is_float(string str) {
    regex float_regex(R"(^[-+]?\d*\.?\d+$)"); // при надобности могу объяснить что значит эта
    if (regex_match(str, float_regex)) {
        return true;
    }
    else {
        return false;
    }
}

bool is_int(string str) {
    regex int_regex(R"(^[-+]?\d+$)");
    if (regex_match(str, int_regex)) {
        return true;
    }
    else {
        return false;
    }
}

class Pipe {
public:
    string km_mark;
    float length; // km
    float diameter; // mm
    bool is_in_repair;

    void read_from_console() {
        string input;

        cout << "Input kilometers mark (name): ";
        cin >> km_mark;
        cout << "km_mark: " << km_mark << endl;

        while (true) {
            cout << "Input length (km): ";
            cin >> input;
            if (is_float(input)) {
                float temp = stof(input);
                if (temp < 0) {
                    cout << "Length must be positive. Please try again." << endl;
                }
                else {
                    length = temp;
                    cout << "length: " << length << endl;
                    break;
                }
            }
            else {
                cout << "Invalid format. Please enter a valid number." << endl;
            }
            cin.clear();
        }

        while (true) {
            cout << "Input diameter (mm): ";
            cin >> input;
            if (is_float(input)) {
                float temp = stof(input); // string -> float
                if (temp < 0) {
                    cout << "Diameter must be positive. Please try again." << endl;
                }
                else {
                    diameter = temp;
                    cout << "diameter: " << diameter << endl;
                    break;
                }
            }
            else {
                cout << "Invalid format. Please enter a valid number." << endl;
            }
            cin.clear();
        }

        while (true) {
            cout << "Input pipe repair status (true/false): ";
            cin >> input;
            if (input == "true") {
                is_in_repair = true;
                cout << "is_in_repair: " << is_in_repair << endl;
                break;
            }
            else if (input == "false") {
                is_in_repair = false;
                cout << "is_in_repair: " << is_in_repair << endl;
                break;
            }
            else {
                cout << "Incorrect data format. Please enter 'true' or 'false'." << endl;
            }
            cin.clear();
        }
    }

    void write_to_console() {
        cout << "Pipe km_mark: " << km_mark << endl;
        cout << "Pipe length (km): " << length << endl;
        cout << "Pipe diameter (mm): " << diameter << endl;
        cout << "Pipe is_in_repair: " << (is_in_repair ? "true" : "false") << endl;
    }

    void change_status() {
        is_in_repair = !is_in_repair;
        cout << "Current status: " << (is_in_repair ? "true" : "false") << endl;
    }

    void save_to_file() {
        ofstream out;
        out.open("pipe.txt");
        if (out.is_open()) {
            out << "km_mark " << km_mark << endl;
            out << "length " << length << endl;
            out << "diameter " << diameter << endl;
            out << "is_in_repair " << (is_in_repair ? "1" : "0") << endl; // cохраняем как 1/0
        }
        out.close();
        cout << "Pipe data saved to file" << endl;
    }

    void load_from_file(string filename) {
        ifstream in(filename);
        if (in.is_open()) {
            string line;
            while (getline(in, line)) {
                int space_pos = line.find(' ');
                if (space_pos != string::npos) {
                    string key = line.substr(0, space_pos);
                    string value = line.substr(space_pos + 1);

                    if (key == "km_mark") {
                        km_mark = value;
                    }
                    else if (key == "length") {
                        if (is_float(value)) {
                            float temp = stof(value);
                            if (temp >= 0) {
                                length = temp;
                            }
                        }
                    }
                    else if (key == "diameter") {
                        if (is_float(value)) {
                            float temp = stof(value);
                            if (temp >= 0) {
                                diameter = temp;
                            }
                        }
                    }
                    else if (key == "is_in_repair") {
                        if (value == "1") {
                            is_in_repair = true;
                        }
                        else if (value == "0") {
                            is_in_repair = false;
                        }
                    }
                }
            }
            in.close();
            cout << "Pipe data loaded from " << filename << endl;
        }
        else {
            cout << "File " << filename << " is not in working directory" << endl;
        }
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
        cin >> name;
        cout << "name: " << name << endl;

        while (true) {
            cout << "Input workshop_count: ";
            cin >> input;
            if (is_int(input)) {
                int temp = stoi(input); // string -> int
                if (temp < 0) {
                    cout << "workshop_count must be positive. Please try again." << endl;
                }
                else {
                    workshop_count = temp;
                    cout << "workshop_count: " << workshop_count << endl;
                    break;
                }
            }
            else {
                cout << "Invalid format. Please enter a valid integer." << endl;
            }
            cin.clear();
        }

        while (true) {
            cout << "Input current_working_workshop_count: ";
            cin >> input;
            if (is_int(input)) {
                int temp = stoi(input);
                if (temp < 0) {
                    cout << "current_working_workshop_count must be positive. Please try again." << endl;
                }
                else if (temp > workshop_count) {
                    cout << "Cannot have more working workshops than total workshops ("
                        << workshop_count << "). Please try again." << endl;
                }
                else {
                    current_working_workshop_count = temp;
                    cout << "current_working_workshop_count: " << current_working_workshop_count << endl;
                    break;
                }
            }
            else {
                cout << "Invalid format. Please enter a valid integer." << endl;
            }
            cin.clear();
        }

        while (true) {
            cout << "Input station_cls: ";
            cin >> input;
            if (is_float(input)) {
                float temp = stof(input);
                if (temp < 0) {
                    cout << "station_cls must be positive. Please try again." << endl;
                }
                else {
                    station_cls = temp;
                    cout << "station_cls: " << station_cls << endl;
                    break;
                }
            }
            else {
                cout << "Invalid format. Please enter a valid number." << endl;
            }
            cin.clear();
        }
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
            out << "name " << name << endl;
            out << "workshop_count " << workshop_count << endl;
            out << "current_working_workshop_count " << current_working_workshop_count << endl;
            out << "station_cls " << station_cls << endl;
        }
        out.close();
        cout << "CS data saved to file" << endl;
    }

    void load_from_file(string filename) {
        ifstream in(filename);
        if (in.is_open()) {
            string line;
            while (getline(in, line)) {
                int space_pos = line.find(' ');
                if (space_pos != string::npos) {
                    string key = line.substr(0, space_pos);
                    string value = line.substr(space_pos + 1);

                    if (key == "name") {
                        name = value;
                    }
                    else if (key == "workshop_count") {
                        if (is_int(value)) {
                            int temp = stoi(value);
                            if (temp >= 0) {
                                workshop_count = temp;
                            }
                        }
                    }
                    else if (key == "current_working_workshop_count") {
                        if (is_int(value)) {
                            int temp = stoi(value);
                            if (temp >= 0) {
                                current_working_workshop_count = temp;
                            }
                        }
                    }
                    else if (key == "station_cls") {
                        if (is_float(value)) {
                            float temp = stof(value);
                            if (temp >= 0) {
                                station_cls = temp;
                            }
                        }
                    }
                }
            }
            in.close();
            cout << "CS data loaded from " << filename << endl;
        }
        else {
            cout << "File " << filename << " is not in working directory" << endl;
        }
    }
};

int main() {
    Pipe pipe;
    CompressorStation cs;
    int user_input;

    cout << "=== Pipeline System Management ===" << endl;

    while (true) {
        cout << "\n================================" << endl;
        cout << "1. Add Pipe" << endl;
        cout << "2. Add Compressor Station" << endl;
        cout << "3. View All Objects" << endl;
        cout << "4. Change Pipe Status" << endl;
        cout << "5. Manage Compressor Station Workshops" << endl;
        cout << "6. Save Data to Files" << endl;
        cout << "7. Load Data from Files" << endl;
        cout << "0. Exit" << endl;
        cout << "================================" << endl;
        cout << "Enter command [0-7]: ";

        if (!(cin >> user_input)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            continue;
        }

        switch (user_input) {
        case 1:
            cout << "\n=== Adding New Pipe ===" << endl;
            pipe.read_from_console();
            cout << "Pipe added successfully!" << endl;
            break;

        case 2:
            cout << "\n=== Adding New Compressor Station ===" << endl;
            cs.read_from_console();
            cout << "Compressor Station added successfully!" << endl;
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
                cout << "No compressor station data available" << endl;
            }
            break;

        case 4:
            if (pipe.km_mark != "") {
                cout << "\n=== Changing Pipe Status ===" << endl;
                pipe.change_status();
                cout << "Pipe status changed successfully!" << endl;
            }
            else {
                cout << "No pipe available to modify. Please add a pipe first." << endl;
            }
            break;

        case 5:
            if (cs.name != "") {
                cout << "\n=== Managing Compressor Station ===" << endl;
                cout << "Current working workshops: " << cs.current_working_workshop_count
                    << " / " << cs.workshop_count << endl;
                cout << "1. Start workshop" << endl;
                cout << "2. Stop workshop" << endl;
                cout << "Choose action: ";

                int cs_action;
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
                }
                else {
                    cout << "Invalid input!" << endl;
                    cin.clear();
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
        }
    }
    return 0;
}