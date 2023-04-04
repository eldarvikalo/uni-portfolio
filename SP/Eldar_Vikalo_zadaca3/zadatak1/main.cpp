#include <iostream>
#include <string>
#include "Lista.hpp"

int generateId()
{
    static int counter = 0;
    return ++counter;
}

struct ToDoTask
{
    int id;
    std::string title;
    std::string description;
    int priority;
    bool operator>(const ToDoTask &drugi)
    {
        return priority > drugi.priority;
    }
    bool operator<(const ToDoTask &drugi)
    {
        return priority < drugi.priority;
    }
};

int printMenuAndGetChoice()
{
    int choice;
    std::cout << "Choose one of the options" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "1. Display the current list of ToDoTask" << std::endl;
    std::cout << "2. Enter a new ToDoTask" << std::endl;
    std::cout << "3. Mark ToDoTask as done" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cout << "****************************************" << std::endl;
    return choice;
}

int main()
{
    int choice, najveciId;
    Lista<ToDoTask> listaTaskova;
    ToDoTask novi;

    while (true)
    {
        choice = printMenuAndGetChoice();
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        switch (choice)
        {
        case 1:
            if (listaTaskova.size() == 0)
            {
                std::cout << "Your notes is empty" << std::endl;
            }
            else
            {
                for (ToDoTask t : listaTaskova)
                {
                    std::cout << "********" << std::endl;
                    std::cout << "* Task *" << std::endl;
                    std::cout << "********" << std::endl;
                    std::cout << "Title: " << t.title << std::endl;
                    std::cout << "Description: " << t.description << std::endl;
                    std::cout << "Priority: " << t.priority << std::endl;
                }
            }
            break;
        case 2:
            novi.id = generateId();
            najveciId = novi.id;
            std::cout << "Enter a new ToDoTask: " << std::endl;
            std::cout << "Enter the title of the task: ";
            std::getline(std::cin, novi.title);
            std::cout << "Enter the description of the task: ";
            std::getline(std::cin, novi.description);
            std::cout << "Enter a priority (>0): ";
            std::cin >> novi.priority;

            listaTaskova.add(novi);
            break;
        case 3:
            if (listaTaskova.size() == 0)
            {
                std::cout << "Your notes is empty" << std::endl;
                continue;
            }
            std::cout << "****************************************" << std::endl;
            for (ToDoTask t : listaTaskova)
            {
                std::cout << "Title: " << t.title << std::endl;
                std::cout << "Description: " << t.description << std::endl;
                std::cout << "Priority: " << t.priority << std::endl;
                std::cout << "Id: " << t.id << std::endl
                          << std::endl;
            }
            std::cout << "****************************************" << std::endl;
            std::cout << "Enter id of the task which you want to mark as done: ";
            std::cin >> choice;
            if (choice > najveciId || choice < 0)
            {
                std::cout << "Task with id = " << choice << " does not exist" << std::endl;
            }
            else
            {
                Lista<ToDoTask>::Iterator it = listaTaskova.find([&choice](ToDoTask t)
                                                               { return t.id == choice; });
                listaTaskova.remove(it);
            }
            break;
        }
        std::cout << "Enter number 0 to exit program, or something else to continue:";
        std::cin >> choice;
        if (choice == 0)
        {
            break;
        }
    }
}
