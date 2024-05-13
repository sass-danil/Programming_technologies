/*
 * server.cpp
 *
 *  Created on: 23 февр. 2024 г.
 *      Author: c0nt1nyou
 */

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

#define MAX_PARAMS 4
#define MAX_PARAM_LENGTH 65536
#define BUF_SIZE MAX_PARAMS*MAX_PARAM_LENGTH+30

struct Command {
    char keyword[20];
    int num_params;
    char params[MAX_PARAMS][MAX_PARAM_LENGTH];
};

void serialize_command(const struct Command *cmd, char *buffer, int buffer_size) {
    int offset = 0;

    // Копируем ключевое слово в буфер
    strncpy(buffer + offset, cmd->keyword, strlen(cmd->keyword) + 1);
    offset += strlen(cmd->keyword) + 1;

    // Копируем количество параметров в буфер
    strncpy(buffer + offset, to_string(cmd->num_params).c_str(), strlen(to_string(cmd->num_params).c_str()));
    offset += strlen(to_string(cmd->num_params).c_str());
    buffer[offset++] = '\0'; // Разделитель после числа параметров

    // Копируем каждый параметр в буфер
    for (int i = 0; i < cmd->num_params; ++i) {
        strncpy(buffer + offset, cmd->params[i], strlen(cmd->params[i]) + 1);
        offset += strlen(cmd->params[i]) + 1;
    }
    buffer[offset] = '\0'; // Завершаем строку
}

void deserialize_command(const char *buffer, int buffer_size, struct Command *cmd) {
    int offset = 0;

    int i = 0;
    while (buffer[offset] != '\0') {
        cmd->keyword[i++] = buffer[offset++];
    }
    cmd->keyword[i] = '\0';
    ++offset; // Пропускаем разделитель числа параметров

    // Считываем число параметров
    char num[10];
    i = 0;
    while (buffer[offset] != '\0') {
        num[i++] = buffer[offset++];
    }
    num[i] = '\0';
    cmd->num_params = stoi(num);
    ++offset; // Пропускаем разделитель после числа параметров

    // Считываем каждый параметр
    for (int j = 0; j < cmd->num_params; ++j) {
        i = 0;
        while (buffer[offset] != '\0') {
            cmd->params[j][i++] = buffer[offset++];
        }
        cmd->params[j][i] = '\0';
        ++offset; // Пропускаем разделитель между параметрами
    }
}

int server;
int fd;
bool is_running = true;

void CloseAll(){
	is_running = false;
	close(fd);
	close(server);
}

void KillHandler(int signum){
	CloseAll();
	printf("Killed, allright!\n");
	exit(EXIT_SUCCESS);
}

int Socket(int domain, int type, int protocol){
	int res = socket(domain, type, protocol);
	if(res == -1){
		perror("Socket failed");
		CloseAll();
		exit(EXIT_FAILURE);
	}
	return res;
}

void Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen){
	int res = bind(sockfd, addr, addrlen);
	if(res == -1){
		perror("Binding failed");
		CloseAll();
		exit(EXIT_FAILURE);
	}
}

void Listen(int sockfd, int backlog){
	int res = listen(sockfd, backlog);
	if(res == -1){
		perror("Listening failed");
		CloseAll();
		exit(EXIT_FAILURE);
	}
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
	int res = accept(sockfd, addr, addrlen);
	if(res == -1){
		perror("Listening failed");
		CloseAll();
		exit(EXIT_FAILURE);
	}
	return res;
}

bool Register(string login, string passwd);
bool Auth(string login, string passwd);
bool Fetch_data(string login, string data_type, string filenames, struct Command* cmd);
bool Update_products(string login, string text);
bool Create_note(string login, string data, string filename);
bool Update_note(string login, string data, string filename);
bool Delete_note(string login, string filename);

