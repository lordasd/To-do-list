#ifndef TODOLIST_H
#define TODOLIST_H

//-----------------Structs------------------//
struct Task {
    std::string todo;
    bool task_status{};
};

struct ToDoList {
    std::vector<Task> todo_list;
    std::string title;
    bool all_done{};
};

struct ToDoLists {
    std::vector<ToDoList> todo_lists;
};

//---------------------Prototypes----------------------//
void create_list(ToDoLists& lists);
//Add a task to chosen list  
void add_to_list(ToDoLists& lists);
//Add a task to a list(from 'add_to_list')
void add_task(ToDoList& list);
//Shows all lists - choose a list to mark/umark(done/undone) tasks
void show_lists(ToDoLists& lists);
//Mark/unmark(done/undone) tasks of a chosen list in "show_lists" 
void mark_tasks(ToDoList& list);
//Shows a list content
void list_view(const ToDoList& list);
//Shows all titles of lists
void title_lists_view(const ToDoLists& lists);
//Checks if title already in use
bool check_title(const ToDoLists& lists, std::string new_title);
//Saves the current lists to a file
void save_list(ToDoLists& lists);
//Loads up a lists from a file
void load_list(ToDoLists& lists);
//Deletes a task from a list
void delete_from_list(ToDoLists& lists);
//Deletes all lists/ a list
void delete_list(ToDoLists& lists);
//Checks if inputed index is available in the list(validity check)
bool index_in_list(const ToDoLists& lists, size_t index);

//----------------------Enums---------------------------//
enum Options {
    CREATE_LIST = 1, ADD_TO_LIST, SHOW_LISTS, SAVE_LIST,
    LOAD_LIST, DELETE_FROM_LIST, DELETE_LIST, EXIT
};

enum Taskstatus {
    STARTED, FINISHED
};

#endif //TODOLIST_H
