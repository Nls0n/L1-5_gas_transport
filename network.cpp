#include "network.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

bool GasNetwork::connect_stations(int start_cs_id, int end_cs_id, int diameter, 
                                 unordered_map<int, Pipe>& pipes) {
    // Проверка на петли
    if (start_cs_id == end_cs_id) {
        cout << "Error: Cannot connect a station to itself!" << endl;
        return false;
    }
    
    // Проверка валидности диаметра
    if (!is_diameter_valid(diameter)) {
        cout << "Error: Invalid diameter! Valid diameters are: 500, 700, 1000, 1400 mm" << endl;
        return false;
    }
    
    // Поиск доступной трубы
    int pipe_id = find_available_pipe(diameter, pipes);
    
    if (pipe_id != -1) {
        // Используем существующую трубу
        Connection conn(pipe_id, start_cs_id, end_cs_id);
        connections.insert({get_next_connection_id(), conn});  // Используем insert вместо operator[]
        pipes[pipe_id].set_connected(true);
        
        // Добавляем ребро в граф
        adjacency_list[start_cs_id].push_back(end_cs_id);
        
        cout << "Connected CS " << start_cs_id << " to CS " << end_cs_id 
             << " using existing pipe ID " << pipe_id << endl;
        return true;
    } else {
        // Создаем новую трубу
        create_and_connect_pipe(start_cs_id, end_cs_id, diameter, pipes);
        return true;
    }
}

int GasNetwork::find_available_pipe(int diameter, unordered_map<int, Pipe>& pipes) {
    for (auto& pair : pipes) {
        Pipe& pipe = pair.second;
        // Ищем свободную трубу нужного диаметра, не в ремонте
        if (pipe.get_diameter() == diameter && 
            !pipe.get_is_connected() && 
            !pipe.get_is_in_repair()) {
            return pair.first;
        }
    }
    return -1; // Не найдена подходящая труба
}

void GasNetwork::create_and_connect_pipe(int start_cs_id, int end_cs_id, int diameter,
                                        unordered_map<int, Pipe>& pipes) {
    cout << "\n=== Creating new pipe for connection ===" << endl;
    
    // Создаем новую трубу
    Pipe new_pipe;
    new_pipe.read_from_console();
    
    // Устанавливаем указанный диаметр
    new_pipe.set_diameter(diameter);
    
    // Назначаем ID
    new_pipe.assign_id(pipes);
    
    // Помечаем как подключенную
    new_pipe.set_connected(true);
    
    // Сохраняем трубу
    int pipe_id = new_pipe.get_id();
    pipes[pipe_id] = new_pipe;
    
    // Создаем соединение с использованием insert
    Connection conn(pipe_id, start_cs_id, end_cs_id);
    connections.insert({get_next_connection_id(), conn});
    
    // Добавляем ребро в граф
    adjacency_list[start_cs_id].push_back(end_cs_id);
    
    cout << "Created new pipe ID " << pipe_id << " and connected CS " 
         << start_cs_id << " to CS " << end_cs_id << endl;
}

