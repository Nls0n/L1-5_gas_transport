#ifndef COMPRESSORSTATION_H
#define COMPRESSORSTATION_H

#include <string>
#include <vector>

class CompressorStation {
private:
    std::string name;
    int workshop_count;
    int current_working_workshop_count;
    float station_cls;
    int id;

public:
    void read_from_console();
    bool validate_name();
    void write_to_console();
    void start_workshop();
    void stop_workshop();
    void save_to_file(std::string filename);
    void print_workshop_managment();
    void assign_id(std::vector<CompressorStation> CSes);

    // Геттеры
    int get_id();
    std::string get_name();
    int get_workshop_count();
    int get_current_working_workshop_count();
    double get_unused_workshop_percent();
    
    void load_data(int new_id, std::string new_name, int workshops, int working_workshops, float cls);
};

#endif