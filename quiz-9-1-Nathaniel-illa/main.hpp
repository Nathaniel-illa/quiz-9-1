#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

const int NUMCOURSE = 2;

struct Student {
    int id;
    string name;
    int score[NUMCOURSE];
    double sum;
    double avg;
    struct Student *next;
};

#define struct Student Student

// Function declarations
Student *makeStudents(void); // Changed to match the expected call
int getLength(Student *head);
void printStudents(Student *head); // Changed to match the expected call
Student *sortStudents(Student *head, int ascending); // Kept consistent

// Function to create a linked list of students from the file
Student *makeStudents(void) {
    ifstream file("student.txt");
    if (!file) {
        cerr << "Unable to open file student.txt";
        return nullptr; // Return null if file cannot be opened
    }

    Student *head = nullptr;
    Student *tail = nullptr;

    while (true) {
        Student *newStudent = (Student *)malloc(sizeof(Student)); // Allocate memory for new student
        if (!newStudent) {
            cerr << "Memory allocation failed";
            break; // Exit on memory allocation failure
        }

        // Read data from the file
        if (!(file >> newStudent->id >> newStudent->name >> newStudent->score[0] >> newStudent->score[1])) {
            free(newStudent); // Free memory if reading fails
            break; // Exit loop if no more data
        }

        // Calculate sum and average
        newStudent->sum = newStudent->score[0] + newStudent->score[1];
        newStudent->avg = newStudent->sum / NUMCOURSE;
        newStudent->next = nullptr; // Initialize the next pointer to null

        // Add to the linked list
        if (head == nullptr) {
            head = newStudent; // If list is empty, set head
            tail = newStudent; // Tail also points to the new student
        } else {
            tail->next = newStudent; // Link the new student to the end of the list
            tail = newStudent; // Move tail to the new student
        }
    }

    file.close(); // Close the file
    return head; // Return pointer to the first node
}

// Function to print all student information
void printStudents(Student *head) {
    Student *ptr = head;
    while (ptr != nullptr) {
        cout << ptr->id << "\t" << ptr->name << "\t" 
             << ptr->score[0] << "\t" << ptr->score[1] << "\t" 
             << ptr->sum << "\t" << ptr->avg << "\n";
        ptr = ptr->next; // Move to the next student
    }
    cout << endl;
}

// Function to get the length of the linked list
int getLength(Student *head) {
    int length = 0;
    Student *ptr = head;
    while (ptr != nullptr) {
        length++; // Count each node
        ptr = ptr->next; // Move to the next node
    }
    return length; // Return the total length
}

// Function to sort students by sum
Student *sortStudents(Student *head, int ascending) {
    if (head == nullptr || head->next == nullptr) {
        return head; // Return if the list is empty or has one element
    }

    bool swapped;
    do {
        swapped = false; // Reset swapped flag
        Student *current = head;
        while (current->next != nullptr) {
            // Compare the sum of the current and next student
            if ((ascending && current->sum > current->next->sum) || 
                (!ascending && current->sum < current->next->sum)) {
                // Swap data
                swap(current->id, current->next->id);
                swap(current->name, current->next->name);
                swap(current->score[0], current->next->score[0]);
                swap(current->score[1], current->next->score[1]);
                swap(current->sum, current->next->sum);
                swap(current->avg, current->next->avg);
                swapped = true; // Mark as swapped
            }
            current = current->next; // Move to the next node
        }
    } while (swapped); // Repeat until no swaps are made

    return head; // Return the sorted list
}