int main(){
	signal(SIGKILL, KillHandler);
	signal(SIGINT, KillHandler);
	server = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1488);
	Bind(server, (struct sockaddr*)&addr, sizeof addr);
	Listen(server, 5);
	while(is_running){
		socklen_t addrlen = sizeof addr;
		fd = Accept(server, (struct sockaddr*)&addr, &addrlen);
		ssize_t nread;
		char rbuf[BUF_SIZE];
		char sbuf[BUF_SIZE];
		nread = recv(fd, rbuf, BUF_SIZE, 0);
		if(nread == -1){
			perror("Reading failed");
			CloseAll();
			exit(EXIT_FAILURE);
		}
		if(nread == 0){
			printf("EOF\n");
		}

		struct Command rcmd = {};
		struct Command scmd = {};

		deserialize_command(rbuf, sizeof(rbuf), &rcmd);

		cout << endl << "KEYWORD: " << rcmd.keyword << endl;
		cout << "PARAM1: " << rcmd.params[0] << endl;
		cout << "PARAM2: " << rcmd.params[1] << endl;
		cout << "PARAM3: " << rcmd.params[2] << endl;
		cout << "PARAM4: " << rcmd.params[3] << endl;
		cout << "PARAMS_NUM: " << rcmd.num_params << endl << endl;

		if(!strncmp(rcmd.keyword, "register", 8)){
			cout << "REG " << rcmd.params[0] << " " << rcmd.params[1] << endl;
			if(Register(rcmd.params[0], rcmd.params[1])) { scmd.keyword[0] = 'S'; }
			else { scmd.keyword[0] = 'F'; }
		}
		else if(!strncmp(rcmd.keyword, "auth", 4)){
			if(Auth(rcmd.params[0], rcmd.params[1])) { scmd.keyword[0] = 'S'; }
			else { scmd.keyword[0] = 'F'; }
		}
		else if(!strncmp(rcmd.keyword, "fetch", 5)){
			if(Fetch_data(rcmd.params[0], rcmd.params[1], rcmd.params[2], &scmd)) { scmd.keyword[0] = 'S'; }
			else { scmd.keyword[0] = 'F'; }
		}
		else if(!strncmp(rcmd.keyword, "update", 6)){
			if(Update_products(rcmd.params[0], rcmd.params[1])) { scmd.keyword[0] = 'S'; }
			else { scmd.keyword[0] = 'F'; }
		}
		else if(!strncmp(rcmd.keyword, "create_note", 11)){
			if(Create_note(rcmd.params[0], rcmd.params[1], rcmd.params[2])) { scmd.keyword[0] = 'S'; }
			else { scmd.keyword[0] = 'F'; }
		}
		else if(!strncmp(rcmd.keyword, "update_note", 11)){
			if(Update_note(rcmd.params[0], rcmd.params[1], rcmd.params[2])) { scmd.keyword[0] = 'S'; }
			else { scmd.keyword[0] = 'F'; }
		}
		else if(!strncmp(rcmd.keyword, "delete_note", 11)){
			if(Delete_note(rcmd.params[0], rcmd.params[1])) { scmd.keyword[0] = 'S'; }
			else { scmd.keyword[0] = 'F'; }
		}
		else{
			printf("Wrong cmd input!");
			scmd.keyword[0] = 'F';
		}

		serialize_command(&scmd, sbuf, sizeof(sbuf));

		send(fd, sbuf, sizeof(sbuf), 0);
		printf("\n");


		close(fd);
		sleep(1);
	}
	CloseAll();
	return 0;
}


bool Register(string login, string passwd){

	fstream fs;
	fs.open("ureg.txt", fstream::app);

	if (!fs.is_open()) {
		return false;
	}

	fs << login << ' ' << passwd << '\n';

	fs.close();

	filesystem::path folder = (string)"./" + login;

	filesystem::create_directory(folder);

	folder = (string)"./" + login + "/" + "recipes";

	filesystem::create_directory(folder);

	folder = (string)"./" + login + "/" + "notes";

	filesystem::create_directory(folder);

	return true;
}

bool Auth(string login, string passwd){

	fstream fs;
	fs.open("ureg.txt", fstream::in);

	if (!fs.is_open()) {
		return false;
	}

	string stored_login;
	string stored_passwd;

	while (fs >> stored_login >> stored_passwd) {
		if (stored_login == login && stored_passwd == passwd) {
			fs.close();
			return true;
		}
	}

	fs.close();
	return false;
}

bool Fetch_data(string login, string data_type, string filenames, struct Command* cmd){
	string directory;
	if (data_type == "r") {
		directory = "./recipes/";
	} else if (data_type == "n") {
		directory = "./" + login + "/notes/";
	} else if (data_type == "p") {
		directory = "./" + login + "/products.txt";
		ifstream file(directory);
		if (!file.is_open()) {
			cerr << "Error: could not open the file" << directory << endl;
			return false;
		}
		string file_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		strcpy(cmd->params[0], file_content.c_str());
		cmd->num_params = 1;
		return true;
	} else {
		cerr << "Error: wrong data type" << endl;
		return false;
	}

	vector<string> existing_files;

	for (const auto& entry : filesystem::directory_iterator((filesystem::path)directory)) {
		if (entry.is_regular_file()) {
			existing_files.push_back(entry.path().filename().string());
		}
	}

	istringstream iss(filenames);
	vector<string> client_files;
	string file_name;
	while (getline(iss, file_name)) {
		client_files.push_back(file_name);
	}

	vector<string> new_files;
	for (const auto& file_name : existing_files) {
		if (find(client_files.begin(), client_files.end(), file_name) == client_files.end()) {
			new_files.push_back(file_name);
		}
	}
	if(new_files.empty()){
		cout << "EMPTY FETCH" << endl;
		cmd->num_params = 0;
		return true;
	}
	for (int i = 0; i < min(2, static_cast<int>(new_files.size())); ++i) {
		string file_name = new_files[i];
		ifstream file(directory + file_name);
		if (!file.is_open()) {
			cerr << "Error: could not open the file" << directory + file_name << endl;
			return false;
		}



		string file_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

		strcpy(cmd->params[i * 2], file_name.c_str());
		strcpy(cmd->params[i * 2 + 1], file_content.c_str());
		cout << "FETCHING FILE " << i*2 << ": " << file_name << endl;
		cout << "WITH CONTENT: " << file_content << endl;
		cmd->num_params += 2;

		file.close();
	}

	return true;
}

bool Update_products(string login, string text){
	fstream fs;
	fs.open("./" + login + "/products.txt", fstream::out);

	if (!fs.is_open()) {
		return false;
	}

	fs << text;

	fs.close();

	return true;
}

bool Create_note(string login, string data, string filename){
	fstream fs;
	fs.open("./" + login + "/notes/" + filename, fstream::out);

	if (!fs.is_open()) {
		return false;
	}

	fs << data;

	fs.close();

	return true;
}

bool Update_note(string login, string data, string filename){
	return Create_note(login, data, filename);
}

bool Delete_note(string login, string filename){
	return filesystem::remove("./" + login + "/notes/" + filename);
}