void GasNetwork::display_network(const unordered_map<int, CompressorStation>& CSes,
                                const unordered_map<int, Pipe>& pipes) const {
    cout << "\n=== Gas Transmission Network ===" << endl;
    
    if (adjacency_list.empty()) {
        cout << "Network is empty. No connections yet." << endl;
        return;
    }
    
    for (const auto& node : adjacency_list) {
        int cs_id = node.first;
        
        auto cs_it = CSes.find(cs_id);
        if (cs_it != CSes.end()) {
            cout << "CS " << cs_id << " (" << cs_it->second.get_name() << ") -> ";
        } else {
            cout << "CS " << cs_id << " (deleted) -> ";
        }
        
        const auto& neighbors = node.second;
        for (size_t i = 0; i < neighbors.size(); ++i) {
            int neighbor_id = neighbors[i];
            auto neighbor_it = CSes.find(neighbor_id);
            
            if (neighbor_it != CSes.end()) {
                cout << neighbor_id << " (" << neighbor_it->second.get_name() << ")";
            } else {
                cout << neighbor_id << " (deleted)";
            }
            
            if (i < neighbors.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    
    // Показываем информацию о соединениях
    if (!connections.empty()) {
        cout << "\n=== Connections Details ===" << endl;
        display_connections();
    }
}

void GasNetwork::display_connections() const {
    for (const auto& conn_pair : connections) {
        const Connection& conn = conn_pair.second;
        cout << "Connection ID: " << conn_pair.first 
             << " | Pipe: " << conn.pipe_id 
             << " | From CS: " << conn.start_cs_id 
             << " -> To CS: " << conn.end_cs_id 
             << " | Active: " << (conn.is_active ? "Yes" : "No") << endl;
    }
}

vector<int> GasNetwork::topological_sort(const unordered_map<int, CompressorStation>& CSes) const {
    vector<int> result;
    
    if (adjacency_list.empty()) {
        return result;
    }
    
    // Вычисляем полустепени захода (in-degree)
    unordered_map<int, int> in_degree;
    
    // Инициализируем in_degree для всех узлов (включая изолированные)
    for (const auto& cs_pair : CSes) {
        in_degree[cs_pair.first] = 0;
    }
    
    // Вычисляем in_degree
    for (const auto& node : adjacency_list) {
        for (int neighbor : node.second) {
            in_degree[neighbor]++;
        }
    }
    
    // Очередь вершин с нулевым in_degree
    queue<int> zero_in_degree;
    for (const auto& degree_pair : in_degree) {
        if (degree_pair.second == 0) {
            zero_in_degree.push(degree_pair.first);
        }
    }
    
    // Алгоритм Кана
    while (!zero_in_degree.empty()) {
        int current = zero_in_degree.front();
        zero_in_degree.pop();
        result.push_back(current);
        
        if (adjacency_list.find(current) != adjacency_list.end()) {
            for (int neighbor : adjacency_list.at(current)) {
                in_degree[neighbor]--;
                if (in_degree[neighbor] == 0) {
                    zero_in_degree.push(neighbor);
                }
            }
        }
    }
    
    // Проверка на циклы
    if (result.size() != CSes.size()) {
        cout << "Warning: Graph has cycles! Topological sort may be incomplete." << endl;
    }
    
    return result;
}

bool GasNetwork::has_cycle() const {
    unordered_map<int, int> visited; // 0 - не посещена, 1 - посещается, 2 - обработана
    stack<pair<int, int>> dfs_stack; // пара (вершина, индекс следующего соседа)
    
    // Инициализация
    for (const auto& node : adjacency_list) {
        visited[node.first] = 0;
    }
    
    // DFS для каждой вершины
    for (const auto& node : adjacency_list) {
        if (visited[node.first] == 0) {
            dfs_stack.push({node.first, 0});
            
            while (!dfs_stack.empty()) {
                auto& current = dfs_stack.top();
                int vertex = current.first;
                
                if (current.second == 0) {
                    visited[vertex] = 1; // Начинаем обработку
                }
                
                if (adjacency_list.find(vertex) != adjacency_list.end() && 
                    current.second < adjacency_list.at(vertex).size()) {
                    
                    int neighbor = adjacency_list.at(vertex)[current.second];
                    current.second++;
                    
                    if (visited[neighbor] == 1) {
                        return true; // Найден цикл
                    }
                    
                    if (visited[neighbor] == 0) {
                        dfs_stack.push({neighbor, 0});
                    }
                } else {
                    visited[vertex] = 2; // Завершили обработку
                    dfs_stack.pop();
                }
            }
        }
    }
    
    return false;
}

bool GasNetwork::cs_exists(int cs_id, const unordered_map<int, CompressorStation>& CSes) const {
    return CSes.find(cs_id) != CSes.end();
}

bool GasNetwork::is_diameter_valid(int diameter) const {
    return valid_diameters.find(diameter) != valid_diameters.end();
}