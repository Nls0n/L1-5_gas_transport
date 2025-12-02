#include "utils.h"
#include "pipe.h"
#include "compressor_station.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <set>

using namespace std;

// Глобальная переменная для лог-файла
ofstream log_file;
string log_filename;

void initialize_logging() {
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    tm local_time = *localtime(&time);
    
    ostringstream filename_stream;
    filename_stream << "logs_"
                   << setfill('0') << setw(2) << local_time.tm_mday
                   << setfill('0') << setw(2) << (local_time.tm_mon + 1)
                   << (local_time.tm_year + 1900) << "_"
                   << setfill('0') << setw(2) << local_time.tm_hour
                   << setfill('0') << setw(2) << local_time.tm_min
                   << setfill('0') << setw(2) << local_time.tm_sec << ".txt";
    log_filename = filename_stream.str();
    
    log_file.open(log_filename);
}

void close_logging() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void write_to_log(const string& message) {
    if (log_file.is_open()) {
        log_file << message << endl;
    }
}

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

// Новая функция для валидации диаметра
bool input_valid_diameter(int& diameter) {
    set<int> valid_diameters = {500, 700, 1000, 1400};
    
    cout << "Enter pipe diameter (valid values: 500, 700, 1000, 1400 mm): ";
    
    while (!(cin >> diameter) || valid_diameters.find(diameter) == valid_diameters.end()) {
        clear();
        cout << "Invalid diameter! Please enter one of: 500, 700, 1000, 1400: ";
    }
    clear();
    return true;
}

// Явная инстанциация шаблона для поддерживаемых типов
template void input_positive<int>(int&);
template void input_positive<float>(float&);
template void input_positive<double>(double&);

void load_from_file(string filename, unordered_map<int, Pipe>& pipes, unordered_map<int, CompressorStation>& CSes) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    pipes.clear();
    CSes.clear();

    string line;
    char object_type = ' ';
    int count = 0;
    int objects_loaded = 0;

    while (getline(in, line)) {
        if (line.empty()) continue;

        if (line[0] == 'P' || line[0] == 'C') {
            object_type = line[0];
            count = stoi(line.substr(2));
            continue;
        }

        if (object_type == 'P' && count > 0) {
            int id = stoi(line);
            
            string km_mark;
            getline(in, km_mark);
            
            float length;
            in >> length;
            in.ignore();
            
            int diameter;
            in >> diameter;
            in.ignore();
            
            bool is_in_repair;
            in >> is_in_repair;
            in.ignore();

            Pipe pipe;
            pipe.load_data(id, km_mark, length, diameter, is_in_repair);
            pipes[id] = pipe;
            count--;
            objects_loaded++;
        }
        else if (object_type == 'C' && count > 0) {
            int id = stoi(line);
            
            string name;
            getline(in, name);
            
            int workshop_count;
            in >> workshop_count;
            in.ignore();
            
            int current_working_workshop_count;
            in >> current_working_workshop_count;
            in.ignore();
            
            float station_cls;
            in >> station_cls;
            in.ignore();

            CompressorStation cs;
            cs.load_data(id, name, workshop_count, current_working_workshop_count, station_cls);
            CSes[id] = cs;
            count--;
            objects_loaded++;
        }
    }

    in.close();
    cout << "Successfully loaded " << objects_loaded << " objects" << endl;
}

void truncate_file(string filename) {
    ofstream clear_file(filename, ios::out | ios::trunc);
    clear_file.close();
}