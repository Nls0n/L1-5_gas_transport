#include "pipe.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

void Pipe::read_from_console() {
    cout << "Input kilometers mark (name): ";
    getline(cin, km_mark);
    write_to_log(km_mark);
    
    cout << "Input pipe length: ";
    input_positive(length);
    write_to_log(to_string(length));
    
    // Используем новую функцию для валидации диаметра
    cout << "Input pipe diameter (valid values: 500, 700, 1000, 1400 mm): ";
    int temp_diameter;
    input_valid_diameter(temp_diameter);
    diameter = temp_diameter;
    write_to_log(to_string(diameter));
    
    cout << "Input is_in_repair status: ";
    while (!(cin >> is_in_repair)) {
        clear();
        cout << "Invalid input. Enter 1 or 0: ";
    }
    write_to_log(to_string(is_in_repair));
    clear();
    
    is_connected = false;  // Инициализируем как неподключенную
}

bool Pipe::validate_km_mark() const {
    return (km_mark != "");
}

void Pipe::assign_id(const unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) {
        id = 1;
    } else {
        int max_id = 0;
        for (const auto& pair : pipes) {
            if (pair.first > max_id) {
                max_id = pair.first;
            }
        }
        id = max_id + 1;
    }
}

void Pipe::write_to_console() const {
    cout << "Pipe id: " << id << endl;
    cout << "Pipe km_mark: " << km_mark << endl;
    cout << "Pipe length (km): " << length << endl;
    cout << "Pipe diameter (mm): " << diameter << endl;
    cout << "Pipe is_in_repair: " << is_in_repair << endl;
    cout << "Pipe is_connected: " << is_connected << endl;
    cout << "------------------------" << endl;
}

void Pipe::change_status() {
    is_in_repair = !is_in_repair;
    cout << "Current status: " << is_in_repair << endl;
}

void Pipe::save_to_file(string filename) const {
    ofstream out(filename, ios::app);
    if (out.is_open()) {
        if (validate_km_mark()) {
            out << id << endl;
            out << km_mark << endl;
            out << length << endl;
            out << diameter << endl;
            out << is_in_repair << endl;
            // Не сохраняем is_connected, так как это временное состояние
        }
    }
    else {
        cout << "Error with opening file" << endl;
    }
}

void Pipe::load_data(int new_id, string mark, float len, int diam, bool repair) {
    id = new_id;
    km_mark = mark;
    length = len;
    diameter = diam;
    is_in_repair = repair;
    is_connected = false;  // При загрузке из файла считаем трубу неподключенной
}