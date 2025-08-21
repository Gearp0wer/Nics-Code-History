/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 10 Q1
 * 
 */

#include <stdio.h>
#include <stdlib.h>

struct Student{
    char name[50];
    int ID;
    char course[50];
};

int main(){
    struct Student student;

    printf("please input the student name : ");
    scanf(" %s", student.name);
    printf("please input the student ID : ");
    scanf(" %d", &student.ID);
    printf("please input the student course : ");
    scanf(" %s", student.course);

    printf("%s\n", student.name);
    printf("%d\n", student.ID);
    printf("%s\n", student.course);
    printf("\n");

    return 0;
}
