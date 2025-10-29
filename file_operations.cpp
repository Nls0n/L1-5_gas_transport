#include "file_operations.h"
#include "utils.h"
#include <fstream>
#include <iostream>

void load_from_file(std::string filename, std::vector<Pipe>& pipes, std::vector<CompressorStation>& CSes) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    pipes.clear();
    CSes.clear();

    std::string line;
    char object_type = ' ';
    int count = 0;
    int objects_loaded = 0;

    while (std::getline(in, line)) {
        if (line.empty()) continue;

        if (line[0] == 'P' || line[0] == 'C') {
            object_type = line[0];
            count = std::stoi(line.substr(2));
            continue;
        }

        if (object_type == 'P' && count > 0) {
            int id = std::stoi(line);
            
            std::string km_mark;
            std::getline(in, km_mark);
            
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
            pipes.push_back(pipe);
            count--;
            objects_loaded++;
        }
        else if (object_type == 'C' && count > 0) {
            int id = std::stoi(line);
            
            std::string name;
            std::getline(in, name);
            
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
            CSes.push_back(cs);
            count--;
            objects_loaded++;
        }
    }

    in.close();
    std::cout << "Successfully loaded " << objects_loaded << " objects" << std::endl;
}

void truncate_file(std::string filename) {
    std::ofstream clear_file(filename, std::ios::out | std::ios::trunc);
    clear_file.close();
}

void write_to_log(int user_input) {
    std::ofstream logger("logs.txt", std::ios::app);
    if (logger.is_open()) {
        logger << user_input << std::endl;
        logger.close();
    }
}