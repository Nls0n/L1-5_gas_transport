#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

void clear() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

template<typename T>
void input_positive(T& var) {
    while (!(cin >> var) || var <= 0) {
        clear();
        cout << "Invalid input. Enter positive number: ";
    }
    clear();
}


class Pipe {
    private:
    string km_mark;
    float length; // km
    int diameter; // mm
    bool is_in_repair;
    int id;
    string input;

    public:
    void read_from_console() {
        cout << "Input kilometers mark (name): ";
        getline(cin, km_mark);
        cout << "Input pipe length: ";
        input_positive(length);
        cout << "Input pipe diameter: ";
        input_positive(diameter);
        cout << "Input is_in_repair status: ";
        while (!(cin >> is_in_repair)) {
            clear();
            cout << "Invalid input. Enter 1 or 0: ";
        }
    }
    bool validate_km_mark() {
        return (km_mark != "");
    }
    void assign_id(vector<Pipe> pipes) {
        id = pipes.size() + 1;
    }
    void write_to_console() {
        cout << "Pipe id: " << id << endl;
        cout << "Pipe km_mark: " << km_mark << endl;
        cout << "Pipe length (km): " << length << endl;
        cout << "Pipe diameter (mm): " << diameter << endl;
        cout << "Pipe is_in_repair: " << is_in_repair << endl;
    }

    void change_status() {
        is_in_repair = !is_in_repair;
        cout << "Current status: " << is_in_repair << endl;
    }
    void save_to_file(string filename) {
        ofstream out(filename, ios::app);
        if (out.is_open()) {
            bool has_pipe = validate_km_mark();
            if (has_pipe) {
                out << id << endl;
                out << km_mark << endl;
                out << length << endl;
                out << diameter << endl;
                out << is_in_repair << endl;
                out.close();
            }
        }
        else {
            cout << "Error with opening file" << endl;
        }
    }
};

class CompressorStation {
    private:
    string name;
    int workshop_count;
    int current_working_workshop_count;
    float station_cls;
    int id;
    public:

