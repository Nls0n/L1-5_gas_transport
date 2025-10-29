#include "search.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include <set>

// Функции поиска для пакетного редактирования
std::vector<int> search_pipes_by_name_for_batch(std::vector<Pipe>& pipes) {
    std::string search_name;
    std::cout << "Enter pipe name to search: ";
    std::getline(std::cin, search_name);
    
    std::vector<int> found_ids;
    for (int i = 0; i < pipes.size(); i++) {
        if (pipes[i].get_km_mark().find(search_name) != std::string::npos) {
            std::cout << "ID: " << pipes[i].get_id() << " - " << pipes[i].get_km_mark() << std::endl;
            found_ids.push_back(pipes[i].get_id());
        }
    }
    return found_ids;
}

std::vector<int> search_pipes_by_repair_status_for_batch(std::vector<Pipe>& pipes) {
    int status;
    std::cout << "Search pipes by repair status (0 - not in repair, 1 - in repair): ";
    std::cin >> status;
    clear();
    
    bool search_repair = (status == 1);
    std::vector<int> found_ids;
    
    for (int i = 0; i < pipes.size(); i++) {
        if (pipes[i].get_is_in_repair() == search_repair) {
            std::cout << "ID: " << pipes[i].get_id() << " - " << pipes[i].get_km_mark() 
                 << " (in repair: " << pipes[i].get_is_in_repair() << ")" << std::endl;
            found_ids.push_back(pipes[i].get_id());
        }
    }
    return found_ids;
}

// Функции пакетного редактирования
void batch_change_repair_status(std::vector<Pipe>& pipes, std::vector<int> pipe_ids) {
    int new_status;
    std::cout << "Set new repair status (0 - not in repair, 1 - in repair): ";
    std::cin >> new_status;
    clear();
    
    bool status = (new_status == 1);
    int changed_count = 0;
    
    for (int id : pipe_ids) {
        for (int i = 0; i < pipes.size(); i++) {
            if (pipes[i].get_id() == id) {
                pipes[i].set_repair_status(status);
                changed_count++;
                break;
            }
        }
    }
    std::cout << "Changed repair status for " << changed_count << " pipes" << std::endl;
}

void batch_change_diameter(std::vector<Pipe>& pipes, std::vector<int> pipe_ids) {
    int new_diameter;
    std::cout << "Enter new diameter: ";
    input_positive(new_diameter);
    
    int changed_count = 0;
    for (int id : pipe_ids) {
        for (int i = 0; i < pipes.size(); i++) {
            if (pipes[i].get_id() == id) {
                pipes[i].set_diameter(new_diameter);
                changed_count++;
                break;
            }
        }
    }
    std::cout << "Changed diameter for " << changed_count << " pipes" << std::endl;
}

void batch_delete_pipes(std::vector<Pipe>& pipes, std::vector<int> pipe_ids) {
    std::cout << "This will delete " << pipe_ids.size() << " pipes. Are you sure? (1 - yes, 0 - no): ";
    int confirm;
    std::cin >> confirm;
    clear();
    
    if (confirm != 1) {
        std::cout << "Deletion cancelled" << std::endl;
        return;
    }
    
    // Удаляем трубы в обратном порядке чтобы не сломать индексы
    std::sort(pipe_ids.rbegin(), pipe_ids.rend());
    int deleted_count = 0;
    
    for (int id : pipe_ids) {
        for (int i = 0; i < pipes.size(); i++) {
            if (pipes[i].get_id() == id) {
                pipes.erase(pipes.begin() + i);
                deleted_count++;
                break;
            }
        }
    }
    std::cout << "Deleted " << deleted_count << " pipes" << std::endl;
}

