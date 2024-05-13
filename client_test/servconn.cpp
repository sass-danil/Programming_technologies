#include "servconn.h"

using namespace std;

//void serialize_command(const struct Command *cmd, char *buffer, int buffer_size) {
//    int offset = 0;
//    
//    // Копируем ключевое слово в буфер
//    strncpy(buffer + offset, cmd->keyword, sizeof(cmd->keyword));
//    offset += sizeof(cmd->keyword);
//    
//    // Копируем количество параметров в буфер
//    memcpy(buffer + offset, &(cmd->num_params), sizeof(cmd->num_params));
//    offset += sizeof(cmd->num_params);
//    
//    // Копируем каждый параметр в буфер
//    for (int i = 0; i < cmd->num_params; ++i) {
//        strncpy(buffer + offset, cmd->params[i], sizeof(cmd->params[i]));
//        offset += sizeof(cmd->params[i]);
//    }
//}
//
//void deserialize_command(const char *buffer, int buffer_size, struct Command *cmd) {
//    int offset = 0;
//    
//    // Копируем ключевое слово из буфера в структуру Command
//    strncpy(cmd->keyword, buffer + offset, sizeof(cmd->keyword));
//    offset += sizeof(cmd->keyword);
//    
//    // Копируем количество параметров из буфера в структуру Command
//    memcpy(&(cmd->num_params), buffer + offset, sizeof(cmd->num_params));
//    offset += sizeof(cmd->num_params);
//    
//    // Копируем каждый параметр из буфера в структуру Command
//    for (int i = 0; i < cmd->num_params; ++i) {
//        strncpy(cmd->params[i], buffer + offset, sizeof(cmd->params[i]));
//        offset += sizeof(cmd->params[i]);
//    }
//}

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

//--------------------------------------------------------------------------------------
    
Server_connection::Server_connection(string ip, int port, string _login){
    _ip = ip;
    _port = port;
    _fd = Socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    Inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
    Connect(_fd, (struct sockaddr*) &addr, sizeof(addr));
    login = _login;
}

void Server_connection::reconnect() {
    cout << "RECONNECTING..." << endl;
    // Закрываем текущее соединение и создаем новое
    close(this->_fd);
    this->_fd = Socket(AF_INET, SOCK_STREAM, 0);

    // Устанавливаем соединение с сервером
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->_port);
    inet_aton(this->_ip.c_str(), &addr.sin_addr);
    Connect(this->_fd, (struct sockaddr*)&addr, sizeof addr);
    cout << "RECONNECT SUCCESSFUL" << endl;
}

bool Server_connection::Register(string _login, string passwd){
    struct Command cmd = {};

    strcpy(cmd.keyword, "register");
    strcpy(cmd.params[0], _login.c_str());
    strcpy(cmd.params[1], passwd.c_str());
    cmd.num_params = 2;

    char send_buff [MAX_PARAMS*MAX_PARAM_LENGTH + 52];

    serialize_command(&cmd, send_buff, sizeof(send_buff));
    write(this->_fd, send_buff, sizeof(send_buff));

    char buf[MAX_PARAMS*MAX_PARAM_LENGTH + 52];

    ssize_t nread;
	nread = read(this->_fd, buf, MAX_PARAMS*MAX_PARAM_LENGTH + 52);
    
    struct Command cmd_r;
    deserialize_command(buf, sizeof(buf), &cmd_r);
    cout << cmd_r.keyword[0] << endl;
	if(nread == -1){
		perror("Reading failed");
		exit(EXIT_FAILURE);
	}
    reconnect();
	if(nread == 0){
		printf("EOF\n"); return false;
	}
    if(cmd_r.keyword[0] == 'S'){
        return true;
    } 
    else if(cmd_r.keyword[0] == 'F'){
        return false;
    }
}

bool Server_connection::Auth(string _login, string passwd){
    struct Command cmd = {};

    strcpy(cmd.keyword, "auth");
    strcpy(cmd.params[0], _login.c_str());
    strcpy(cmd.params[1], passwd.c_str());
    cmd.num_params = 2;

    char send_buff [MAX_PARAMS*MAX_PARAM_LENGTH + 52];

    serialize_command(&cmd, send_buff, sizeof(send_buff));
    write(this->_fd, send_buff, sizeof(send_buff));

    char buf[MAX_PARAMS*MAX_PARAM_LENGTH + 52];

    ssize_t nread;
	nread = read(this->_fd, buf, MAX_PARAMS*MAX_PARAM_LENGTH + 52);
    
    struct Command cmd_r;
    deserialize_command(buf, sizeof(buf), &cmd_r);
    reconnect();
	if(nread == -1){
		perror("Reading failed");
		return false;
	}
	if(nread == 0){
		printf("EOF\n"); return false;
	}
    if(cmd_r.keyword[0] == 'S'){
        this->login = _login;
        return true;
    } 
    else if(cmd_r.keyword[0] == 'F'){
        return false;
    }
}

