#ifndef SEARCH_UTILS_H
#define SEARCH_UTILS_H

#include <unordered_map>
#include <vector>
#include "pipe.h"
#include "compressor_station.h"

// Функции поиска
void search_objects(const std::unordered_map<int, Pipe>& pipes, 
                   const std::unordered_map<int, CompressorStation>& CSes);
void search_pipes_by_name(const std::unordered_map<int, Pipe>& pipes);
void search_pipes_by_repair_status(const std::unordered_map<int, Pipe>& pipes);
void search_cs_by_name(const std::unordered_map<int, CompressorStation>& CSes);
void search_cs_by_unused_percent(const std::unordered_map<int, CompressorStation>& CSes);

// Функции пакетного редактирования
void batch_edit_pipes(std::unordered_map<int, Pipe>& pipes);
std::vector<int> search_pipes_by_name_for_batch(std::unordered_map<int, Pipe>& pipes);
std::vector<int> search_pipes_by_repair_status_for_batch(std::unordered_map<int, Pipe>& pipes);
void batch_change_repair_status(std::unordered_map<int, Pipe>& pipes, std::vector<int> pipe_ids);
void batch_change_diameter(std::unordered_map<int, Pipe>& pipes, std::vector<int> pipe_ids);
void batch_delete_pipes(std::unordered_map<int, Pipe>& pipes, std::vector<int> pipe_ids);

#endif