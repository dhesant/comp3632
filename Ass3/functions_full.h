#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

struct entry_t {
    uint index;
    int data[5];
    bool phage;
};

bool sort_index(entry_t e1, entry_t e2);

void print_entry(const entry_t &e);

void parse_csv(const char* filename, std::vector<entry_t> &d);
void write_csv(const char* filename, const std::vector<entry_t> &d);

int calc_change (const std::vector<entry_t> d1, const std::vector<entry_t> d2);

std::vector<std::vector<entry_t>> split_vector(const std::vector<std::vector<entry_t>> &v, int index);

#endif