bool Server_connection::Fetch_data(string _path, string data_type){
    struct Command cmd = {};
    strcpy(cmd.keyword, "fetch");
    strcpy(cmd.params[0], login.c_str());
    strcpy(cmd.params[1], data_type.c_str());

    // Путь относительно текущей рабочей директории
    string directory_path = _path; 

    // Получаем текущую рабочую директорию
    filesystem::path current_path = std::filesystem::current_path();

    // Собираем абсолютный путь
    filesystem::path absolute_path = current_path / directory_path;

    if(data_type == "p"){
        cmd.num_params = 2;
        cout << "PRODS REACHED!\n\n";

        char send_buff [MAX_PARAMS*MAX_PARAM_LENGTH + 52];

        serialize_command(&cmd, send_buff, sizeof(send_buff));
        write(this->_fd, send_buff, sizeof(send_buff));

        char buf[MAX_PARAMS*MAX_PARAM_LENGTH + 52];

        ssize_t nread;
	    nread = read(this->_fd, buf, MAX_PARAMS*MAX_PARAM_LENGTH + 52);
        
        struct Command cmd_r;
        deserialize_command(buf, sizeof(buf), &cmd_r);
        reconnect();
	    if(nread == -1){
		    perror("Reading failed");
		    exit(EXIT_FAILURE);
	    }
	    if(nread == 0){
		    printf("EOF\n"); return false;
	    }
        
        cout << "FETCHING:" << endl;
        cout << cmd_r.keyword << endl;
        cout << cmd_r.params[0] << endl;
        cout << cmd_r.num_params << endl;

        FILE* f = fopen(_path.c_str(), "w");
        fputs(cmd_r.params[0], f);
        fclose(f);
        return true;
    }
    cmd.num_params = 3;

    std::vector<std::string> file_names;

    for (const auto& entry : filesystem::directory_iterator(absolute_path)) {
        if (entry.is_regular_file()) {
            file_names.push_back(entry.path().filename().string());
        }
    }

    // Выводим содержимое списка
    string buffer;
    
    for (const auto& file_name : file_names) {
        buffer.append(file_name + '\n');
    }

    /*

       Названия имеющихся файлов передается на сервер ->
    -> сервер считает названия файлов и передаст два новых файла
       [чет] - название файла [нечет] - содержание файла ->
    -> клиент посылает рекусивно команду fetch пока параметров в ответе не будет 0

    */
    
    strcpy(cmd.params[2], buffer.c_str());

    cout << cmd.params[2] << endl;

    char send_buff [MAX_PARAMS*MAX_PARAM_LENGTH + 52];

    serialize_command(&cmd, send_buff, sizeof(send_buff));
    write(this->_fd, send_buff, sizeof(send_buff));

    char buf[MAX_PARAMS*MAX_PARAM_LENGTH + 52];

    ssize_t nread;
	nread = read(this->_fd, buf, MAX_PARAMS*MAX_PARAM_LENGTH + 52);
    
    struct Command cmd_r;
    deserialize_command(buf, sizeof(buf), &cmd_r);
    reconnect();
	if(nread == -1){
		perror("Reading failed");
		exit(EXIT_FAILURE);
	}
	if(nread == 0){
		printf("EOF\n"); return false;
	}
    
    cout << "FETCHING:" << endl;
    cout << cmd_r.keyword << endl;
    cout << cmd_r.params[0] << endl;
    cout << cmd_r.params[1] << endl;
    cout << cmd_r.params[2] << endl;
    cout << cmd_r.params[3] << endl;
    cout << cmd_r.num_params << endl;

    if(cmd_r.num_params == 0){
        return true;
    }
    if(cmd_r.keyword[0] == 'S'){
        FILE* f = fopen(((string)_path + "/" + cmd_r.params[0]).c_str(), "w");
        fputs(cmd_r.params[1], f);
        fclose(f);
        if(cmd_r.num_params > 2){
            f = fopen(((string)_path + "/" + cmd_r.params[2]).c_str(), "w");
            fputs(cmd_r.params[3], f);
            fclose(f);
        }
        if(cmd_r.num_params == 2){
            return true;
        }
        Fetch_data(_path, data_type);
        return true;
    } 
    else if(cmd_r.keyword[0] == 'F'){
        return false;
    }
}

