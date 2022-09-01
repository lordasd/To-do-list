#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include "Todolist.hpp"

//----------------------Create_List--------------------------//
void Todolist::create_list(Todolist& list)
{
    std::cout << "Create a new list\n________________\n\n";
    
    std::vector<std::string> tasks;
    std::vector<bool> done;
    std::string list_title{};

    if(list.todo_list.size() == 0)
        list.todo_list.reserve(5);
    //Print Titles
    title_lists_view(list.todo_list);
    std::cout << "Enter list title: ";
    std::cin >> list_title;
    list_title = list_title + ": ";
    tasks.push_back(list_title);
    done.push_back(0);
    
    add_task(tasks, done);
    list.todo_list.push_back(tasks);
    list.done_list.push_back(done);


    std::cout << "\nList has been added.\nReturning...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

//----------------------Add_To_List---------------------------//
void Todolist::add_to_list(Todolist& list)
{
    if(list.todo_list.size() == 0)
    {
        std::cout << "List is empty! Create a list first.\nReturning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    std::cout << "Add to list\n__________\n\n";
    size_t list_index{};
    while(true)
    {
        title_lists_view(list.todo_list);
        std::cout << "Choose a list: ";
        std::cin >> list_index;
        if(list_index > 0 && list_index <= list.todo_list.size())
            break;
        std::cout << "Wrong title. Try again...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    add_task(list.todo_list[list_index-1], list.done_list[list_index-1]);
}

//-------------------Add_Task-----------------------//
void Todolist::add_task(std::vector<std::string>& tasks,
                        std::vector<bool>& done)
{
    while(true)
    {
        list_view(tasks, done); //Print current list
        std::cout << "\nAdd task (0 to return): ";
        std::string task;
        std::getline(std::cin >> std::ws, task);
        if(task == "0")
            return;
        tasks.push_back(task);
        done.push_back(0);
        std::cout << "Task added!\n\n";
    }
}

//----------------------Show_Lists----------------------------//
void Todolist::show_lists(Todolist& list)
{
    std::cout << "List\n_______\n\n";

    if(list.todo_list.size() == 0)
    {
        std::cout << "No existing lists!\nReturning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    //Print Titles
    title_lists_view(list.todo_list);
    std::cout << "Choose a list: (0 to return)";
    size_t list_input{};
    while(true)
    {
        std::cin >> list_input;
        if(list_input == 0)
            return;
        if(index_in_list(list.todo_list, list_input))
            break;
        else
            std::cout << "Wrong list, Try again: ";
    }
    mark_tasks(list.todo_list[list_input-1], list.done_list[list_input-1]);
}

//----------------------Mark_Tasks----------------------------//
void Todolist::mark_tasks(std::vector<std::string>& tasklist,
                std::vector<bool>& donelist)
{
    while(true)
    { 
        //Print whole task list
        list_view(tasklist, donelist);

        std::cout << "\n1) Mark done/undone task\n";
        std::cout << "2) Back\n";
        std::cout << "Option: ";

        size_t input{};
        std::cin >> input;
        //Mark/Unmark a task as done/undone
        if(input == 1)
        {
            size_t task_mark{};
            std::cout << "Select a task to mark/unmark: ";
            std::cin >> task_mark;
            while(task_mark < 0 || task_mark > tasklist.size())
            {
                std::cout << "Invalid task index, try again: ";
                std::cin.clear();
                std::cin.ignore();
                std::cin >> task_mark;
            }
            if(task_mark == 0) //Fill whole list as done.
            {
                for(size_t task{}; task < tasklist.size(); ++task)
                {
                    if(!donelist[task]) //Turn everthing done
                    {
                        for(size_t task{}; task < tasklist.size(); ++task)
                            donelist[task] = true;
                    }
                    else //Turn everything undone
                    {
                        for(size_t task{}; task < donelist.size(); ++task)
                            donelist[task] = false;
                    }                                
                }       
            }
            else //Change mark state
            {
                if(donelist[task_mark] == true)
                {
                    donelist[task_mark] = false;
                    donelist[0] = false; //Done all - disabled
                }
                else
                    donelist[task_mark] = true;
            }
            
        }
        else if(input == 2)
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
void Todolist::save_list(Todolist& list)
{
    std::ofstream out;
    out.open("savefile.txt");
    if(!out.is_open())
    {
        std::cout << "File did not open correctly.\nCheck if file exists.\n";
        return;
    }
    //Clear file
    out.std::ofstream::out | std::ofstream::trunc;

    for(size_t listindx = 0; listindx < list.todo_list.size(); ++listindx)
    {
        for(size_t task = 0; task < list.todo_list[listindx].size(); ++task)
        {
            if(list.done_list[listindx][task])
                out << "true ";
            else
                out << "false ";
            out << list.todo_list[listindx][task];
            if(task < list.todo_list[listindx].size()-1)
                out << "\n";
        }
        if(listindx < list.todo_list.size())
            out << "\n::\n";//meaning next list
    }

    std::cout << "Lists have been saved!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    out.close();
}

//------------------------Load_List------------------------//
void Todolist::load_list(Todolist& list)
{
    std::ifstream inp;
    inp.open("savefile.txt");
    list.todo_list.clear();
    list.done_list.clear();
    
    if(!inp.is_open())
    {
        std::cout << "File did not open correctly.\nCheck if file exists.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }
    if(inp.eof())
    {
        std::cout << "File is empty!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    std::string str{};
    std::vector<std::string> currlist;
    std::vector<bool> currdonelist;
    while(!inp.eof())
    {
        inp >> str;
        if(str == "::")
        {   //Reading "::" twice;
            if(currlist.size() == 0 || currdonelist.size() == 0)
                break;
            list.todo_list.push_back(currlist);
            list.done_list.push_back(currdonelist);
            currlist.clear();
            currdonelist.clear();
            continue;
        }
        if(str == "true")
            currdonelist.push_back(1);
        else if(str == "false")
            currdonelist.push_back(0);
        std::getline(inp >> std::ws, str);
        currlist.push_back(str);
    }
    std::cout << "Lists are loaded!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    inp.close();
}

//--------------------Delete_From_List--------------------//
void Todolist::delete_from_list(Todolist& list)
{
    std::cout << "Delete from list\n_____________\n\n";

    //Check if list empty
    if (list.todo_list.size() == 0)
    {
        std::cout << "List is empty! Create a list first.\nReturning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    while(true)
    {
        title_lists_view(list.todo_list);
        std::cout << "Choose a list to delete from: ";
        size_t choice{};
        while(true)
        {
            std::cin >> choice;
            if(index_in_list(list.todo_list, choice))
                break;
            std::cout << "Invalid choice, try again: \n";
        }
        
        //Get the 1d vectors for easier code writing
        std::vector<std::string>& chosen_list = list.todo_list[choice-1];
        std::vector<bool>& chosen_done = list.done_list[choice-1];

        while(true)
        {
            list_view(chosen_list, chosen_done);
            std::cout << "Choose task to delete: (0 to return): ";
            size_t task;
            std::cin >> task;
            if(task == 0)
                return;
            else if(task > 0 && task <= chosen_list.size())
            {
                chosen_list.erase(chosen_list.begin()+task);
                chosen_done.erase(chosen_done.begin()+task);
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
void Todolist::delete_list(Todolist& list)
{
    if(list.todo_list.size() == 0)
    {
        std::cout << "List is empty! Create a list first.\nReturning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }
    std::cout << "1) Delete a list\n";
    std::cout << "2) Delete all lists\n";
    std::cout << "3) Return\n";
    size_t choice{};
    while(true)
    {
        std::cin >> choice;
        if(choice > 0 && choice < 4)
            break;
        std::cout << "Wrong choice, try again: ";
    }

    if(choice == 1)
    {
        size_t choice{};
        while(true)
        {
            title_lists_view(list.todo_list);
            std::cout << "Choose a list: (0 to return)";
            
            while(true)
            {
                std::cin >> choice;
                if(index_in_list(list.todo_list, choice))
                    break;
                else if(choice == 0)
                    return;
                std::cout << "Wrong choice, try again: ";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            list.todo_list.erase(list.todo_list.begin()+choice-1);
            list.done_list.erase(list.done_list.begin()+choice-1); 
            std::cout << "List has been removed!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else if(choice == 2)
    {
        std::cout << "Are you sure you want to delete all lists?\n Yes/No: ";
        std::string input{};
        while(true)
        {
            std::cin >> input;
            if(input == "Yes" || input == "yes")
            {
                list.todo_list.clear();
                list.done_list.clear();
                std::cout << "Lists have been removed!\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }
            else if(input == "No" || input == "no")
                return;
        }
    }
    else if(choice == 3)
        return;
}

//-------------------List_View-----------------------//
void Todolist::list_view(const std::vector<std::string> tasks,
                         const std::vector<bool> done)
{
    for (size_t task = 0; task < tasks.size(); ++task)
    {
        if (done[task])
            std::cout << task << "[v]" << tasks[task] << "\n";
        else
            std::cout << task << "[]" << tasks[task] << "\n";
    }
}

//-------------------Title_Lists_View-----------------------//
void Todolist::title_lists_view(const std::vector<std::vector<std::string>>& lists)
{
    size_t index{1};
    for(auto list: lists)
    {
        for(auto listitle: list)
        {   
            std::cout << index << ") ";
            std::cout << listitle << "\n";
            break;
        }
        index++;
    }
}

//-------------------Index_In_List-----------------------//
bool Todolist::index_in_list(const std::vector<std::vector<std::string>>& lists, size_t index)
{
    if(index > 0 && index <= lists.size())
        return true;
    return false;
}
