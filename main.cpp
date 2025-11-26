#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "pipe.h"
#include "compressor_station.h"
#include "utils.h"
#include "search_utils.h"

using namespace std;

int main() {
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CompressorStation> CSes;
    int user_input;
    string filename;
    
    initialize_logging();
    
    while (true) {
        cout << "\n=== Gas Transmission Network Manager ===" << endl;
        cout << "1. Add Pipe" << endl;
        cout << "2. Add Compressor Station" << endl;
        cout << "3. View All Objects" << endl;
        cout << "4. Change Pipe Status" << endl;
        cout << "5. Manage Compressor Station Workshops" << endl;
        cout << "6. Save Data to Files" << endl;
        cout << "7. Load Data from Files" << endl;
        cout << "8. Search Objects" << endl;
        cout << "9. Batch Edit Pipes" << endl;
        cout << "10. Truncate File" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter command [0-10]: ";

        if (!(cin >> user_input)) {
            cout << "Invalid input. Please enter a number." << endl;
            clear();
            continue;
        }
        
        write_to_log(to_string(user_input));
        clear();
        
        switch (user_input) {
        case 1: {
            Pipe pipe;
            pipe.read_from_console();
            pipe.assign_id(pipes);
            pipes[pipe.get_id()] = pipe;
            cout << "Pipe added successfully!" << endl;
            break;
        }

        case 2: {
            CompressorStation cs;
            cs.read_from_console();
            cs.assign_id(CSes);
            CSes[cs.get_id()] = cs;
            cout << "Compressor Station added successfully!" << endl;
            break;
        }

        case 3:
            cout << "\n=== All Objects ===" << endl;
            if (pipes.empty()) {
                cout << "No pipes data available" << endl;
            } else {
                cout << "\n--- Pipes (" << pipes.size() << ") ---" << endl;
                for (const auto& pair : pipes) {
                    pair.second.write_to_console();
                }
            }

            if (CSes.empty()) {
                cout << "No compressor stations data available" << endl;
            } else {
                cout << "\n--- Compressor Stations (" << CSes.size() << ") ---" << endl;
                for (const auto& pair : CSes) {
                    pair.second.write_to_console();
                }
            }
            break;

        case 4:
            if (pipes.empty()) {
                cout << "No pipe available to modify. Please add a pipe first." << endl;
                break;
            }
            
            cout << "Available pipes:" << endl;
            for (const auto& pair : pipes) {
                cout << "ID: " << pair.first << " - " << pair.second.get_km_mark() << endl;
            }
            
            cout << "Enter pipe ID to change status: ";
            int pipe_id;
            if (cin >> pipe_id) {
                write_to_log(to_string(pipe_id));
                auto it = pipes.find(pipe_id);
                if (it != pipes.end()) {
                    it->second.change_status();
                } else {
                    cout << "Pipe with ID " << pipe_id << " not found!" << endl;
                }
            } else {
                cout << "Invalid input!" << endl;
            }
            clear();
            break;

        case 5:
            if (CSes.empty()) {
                cout << "No compressor station available to modify. Please add a CS first." << endl;
                break;
            }
            
            cout << "Available compressor stations:" << endl;
            for (const auto& pair : CSes) {
                cout << "ID: " << pair.first << " - " << pair.second.get_name() << endl;
            }
            
            cout << "Enter CS ID to manage: ";
            int cs_id;
            if (cin >> cs_id) {
                write_to_log(to_string(cs_id));
                auto it = CSes.find(cs_id);
                if (it != CSes.end()) {
                    it->second.print_workshop_managment();
                    cout << "1. Start workshop" << endl;
                    cout << "2. Stop workshop" << endl;

                    int cs_action;
                    cout << "Choose action: ";
                    if (cin >> cs_action) {
                        write_to_log(to_string(cs_action));
                        if (cs_action == 1) {
                            it->second.start_workshop();
                        } else if (cs_action == 2) {
                            it->second.stop_workshop();
                        } else {
                            cout << "Invalid action!" << endl;
                        }
                    } else {
                        cout << "Invalid input!" << endl;
                    }
                } else {
                    cout << "CS with ID " << cs_id << " not found!" << endl;
                }
            } else {
                cout << "Invalid input!" << endl;
            }
            clear();
            break;

        case 6:
            cout << "Enter filename: ";
            getline(cin, filename);
            write_to_log(filename);
            
            cout << "\n=== Saving Data ===" << endl;
            if (pipes.empty() && CSes.empty()) {
                cout << "No data available to save" << endl;
                break;
            }
            
            truncate_file(filename);
            
            if (!pipes.empty()) {
                ofstream out(filename, ios::app);
                out << "P " << pipes.size() << endl;
                out.close();
                for (const auto& pair : pipes) {
                    pair.second.save_to_file(filename);
                }
                cout << "Saved " << pipes.size() << " pipes" << endl;
            }
            
            if (!CSes.empty()) {
                ofstream out(filename, ios::app);
                out << "C " << CSes.size() << endl;
                out.close();
                for (const auto& pair : CSes) {
                    pair.second.save_to_file(filename);
                }
                cout << "Saved " << CSes.size() << " compressor stations" << endl;
            }
            break;

        case 7:
            cout << "Enter filename: ";
            getline(cin, filename);
            write_to_log(filename);
            cout << "\n=== Loading Data ===" << endl;
            load_from_file(filename, pipes, CSes);
            break;

        case 8:
            search_objects(pipes, CSes);
            break;

        case 9:
            batch_edit_pipes(pipes);
            break;

        case 10:
            cout << "Enter filename to truncate: ";
            getline(cin, filename);
            write_to_log(filename);
            truncate_file(filename);
            cout << "Successfully truncated the file" << endl;
            break;

        case 0:
            cout << "Exiting program. Goodbye!" << endl;
            close_logging();
            return 0;
            
        default:
            cout << "Input is incorrect. Please try digits in range [0-10]" << endl;
        }
    }
    return 0;
}