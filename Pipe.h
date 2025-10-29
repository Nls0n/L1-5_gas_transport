#ifndef PIPE_H
#define PIPE_H

#include <string>
#include <vector>

class Pipe {
private:
    std::string km_mark;
    float length;
    int diameter;
    bool is_in_repair;
    int id;

public:
    void read_from_console();
    bool validate_km_mark();
    void assign_id(std::vector<Pipe> pipes);
    void write_to_console();
    void change_status();
    void save_to_file(std::string filename);
    
    // Геттеры
    int get_id();
    std::string get_km_mark();
    bool get_is_in_repair();
    float get_length();
    int get_diameter();
    
    // Сеттеры
    void set_km_mark(std::string new_mark);
    void set_length(float new_length);
    void set_diameter(int new_diameter);
    void set_repair_status(bool status);
    
    void load_data(int new_id, std::string mark, float len, int diam, bool repair);
};

#endif