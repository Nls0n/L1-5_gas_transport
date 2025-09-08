#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

bool is_float(string str) {
    regex float_regex(R"(^[-+]?\d*\.?\d+$)"); // при надобности могу объяснить что значит эта регулярка
    if (regex_match(str, float_regex)) {
        return true;
    }
    else {
        return false;
    }
}

bool is_int(string str) {
    regex int_regex(R"(^[-+]?\d+)");
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
            cout << "Input kilometers mark (name)" << endl;
            cin >> km_mark;
            cout << "km_mark " << km_mark << endl;
            cout << "Input length (km)" << endl;
            cin >> input;
            if (is_float(input)) {
                float temp;
                temp = stof(input);
                if (temp < 0) {
                    cout << "Length must be positive" << endl;
                }
                else {
                    length = temp;
                    cout << "length" << length << endl;
                }
            }
            cout << "Input diameter (km)\n";
            cin >> input;
            if (is_float(input)) {
                float temp;
                temp = stof(input);
                if (temp < 0) {
                    cout << "Diameter must be positive" << endl;
                }
                else {
                    diameter = temp;
                    cout << "diameter " << diameter << endl;
                }
            }
            cout << "Input pipe repair status true/false" << endl;
            cin >> input;
            if (input == "true") {
                is_in_repair = true;
                cout << "is_in_repair" << is_in_repair << endl;
            }
            else if (input == "false") {
                is_in_repair = false;
                cout << "is_in_repair" << is_in_repair << endl;
            }
            else {
                cout << "Incorrect data format";
            }
        }
        void write_to_console() {
            cout << "Pipe km_mark " << km_mark << endl;
            cout << "Pipe length (km) " << length << endl;
            cout << "Pipe diameter (mm) " << diameter << endl;
            cout << "Pipe is_in_repair " << is_in_repair << endl;
        }
        void change_status() {
            is_in_repair = !is_in_repair;
            cout << "Current status " << is_in_repair << endl;
        }
        void save_to_file() {
            ofstream out;
            out.open("pipe.txt");
            if (out.is_open())
            {
                out << "km_mark " << km_mark << endl;
                out << "length" << length << endl;
                out << "diameter" << diameter << endl;
                out << "is_in_repair" << is_in_repair << endl;
            }
            out.close();
            cout << "data saved to file" << endl;
        }
        void load_from_file(string filename) {
            string line;
            string word;
            string value;
            int whitespace_counter = 0;
            ifstream in(filename);
            if (in.is_open()) {
                while (getline(in, line)) {
                    word = "";
                    value = "";
                    for (int i = 0; i < line.length(); i++) {
                        if (whitespace_counter > 1) {
                            cout << "Incorrect data format" << endl;
                            break;
                        }
                        if (line[i] && whitespace_counter == 0) {
                            word += line[i];
                        }
                        else if (!line[i]){
                            whitespace_counter++;
                        }
                        if (line[i] == '\n') {
                            if (word == "km_mark") {
                                km_mark = value;
                            }
                            else if (word == "length") {
                                if (is_float(value)) {
                                    float temp;
                                    temp = stof(value); // string -> float
                                    if (temp < 0) {
                                        cout << "Length must be positive" << endl;
                                    }
                                    else {
                                        length = temp;
                                    }
                                }
                                else {
                                    cout << "Incorrect format of length" << endl;
                                }
                                
                            }
                            else if (word == "diameter") {
                                if (is_float(value)) {
                                    float temp;
                                    temp = stof(value); // string -> float
                                    if (temp < 0) {
                                        cout << "Diameter must be positive" << endl;
                                    }
                                    else {
                                        diameter = temp;
                                    }
                                }
                                else {
                                    cout << "Incorrect format of diameter" << endl;
                                }
                            }
                            else if (word == "is_in_repair") {
                                if (value == "true") {
                                    is_in_repair = true;
                                }
                                else if (value == "false") {
                                    is_in_repair = false;
                                }
                                else {
                                    cout << "Incorrect format of is_in_repair, must be boolean and not null" << endl;
                                }
                            }
                        }
                    }
                }
            }
            else {
                cout << "File is not in working directory" << endl;
            }
            in.close();
        }
};  

