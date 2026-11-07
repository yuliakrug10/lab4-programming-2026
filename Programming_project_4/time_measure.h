#pragma once
#include <string>
#include <vector>
#include "DataStructure.h"
#include "operations.h"


void execute(DataStructure& data, const std::vector<Operation>& operations, long long& checksum);

double measure(const std::string& scenario, int thread_count);

double measure_average(const std::string& scenario, int thread_count, int run_count);

void print_row(const std::string& title, const std::string& scenario, int run_count);