    void read_from_console() {
        string input;

        cout << "Input CS name: ";
        getline(cin, name);
        cout << "Input workshop_count: ";
        input_positive(workshop_count);
        
        cout << "Input current_working_workshop_count: ";
        do {
            input_positive(current_working_workshop_count);
            if (current_working_workshop_count > workshop_count) {
                cout << "current_working_workshop_count must be less or equal to workshop_count, try again" << endl;
                cout << "Input current_working_workshop_count: ";
            }
        } while (current_working_workshop_count > workshop_count);
        
        cout << "Input station_cls ";
        input_positive(station_cls);
    }
    bool validate_name() {
        return (name != "");
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

    void save_to_file(string filename) { 
        ofstream out(filename, std::ios::app);
        if (out.is_open()) {
            if (validate_name()) {
                out << id << endl;
                out << name << endl;
                out << workshop_count << endl;
                out << current_working_workshop_count << endl;
                out << station_cls << endl;
            }
            else {
                cout << "Invalid CS name" << endl;
            }
            out.close();
        }
        else {
            cout << "Error with opening file" << endl;
        }
    }

    void print_workshop_managment() {
        cout << "Current working workshops: " << current_working_workshop_count << " / " << workshop_count << endl;
    }

    void assign_id(vector<CompressorStation> CSes) {
        id = CSes.size() + 1;
    }
};


void load_from_file(string filename, vector<Pipe>& pipes, vector<CompressorStation>& CSes) {
    cout << "Data loaded from file " << filename << endl;
}

void truncate_file(string filename) {
    fstream clear_file(filename, ios::out);
    clear_file.close();
}

int main() {
    Pipe pipe;
    CompressorStation cs;
    vector<Pipe> pipes;
    vector<CompressorStation> CSes;
    int user_input;
    string filename;
    truncate_file("logs.txt");
    ofstream logger("logs.txt", ios::app);
    

    while (true) {
        cout << "1. Add Pipe" << endl;
        cout << "2. Add Compressor Station" << endl;
        cout << "3. View All Objects" << endl;
        cout << "4. Change Pipe Status" << endl;
        cout << "5. Manage Compressor Station Workshops" << endl;
        cout << "6. Save Data to Files" << endl;
        cout << "7. Load Data from Files" << endl;
        cout << "8. Truncate File" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter command [0-8]: ";

        if (!(cin >> user_input)) {
            logger << user_input << endl;
            cout << "Invalid input. Please enter a number." << endl;
            clear();
            continue;
        }
        clear();
        switch (user_input) {
        case 1:
            logger << user_input << endl;
            cout << "\n=== Adding New Pipe ===" << endl;
            pipe.read_from_console();
            pipe.assign_id(pipes);
            pipes.push_back(pipe);

            break;

        case 2:
            logger << user_input << endl;
            cout << "\n=== Adding New Compressor Station ===" << endl;
            cs.read_from_console();
            cs.assign_id(CSes);
            CSes.push_back(cs);
            break;

        case 3:
            logger << user_input << endl;
            cout << "\n=== All Objects ===" << endl;
            if (pipes.size()) {
                cout << "\n--- Pipes ---" << endl;
                for (int i=0; i<pipes.size(); i++) {
                    pipes[i].write_to_console();
                }
            }
            else {
                cout << "No pipes data available" << endl;
            }    

            if (CSes.size()) {
                cout << "\n--- Compressor Stations ---" << endl;
                for (int i = 0; i < CSes.size(); i++) {
                    CSes[i].write_to_console();
                }
            }
            else {
                cout << "No compressor stations data available" << endl << endl;
            }
            break;

        case 4:
            logger << user_input << endl;
            if (!pipe.validate_km_mark()) {
                pipe.change_status();
                cout << "Pipe status changed successfully!" << endl;
            }
            else {
                cout << "No pipe available to modify. Please add a pipe first." << endl;
            }
            break;

        case 5:
            logger << user_input << endl;
            if (!cs.validate_name()) {
                cout << "No compressor station available to modify. Please add a CS first." << endl;
                break;
            }

            cs.print_workshop_managment();
            cout << "1. Start workshop" << endl;
            cout << "2. Stop workshop" << endl;

            int cs_action;
            cout << "Choose action: ";
            if (!(cin >> cs_action))
            {
                cout << "Invalid input!" << endl;
                clear();
                break;
            }
            if (cs_action == 1) {
                cs.start_workshop();
            }
            else if (cs_action == 2) {
                cs.stop_workshop();
            }
            else {
                cout << "Invalid action!" << endl;
            }
            clear();
            break;
        case 6:
            logger << user_input << endl;
            cout << "Enter filename" << endl;
            getline(cin, filename);
            clear();

            cout << "\n=== Saving Data ===" << endl;
            if (pipes.size()) {
                ofstream out(filename);
                out << "P " << pipes.size() << endl;
                out.close();
                for (int i = 0; i < pipes.size(); i++) {
                    pipes[i].save_to_file(filename);
                }
            } else {
                cout << "No data available to save" << endl;
            }
            if (CSes.size()) {
                ofstream out(filename, ios::app);
                out << "C " << CSes.size() << endl;
                out.close();
                for (int i = 0; i < CSes.size(); i++) {
                    CSes[i].save_to_file(filename);
                }
            }
            break;
        case 7:
            logger << user_input << endl;
            cout << "Enter filename" << endl;
            getline(cin, filename);
            cout << "\n=== Loading Data ===" << endl;
            load_from_file(filename, pipes, CSes);
            cout << "Data loaded successfully!" << endl;
            break;


        case 8:
            logger << user_input << endl;
            cout << "Enter filename to truncate it" << endl;
            getline(cin, filename);
            truncate_file(filename);
            cout << "Succesfully truncated the file" << endl;
            break;

            
        case 0:
            logger << user_input;
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            logger << user_input << endl;
            cout << "Input is incorrect. Please try digits in range [0-8]" << endl;
            clear();
        }
    }
    return 0;
}