bool Server_connection::Update_products(string _path){
    struct Command cmd = {};

    strcpy(cmd.keyword, "update");
    strcpy(cmd.params[0], login.c_str());
    cmd.num_params = 2; 

    char send_buff [MAX_PARAMS*MAX_PARAM_LENGTH + 52];
    
    
    fstream fs;
    fs.open(_path, fstream::in);
    
    string text;
        
    while(!fs.eof()){
        string tmp;
        getline(fs, tmp);
        text.append(tmp + "\n");
    }

    fs.close();

    strcpy(cmd.params[1], text.c_str());
    
    serialize_command(&cmd, send_buff, sizeof(send_buff));
    write(this->_fd, send_buff, sizeof(send_buff));

    char buf[MAX_PARAMS*MAX_PARAM_LENGTH + 52];

    ssize_t nread;
	nread = read(this->_fd, buf, MAX_PARAMS*MAX_PARAM_LENGTH + 52);
    
    struct Command cmd_r;
    deserialize_command(buf, sizeof(buf), &cmd_r);
    reconnect();
	if(nread == -1){
		perror("Reading failed");
		exit(EXIT_FAILURE);
	}
	if(nread == 0){
		printf("EOF\n"); return false;
	}
    if(cmd_r.keyword[0] == 'S'){
        return true;
    } 
    else if(cmd_r.keyword[0] == 'F'){
        return false;
    }
}

bool Server_connection::Create_note(string _path){
    struct Command cmd = {};

    strcpy(cmd.keyword, "create_note");
    strcpy(cmd.params[0], login.c_str());
    cmd.num_params = 3;
    filesystem::path filePath(_path);

    char send_buff [MAX_PARAMS*MAX_PARAM_LENGTH + 52];
    
    
    fstream fs;
    fs.open(_path, fstream::in);
    
    string text;
        
    while(!fs.eof()){
        string tmp;
        getline(fs, tmp);
        text.append(tmp + "\n");
    }

    fs.close();

    strcpy(cmd.params[1], text.c_str());
    strcpy(cmd.params[2], filePath.filename().c_str());
    
    serialize_command(&cmd, send_buff, sizeof(send_buff));
    write(this->_fd, send_buff, sizeof(send_buff));

    char buf[MAX_PARAMS*MAX_PARAM_LENGTH + 52];

    ssize_t nread;
	nread = read(this->_fd, buf, MAX_PARAMS*MAX_PARAM_LENGTH + 52);
    
    struct Command cmd_r;
    deserialize_command(buf, sizeof(buf), &cmd_r);
    reconnect();
	if(nread == -1){
		perror("Reading failed");
		exit(EXIT_FAILURE);
	}
	if(nread == 0){
		printf("EOF\n"); return false;
	}
    if(cmd_r.keyword[0] == 'S'){
        return true;
    } 
    else if(cmd_r.keyword[0] == 'F'){
        return false;
    }
}

bool Server_connection::Update_note(string _path){
    return Create_note(_path);
}

bool Server_connection::Delete_note(string _path){
    struct Command cmd = {};

    strcpy(cmd.keyword, "delete_note");
    strcpy(cmd.params[0], login.c_str());
    cmd.num_params = 2;
    filesystem::path filePath(_path);

    char send_buff [MAX_PARAMS*MAX_PARAM_LENGTH + 52];
    
    strcpy(cmd.params[1], filePath.filename().c_str());
    
    serialize_command(&cmd, send_buff, sizeof(send_buff));
    write(this->_fd, send_buff, sizeof(send_buff));

    char buf[MAX_PARAMS*MAX_PARAM_LENGTH + 52];

    ssize_t nread;
	nread = read(this->_fd, buf, MAX_PARAMS*MAX_PARAM_LENGTH + 52);
    
    struct Command cmd_r;
    deserialize_command(buf, sizeof(buf), &cmd_r);
    reconnect();
	if(nread == -1){
		perror("Reading failed");
		exit(EXIT_FAILURE);
	}
	if(nread == 0){
		printf("EOF\n"); return false;
	}
    if(cmd_r.keyword[0] == 'S'){
        return true;
    } 
    else if(cmd_r.keyword[0] == 'F'){
        return false;
    }
}

Server_connection::~Server_connection(){
    close(this->_fd);
}
