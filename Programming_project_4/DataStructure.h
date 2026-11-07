#pragma once
#include <string>
#include <shared_mutex>

class DataStructure
{
public:
	DataStructure();
	int get(int index) const;
	void set(int index, int value);
	operator std::string() const;
private:
	static const int field_count = 2;
	struct alignas(64) Field {
		mutable std::shared_mutex mutex;
		int value;
	};

	Field fields[field_count];
};

