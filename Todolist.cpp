#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include "Todolist.h"

//----------------------Create_List--------------------------//
void create_list(ToDoLists& lists)
{
    std::cout << "Create a new list\n________________\n\n";

    ToDoList list;
    std::vector<ToDoList> todo_list;
    /*lists.todo_lists.push_back(list);*/
    std::string list_title{};

    if (lists.todo_lists.size() == 0)
        lists.todo_lists.reserve(5);
    //Print Titles
    title_lists_view(lists);
    std::cout << "Enter list title: ";
    while (true)
    {
        std::cin >> list_title;
        if (check_title(lists, list_title))
            break;
        std::cout << "Title is in use, try again: ";
    }
    list.title = list_title + ":";

    add_task(list);
    lists.todo_lists.push_back(list);

    std::cout << "\nList has been added.\nReturning...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

//----------------------Add_To_List---------------------------//
void add_to_list(ToDoLists& lists)
{
    if (lists.todo_lists.size() == 0)
    {
        std::cout << "List is empty! Create a list first.\nReturning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    std::cout << "Add to list\n__________\n\n";
    size_t list_index{};
    while (true)
    {
        title_lists_view(lists);
        std::cout << "Choose a list: ";
        std::cin >> list_index;
        if (list_index > 0 && list_index <= lists.todo_lists.size())
            break;
        std::cout << "Wrong title. Try again...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    add_task(lists.todo_lists[list_index - 1]);
}

//-------------------Add_Task-----------------------//
void add_task(ToDoList& list)
{
    while (true)
    {
        Task task;
        list_view(list); //Print current list
        std::cout << "\nAdd task (0 to return): ";
        std::string curr_task;
        std::getline(std::cin >> std::ws, curr_task);
        task.todo = curr_task;
        if (curr_task == "0")
            return;
        list.todo_list.push_back(task);
        std::cout << "Task added!\n\n";
    }
}

//----------------------Show_Lists----------------------------//
void show_lists(ToDoLists& lists)
{
    std::cout << "List\n_______\n\n";

    if (lists.todo_lists.size() == 0)
    {
        std::cout << "No existing lists!\nReturning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    //Print Titles
    title_lists_view(lists);
    std::cout << "Choose a list: (0 to return)";
    size_t list_input{};
    while (true)
    {
        std::cin >> list_input;
        if (list_input == 0)
            return;
        if (index_in_list(lists, list_input))
            break;
        else
            std::cout << "Wrong list, Try again: ";
    }
    mark_tasks(lists.todo_lists[list_input - 1]);
}

//----------------------Mark_Tasks----------------------------//
void mark_tasks(ToDoList& list)
{
    while (true)
    {
        //Print whole task list
        list_view(list);

        std::cout << "\n1) Mark done/undone task\n";
        std::cout << "2) Back\n";
        std::cout << "Option: ";

        size_t input{};
        std::cin >> input;
        //Mark/Unmark a task as done/undone
        if (input == 1)
        {
            size_t task_mark{};
            std::cout << "Select a task to mark/unmark: ";
            std::cin >> task_mark;
            while (task_mark < 0 || task_mark > list.todo_list.size())
            {
                std::cout << "Invalid task index, try again: ";
                std::cin.clear();
                std::cin.ignore();
                std::cin >> task_mark;
            }
            if (task_mark == 0) //Fill whole list as done.
            {
                if (list.all_done) //Turn everything undone
                {
                    for (size_t task{}; task < list.todo_list.size(); ++task)
                        list.todo_list[task].task_status = STARTED;
                    list.all_done = STARTED;
                }
                else               //Turn everything done
                {
                    for (size_t task{}; task < list.todo_list.size(); ++task)
                        list.todo_list[task].task_status = FINISHED;
                    list.all_done = FINISHED;
                }
            }
            else //Change mark state
            {
                if (list.todo_list[task_mark - 1].task_status == FINISHED)
                {
                    list.todo_list[task_mark - 1].task_status = STARTED;
                    list.all_done = STARTED;
                }     
                else
                    list.todo_list[task_mark-1].task_status = FINISHED;
            }

        }
        else if (input == 2)
            return;
        else
        {
            std::cout << "Invalid option.\n";
            std::cin.clear();
            std::cin.ignore();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

//------------------------Save_List-------------------------//
void save_list(ToDoLists& lists)
{
    std::ofstream out;
    out.open("savefile.txt");
    if (!out.is_open())
    {
        std::cout << "File did not open correctly.\nCheck if file exists.\n";
        return;
    }
    if (lists.todo_lists.size() == 0)
    {
        std::cout << "Nothing to save.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }
    //Clear file
    out.std::ofstream::out | std::ofstream::trunc;

    for (size_t listindx = 0; listindx < lists.todo_lists.size(); ++listindx)
    {
        out << lists.todo_lists[listindx].title << ":\n";
        for (size_t task = 0; task < lists.todo_lists[listindx].todo_list.size(); ++task)
        {
            if (lists.todo_lists[listindx].todo_list[task].task_status)
                out << "true ";
            else
                out << "false ";
            out << lists.todo_lists[listindx].todo_list[task].todo;
            if (task < lists.todo_lists[listindx].todo_list.size() - 1)
                out << "\n";
        }
        if (listindx < lists.todo_lists.size())
            out << "\n::\n";//meaning next list
    }

    std::cout << "Lists have been saved!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    out.close();
}

//------------------------Load_List------------------------//
void load_list(ToDoLists& lists)
{
    std::ifstream inp;
    inp.open("savefile.txt");
    lists.todo_lists.clear();

    if (!inp.is_open())
    {
        std::cout << "File did not open correctly.\nCheck if file exists.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }
    if (inp.peek() == -1)
    {
        std::cout << "File is empty!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    std::string str{};

    while (!inp.eof())
    {
        ToDoList currlist;
        size_t index{};

        while (true)
        {   
            Task task;
            inp >> str;
            if (str == "::")
            {
                //Checking if it reads "::" twice, then finish.
                if (currlist.todo_list.size() == 0)
                    break;
                lists.todo_lists.push_back(currlist);
                break;
            }
            if (str == "true")
                task.task_status = FINISHED;
            else if (str == "false")
                task.task_status = STARTED;
            else if (str[str.length() - 1] == ':')
            {
                currlist.title = str;
                continue;
            }
            currlist.todo_list.push_back(task);
            std::getline(inp >> std::ws, str);
            currlist.todo_list[index++].todo = str;
        }
    }
    std::cout << "Lists are loaded!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    inp.close();
}

//--------------------Delete_From_List--------------------//
void delete_from_list(ToDoLists& lists)
{
    std::cout << "Delete from list\n_____________\n\n";

    //Check if list empty
    if (lists.todo_lists.size() == 0)
    {
        std::cout << "List is empty! Create a list first.\nReturning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    while (true)
    {
        title_lists_view(lists);
        std::cout << "Choose a list to delete from: ";
        size_t choice{};
        while (true)
        {
            std::cin >> choice;
            if (index_in_list(lists, choice))
                break;
            std::cout << "Invalid choice, try again: \n";
        }

        while (true)
        {
            list_view(lists.todo_lists[choice - 1]);
            std::cout << "Choose task to delete: (0 to return): ";
            size_t task;
            std::cin >> task;
            if (task == 0)
                return;
            else if (task > 0 && task <= lists.todo_lists[choice - 1].todo_list.size())
            {
                lists.todo_lists[choice - 1].todo_list.erase(lists.todo_lists[choice - 1].todo_list.begin() + task);
            }
            else
            {
                std::cout << "Task doesn't exist.\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }
}

//--------------------Delete_List------------------------//
void delete_list(ToDoLists& lists)
{
    if (lists.todo_lists.size() == 0)
    {
        std::cout << "List is empty! Create a list first.\nReturning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }
    std::cout << "1) Delete a list\n";
    std::cout << "2) Delete all lists\n";
    std::cout << "3) Return\n";
    size_t choice{};
    while (true)
    {
        std::cin >> choice;
        if (choice > 0 && choice < 4)
            break;
        std::cout << "Wrong choice, try again: ";
    }

    if (choice == 1)
    {
        size_t choice{};
        while (true)
        {
            title_lists_view(lists);
            std::cout << "Choose a list: (0 to return)";

            while (true)
            {
                std::cin >> choice;
                if (index_in_list(lists, choice))
                    break;
                else if (choice == 0)
                    return;
                std::cout << "Wrong choice, try again: ";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            lists.todo_lists.erase(lists.todo_lists.begin() + choice - 1);
            std::cout << "List has been removed!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else if (choice == 2)
    {
        std::cout << "Are you sure you want to delete all lists?\n Yes/No: ";
        std::string input{};
        while (true)
        {
            std::cin >> input;
            if (input == "Yes" || input == "yes")
            {
                lists.todo_lists.clear();
                std::cout << "Lists have been removed!\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }
            else if (input == "No" || input == "no")
                return;
        }
    }
    else if (choice == 3)
        return;
}

//-------------------List_View-----------------------//
void list_view(const ToDoList& list)
{
    size_t index{ 1 };

    for (Task task : list.todo_list)
    {
        if (task.task_status)
            std::cout << index++ << "[v] " << task.todo << "\n";
        else
            std::cout << index++ << "[] " << task.todo << "\n";
    }

}

//-------------------Title_Lists_View-----------------------//
void title_lists_view(const ToDoLists& lists)
{
    size_t index{ 1 };

    for (ToDoList list : lists.todo_lists)
    {
        std::cout << index++ << ") ";
        std::cout << list.title << "\n";
    }
}

//-------------------Check_Title-----------------------//
bool check_title(const ToDoLists& lists, std::string new_title)
{
    for (ToDoList title : lists.todo_lists)
        if (title.title == new_title + ":")
            return false;
    return true;
}

//-------------------Index_In_List-----------------------//
bool index_in_list(const ToDoLists& lists, size_t index)
{
    if (index > 0 && index <= lists.todo_lists.size())
        return true;
    return false;
}
