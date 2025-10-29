#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

void clear() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

template<typename T>
void input_positive(T& var) {
    while (!(cin >> var) || var <= 0) {
        clear();
        cout << "Invalid input. Enter positive number: ";
    }
    clear();
}

class Pipe {
private:
    string km_mark;
    float length;
    int diameter;
    bool is_in_repair;
    int id;

public:
    void read_from_console() {
        cout << "Input kilometers mark (name): ";
        getline(cin, km_mark);
        cout << "Input pipe length: ";
        input_positive(length);
        cout << "Input pipe diameter: ";
        input_positive(diameter);
        cout << "Input is_in_repair status: ";
        while (!(cin >> is_in_repair)) {
            clear();
            cout << "Invalid input. Enter 1 or 0: ";
        }
        clear();
    }

    bool validate_km_mark() {
        return (km_mark != "");
    }

    void assign_id(vector<Pipe> pipes) {
        id = pipes.size() + 1;
    }

    void write_to_console() {
        cout << "Pipe id: " << id << endl;
        cout << "Pipe km_mark: " << km_mark << endl;
        cout << "Pipe length (km): " << length << endl;
        cout << "Pipe diameter (mm): " << diameter << endl;
        cout << "Pipe is_in_repair: " << is_in_repair << endl;
        cout << "------------------------" << endl;
    }

    void change_status() {
        is_in_repair = !is_in_repair;
        cout << "Current status: " << is_in_repair << endl;
    }

    void save_to_file(string filename) {
        ofstream out(filename, ios::app);
        if (out.is_open()) {
            if (validate_km_mark()) {
                out << id << endl;
                out << km_mark << endl;
                out << length << endl;
                out << diameter << endl;
                out << is_in_repair << endl;
            }
        }
        else {
            cout << "Error with opening file" << endl;
        }
    }

    int get_id() { return id; }
    string get_km_mark() { return km_mark; }
    bool get_is_in_repair() { return is_in_repair; }
    float get_length() { return length; }
    int get_diameter() { return diameter; }
    
    void set_km_mark(string new_mark) { km_mark = new_mark; }
    void set_length(float new_length) { length = new_length; }
    void set_diameter(int new_diameter) { diameter = new_diameter; }
    void set_repair_status(bool status) { is_in_repair = status; }
    
    void load_data(int new_id, string mark, float len, int diam, bool repair) {
        id = new_id;
        km_mark = mark;
        length = len;
        diameter = diam;
        is_in_repair = repair;
    }
};

class CompressorStation {
private:
    string name;
    int workshop_count;
    int current_working_workshop_count;
    float station_cls;
    int id;

public:
    void read_from_console() {
        cout << "Input CS name: ";
        getline(cin, name);
        cout << "Input workshop_count: ";
        input_positive(workshop_count);
        
        cout << "Input current_working_workshop_count: ";
        do {
            input_positive(current_working_workshop_count);
            if (current_working_workshop_count > workshop_count) {
                cout << "current_working_workshop_count must be less or equal to workshop_count, try again" << endl;
                cout << "Input current_working_workshop_count: ";
            }
        } while (current_working_workshop_count > workshop_count);
        
        cout << "Input station_cls: ";
        input_positive(station_cls);
    }

    bool validate_name() {
        return (name != "");
    }

    void write_to_console() {
        cout << "CS id: " << id << endl;
        cout << "CS name: " << name << endl;
        cout << "CS workshop_count: " << workshop_count << endl;
        cout << "CS current_working_workshop_count: " << current_working_workshop_count << endl;
        cout << "CS station_cls: " << station_cls << endl;
        cout << "------------------------" << endl;
    }

    void start_workshop() {
        if (current_working_workshop_count < workshop_count) {
            current_working_workshop_count++;
            cout << "Workshop started. Current working: " << current_working_workshop_count << endl;
        }
        else {
            cout << "Cannot start more workshops. All " << workshop_count << " workshops are already working." << endl;
        }
    }

    void stop_workshop() {
        if (current_working_workshop_count > 0) {
            current_working_workshop_count--;
            cout << "Workshop stopped. Current working: " << current_working_workshop_count << endl;
        }
        else {
            cout << "There are no available workshops to stop." << endl;
        }
    }

