#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

struct entry_t {
    int age;
    bool phage;
};

void parse_csv(const char* filename, std::vector<entry_t> &d);
int calc_change(const std::vector<entry_t> d1, const std::vector<entry_t> d2);

#endif
