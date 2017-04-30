#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

struct entry_t {
    int age;
    bool phage;
    int pos;
};

bool sort_age(entry_t e1, entry_t e2);
bool sort_pos(entry_t e1, entry_t e2);

int sum_age(const std::vector<entry_t> &d, int start, int len);
int mean_age(const std::vector<entry_t> &d, int start, int len);
int opt_age(const std::vector<entry_t> &d, int start, int len);

void parse_csv(const char* filename, std::vector<entry_t> &d);
void write_csv(const char* filename, const std::vector<entry_t> &d);

int calc_change(const std::vector<entry_t> d1, const std::vector<entry_t> d2);

#endif
