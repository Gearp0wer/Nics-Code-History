/* Nicholas Locklear G01090642
 * CS 262, Lab Section 221
 * Lab 10 Q3
 * 
 */

#include <stdio.h>
#include <stdlib.h>

enum YEAR { first = 1, second, third, fourth, fifth };

typedef struct Student{
    char name[50];
    int ID;
    char course[50];
    int year;
}GMU_student;

int SetYear(int ID){
    if(ID % 10 == 0 || ID % 10 == 1)
        return first;
    if(ID % 10 == 2 || ID % 10 == 3)
        return second;
    if(ID % 10 == 4 || ID % 10 == 5)
        return third;
    if(ID % 10 == 6 || ID % 10 == 7)
        return fourth;
    if(ID % 10 == 8 || ID % 10 == 9)
        return fifth;
}

int main(){
    printf("please input the size array : ");
    int size = 0;
    scanf(" %d",&size);

    GMU_student *student = (GMU_student *)malloc(size * sizeof(GMU_student));

    int i = 0;
    for (i = 0; i < size; i++){
        printf("please input the student %d's name : ", i+1);
        scanf(" %s", (student+i)->name);
        printf("please input the student %d's ID : ", i+1);
        scanf(" %d", &((student+i)->ID));
        printf("please input the student %d's course : ", i+1);
        scanf(" %s", (student+i)->course);
    }

    for (i = 0; i < size; i++){
        (student+i)->year = SetYear((student+i)->ID);
    }

    for (i = 0; i < size; i++){
        printf("student %d's name is %s \n", i+1, (student+i)->name);
        printf("%d's ID is %d \n", i+1, (student+i)->ID);
        printf("%d's course is %s \n", i+1, (student+i)->course);
        printf("%d's year is %d \n", i+1, (student+i)->year);
    }

    return 0;
}