    void save_to_file(string filename) { 
        ofstream out(filename, ios::app);
        if (out.is_open()) {
            if (validate_name()) {
                out << id << endl;
                out << name << endl;
                out << workshop_count << endl;
                out << current_working_workshop_count << endl;
                out << station_cls << endl;
            }
        }
        else {
            cout << "Error with opening file" << endl;
        }
    }

    void print_workshop_managment() {
        cout << "Current working workshops: " << current_working_workshop_count << " / " << workshop_count << endl;
    }

    void assign_id(vector<CompressorStation> CSes) {
        id = CSes.size() + 1;
    }

    int get_id() { return id; }
    string get_name() { return name; }
    int get_workshop_count() { return workshop_count; }
    int get_current_working_workshop_count() { return current_working_workshop_count; }
    
    double get_unused_workshop_percent() {
        if (workshop_count == 0) return 0;
        return ((workshop_count - current_working_workshop_count) * 100.0) / workshop_count;
    }
    
    void load_data(int new_id, string new_name, int workshops, int working_workshops, float cls) {
        id = new_id;
        name = new_name;
        workshop_count = workshops;
        current_working_workshop_count = working_workshops;
        station_cls = cls;
    }
};

// Функции поиска для пакетного редактирования
vector<int> search_pipes_by_name_for_batch(vector<Pipe>& pipes) {
    string search_name;
    cout << "Enter pipe name to search: ";
    getline(cin, search_name);
    
    vector<int> found_ids;
    for (int i = 0; i < pipes.size(); i++) {
        if (pipes[i].get_km_mark().find(search_name) != string::npos) {
            cout << "ID: " << pipes[i].get_id() << " - " << pipes[i].get_km_mark() << endl;
            found_ids.push_back(pipes[i].get_id());
        }
    }
    return found_ids;
}

vector<int> search_pipes_by_repair_status_for_batch(vector<Pipe>& pipes) {
    int status;
    cout << "Search pipes by repair status (0 - not in repair, 1 - in repair): ";
    cin >> status;
    clear();
    
    bool search_repair = (status == 1);
    vector<int> found_ids;
    
    for (int i = 0; i < pipes.size(); i++) {
        if (pipes[i].get_is_in_repair() == search_repair) {
            cout << "ID: " << pipes[i].get_id() << " - " << pipes[i].get_km_mark() 
                 << " (in repair: " << pipes[i].get_is_in_repair() << ")" << endl;
            found_ids.push_back(pipes[i].get_id());
        }
    }
    return found_ids;
}

// Функции пакетного редактирования
void batch_change_repair_status(vector<Pipe>& pipes, vector<int> pipe_ids) {
    int new_status;
    cout << "Set new repair status (0 - not in repair, 1 - in repair): ";
    cin >> new_status;
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
    cout << "Changed repair status for " << changed_count << " pipes" << endl;
}

void batch_change_diameter(vector<Pipe>& pipes, vector<int> pipe_ids) {
    int new_diameter;
    cout << "Enter new diameter: ";
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
    cout << "Changed diameter for " << changed_count << " pipes" << endl;
}

void batch_delete_pipes(vector<Pipe>& pipes, vector<int> pipe_ids) {
    cout << "This will delete " << pipe_ids.size() << " pipes. Are you sure? (1 - yes, 0 - no): ";
    int confirm;
    cin >> confirm;
    clear();
    
    if (confirm != 1) {
        cout << "Deletion cancelled" << endl;
        return;
    }
    
    // Удаляем трубы в обратном порядке чтобы не сломать индексы
    sort(pipe_ids.rbegin(), pipe_ids.rend());
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
    cout << "Deleted " << deleted_count << " pipes" << endl;
}

