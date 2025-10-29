#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "Pipe.h"
#include "CompressorStation.h"
#include <vector>
#include <string>

void load_from_file(std::string filename, std::vector<Pipe>& pipes, std::vector<CompressorStation>& CSes);
void truncate_file(std::string filename);
void write_to_log(int user_input);

#endif