#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include "pipe.h"
#include "compressor_station.h"

struct Connection {
    int pipe_id;
    int start_cs_id;
    int end_cs_id;
    bool is_active;
    
    // Конструктор по умолчанию
    Connection() : pipe_id(0), start_cs_id(0), end_cs_id(0), is_active(false) {}
    
    // Конструктор с параметрами
    Connection(int p_id, int start_id, int end_id) 
        : pipe_id(p_id), start_cs_id(start_id), end_cs_id(end_id), is_active(true) {}
};

class GasNetwork {
private:
    std::unordered_map<int, std::vector<int>> adjacency_list;  // Граф: CS_id -> список смежных CS
    std::unordered_map<int, Connection> connections;  // Хранилище соединений
    std::set<int> valid_diameters = {500, 700, 1000, 1400};  // Допустимые диаметры
    
public:
    // Основные методы
    bool connect_stations(int start_cs_id, int end_cs_id, int diameter, 
                         std::unordered_map<int, Pipe>& pipes);
    
    // Поиск и создание труб
    int find_available_pipe(int diameter, std::unordered_map<int, Pipe>& pipes);
    void create_and_connect_pipe(int start_cs_id, int end_cs_id, int diameter,
                                std::unordered_map<int, Pipe>& pipes);
    
    // Отображение сети
    void display_network(const std::unordered_map<int, CompressorStation>& CSes,
                        const std::unordered_map<int, Pipe>& pipes) const;
    void display_connections() const;
    
    // Топологическая сортировка
    std::vector<int> topological_sort(const std::unordered_map<int, CompressorStation>& CSes) const;
    
    // Вспомогательные методы
    bool has_cycle() const;
    bool cs_exists(int cs_id, const std::unordered_map<int, CompressorStation>& CSes) const;
    bool is_diameter_valid(int diameter) const;
    int get_next_connection_id() const { return connections.size() + 1; }
    
    // Геттеры
    const std::unordered_map<int, std::vector<int>>& get_adjacency_list() const { return adjacency_list; }
    const std::unordered_map<int, Connection>& get_connections() const { return connections; }
};

#endif