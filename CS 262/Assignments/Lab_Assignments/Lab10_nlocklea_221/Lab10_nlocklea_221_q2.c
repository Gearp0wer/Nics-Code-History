/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 10 Q2
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Student{
    char name[50];
    int ID;
    char course[50];
}GMU_student;

int main(){
    printf("please input the size array : ");
    int size = 0;
    scanf(" %d",&size);

    GMU_student *student = (GMU_student *)malloc(size * sizeof(GMU_student));

    int i = 0;
    for (i = 0; i < size; i++){
        printf("please input the student %d's name : ", i+1);
        scanf(" %s", &(student+i)->name);
        printf("please input the student %d's ID : ", i+1);
        scanf(" %d", &((student+i)->ID));
        printf("please input the student %d's course : ", i+1);
        scanf(" %s", &(student+i)->course);
    }

    for (i = 0; i < size; i++){
        printf("student %d's name is: %s \n", i+1, (student+i)->name);
        printf("%d's ID is %d: \n", i+1, (student+i)->ID);
        printf("%d's course is: %s \n", i+1, (student+i)->course);
    }

    return 0;
}
