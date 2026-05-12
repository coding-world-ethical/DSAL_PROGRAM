#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

struct Student
{
    int id;
    char name[50];
    float cgpa;
};

void addStudent(Student*& students, int& count, int& capacity);
void displayStudents(Student* students, int count);
void bubbleSortByName(Student* students, int count);
void selectionSortByCGPA(Student* students, int count, bool ascending);

int main()
{
    Student* students = nullptr;
    int count = 0, capacity = 0;
    int choice;

    do
    {
        cout << "\n--- Student Database Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Sort by Name (Bubble Sort)\n";
        cout << "4. Sort by CGPA (Selection Sort)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent(students, count, capacity);
            break;

        case 2:
            displayStudents(students, count);
            break;

        case 3:
            bubbleSortByName(students, count);
            cout << "Students sorted by name (alphabetically).\n";
            break;

        case 4:
        {
            char order;

            cout << "Enter 'a' for ascending or 'd' for descending CGPA: ";
            cin >> order;

            selectionSortByCGPA(
                students,
                count,
                order == 'a' || order == 'A'
            );

            break;
        }

        case 5:
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    free(students);

    return 0;
}

void addStudent(Student*& students, int& count, int& capacity)
{
    if (count == capacity)
    {
        capacity += 1;

        students = (Student*)realloc(
            students,
            capacity * sizeof(Student)
        );

        if (!students)
        {
            cout << "Memory allocation failed!\n";
            exit(1);
        }
    }

    cout << "Enter Student ID: ";
    cin >> students[count].id;

    cin.ignore();

    cout << "Enter Student Name: ";
    cin.getline(students[count].name, 50);

    cout << "Enter CGPA: ";
    cin >> students[count].cgpa;

    count++;
}

void displayStudents(Student* students, int count)
{
    if (count == 0)
    {
        cout << "No student records available.\n";
        return;
    }

    cout << "\n--- Student List ---\n";

    for (int i = 0; i < count; i++)
    {
        cout << "ID: " << students[i].id
             << ", Name: " << students[i].name
             << ", CGPA: " << students[i].cgpa
             << "\n";
    }
}

void bubbleSortByName(Student* students, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(
                    students[j].name,
                    students[j + 1].name
                ) > 0)
            {
                swap(
                    students[j],
                    students[j + 1]
                );
            }
        }
    }
}

void selectionSortByCGPA(
    Student* students,
    int count,
    bool ascending
)
{
    for (int i = 0; i < count - 1; i++)
    {
        int minOrMax = i;

        for (int j = i + 1; j < count; j++)
        {
            if ((ascending &&
                 students[j].cgpa <
                 students[minOrMax].cgpa)
                ||
                (!ascending &&
                 students[j].cgpa >
                 students[minOrMax].cgpa))
            {
                minOrMax = j;
            }
        }

        if (minOrMax != i)
        {
            swap(
                students[i],
                students[minOrMax]
            );
        }
    }

    cout << "Students sorted by CGPA "
         << (ascending
             ? "(Ascending)."
             : "(Descending).")
         << "\n";
}
