#include "Pipe.h"
#include "utils.h"
#include <iostream>
#include <fstream>

void Pipe::read_from_console() {
    std::cout << "Input kilometers mark (name): ";
    std::getline(std::cin, km_mark);
    std::cout << "Input pipe length: ";
    input_positive(length);
    std::cout << "Input pipe diameter: ";
    input_positive(diameter);
    std::cout << "Input is_in_repair status: ";
    while (!(std::cin >> is_in_repair)) {
        clear();
        std::cout << "Invalid input. Enter 1 or 0: ";
    }
    clear();
}

bool Pipe::validate_km_mark() {
    return (km_mark != "");
}

void Pipe::assign_id(std::vector<Pipe> pipes) {
    id = pipes.size() + 1;
}

void Pipe::write_to_console() {
    std::cout << "Pipe id: " << id << std::endl;
    std::cout << "Pipe km_mark: " << km_mark << std::endl;
    std::cout << "Pipe length (km): " << length << std::endl;
    std::cout << "Pipe diameter (mm): " << diameter << std::endl;
    std::cout << "Pipe is_in_repair: " << is_in_repair << std::endl;
    std::cout << "------------------------" << std::endl;
}

void Pipe::change_status() {
    is_in_repair = !is_in_repair;
    std::cout << "Current status: " << is_in_repair << std::endl;
}

void Pipe::save_to_file(std::string filename) {
    std::ofstream out(filename, std::ios::app);
    if (out.is_open()) {
        if (validate_km_mark()) {
            out << id << std::endl;
            out << km_mark << std::endl;
            out << length << std::endl;
            out << diameter << std::endl;
            out << is_in_repair << std::endl;
        }
    }
    else {
        std::cout << "Error with opening file" << std::endl;
    }
}

int Pipe::get_id() { return id; }
std::string Pipe::get_km_mark() { return km_mark; }
bool Pipe::get_is_in_repair() { return is_in_repair; }
float Pipe::get_length() { return length; }
int Pipe::get_diameter() { return diameter; }

void Pipe::set_km_mark(std::string new_mark) { km_mark = new_mark; }
void Pipe::set_length(float new_length) { length = new_length; }
void Pipe::set_diameter(int new_diameter) { diameter = new_diameter; }
void Pipe::set_repair_status(bool status) { is_in_repair = status; }

void Pipe::load_data(int new_id, std::string mark, float len, int diam, bool repair) {
    id = new_id;
    km_mark = mark;
    length = len;
    diameter = diam;
    is_in_repair = repair;
}