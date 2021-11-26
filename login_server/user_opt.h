#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <string>

void AddUser(const char* _name, const char* _password);
bool CheckUser(const char* _name, const char* _password_dgst);
std::string CreateContainer(int _room_no);
std::string CheckRoom(const char* _room_no);
