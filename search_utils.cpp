#include "search_utils.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<int> search_pipes_by_name_for_batch(unordered_map<int, Pipe>& pipes) {
    string search_name;
    cout << "Enter pipe name to search: ";
    getline(cin, search_name);
    write_to_log(search_name);
    
    vector<int> found_ids;
    for (const auto& pair : pipes) {
        if (pair.second.get_km_mark().find(search_name) != string::npos) {
            cout << "ID: " << pair.first << " - " << pair.second.get_km_mark() << endl;
            found_ids.push_back(pair.first);
        }
    }
    return found_ids;
}

vector<int> search_pipes_by_repair_status_for_batch(unordered_map<int, Pipe>& pipes) {
    int status;
    cout << "Search pipes by repair status (0 - not in repair, 1 - in repair): ";
    cin >> status;
    write_to_log(to_string(status));
    clear();
    
    bool search_repair = (status == 1);
    vector<int> found_ids;
    
    for (const auto& pair : pipes) {
        if (pair.second.get_is_in_repair() == search_repair) {
            cout << "ID: " << pair.first << " - " << pair.second.get_km_mark() 
                 << " (in repair: " << pair.second.get_is_in_repair() << ")" << endl;
            found_ids.push_back(pair.first);
        }
    }
    return found_ids;
}

void batch_change_repair_status(unordered_map<int, Pipe>& pipes, vector<int> pipe_ids) {
    int new_status;
    cout << "Set new repair status (0 - not in repair, 1 - in repair): ";
    cin >> new_status;
    write_to_log(to_string(new_status));
    clear();
    
    bool status = (new_status == 1);
    int changed_count = 0;
    
    for (int id : pipe_ids) {
        auto it = pipes.find(id);
        if (it != pipes.end()) {
            it->second.set_repair_status(status);
            changed_count++;
        }
    }
    cout << "Changed repair status for " << changed_count << " pipes" << endl;
}

void batch_change_diameter(unordered_map<int, Pipe>& pipes, vector<int> pipe_ids) {
    int new_diameter;
    cout << "Enter new diameter: ";
    input_positive(new_diameter);
    write_to_log(to_string(new_diameter));
    
    int changed_count = 0;
    for (int id : pipe_ids) {
        auto it = pipes.find(id);
        if (it != pipes.end()) {
            it->second.set_diameter(new_diameter);
            changed_count++;
        }
    }
    cout << "Changed diameter for " << changed_count << " pipes" << endl;
}

void batch_delete_pipes(unordered_map<int, Pipe>& pipes, vector<int> pipe_ids) {
    cout << "This will delete " << pipe_ids.size() << " pipes. Are you sure? (1 - yes, 0 - no): ";
    int confirm;
    cin >> confirm;
    write_to_log(to_string(confirm));
    clear();
    
    if (confirm != 1) {
        cout << "Deletion cancelled" << endl;
        return;
    }
    
    int deleted_count = 0;
    for (int id : pipe_ids) {
        if (pipes.erase(id)) {
            deleted_count++;
        }
    }
    cout << "Deleted " << deleted_count << " pipes" << endl;
}

void batch_edit_pipes(unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) {
        cout << "No pipes available for batch editing." << endl;
        return;
    }
    
    cout << "\n=== Batch Pipe Editing ===" << endl;
    cout << "1. Search pipes by name" << endl;
    cout << "2. Search pipes by repair status" << endl;
    cout << "3. Select all pipes" << endl;
    cout << "0. Back to main menu" << endl;
    cout << "Choose search method: ";
    
    int search_method;
    cin >> search_method;
    write_to_log(to_string(search_method));
    clear();
    
    vector<int> selected_ids;
    
    switch (search_method) {
        case 1:
            selected_ids = search_pipes_by_name_for_batch(pipes);
            break;
        case 2:
            selected_ids = search_pipes_by_repair_status_for_batch(pipes);
            break;
        case 3:
            for (const auto& pair : pipes) {
                selected_ids.push_back(pair.first);
            }
            cout << "Selected all " << selected_ids.size() << " pipes" << endl;
            break;
        case 0:
            return;
        default:
            cout << "Invalid search method!" << endl;
            return;
    }
    
    if (selected_ids.empty()) {
        cout << "No pipes found for editing." << endl;
        return;
    }
    
    cout << "\nFound " << selected_ids.size() << " pipes." << endl;
    cout << "1. Edit all found pipes" << endl;
    cout << "2. Select specific pipes" << endl;
    cout << "Choose option: ";
    
    int selection_option;
    cin >> selection_option;
    write_to_log(to_string(selection_option));
    clear();
    
    vector<int> final_selection;
    
    if (selection_option == 1) {
        final_selection = selected_ids;
    } else if (selection_option == 2) {
        cout << "Enter pipe IDs to edit (separated by spaces, 0 to finish): ";
        int id;
        set<int> selected_set(selected_ids.begin(), selected_ids.end());
        
        while (cin >> id && id != 0) {
            write_to_log(to_string(id));
            if (selected_set.count(id)) {
                final_selection.push_back(id);
                cout << "Added pipe ID: " << id << endl;
            } else {
                cout << "Pipe ID " << id << " not in found pipes!" << endl;
            }
        }
        clear();
    } else {
        cout << "Invalid option!" << endl;
        return;
    }
    
    if (final_selection.empty()) {
        cout << "No pipes selected for editing." << endl;
        return;
    }
    
    cout << "\nSelected " << final_selection.size() << " pipes for editing." << endl;
    cout << "1. Change repair status" << endl;
    cout << "2. Change diameter" << endl;
    cout << "3. Delete pipes" << endl;
    cout << "0. Cancel" << endl;
    cout << "Choose action: ";
    
    int action;
    cin >> action;
    write_to_log(to_string(action));
    clear();
    
    switch (action) {
        case 1:
            batch_change_repair_status(pipes, final_selection);
            break;
        case 2:
            batch_change_diameter(pipes, final_selection);
            break;
        case 3:
            batch_delete_pipes(pipes, final_selection);
            break;
        case 0:
            cout << "Editing cancelled" << endl;
            break;
        default:
            cout << "Invalid action!" << endl;
    }
}

