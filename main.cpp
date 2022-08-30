#include <iostream>
#include <vector>
#include <string>
#include "Todolist.hpp"

int main()
{
    Todolist list;

    int input{};
    while(true)
    {
        std::cout <<  " ____________\n";
        std::cout << "| To-Do-List |\n";
        std::cout <<  " ------------\n\n";
        std::cout << "1) Create List\n2) Add to list\n3) Show list\n";
        std::cout << "4) Save list\n5) Delete from list\n6) Delete list\n7) Exit\n";
        
        list.load_save_file(list);

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
        case DELETE_FROM_LIST:
            list.delete_from_list(list);
            break;
        case DELETE_LIST:
            list.delete_list(list);
            break;
        case EXIT:
            exit(EXIT_SUCCESS);
        default:
            std::cout << "Wrong input\nOptions: (1-7)\n";
            break;
        }
    }

    return EXIT_SUCCESS;
}