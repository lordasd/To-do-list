#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include "Todolist.hpp"

void Todolist::create_list(Todolist& list)
{
    //Initialize default capacity
    list.todo_list.clear();
    list.todo_list.reserve(10);
    list.done_list.reserve(10);
    size_t num_of_tasks;
    std::string task;

    std::cout << "Create a new list\n________________\n\n";
    std::cout << "Input number of tasks to add: ";
    std::cin >> num_of_tasks;

    //Initialize requsted capacity if > default capacity
    if(list.todo_list.capacity() < num_of_tasks)
    {
        list.todo_list.reserve(num_of_tasks);
        list.done_list.reserve(num_of_tasks);
        std::cout << num_of_tasks << " available tasks added for use.\n";
    }
    //Input tasks
    for(size_t tasknum = 0; tasknum < num_of_tasks; ++tasknum)
    {
        std::cout << "Input " << tasknum+1 << " out of " << num_of_tasks << ": ";
        std::getline(std::cin >> std::ws, task);
        list.todo_list.push_back(task);
        list.done_list.push_back(0);
        std::cout << "Task added\n";
    }
    std::cout << "\nTasks are added!\nReturning...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Todolist::add_to_list(Todolist& list)
{
    if(list.todo_list.size() == 0)
    {
        std::cout << "List is empty! Create a list first.\nReturning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    while(true)
    {
        list.list_view(list);
        std::cout << "Add task (0 to return): ";
        std::string task;
        std::getline(std::cin >> std::ws, task);
        if(task == "0")
            return;
        list.todo_list.push_back(task);
        list.done_list.push_back(0);
        std::cout << "Task added!\n\n";
    }
}

void Todolist::show_list(Todolist& list)
{
    std::cout << "List\n_______\n\n";

    if(list.todo_list.size() == 0)
    {
        std::cout << "List is empty!\nReturning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    while(true)
    {
        //Print whole task list
        list.list_view(list);

        std::cout << "\n1) Mark done/undone task\n";
        std::cout << "2) Back\n";

        int input{};
        std::cin >> input;
        //Mark/Unmark a task as done/undone
        if(input == 1)
        {
            size_t task_mark{};
            std::cout << "Select a task to mark/unmark: ";
            std::cin >> task_mark;
            while(task_mark < 1 && task_mark > list.todo_list.size())
            {
                std::cout << "Invalid task index, try again: ";
                std::cin >> task_mark;
            }
            if(list.done_list[task_mark-1] == true)
                list.done_list[task_mark-1] = false;
            else
                list.done_list[task_mark-1] = true;
        }
        else if(input == 2)
            return;
        else
        {
            std::cout << "Invalid task. Tasks:\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void Todolist::save_list(Todolist& list)
{
    std::ofstream out;
    out.open("savefile.txt");
    //Clear file
    out.std::ofstream::out | std::ofstream::trunc;

    for(size_t line = 0; line < list.todo_list.size(); ++line)
    {
        if(list.done_list[line])
            out << "true ";
        else
            out << "false ";
        out << list.todo_list[line];
        //Don't count last row
        if(line < list.todo_list.size()-1)
            out << "\n";
    }
    std::cout << "List saved!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    out.close();
}

void Todolist::load_list(Todolist& list)
{
    std::ifstream inp;
    inp.open("savefile.txt");

    while(!inp.eof())
    {
        std::string str;
        inp >> str;
        if(str == "true")
            list.done_list.push_back(1);
        else
            list.done_list.push_back(0);
        std::getline(inp >> std::ws, str);
        list.todo_list.push_back(str);
    }
    std::cout << "List loaded\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    inp.close();
}

void Todolist::delete_from_list(Todolist& list)
{
    std::cout << "Delete from list\n_____________\n\n";

    while(true)
    {
        //Check if list empty
        if (list.todo_list.size() == 0)
        {
            std::cout << "List is empty! Create a list first.\nReturning...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }

        list.list_view(list);

        std::cout << "Choose task to delete: (0 to return): ";
        size_t task{};
        std::cin >> task;
        if(task == 0)
            return;
        else if(task > 0 && task <= list.todo_list.size())
        {
            list.todo_list.erase(list.todo_list.begin()+task-1);
            list.done_list.erase(list.done_list.begin()+task-1);
        }
        else
        {
            std::cout << "Invalid input, try again\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void Todolist::delete_list(Todolist& list)
{
    if(list.todo_list.size() == 0)
    {
        std::cout << "List is empty!\nReturning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    std::cout << "Are you sure you want to delete the list?\n Yes/No: ";
    std::string input{};
    while(true)
    {
        std::cin >> input;
        if(input == "Yes" || input == "yes")
        {
            list.todo_list.resize(0);
            list.done_list.resize(0);
            std::cout << "List have been removed!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }
        else if(input == "No" || input == "no")
            return;
    }
}

void Todolist::list_view(Todolist& list)
{
    for (size_t task = 0; task < list.todo_list.size(); ++task)
    {
        if (list.done_list[task])
            std::cout << task + 1 << "[v]" << list.todo_list[task] << "\n";
        else
            std::cout << task + 1 << "[]" << list.todo_list[task] << "\n";
    }
}