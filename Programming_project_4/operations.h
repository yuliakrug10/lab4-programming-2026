#pragma once

enum class OperationType {
    read,
    write,
    string
};

struct Operation {
    OperationType type;
    int field;
    int value;
};
