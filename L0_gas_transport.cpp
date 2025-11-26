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

using namespace std;

// Глобальная переменная для лог-файла
ofstream log_file;
string log_filename;

void initialize_logging() {
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    tm local_time = *localtime(&time);
    
    ostringstream filename_stream;
    filename_stream << "logs_"
                   << setfill('0') << setw(2) << local_time.tm_mday
                   << setfill('0') << setw(2) << (local_time.tm_mon + 1)
                   << (local_time.tm_year + 1900) << "_"
                   << setfill('0') << setw(2) << local_time.tm_hour
                   << setfill('0') << setw(2) << local_time.tm_min
                   << setfill('0') << setw(2) << local_time.tm_sec << ".txt";
    log_filename = filename_stream.str();
    
    log_file.open(log_filename);
}

void close_logging() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void write_to_log(const string& message) {
    if (log_file.is_open()) {
        log_file << message << endl;
    }
}

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
        write_to_log(km_mark);
        
        cout << "Input pipe length: ";
        input_positive(length);
        write_to_log(to_string(length));
        
        cout << "Input pipe diameter: ";
        input_positive(diameter);
        write_to_log(to_string(diameter));
        
        cout << "Input is_in_repair status: ";
        while (!(cin >> is_in_repair)) {
            clear();
            cout << "Invalid input. Enter 1 or 0: ";
        }
        write_to_log(to_string(is_in_repair));
        clear();
    }

    bool validate_km_mark() const {
        return (km_mark != "");
    }

    void assign_id(const unordered_map<int, Pipe>& pipes) {
        if (pipes.empty()) {
            id = 1;
        } else {
            int max_id = 0;
            for (const auto& pair : pipes) {
                if (pair.first > max_id) {
                    max_id = pair.first;
                }
            }
            id = max_id + 1;
        }
    }

    void write_to_console() const {
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

    void save_to_file(string filename) const {
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

    int get_id() const { return id; }
    string get_km_mark() const { return km_mark; }
    bool get_is_in_repair() const { return is_in_repair; }
    float get_length() const { return length; }
    int get_diameter() const { return diameter; }
    
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
        write_to_log(name);
        
        cout << "Input workshop_count: ";
        input_positive(workshop_count);
        write_to_log(to_string(workshop_count));
        
        cout << "Input current_working_workshop_count: ";
        do {
            input_positive(current_working_workshop_count);
            if (current_working_workshop_count > workshop_count) {
                cout << "current_working_workshop_count must be less or equal to workshop_count, try again" << endl;
                cout << "Input current_working_workshop_count: ";
            }
        } while (current_working_workshop_count > workshop_count);
        write_to_log(to_string(current_working_workshop_count));
        
        cout << "Input station_cls: ";
        input_positive(station_cls);
        write_to_log(to_string(station_cls));
    }

    bool validate_name() const {
        return (name != "");
    }

    void write_to_console() const {
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

    void save_to_file(string filename) const { 
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

    void print_workshop_managment() const {
        cout << "Current working workshops: " << current_working_workshop_count << " / " << workshop_count << endl;
    }

    void assign_id(const unordered_map<int, CompressorStation>& CSes) {
        if (CSes.empty()) {
            id = 1;
        } else {
            int max_id = 0;
            for (const auto& pair : CSes) {
                if (pair.first > max_id) {
                    max_id = pair.first;
                }
            }
            id = max_id + 1;
        }
    }

    int get_id() const { return id; }
    string get_name() const { return name; }
    int get_workshop_count() const { return workshop_count; }
    int get_current_working_workshop_count() const { return current_working_workshop_count; }
    
    double get_unused_workshop_percent() const {
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

void load_from_file(string filename, unordered_map<int, Pipe>& pipes, unordered_map<int, CompressorStation>& CSes) {
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
            pipes[id] = pipe;
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
            CSes[id] = cs;
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