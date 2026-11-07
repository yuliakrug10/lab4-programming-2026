#include "file_operations.h"
#include <fstream>

std::string make_file_name(const std::string& scenario, int thread_count, int thread_index) {
    return scenario + "_" + std::to_string(thread_count) + "_" + std::to_string(thread_index) + ".txt";
}

void generate_file(const std::string& file_name, int operation_count, const Frequencies& frequencies, std::mt19937& generator) {
    std::discrete_distribution<int> distribution({
        frequencies.read_first,
        frequencies.write_first,
        frequencies.read_second,
        frequencies.write_second,
        frequencies.string_request
        });
    std::ofstream output(file_name);
    for (int i = 0; i < operation_count; i++) {
        int choice = distribution(generator);
        if (choice == 0) {
            output << "read 0\n";
        }
        else if (choice == 1) {
            output << "write 0 1\n";
        }
        else if (choice == 2) {
            output << "read 1\n";
        }
        else if (choice == 3) {
            output << "write 1 1\n";
        }
        else {
            output << "string\n";
        }
    }
}

void generate_scenario(const std::string& scenario, int total_operations, const Frequencies& frequencies, std::mt19937& generator) {
    for (int thread_count = 1; thread_count <= 3; thread_count++) {
        for (int thread_index = 0; thread_index < thread_count; thread_index++) {
            generate_file(make_file_name(scenario, thread_count, thread_index), total_operations / thread_count, frequencies, generator);
        }
    }
}

std::vector<Operation> read_file(const std::string& file_name) {
    std::ifstream input(file_name);
    std::vector<Operation> operations;
    std::string command;
    while (input >> command) {
        Operation operation;
        operation.field = 0;
        operation.value = 0;
        if (command == "read") {
            operation.type = OperationType::read;
            input >> operation.field;
        }
        else if (command == "write") {
            operation.type = OperationType::write;
            input >> operation.field >> operation.value;
        }
        else {
            operation.type = OperationType::string;
        }
        operations.push_back(operation);
    }
    return operations;
}