class CompressorStation {
public:
    string name;
    int workshop_count;
    int current_working_workshop_count;
    float station_cls; // я так и не понял какой нужен тип
    void read_from_console() {
        string input;
        cout << "Input CS name" << endl;
        cin >> name;
        cout << "name " << name << endl;
        cout << "Input workshop_count" << endl;
        cin >> input;
        if (is_int(input)) {
            int temp;
            temp = stoi(input);
            if (temp < 0) {
                cout << "workshop_count must be positive" << endl;
            }
            else {
                workshop_count = temp;
                cout << "workshop_count " << workshop_count << endl;
            }
        }
        cout << "Input current_working_workshop_count" << endl;
        cin >> input;
        if (is_int(input)) {
            int temp;
            temp = stoi(input);
            if (temp < 0) {
                cout << "current_working_workshop_count must be positive" << endl;
            }
            else {
                current_working_workshop_count = temp;
                cout << "current_working_workshop_count " << current_working_workshop_count << endl;
            }
        }
        cout << "Input station_cls" << endl;
        cin >> input;
        if (is_float(input)) {
            float temp;
            temp = stof(input);
            if (temp < 0) {
                cout << "station_cls must be positive" << endl;
            }
            else {
                cout << "station_cls " << station_cls << endl;
            }
        }
        else {
            cout << "Incorrect data format" << endl;
        }
    }
    void write_to_console() {
        cout << "CS name " << name << endl;
        cout << "CS workshop_count " << workshop_count << endl;
        cout << "CS current_working_workshop_count " << current_working_workshop_count << endl;
        cout << "CS station_cls " << station_cls << endl;
    }
    void start_workshop() {
        current_working_workshop_count++;
    }
    void stop_workshop() {
        if (current_working_workshop_count > 0) {
            current_working_workshop_count--;
        }
        else {
            cout << "There are no avialiable workshops " << endl;
        }
    }
    void save_to_file() {
        ofstream out;
        out.open("CS.txt");
        if (out.is_open())
        {
            out << "name " << name << endl;
            out << "workshop_count" << workshop_count << endl;
            out << "current_working_workshop_count" << current_working_workshop_count << endl;
            out << "station_cls" << station_cls << endl;
        }
        out.close();
        cout << "data saved to file" << endl;
    }
    void load_from_file(string filename) {
        string line;
        string word;
        string value;
        int whitespace_counter = 0;
        ifstream in(filename);
        if (in.is_open()) {
            while (getline(in, line)) {
                word = "";
                value = "";
                for (int i = 0; i < line.length(); i++) {
                    if (whitespace_counter > 1) {
                        cout << "Incorrect data format" << endl;
                        break;
                    }
                    if (line[i] && whitespace_counter == 0) {
                        word += line[i];
                    }
                    else if (!line[i]) {
                        whitespace_counter++;
                    }
                    if (line[i] == '\n') {
                        if (word == "name") {
                            name = value;
                        }
                        else if (word == "workshop_count") {
                            if (is_int(value)) {
                                int temp;
                                temp = stoi(value); // string -> int
                                if (temp < 0) {
                                    cout << "workshop_count must be positive" << endl;
                                }
                                else {
                                    workshop_count = temp;
                                }
                            }
                            else {
                                cout << "Incorrect format of workshop_count" << endl;
                            }

                        }
                        else if (word == "current_working_workshop_count") {
                            if (is_float(value)) {
                                int temp;
                                temp = stoi(value); // string -> int
                                if (temp < 0) {
                                    cout << "current_working_workshop_count must be positive" << endl;
                                }
                                else {
                                    current_working_workshop_count = temp;
                                }
                            }
                            else {
                                cout << "Incorrect format of current_working_workshop_count" << endl;
                            }
                        }
                        else if (word == "station_cls") {
                            if (is_float(value)) {
                                station_cls = stof(value);
                                cout << "station_cls " << station_cls << endl;
                            }
                            else {
                                cout << "Incorrect format of station_cls";
                            }
                        }
                    }
                }
            }
        }
        else {
            cout << "File is not in working directory" << endl;
        }
        in.close();
    }
};



int main()
{
    int user_input;
    Pipe pipe;
    CompressorStation cs;
    while (true) {
        cin >> user_input;
        switch (user_input){
        case 1: // add pipe
        case 2: // add CS
        case 3: // see all objects
        case 4: // change pipe
        case 5: // change CS
        case 6: // save
        case 7: // load
        case 0: // exit
        default: cout << "Input is incorrect\n try digits in range [0-7]";
        }
    }
    return 0;
}