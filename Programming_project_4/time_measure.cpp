#include "time_measure.h"
#include "file_operations.h"
#include <iostream>
#include <format>
#include <thread>
#include <chrono>
#include <functional>

using namespace std;

void execute(DataStructure& data, const vector<Operation>& operations, long long& checksum) {
    long long sum = 0;
    for (const Operation& operation : operations) {
        if (operation.type == OperationType::read) {
            sum += data.get(operation.field);
        }
        else if (operation.type == OperationType::write) {
            data.set(operation.field, operation.value);
        }
        else {
            string text = data;
            sum += static_cast<long long>(text.size());
        }
    }
    checksum = sum;
}

double measure(const string& scenario, int thread_count) {
    vector<vector<Operation>> operations_per_thread;
    for (int thread_index = 0; thread_index < thread_count; thread_index++) {
        operations_per_thread.push_back(read_file(make_file_name(scenario, thread_count, thread_index)));
    }

    DataStructure data;
    vector<long long> checksums(thread_count, 0);
    vector<thread> threads;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    for (int thread_index = 0; thread_index < thread_count; thread_index++) {
        threads.emplace_back(execute, ref(data), cref(operations_per_thread[thread_index]), ref(checksums[thread_index]));
    }
    for (thread& thread : threads) {
        thread.join();
    }
    chrono::steady_clock::time_point finish = chrono::steady_clock::now();

    return chrono::duration<double, milli>(finish - start).count();
}

double measure_average(const string& scenario, int thread_count, int run_count) {
    double total = 0;
    for (int run = 0; run < run_count; run++) {
        total += measure(scenario, thread_count);
    }
    return total / run_count;
}

void print_row(const string& title, const string& scenario, int run_count) {
    cout << format("{:<16}", title);
    for (int thread_count = 1; thread_count <= 3; thread_count++) {
        cout << format("{:>12.2f}", measure_average(scenario, thread_count, run_count));
    }
    cout << "\n";
}
