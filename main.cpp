#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include "Todolist.hpp"

int main()
{
    Todolist list;

    size_t input{};
    while(true)
    {
        std::cout <<  " ____________\n";
        std::cout << "| To-Do-List |\n";
        std::cout <<  " ------------\n\n";
        std::cout << "1) Create List\n2) Add to list\n3) Show list\n4) Save list\n";
        std::cout << "5) Load list\n6) Delete from list\n7) Delete list\n8) Exit\n";
        
        std::cin >> input;
        switch (input)
        {
        case CREATE_LIST:
            list.create_list(list);
            break;
        case ADD_TO_LIST:
            list.add_to_list(list);
            break;
        case SHOW_LIST:
            list.show_list(list);
            break;
        case SAVE_LIST:
            list.save_list(list);
            break;
        case LOAD_LIST:
            list.load_list(list);
            break;
        case DELETE_FROM_LIST:
            list.delete_from_list(list);
            break;
        case DELETE_LIST:
            list.delete_list(list);
            break;
        case EXIT:
            exit(EXIT_SUCCESS);
        default:
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
        }
    }

    return EXIT_SUCCESS;
}
