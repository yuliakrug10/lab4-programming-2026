#pragma once
#include "operations.h"
#include <string>
#include <vector>
#include <random>

struct Frequencies {
    double read_first;
    double write_first;
    double read_second;
    double write_second;
    double string_request;
};

std::string make_file_name(const std::string& scenario, int thread_count, int thread_index);

void generate_file(const std::string& file_name, int operation_count, const Frequencies& frequencies, std::mt19937& generator);

void generate_scenario(const std::string& scenario, int total_operations, const Frequencies& frequencies, std::mt19937& generator);

std::vector<Operation> read_file(const std::string& file_name);
