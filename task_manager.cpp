#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Task
{
private:
    string title;
    string description;
    bool completed;

public:
    Task(string title, string description, bool completed = false)
    {
        this->title = title;
        this->description = description;
        this->completed = completed;
    }

    void markAsComplete()
    {
        completed = true;
    }

    bool isCompleted() const
    {
        return completed;
    }

    string getTitle() const
    {
        return title;
    }

    string getDescription() const
    {
        return description;
    }
};

class TaskManager
{
private:
    vector<Task> tasks;

public:
    void addTask(string title, string description)
    {
        tasks.push_back(Task(title, description));
    }

    void markTaskAsComplete(int index)
    {
        if (index >= 0 && index < tasks.size())
        {
            tasks[index].markAsComplete();
        }
    }

    void removeTask(int index)
    {
        if (index >= 0 && index < tasks.size())
        {
            tasks.erase(tasks.begin() + index);
        }
    }

    void listAllTasks() const
    {
        cout << "Tasks:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            cout << i + 1 << ". " << tasks[i].getTitle() << " - " << tasks[i].getDescription();
            if (tasks[i].isCompleted())
            {
                cout << " [Completed]";
            }
            cout << endl;
        }
    }

    void saveTasksToFile(const string &filename) const
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (const auto &task : tasks)
            {
                file << task.getTitle() << "  |  " << task.getDescription() << "  |  ";
                if (task.isCompleted())
                {
                    file << "completed";
                }
                else
                {
                    file << "not completed";
                }
                file << endl;
            }
            file.close();
            cout << "Tasks saved to file successfully." << endl;
        }
        else
        {
            cout << "Unable to open file for writing." << endl;
        }
    }

    void loadTasksFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "File not found. Creating a new file..." << endl;
            ofstream newFile(filename); // Create a new file
            newFile.close();
            return; // Exit function as there are no tasks to load
        }

        tasks.clear(); // Clear existing tasks
        string line;
        while (getline(file, line))
        {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            string title = line.substr(0, pos1);
            string description = line.substr(pos1 + 1, pos2 - pos1 - 1);
            bool completed = (line.substr(pos2 + 1) == "completed"); // Check if the task is completed
            tasks.push_back(Task(title, description, completed));
        }
        file.close();
        cout << "Tasks loaded from file successfully." << endl;
    }
};

int main()
{
    TaskManager taskManager;

    string filename;
    cout << "Enter the filename to load tasks from: ";
    cin >> filename;
    taskManager.loadTasksFromFile(filename); // Load tasks from user-specified file

    int choice;

    do
    {
        cout << "Task Manager Menu:" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Mark Task as Complete" << endl;
        cout << "3. Remove Task" << endl;
        cout << "4. List All Tasks" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string title, description;
            cout << "Enter task title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter task description: ";
            getline(cin, description);
            taskManager.addTask(title, description);
            taskManager.saveTasksToFile(filename);
            cout << "Task added successfully." << endl;
            break;
        }
        case 2:
        {
            taskManager.listAllTasks(); // List all tasks before marking one as complete
            int index;
            cout << "Enter the index of the task to mark as complete: ";
            cin >> index;
            taskManager.markTaskAsComplete(index - 1);
            taskManager.saveTasksToFile(filename);
            cout << "Task marked as complete." << endl;
            break;
        }
        case 3:
        {
            int index;
            cout << "Enter the index of the task to remove: ";
            cin >> index;
            taskManager.removeTask(index - 1);
            taskManager.saveTasksToFile(filename);
            cout << "Task removed successfully." << endl;
            break;
        }
        case 4:
        {
            taskManager.listAllTasks();
            break;
        }
        case 5:
        {
            cout << "Exiting..." << endl;
            taskManager.saveTasksToFile(filename);
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    } while (choice != 6);

    return 0;
}
