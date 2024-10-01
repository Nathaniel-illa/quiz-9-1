#include "main.hpp"

int main()
{
    Student *head;
    
    head = makeStudents(); // Call to makeStudents to create the linked list
    printStudents(head);   // Call to printStudents to display student information
    cout << "The length of the list " << getLength(head) << endl; // Get and print the length of the list
    
    head = sortStudents(head, 1); // Sort in ascending order and update head
    printStudents(head);           // Print sorted students
    
    head = sortStudents(head, 0); // Sort in descending order and update head
    printStudents(head);           // Print sorted students again
    
    return 0;
}
