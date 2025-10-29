#include "CompressorStation.h"
#include "utils.h"
#include <iostream>
#include <fstream>

void CompressorStation::read_from_console() {
    std::cout << "Input CS name: ";
    std::getline(std::cin, name);
    std::cout << "Input workshop_count: ";
    input_positive(workshop_count);
    
    std::cout << "Input current_working_workshop_count: ";
    do {
        input_positive(current_working_workshop_count);
        if (current_working_workshop_count > workshop_count) {
            std::cout << "current_working_workshop_count must be less or equal to workshop_count, try again" << std::endl;
            std::cout << "Input current_working_workshop_count: ";
        }
    } while (current_working_workshop_count > workshop_count);
    
    std::cout << "Input station_cls: ";
    input_positive(station_cls);
}

bool CompressorStation::validate_name() {
    return (name != "");
}

void CompressorStation::write_to_console() {
    std::cout << "CS id: " << id << std::endl;
    std::cout << "CS name: " << name << std::endl;
    std::cout << "CS workshop_count: " << workshop_count << std::endl;
    std::cout << "CS current_working_workshop_count: " << current_working_workshop_count << std::endl;
    std::cout << "CS station_cls: " << station_cls << std::endl;
    std::cout << "------------------------" << std::endl;
}

void CompressorStation::start_workshop() {
    if (current_working_workshop_count < workshop_count) {
        current_working_workshop_count++;
        std::cout << "Workshop started. Current working: " << current_working_workshop_count << std::endl;
    }
    else {
        std::cout << "Cannot start more workshops. All " << workshop_count << " workshops are already working." << std::endl;
    }
}

void CompressorStation::stop_workshop() {
    if (current_working_workshop_count > 0) {
        current_working_workshop_count--;
        std::cout << "Workshop stopped. Current working: " << current_working_workshop_count << std::endl;
    }
    else {
        std::cout << "There are no available workshops to stop." << std::endl;
    }
}

void CompressorStation::save_to_file(std::string filename) { 
    std::ofstream out(filename, std::ios::app);
    if (out.is_open()) {
        if (validate_name()) {
            out << id << std::endl;
            out << name << std::endl;
            out << workshop_count << std::endl;
            out << current_working_workshop_count << std::endl;
            out << station_cls << std::endl;
        }
    }
    else {
        std::cout << "Error with opening file" << std::endl;
    }
}

void CompressorStation::print_workshop_managment() {
    std::cout << "Current working workshops: " << current_working_workshop_count << " / " << workshop_count << std::endl;
}

void CompressorStation::assign_id(std::vector<CompressorStation> CSes) {
    id = CSes.size() + 1;
}

int CompressorStation::get_id() { return id; }
std::string CompressorStation::get_name() { return name; }
int CompressorStation::get_workshop_count() { return workshop_count; }
int CompressorStation::get_current_working_workshop_count() { return current_working_workshop_count; }

double CompressorStation::get_unused_workshop_percent() {
    if (workshop_count == 0) return 0;
    return ((workshop_count - current_working_workshop_count) * 100.0) / workshop_count;
}

void CompressorStation::load_data(int new_id, std::string new_name, int workshops, int working_workshops, float cls) {
    id = new_id;
    name = new_name;
    workshop_count = workshops;
    current_working_workshop_count = working_workshops;
    station_cls = cls;
}