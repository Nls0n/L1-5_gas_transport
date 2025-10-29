#ifndef SEARCH_H
#define SEARCH_H

#include "Pipe.h"
#include "CompressorStation.h"
#include <vector>

// Функции поиска для просмотра
void search_pipes_by_name(std::vector<Pipe>& pipes);
void search_pipes_by_repair_status(std::vector<Pipe>& pipes);
void search_cs_by_name(std::vector<CompressorStation>& CSes);
void search_cs_by_unused_percent(std::vector<CompressorStation>& CSes);
void search_objects(std::vector<Pipe>& pipes, std::vector<CompressorStation>& CSes);

// Функции для пакетного редактирования
std::vector<int> search_pipes_by_name_for_batch(std::vector<Pipe>& pipes);
std::vector<int> search_pipes_by_repair_status_for_batch(std::vector<Pipe>& pipes);
void batch_change_repair_status(std::vector<Pipe>& pipes, std::vector<int> pipe_ids);
void batch_change_diameter(std::vector<Pipe>& pipes, std::vector<int> pipe_ids);
void batch_delete_pipes(std::vector<Pipe>& pipes, std::vector<int> pipe_ids);
void batch_edit_pipes(std::vector<Pipe>& pipes);

#endif