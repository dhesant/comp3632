#ifndef _DECRYPT_LIBRARY_H
#define _DECRYPT_LIBRARY_H

char decrypt_byte(const char* y);
char* decrypt_block(const char* y);
char** decrypt(const char* iv, const std::vector<char*> y);
bool oracle(char* block, int len);

#endif
