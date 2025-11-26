#include "compressor_station.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

void CompressorStation::read_from_console() {
    cout << "Input CS name: ";
    getline(cin, name);
    write_to_log(name);
    
    cout << "Input workshop_count: ";
    input_positive(workshop_count);
    write_to_log(to_string(workshop_count));
    
    cout << "Input current_working_workshop_count: ";
    do {
        input_positive(current_working_workshop_count);
        if (current_working_workshop_count > workshop_count) {
            cout << "current_working_workshop_count must be less or equal to workshop_count, try again" << endl;
            cout << "Input current_working_workshop_count: ";
        }
    } while (current_working_workshop_count > workshop_count);
    write_to_log(to_string(current_working_workshop_count));
    
    cout << "Input station_cls: ";
    input_positive(station_cls);
    write_to_log(to_string(station_cls));
}

bool CompressorStation::validate_name() const {
    return (name != "");
}

void CompressorStation::write_to_console() const {
    cout << "CS id: " << id << endl;
    cout << "CS name: " << name << endl;
    cout << "CS workshop_count: " << workshop_count << endl;
    cout << "CS current_working_workshop_count: " << current_working_workshop_count << endl;
    cout << "CS station_cls: " << station_cls << endl;
    cout << "------------------------" << endl;
}

void CompressorStation::start_workshop() {
    if (current_working_workshop_count < workshop_count) {
        current_working_workshop_count++;
        cout << "Workshop started. Current working: " << current_working_workshop_count << endl;
    }
    else {
        cout << "Cannot start more workshops. All " << workshop_count << " workshops are already working." << endl;
    }
}

void CompressorStation::stop_workshop() {
    if (current_working_workshop_count > 0) {
        current_working_workshop_count--;
        cout << "Workshop stopped. Current working: " << current_working_workshop_count << endl;
    }
    else {
        cout << "There are no available workshops to stop." << endl;
    }
}

void CompressorStation::save_to_file(string filename) const { 
    ofstream out(filename, ios::app);
    if (out.is_open()) {
        if (validate_name()) {
            out << id << endl;
            out << name << endl;
            out << workshop_count << endl;
            out << current_working_workshop_count << endl;
            out << station_cls << endl;
        }
    }
    else {
        cout << "Error with opening file" << endl;
    }
}

void CompressorStation::print_workshop_managment() const {
    cout << "Current working workshops: " << current_working_workshop_count << " / " << workshop_count << endl;
}

void CompressorStation::assign_id(const unordered_map<int, CompressorStation>& CSes) {
    if (CSes.empty()) {
        id = 1;
    } else {
        int max_id = 0;
        for (const auto& pair : CSes) {
            if (pair.first > max_id) {
                max_id = pair.first;
            }
        }
        id = max_id + 1;
    }
}

double CompressorStation::get_unused_workshop_percent() const {
    if (workshop_count == 0) return 0;
    return ((workshop_count - current_working_workshop_count) * 100.0) / workshop_count;
}

void CompressorStation::load_data(int new_id, string new_name, int workshops, int working_workshops, float cls) {
    id = new_id;
    name = new_name;
    workshop_count = workshops;
    current_working_workshop_count = working_workshops;
    station_cls = cls;
}