#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include "Todolist.hpp"

int main()
{
    ToDoLists lists;

    size_t input{};
    while (true)
    {
        std::cout << " ____________\n";
        std::cout << "| To-Do-List |\n";
        std::cout << " ------------\n\n";
        std::cout << "1) Create List\n2) Add to list\n3) Show list\n4) Save list\n";
        std::cout << "5) Load list\n6) Delete from list\n7) Delete list\n8) Exit\n\n";
        std::cout << "Option: ";
        std::cin >> input;
        switch (input)
        {
        case CREATE_LIST:
            create_list(lists);
            break;
        case ADD_TO_LIST:
            add_to_list(lists);
            break;
        case SHOW_LISTS:
            show_lists(lists);
            break;
        case SAVE_LIST:
            save_list(lists);
            break;
        case LOAD_LIST:
            load_list(lists);
            break;
        case DELETE_FROM_LIST:
            delete_from_list(lists);
            break;
        case DELETE_LIST:
            delete_list(lists);
            break;
        case EXIT:
            exit(EXIT_SUCCESS);
        default:
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
        }
    }

    return EXIT_SUCCESS;
}
