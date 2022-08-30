#ifndef TODOLIST_HPP
#define TODOLIST_HPP

class Todolist {
    std::vector<std::string> todo_list;
    std::vector<bool> done_list;
public:
    void create_list(Todolist& list);
    void add_to_list(Todolist& list);
    void show_list(Todolist& list);
    void list_view(Todolist& list);
    void save_list(Todolist& list);
    void load_list(Todolist& list);
    void delete_from_list(Todolist& list);
    void delete_list(Todolist& list);
};

enum Options{
    CREATE_LIST = 1, ADD_TO_LIST, SHOW_LIST, SAVE_LIST,
    LOAD_LIST, DELETE_FROM_LIST, DELETE_LIST, EXIT
};

#endif //TODOLIST_HPP