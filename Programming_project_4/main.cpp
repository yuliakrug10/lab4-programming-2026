// Kruhlienia Yulia K-28
#include <iostream>
#include <format>
#include <random>
#include "file_operations.h"
#include "time_measure.h"

using namespace std;

int main() {

    const int total_operations = 300000;
    const int run_count = 5;

    mt19937 generator(random_device{}());

    Frequencies variant = { 10, 5, 50, 10, 25 };
    Frequencies equal = { 20, 20, 20, 20, 20 };
    Frequencies different = { 40, 40, 5, 10, 5 };

    generate_scenario("a", total_operations, variant, generator);
    generate_scenario("b", total_operations, equal, generator);
    generate_scenario("c", total_operations, different, generator);

    cout << "Total operations: " << total_operations << ", runs: " << run_count << "\n";
    cout << "Average time in ms\n";
    cout << format("{:<16}{:>12}{:>12}{:>12}\n", "Scenario", "1 thread", "2 threads", "3 threads");

    print_row("a) variant 15", "a", run_count);
    print_row("b) equal", "b", run_count);
    print_row("c) different", "c", run_count);

	return 0;
}