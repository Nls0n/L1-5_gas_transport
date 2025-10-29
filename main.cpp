#include "Pipe.h"
#include "CompressorStation.h"
#include "search.h"
#include "file_operations.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>  // Добавьте эту строку

int main() {
    std::vector<Pipe> pipes;
    std::vector<CompressorStation> CSes;
    int user_input;
    std::string filename;
    
    truncate_file("logs.txt");
    write_to_log(0);

    while (true) {
        std::cout << "\n=== Gas Transmission Network Manager ===" << std::endl;
        std::cout << "1. Add Pipe" << std::endl;
        std::cout << "2. Add Compressor Station" << std::endl;
        std::cout << "3. View All Objects" << std::endl;
        std::cout << "4. Change Pipe Status" << std::endl;
        std::cout << "5. Manage Compressor Station Workshops" << std::endl;
        std::cout << "6. Save Data to Files" << std::endl;
        std::cout << "7. Load Data from Files" << std::endl;
        std::cout << "8. Search Objects" << std::endl;
        std::cout << "9. Batch Edit Pipes" << std::endl;
        std::cout << "10. Truncate File" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter command [0-10]: ";

        if (!(std::cin >> user_input)) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            write_to_log(-1);
            clear();
            continue;
        }
        
        write_to_log(user_input);
        clear();
        
        switch (user_input) {
        case 1: {
            std::cout << "\n=== Adding New Pipe ===" << std::endl;
            Pipe pipe;
            pipe.read_from_console();
            pipe.assign_id(pipes);
            pipes.push_back(pipe);
            std::cout << "Pipe added successfully!" << std::endl;
            break;
        }

        case 2: {
            std::cout << "\n=== Adding New Compressor Station ===" << std::endl;
            CompressorStation cs;
            cs.read_from_console();
            cs.assign_id(CSes);
            CSes.push_back(cs);
            std::cout << "Compressor Station added successfully!" << std::endl;
            break;
        }

        case 3:
            std::cout << "\n=== All Objects ===" << std::endl;
            if (pipes.empty()) {
                std::cout << "No pipes data available" << std::endl;
            } else {
                std::cout << "\n--- Pipes (" << pipes.size() << ") ---" << std::endl;
                for (int i = 0; i < pipes.size(); i++) {
                    pipes[i].write_to_console();
                }
            }

            if (CSes.empty()) {
                std::cout << "No compressor stations data available" << std::endl;
            } else {
                std::cout << "\n--- Compressor Stations (" << CSes.size() << ") ---" << std::endl;
                for (int i = 0; i < CSes.size(); i++) {
                    CSes[i].write_to_console();
                }
            }
            break;

        case 4:
            if (pipes.empty()) {
                std::cout << "No pipe available to modify. Please add a pipe first." << std::endl;
                break;
            }
            
            std::cout << "Available pipes:" << std::endl;
            for (int i = 0; i < pipes.size(); i++) {
                std::cout << "ID: " << pipes[i].get_id() << " - " << pipes[i].get_km_mark() << std::endl;
            }
            
            std::cout << "Enter pipe ID to change status: ";
            int pipe_id;
            if (std::cin >> pipe_id) {
                bool found = false;
                for (int i = 0; i < pipes.size(); i++) {
                    if (pipes[i].get_id() == pipe_id) {
                        pipes[i].change_status();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Pipe with ID " << pipe_id << " not found!" << std::endl;
                }
            } else {
                std::cout << "Invalid input!" << std::endl;
            }
            clear();
            break;

        case 5:
            if (CSes.empty()) {
                std::cout << "No compressor station available to modify. Please add a CS first." << std::endl;
                break;
            }
            
            std::cout << "Available compressor stations:" << std::endl;
            for (int i = 0; i < CSes.size(); i++) {
                std::cout << "ID: " << CSes[i].get_id() << " - " << CSes[i].get_name() << std::endl;
            }
            
            std::cout << "Enter CS ID to manage: ";
            int cs_id;
            if (std::cin >> cs_id) {
                bool found = false;
                for (int i = 0; i < CSes.size(); i++) {
                    if (CSes[i].get_id() == cs_id) {
                        CSes[i].print_workshop_managment();
                        std::cout << "1. Start workshop" << std::endl;
                        std::cout << "2. Stop workshop" << std::endl;

                        int cs_action;
                        std::cout << "Choose action: ";
                        if (std::cin >> cs_action) {
                            if (cs_action == 1) {
                                CSes[i].start_workshop();
                            } else if (cs_action == 2) {
                                CSes[i].stop_workshop();
                            } else {
                                std::cout << "Invalid action!" << std::endl;
                            }
                        } else {
                            std::cout << "Invalid input!" << std::endl;
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "CS with ID " << cs_id << " not found!" << std::endl;
                }
            } else {
                std::cout << "Invalid input!" << std::endl;
            }
            clear();
            break;

        case 6:
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);
            
            std::cout << "\n=== Saving Data ===" << std::endl;
            if (pipes.empty() && CSes.empty()) {
                std::cout << "No data available to save" << std::endl;
                break;
            }
            
            truncate_file(filename);
            
            if (!pipes.empty()) {
                std::ofstream out(filename, std::ios::app);
                out << "P " << pipes.size() << std::endl;
                out.close();
                for (int i = 0; i < pipes.size(); i++) {
                    pipes[i].save_to_file(filename);
                }
                std::cout << "Saved " << pipes.size() << " pipes" << std::endl;
            }
            
            if (!CSes.empty()) {
                std::ofstream out(filename, std::ios::app);
                out << "C " << CSes.size() << std::endl;
                out.close();
                for (int i = 0; i < CSes.size(); i++) {
                    CSes[i].save_to_file(filename);
                }
                std::cout << "Saved " << CSes.size() << " compressor stations" << std::endl;
            }
            break;

        case 7:
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);
            std::cout << "\n=== Loading Data ===" << std::endl;
            load_from_file(filename, pipes, CSes);
            break;

        case 8:
            search_objects(pipes, CSes);
            break;

        case 9:
            batch_edit_pipes(pipes);
            break;

        case 10:
            std::cout << "Enter filename to truncate: ";
            std::getline(std::cin, filename);
            truncate_file(filename);
            std::cout << "Successfully truncated the file" << std::endl;
            break;

        case 0:
            write_to_log(0);
            std::cout << "Exiting program. Goodbye!" << std::endl;
            return 0;
            
        default:
            std::cout << "Input is incorrect. Please try digits in range [0-10]" << std::endl;
        }
    }
    return 0;
}