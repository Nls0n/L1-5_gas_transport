#ifndef COMPRESSOR_STATION_H
#define COMPRESSOR_STATION_H

#include <string>
#include <unordered_map>

class CompressorStation {
private:
    std::string name;
    int workshop_count;
    int current_working_workshop_count;
    float station_cls;
    int id;

public:
    void read_from_console();
    bool validate_name() const;
    void write_to_console() const;
    void start_workshop();
    void stop_workshop();
    void save_to_file(std::string filename) const;
    void print_workshop_managment() const;
    void assign_id(const std::unordered_map<int, CompressorStation>& CSes);
    
    // Геттеры
    int get_id() const { return id; }
    std::string get_name() const { return name; }
    int get_workshop_count() const { return workshop_count; }
    int get_current_working_workshop_count() const { return current_working_workshop_count; }
    double get_unused_workshop_percent() const;
    
    void load_data(int new_id, std::string new_name, int workshops, int working_workshops, float cls);
};

#endif