// Основная функция пакетного редактирования
void batch_edit_pipes(vector<Pipe>& pipes) {
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
            // Выбираем все трубы
            for (int i = 0; i < pipes.size(); i++) {
                selected_ids.push_back(pipes[i].get_id());
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
    
    // Выбор подмножества
    cout << "\nFound " << selected_ids.size() << " pipes." << endl;
    cout << "1. Edit all found pipes" << endl;
    cout << "2. Select specific pipes" << endl;
    cout << "Choose option: ";
    
    int selection_option;
    cin >> selection_option;
    clear();
    
    vector<int> final_selection;
    
    if (selection_option == 1) {
        final_selection = selected_ids;
    } else if (selection_option == 2) {
        cout << "Enter pipe IDs to edit (separated by spaces, 0 to finish): ";
        int id;
        set<int> selected_set(selected_ids.begin(), selected_ids.end());
        
        while (cin >> id && id != 0) {
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
    
    // Выбор действия
    cout << "\nSelected " << final_selection.size() << " pipes for editing." << endl;
    cout << "1. Change repair status" << endl;
    cout << "2. Change diameter" << endl;
    cout << "3. Delete pipes" << endl;
    cout << "0. Cancel" << endl;
    cout << "Choose action: ";
    
    int action;
    cin >> action;
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

// Старые функции поиска (для просмотра)
void search_pipes_by_name(vector<Pipe>& pipes) {
    string search_name;
    cout << "Enter pipe name to search: ";
    getline(cin, search_name);
    
    bool found = false;
    for (int i = 0; i < pipes.size(); i++) {
        if (pipes[i].get_km_mark().find(search_name) != string::npos) {
            pipes[i].write_to_console();
            found = true;
        }
    }
    if (!found) {
        cout << "No pipes found with name containing: '" << search_name << "'" << endl;
    }
}

void search_pipes_by_repair_status(vector<Pipe>& pipes) {
    int status;
    cout << "Search pipes by repair status (0 - not in repair, 1 - in repair): ";
    cin >> status;
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
        cout << "No pipes found with repair status: " << search_repair << endl;
    }
}

void search_cs_by_name(vector<CompressorStation>& CSes) {
    string search_name;
    cout << "Enter CS name to search: ";
    getline(cin, search_name);
    
    bool found = false;
    for (int i = 0; i < CSes.size(); i++) {
        if (CSes[i].get_name().find(search_name) != string::npos) {
            CSes[i].write_to_console();
            found = true;
        }
    }
    if (!found) {
        cout << "No compressor stations found with name containing: '" << search_name << "'" << endl;
    }
}

void search_cs_by_unused_percent(vector<CompressorStation>& CSes) {
    double min_percent, max_percent;
    cout << "Enter minimum percent of unused workshops: ";
    cin >> min_percent;
    cout << "Enter maximum percent of unused workshops: ";
    cin >> max_percent;
    clear();
    
    bool found = false;
    for (int i = 0; i < CSes.size(); i++) {
        double unused_percent = CSes[i].get_unused_workshop_percent();
        if (unused_percent >= min_percent && unused_percent <= max_percent) {
            CSes[i].write_to_console();
            cout << "Unused workshops: " << unused_percent << "%" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No compressor stations found with unused workshops percentage between " 
             << min_percent << "% and " << max_percent << "%" << endl;
    }
}

void search_objects(vector<Pipe>& pipes, vector<CompressorStation>& CSes) {
    int search_type;
    cout << "\n=== Search Objects ===" << endl;
    cout << "1. Search pipes by name" << endl;
    cout << "2. Search pipes by repair status" << endl;
    cout << "3. Search CS by name" << endl;
    cout << "4. Search CS by unused workshop percentage" << endl;
    cout << "0. Back to main menu" << endl;
    cout << "Choose search type: ";
    
    cin >> search_type;
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

void load_from_file(string filename, vector<Pipe>& pipes, vector<CompressorStation>& CSes) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    pipes.clear();
    CSes.clear();

    string line;
    char object_type = ' ';
    int count = 0;
    int objects_loaded = 0;

    while (getline(in, line)) {
        if (line.empty()) continue;

        if (line[0] == 'P' || line[0] == 'C') {
            object_type = line[0];
            count = stoi(line.substr(2));
            continue;
        }

        if (object_type == 'P' && count > 0) {
            int id = stoi(line);
            
            string km_mark;
            getline(in, km_mark);
            
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
            int id = stoi(line);
            
            string name;
            getline(in, name);
            
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
    cout << "Successfully loaded " << objects_loaded << " objects" << endl;
}

void truncate_file(string filename) {
    ofstream clear_file(filename, ios::out | ios::trunc);
    clear_file.close();
}

void write_to_log(int user_input) {
    ofstream logger("logs.txt", ios::app);
    if (logger.is_open()) {
        logger << user_input << endl;
        logger.close();
    }
}

int main() {
    vector<Pipe> pipes;
    vector<CompressorStation> CSes;
    int user_input;
    string filename;
    
    truncate_file("logs.txt");
    write_to_log(0);

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
            write_to_log(-1);
            clear();
            continue;
        }
        
        write_to_log(user_input);
        clear();
        
        switch (user_input) {
        case 1: {
            cout << "\n=== Adding New Pipe ===" << endl;
            Pipe pipe;
            pipe.read_from_console();
            pipe.assign_id(pipes);
            pipes.push_back(pipe);
            cout << "Pipe added successfully!" << endl;
            break;
        }

        case 2: {
            cout << "\n=== Adding New Compressor Station ===" << endl;
            CompressorStation cs;
            cs.read_from_console();
            cs.assign_id(CSes);
            CSes.push_back(cs);
            cout << "Compressor Station added successfully!" << endl;
            break;
        }

        case 3:
            cout << "\n=== All Objects ===" << endl;
            if (pipes.empty()) {
                cout << "No pipes data available" << endl;
            } else {
                cout << "\n--- Pipes (" << pipes.size() << ") ---" << endl;
                for (int i = 0; i < pipes.size(); i++) {
                    pipes[i].write_to_console();
                }
            }

            if (CSes.empty()) {
                cout << "No compressor stations data available" << endl;
            } else {
                cout << "\n--- Compressor Stations (" << CSes.size() << ") ---" << endl;
                for (int i = 0; i < CSes.size(); i++) {
                    CSes[i].write_to_console();
                }
            }
            break;

        case 4:
            if (pipes.empty()) {
                cout << "No pipe available to modify. Please add a pipe first." << endl;
                break;
            }
            
            cout << "Available pipes:" << endl;
            for (int i = 0; i < pipes.size(); i++) {
                cout << "ID: " << pipes[i].get_id() << " - " << pipes[i].get_km_mark() << endl;
            }
            
            cout << "Enter pipe ID to change status: ";
            int pipe_id;
            if (cin >> pipe_id) {
                bool found = false;
                for (int i = 0; i < pipes.size(); i++) {
                    if (pipes[i].get_id() == pipe_id) {
                        pipes[i].change_status();
                        found = true;
                        break;
                    }
                }
                if (!found) {
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
            for (int i = 0; i < CSes.size(); i++) {
                cout << "ID: " << CSes[i].get_id() << " - " << CSes[i].get_name() << endl;
            }
            
            cout << "Enter CS ID to manage: ";
            int cs_id;
            if (cin >> cs_id) {
                bool found = false;
                for (int i = 0; i < CSes.size(); i++) {
                    if (CSes[i].get_id() == cs_id) {
                        CSes[i].print_workshop_managment();
                        cout << "1. Start workshop" << endl;
                        cout << "2. Stop workshop" << endl;

                        int cs_action;
                        cout << "Choose action: ";
                        if (cin >> cs_action) {
                            if (cs_action == 1) {
                                CSes[i].start_workshop();
                            } else if (cs_action == 2) {
                                CSes[i].stop_workshop();
                            } else {
                                cout << "Invalid action!" << endl;
                            }
                        } else {
                            cout << "Invalid input!" << endl;
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) {
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
                for (int i = 0; i < pipes.size(); i++) {
                    pipes[i].save_to_file(filename);
                }
                cout << "Saved " << pipes.size() << " pipes" << endl;
            }
            
            if (!CSes.empty()) {
                ofstream out(filename, ios::app);
                out << "C " << CSes.size() << endl;
                out.close();
                for (int i = 0; i < CSes.size(); i++) {
                    CSes[i].save_to_file(filename);
                }
                cout << "Saved " << CSes.size() << " compressor stations" << endl;
            }
            break;

        case 7:
            cout << "Enter filename: ";
            getline(cin, filename);
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
            truncate_file(filename);
            cout << "Successfully truncated the file" << endl;
            break;

        case 0:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
            
        default:
            cout << "Input is incorrect. Please try digits in range [0-10]" << endl;
        }
    }
    return 0;
}