void search_pipes_by_name(const unordered_map<int, Pipe>& pipes) {
    string search_name;
    cout << "Enter pipe name to search: ";
    getline(cin, search_name);
    write_to_log(search_name);
    
    bool found = false;
    for (const auto& pair : pipes) {
        if (pair.second.get_km_mark().find(search_name) != string::npos) {
            pair.second.write_to_console();
            found = true;
        }
    }
    if (!found) {
        cout << "No pipes found with name containing: '" << search_name << "'" << endl;
    }
}

void search_pipes_by_repair_status(const unordered_map<int, Pipe>& pipes) {
    int status;
    cout << "Search pipes by repair status (0 - not in repair, 1 - in repair): ";
    cin >> status;
    write_to_log(to_string(status));
    clear();
    
    bool search_repair = (status == 1);
    bool found = false;
    
    for (const auto& pair : pipes) {
        if (pair.second.get_is_in_repair() == search_repair) {
            pair.second.write_to_console();
            found = true;
        }
    }
    if (!found) {
        cout << "No pipes found with repair status: " << search_repair << endl;
    }
}

void search_cs_by_name(const unordered_map<int, CompressorStation>& CSes) {
    string search_name;
    cout << "Enter CS name to search: ";
    getline(cin, search_name);
    write_to_log(search_name);
    
    bool found = false;
    for (const auto& pair : CSes) {
        if (pair.second.get_name().find(search_name) != string::npos) {
            pair.second.write_to_console();
            found = true;
        }
    }
    if (!found) {
        cout << "No compressor stations found with name containing: '" << search_name << "'" << endl;
    }
}

void search_cs_by_unused_percent(const unordered_map<int, CompressorStation>& CSes) {
    double min_percent, max_percent;
    cout << "Enter minimum percent of unused workshops: ";
    cin >> min_percent;
    write_to_log(to_string(min_percent));
    cout << "Enter maximum percent of unused workshops: ";
    cin >> max_percent;
    write_to_log(to_string(max_percent));
    clear();
    
    bool found = false;
    for (const auto& pair : CSes) {
        double unused_percent = pair.second.get_unused_workshop_percent();
        if (unused_percent >= min_percent && unused_percent <= max_percent) {
            pair.second.write_to_console();
            cout << "Unused workshops: " << unused_percent << "%" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No compressor stations found with unused workshops percentage between " 
             << min_percent << "% and " << max_percent << "%" << endl;
    }
}

void search_objects(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CompressorStation>& CSes) {
    int search_type;
    cout << "\n=== Search Objects ===" << endl;
    cout << "1. Search pipes by name" << endl;
    cout << "2. Search pipes by repair status" << endl;
    cout << "3. Search CS by name" << endl;
    cout << "4. Search CS by unused workshop percentage" << endl;
    cout << "0. Back to main menu" << endl;
    cout << "Choose search type: ";
    
    cin >> search_type;
    write_to_log(to_string(search_type));
    clear();
    
    switch (search_type) {
        case 1:
            if (pipes.empty()) {
                cout << "No pipes available for search." << endl;
            } else {
                search_pipes_by_name(pipes);
            }
            break;
        case 2:
            if (pipes.empty()) {
                cout << "No pipes available for search." << endl;
            } else {
                search_pipes_by_repair_status(pipes);
            }
            break;
        case 3:
            if (CSes.empty()) {
                cout << "No compressor stations available for search." << endl;
            } else {
                search_cs_by_name(CSes);
            }
            break;
        case 4:
            if (CSes.empty()) {
                cout << "No compressor stations available for search." << endl;
            } else {
                search_cs_by_unused_percent(CSes);
            }
            break;
        case 0:
            return;
        default:
            cout << "Invalid search type!" << endl;
    }
}