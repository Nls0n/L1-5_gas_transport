#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

class Pipe {
    public:
        string km_mark;
        float length; // km
        float diameter; // mm
        bool is_in_repair;
        void read_from_console() {
            cout << "Input kilometers mark (name)\n";
            cin >> km_mark;
            cout << "Input length (km)\n";
            cin >> length;
            cout << "Input diameter (km)\n";
            cin >> diameter;
            cout << "Input pipe repair status (1 - true, 0 - false)\n";
            cin >> is_in_repair;
        }
        void write_to_console() {
            cout << "Pipe length (km) " << length << endl;
            cout << "Pipe diameter (mm) " << diameter << endl;
            cout << "Pipe repair status " << is_in_repair << endl;
        }
        void change_status() {
            is_in_repair = !is_in_repair;
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
            string word = "";
            string value = "";
            int whitespace_counter = 0;
            ifstream in(filename);
            if (in.is_open()) {
                while (getline(in, line)) {
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
                                regex float_regex(R"(^[-+]?\d*\.?\d+$)"); // при надобности могу объяснить что значит эта регулярка
                                if (regex_match(value, float_regex)) {
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
                                regex float_regex(R"(^[-+]?\d*\.?\d+$)"); // при надобности могу объяснить что значит эта регулярка
                                if (regex_match(value, float_regex)) {
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
};

int main()
{
    int user_input;
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
        default: cout << "Input is incorrect\n try digits in range 0-7";
        }
    }
}

