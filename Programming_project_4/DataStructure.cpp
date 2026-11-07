#include "DataStructure.h"
#include <mutex> 

DataStructure::DataStructure() {
    for (int i = 0; i < field_count; i++) {
        fields[i].value = 0;
    }
}

int DataStructure::get(int index) const {
    std::shared_lock<std::shared_mutex> lock(fields[index].mutex);
    return fields[index].value;
}

void DataStructure::set(int index, int value) {
    std::unique_lock<std::shared_mutex> lock(fields[index].mutex);
    fields[index].value = value;
}

DataStructure::operator std::string() const {
    int first;
    int second;
    {
        std::shared_lock<std::shared_mutex> lock_first(fields[0].mutex);
        std::shared_lock<std::shared_mutex> lock_second(fields[1].mutex);
        first = fields[0].value;
        second = fields[1].value;
    }
    return std::to_string(first) + " " + std::to_string(second);
}
