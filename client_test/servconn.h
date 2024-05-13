#pragma once

#include <iostream>
#include "errproc.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <filesystem>
#include <fstream>
#include <string>

#define MAX_PARAMS 4
#define MAX_PARAM_LENGTH 65536

//Fetch Recipes
#define REC r
//Fetch Notes
#define NT n
//Fetch Products
#define PROD p

#define BUF_SIZE MAX_PARAMS*MAX_PARAM_LENGTH+30

using namespace std;

struct Command {
    char keyword[20];
    int num_params;
    char params[MAX_PARAMS][MAX_PARAM_LENGTH];
};

void serialize_command(const struct Command *cmd, char *buffer, int buffer_size);

void deserialize_command(const char *buffer, int buffer_size, struct Command *cmd);



class Server_connection{
    private:
        int _fd;
        int _port;
        string _ip;
        string login;
        
    public:
        Server_connection(string ip = "127.0.0.1", int port = 1488, string _login = "guest");
        void reconnect();
        bool Register(string login, string passwd);
        bool Auth(string login, string passwd);
        bool Fetch_data(string _path, string data_type);
        bool Update_products(string _path);
        bool Create_note(string _path);
        bool Update_note(string _path);
        bool Delete_note(string _path);
        ~Server_connection();
};
