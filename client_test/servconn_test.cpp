#include "servconn.h"

int main() {
    // Создаем объект серверного соединения
    Server_connection server_conn("127.0.0.1", 1488);

//    // Пример регистрации пользователя
//    if (server_conn.Register("AAAa", "passwd")) {
//        std::cout << "Registration successful" << std::endl;
//    } else {
//        std::cout << "Registration failed" << std::endl;
//    }
    
//    sleep(3);
    
    // Пример аутентификации пользователя
    if (server_conn.Auth("AAAa", "passwd")) {
        std::cout << "Authentication successful" << std::endl;
    } else {
        std::cout << "Authentication failed" << std::endl;
    }

    sleep(3);

    // Пример запроса данных с сервера
//    if (server_conn.Fetch_data("./contains/products.txt", "p")) {
//        std::cout << "Data fetched successfully" << std::endl;
//    } else {
//        std::cout << "Failed to fetch data" << std::endl;
//    }

//    // Пример обновления продуктов на сервере
//    if (server_conn.Update_products("./contains/products.txt")) {
//        std::cout << "Products updated successfully" << std::endl;
//    } else {
//        std::cout << "Failed to update products" << std::endl;
//    }
//
    // Пример создания заметки на сервере
    if (server_conn.Create_note("./contains/notes/1.txt")) {
        std::cout << "Note created successfully" << std::endl;
    } else {
        std::cout << "Failed to create note" << std::endl;
    }
//
//    // Пример обновления заметки на сервере
//    if (server_conn.Update_note("./contains/notes/1.txt")) {
//        std::cout << "Note updated successfully" << std::endl;
//    } else {
//        std::cout << "Failed to update note" << std::endl;
//    }
//
//    // Пример удаления заметки на сервере
//    if (server_conn.Delete_note("./contains/notes/1.txt")) {
//        std::cout << "Note deleted successfully" << std::endl;
//    } else {
//        std::cout << "Failed to delete note" << std::endl;
//    }

    return 0;
}

