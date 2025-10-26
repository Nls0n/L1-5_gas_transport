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
        int id;
        float length; // km
        int diameter; // mm
        bool is_in_repair;
    public:
        void read_from_console() {
            string input;

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        void set_id(const vector<Pipe>& pipes){
            id >> pipes.size();
        }

        void write_to_console() {
            cout << "Pipe id:" << id << endl;
            cout << "Pipe km_mark: " << km_mark << endl;
            cout << "Pipe length (km): " << length << endl;
            cout << "Pipe diameter (mm): " << diameter << endl;
            cout << "Pipe is_in_repair: " << is_in_repair << endl;
        }

        bool check_name() {
            return km_mark != "";
        }

        void change_status() {
        is_in_repair = !is_in_repair;
        cout << "Current status: " << is_in_repair << endl;
    }

    void save_to_file() {
        ofstream out("data.txt");
        if (out.is_open()) {
            if (check_name()) {
                out << id << endl;
                out << km_mark << endl;
                out << length << endl;
                out << diameter << endl;
                out << is_in_repair << endl;
            }
            cout << "Pipe data saved to file" << endl;
            out.close();
        }
        else {
            cout << "Error with opening file" << endl;
        }
    }
    void load_from_file(ifstream& file) {
        if (file.is_open()){
            file >> id;
            file >> km_mark;
            file >> length;
            file >> diameter;
            file >> is_in_repair;
        }
    }
};

void load_from_file(string filename, vector<Pipe>& pipes, const vector<CompressorStation>& CSes) {
    ifstream file(filename);
    Pipe pipe;
    
}


class CompressorStation {
    private:
        string name;
        int workshop_count;
        int current_working_workshop_count;
        int id;
        float station_cls;

    public:
        bool check_name() {
            return name != "";
        }
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
            ofstream out("data.txt", std::ios::app);
            if (out.is_open()) {
                if (check_name()) {
                    out << id << endl;  
                    out << name << endl;
                    out << workshop_count << endl;
                    out << current_working_workshop_count << endl;
                    out << station_cls << endl;
                }
                cout << "CS data saved to file" << endl;
                out.close();
            }
            else {
                cout << "Error with opening file" << endl;
            }
        }
};




int main() {
    Pipe pipe;
    CompressorStation CS;
    int user_input;
    vector<Pipe> pipes;
    vector<CompressorStation> CSes;

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
            clear();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (user_input) {
        case 1:
            cout << "\n=== Adding New Pipe ===" << endl;
            read_from_console(pipe);
            break;

        case 2:
            cout << "\n=== Adding New Compressor Station ===" << endl;
            read_from_console(cs);
            break;

        case 3:
            cout << "\n=== All Objects ===" << endl;
            if (pipe.km_mark != "") {
                cout << "\n--- Pipe ---" << endl;
                write_to_console(pipe);
            }
            else {
                cout << "No pipe data available" << endl;
            }    

            if (cs.name != "") {
                cout << "\n--- Compressor Station ---" << endl;
                write_to_console(cs);
            }
            else {
                cout << "No compressor station data available" << endl << endl;
            }
            break;

        case 4:
            if (pipe.km_mark != "") {
                change_status(pipe);
                cout << "Pipe status changed successfully!" << endl;
            }
            else {
                cout << "No pipe available to modify. Please add a pipe first." << endl;
            }
            break;

        case 5:
        {
            if (cs.name == "") {
                cout << "No compressor station available to modify. Please add a CS first." << endl;
                break;
            }

            cout << "Current working workshops: " << cs.current_working_workshop_count << " / " << cs.workshop_count << endl;
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
                start_workshop(cs);
            }
            else if (cs_action == 2) {
                stop_workshop(cs);
            }
            else {
                cout << "Invalid action!" << endl;
            }
            clear();
            break;
        }
        case 6:
            cout << "\n=== Saving Data ===" << endl;
            if (pipe.km_mark != "" || cs.name != "") {
                save_to_file(pipe);
                save_to_file(cs);
            } else {
                cout << "No data available to save" << endl;
            }
            break;
        case 7:
            cout << "\n=== Loading Data ===" << endl;
            load_from_file("data.txt", pipe, cs);
            cout << "Data loaded successfully!" << endl;
            break;

            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;

        default:
            cout << "Input is incorrect. Please try digits in range [0-7]" << endl;
            clear();
        }
    }
    return 0;
}