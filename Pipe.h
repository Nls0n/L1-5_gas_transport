#ifndef PIPE_H
#define PIPE_H

#include <string>
#include <unordered_map>
#include <iostream>

class Pipe {
private:
    std::string km_mark;
    float length;
    int diameter;
    bool is_in_repair;
    int id;

public:
    void read_from_console();
    bool validate_km_mark() const;
    void assign_id(const std::unordered_map<int, Pipe>& pipes);
    void write_to_console() const;
    void change_status();
    void save_to_file(std::string filename) const;
    
    // Геттеры
    int get_id() const { return id; }
    std::string get_km_mark() const { return km_mark; }
    bool get_is_in_repair() const { return is_in_repair; }
    float get_length() const { return length; }
    int get_diameter() const { return diameter; }
    
    // Сеттеры
    void set_km_mark(std::string new_mark) { km_mark = new_mark; }
    void set_length(float new_length) { length = new_length; }
    void set_diameter(int new_diameter) { diameter = new_diameter; }
    void set_repair_status(bool status) { is_in_repair = status; }
    
    void load_data(int new_id, std::string mark, float len, int diam, bool repair);
};

#endif