// Основная функция пакетного редактирования
void batch_edit_pipes(std::vector<Pipe>& pipes) {
    if (pipes.empty()) {
        std::cout << "No pipes available for batch editing." << std::endl;
        return;
    }
    
    std::cout << "\n=== Batch Pipe Editing ===" << std::endl;
    std::cout << "1. Search pipes by name" << std::endl;
    std::cout << "2. Search pipes by repair status" << std::endl;
    std::cout << "3. Select all pipes" << std::endl;
    std::cout << "0. Back to main menu" << std::endl;
    std::cout << "Choose search method: ";
    
    int search_method;
    std::cin >> search_method;
    clear();
    
    std::vector<int> selected_ids;
    
    switch (search_method) {
        case 1:
            selected_ids = search_pipes_by_name_for_batch(pipes);
            break;
        case 2:
            selected_ids = search_pipes_by_repair_status_for_batch(pipes);
            break;
        case 3:
            // Выбираем все трубы
            for (int i = 0; i < pipes.size(); i++) {
                selected_ids.push_back(pipes[i].get_id());
            }
            std::cout << "Selected all " << selected_ids.size() << " pipes" << std::endl;
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid search method!" << std::endl;
            return;
    }
    
    if (selected_ids.empty()) {
        std::cout << "No pipes found for editing." << std::endl;
        return;
    }
    
    // Выбор подмножества
    std::cout << "\nFound " << selected_ids.size() << " pipes." << std::endl;
    std::cout << "1. Edit all found pipes" << std::endl;
    std::cout << "2. Select specific pipes" << std::endl;
    std::cout << "Choose option: ";
    
    int selection_option;
    std::cin >> selection_option;
    clear();
    
    std::vector<int> final_selection;
    
    if (selection_option == 1) {
        final_selection = selected_ids;
    } else if (selection_option == 2) {
        std::cout << "Enter pipe IDs to edit (separated by spaces, 0 to finish): ";
        int id;
        std::set<int> selected_set(selected_ids.begin(), selected_ids.end());
        
        while (std::cin >> id && id != 0) {
            if (selected_set.count(id)) {
                final_selection.push_back(id);
                std::cout << "Added pipe ID: " << id << std::endl;
            } else {
                std::cout << "Pipe ID " << id << " not in found pipes!" << std::endl;
            }
        }
        clear();
    } else {
        std::cout << "Invalid option!" << std::endl;
        return;
    }
    
    if (final_selection.empty()) {
        std::cout << "No pipes selected for editing." << std::endl;
        return;
    }
    
    // Выбор действия
    std::cout << "\nSelected " << final_selection.size() << " pipes for editing." << std::endl;
    std::cout << "1. Change repair status" << std::endl;
    std::cout << "2. Change diameter" << std::endl;
    std::cout << "3. Delete pipes" << std::endl;
    std::cout << "0. Cancel" << std::endl;
    std::cout << "Choose action: ";
    
    int action;
    std::cin >> action;
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
            std::cout << "Editing cancelled" << std::endl;
            break;
        default:
            std::cout << "Invalid action!" << std::endl;
    }
}

// Старые функции поиска (для просмотра)
void search_pipes_by_name(std::vector<Pipe>& pipes) {
    std::string search_name;
    std::cout << "Enter pipe name to search: ";
    std::getline(std::cin, search_name);
    
    bool found = false;
    for (int i = 0; i < pipes.size(); i++) {
        if (pipes[i].get_km_mark().find(search_name) != std::string::npos) {
            pipes[i].write_to_console();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No pipes found with name containing: '" << search_name << "'" << std::endl;
    }
}

void search_pipes_by_repair_status(std::vector<Pipe>& pipes) {
    int status;
    std::cout << "Search pipes by repair status (0 - not in repair, 1 - in repair): ";
    std::cin >> status;
    clear();
    
    bool search_repair = (status == 1);
    bool found = false;
    
    for (int i = 0; i < pipes.size(); i++) {
        if (pipes[i].get_is_in_repair() == search_repair) {
            pipes[i].write_to_console();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No pipes found with repair status: " << search_repair << std::endl;
    }
}

void search_cs_by_name(std::vector<CompressorStation>& CSes) {
    std::string search_name;
    std::cout << "Enter CS name to search: ";
    std::getline(std::cin, search_name);
    
    bool found = false;
    for (int i = 0; i < CSes.size(); i++) {
        if (CSes[i].get_name().find(search_name) != std::string::npos) {
            CSes[i].write_to_console();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No compressor stations found with name containing: '" << search_name << "'" << std::endl;
    }
}

void search_cs_by_unused_percent(std::vector<CompressorStation>& CSes) {
    double min_percent, max_percent;
    std::cout << "Enter minimum percent of unused workshops: ";
    std::cin >> min_percent;
    std::cout << "Enter maximum percent of unused workshops: ";
    std::cin >> max_percent;
    clear();
    
    bool found = false;
    for (int i = 0; i < CSes.size(); i++) {
        double unused_percent = CSes[i].get_unused_workshop_percent();
        if (unused_percent >= min_percent && unused_percent <= max_percent) {
            CSes[i].write_to_console();
            std::cout << "Unused workshops: " << unused_percent << "%" << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No compressor stations found with unused workshops percentage between " 
             << min_percent << "% and " << max_percent << "%" << std::endl;
    }
}

void search_objects(std::vector<Pipe>& pipes, std::vector<CompressorStation>& CSes) {
    int search_type;
    std::cout << "\n=== Search Objects ===" << std::endl;
    std::cout << "1. Search pipes by name" << std::endl;
    std::cout << "2. Search pipes by repair status" << std::endl;
    std::cout << "3. Search CS by name" << std::endl;
    std::cout << "4. Search CS by unused workshop percentage" << std::endl;
    std::cout << "0. Back to main menu" << std::endl;
    std::cout << "Choose search type: ";
    
    std::cin >> search_type;
    clear();
    
    switch (search_type) {
        case 1:
            if (pipes.empty()) {
                std::cout << "No pipes available for search." << std::endl;
            } else {
                search_pipes_by_name(pipes);
            }
            break;
        case 2:
            if (pipes.empty()) {
                std::cout << "No pipes available for search." << std::endl;
            } else {
                search_pipes_by_repair_status(pipes);
            }
            break;
        case 3:
            if (CSes.empty()) {
                std::cout << "No compressor stations available for search." << std::endl;
            } else {
                search_cs_by_name(CSes);
            }
            break;
        case 4:
            if (CSes.empty()) {
                std::cout << "No compressor stations available for search." << std::endl;
            } else {
                search_cs_by_unused_percent(CSes);
            }
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid search type!" << std::endl;
    }
}