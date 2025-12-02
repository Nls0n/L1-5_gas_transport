#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <unordered_map>

// Предварительное объявление классов
class Pipe;
class CompressorStation;

// Функции для работы с вводом
void clear();
template<typename T>
void input_positive(T& var);
bool input_valid_diameter(int& diameter);  // Новая функция

// Функции для логирования
void initialize_logging();
void close_logging();
void write_to_log(const std::string& message);

// Функции для работы с файлами
void load_from_file(std::string filename, std::unordered_map<int, Pipe>& pipes, 
                   std::unordered_map<int, CompressorStation>& CSes);
void truncate_file(std::string filename);

#endif