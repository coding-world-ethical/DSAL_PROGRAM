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
int linearSearch(Student* students, int count, int keyID);
int binarySearch(Student* students, int count, int keyID);
void sortByID(Student* students, int count);

int main()
{
    Student* students = nullptr;
    int count = 0, capacity = 0;
    int choice, searchID;

    do
    {
        cout << "\n--- Student Database Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Linear Search by ID\n";
        cout << "4. Binary Search by ID\n";
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
        {
            cout << "Enter ID to search: ";
            cin >> searchID;

            int index = linearSearch(students, count, searchID);

            if (index != -1)
                cout << "Found: " << students[index].name
                     << ", CGPA: " << students[index].cgpa << "\n";
            else
                cout << "Student not found.\n";

            break;
        }

        case 4:
        {
            sortByID(students, count);

            cout << "Enter ID to search: ";
            cin >> searchID;

            int index = binarySearch(students, count, searchID);

            if (index != -1)
                cout << "Found: " << students[index].name
                     << ", CGPA: " << students[index].cgpa << "\n";
            else
                cout << "Student not found.\n";

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

        students = (Student*)realloc(students, capacity * sizeof(Student));

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
             << ", CGPA: " << students[i].cgpa << "\n";
    }
}

int linearSearch(Student* students, int count, int keyID)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == keyID)
            return i;
    }

    return -1;
}

int binarySearch(Student* students, int count, int keyID)
{
    int low = 0, high = count - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (students[mid].id == keyID)
            return mid;
        else if (students[mid].id < keyID)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

void sortByID(Student* students, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (students[j].id > students[j + 1].id)
            {
                swap(students[j], students[j + 1]);
            }
        }
    }
}
