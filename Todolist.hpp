#ifndef TODOLIST_HPP
#define TODOLIST_HPP

class Todolist {
    std::vector<std::vector<std::string>> todo_list;
    std::vector<std::vector<bool>> done_list;
public:
    //Creates a new list and adds tasks
    void create_list(Todolist& list);
    //Add a task to chosen list  
    void add_to_list(Todolist& list);
    //Add a task to a list(from 'add_to_list')
    void add_task(std::vector<std::string>& tasks, std::vector<bool>& done);
    //Shows all lists - choose a list to mark/umark(done/undone) tasks
    void show_lists(Todolist& list);
    //Mark/unmark(done/undone) tasks of a chosen list in "show_lists" 
    void mark_tasks(std::vector<std::string>& tasklist, std::vector<bool>& donelist);
    //Shows a list content
    void list_view(const std::vector<std::string> tasks, const std::vector<bool> done);
    //Shows all titles of lists
    void title_lists_view(const std::vector<std::vector<std::string>>& lists);
    //Saves the current lists to a file
    void save_list(Todolist& list);
    //Loads up a lists from a file
    void load_list(Todolist& list);
    //Deletes a task from a list
    void delete_from_list(Todolist& list);
    //Deletes all lists/ a list
    void delete_list(Todolist& list);
    //Checks if inputed index is available in the list(validity check)
    bool index_in_list(const std::vector<std::vector<std::string>>& lists, size_t index);
};

enum Options{
    CREATE_LIST = 1, ADD_TO_LIST, SHOW_LISTS, SAVE_LIST,
    LOAD_LIST, DELETE_FROM_LIST, DELETE_LIST, EXIT
};

#endif //TODOLIST_HPP
