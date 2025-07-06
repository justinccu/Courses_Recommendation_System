#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "import.h"
#include "Person.h"

void readclass()
{
    FILE *fptr;
    
    char path[256];
    getcwd(path, sizeof(path));
    strcat(path, "/output.txt");
    fptr = fopen(path, "r");
    
    // fptr = fopen("/Users/justinkim/Desktop/Courses_Recommendation_System/Final_Project/output.txt", "r");
    if (fptr == NULL)
    {
        return;
    }

    char S[100], time[100];
    int state = 0;
    int id, type;

    while (fgets(S, 100, fptr) != NULL)
    {
        if (S[strlen(S) - 1] == '\n')
            S[strlen(S) - 1] = '\0';

        switch (state)
        {
        case 0:
            id = atoi(S);
            state = 1;
            break;
        case 1:
            type = atoi(S);
            state = 2;
            break;
        case 2:
            strcpy(time, S);
            course_time(id, type, time, 0);
            state = 0;
            break;
        }
    }
    fclose(fptr);
}

void readfile()
{
    FILE *fptr;
    
    char path[256];
    getcwd(path, sizeof(path));
    strcat(path, "/courses_1.txt");
    fptr = fopen(path, "r");
    
    // fptr = fopen("/Users/justinkim/Desktop/Courses_Recommendation_System/Final_Project/courses_1.txt", "r");
    if (fptr == NULL)
        printf("Error\n");

    char S[201];
    char dep[201];
    int count;
    int i = 0;
    int state = 0;

    while (fgets(S, 201, fptr) != NULL)
    {

        if (S[strlen(S) - 1] == '\n')
            S[strlen(S) - 1] = '\0';

        switch (state)
        {
        case 0:
            strcpy(dep, S);
            state = 1;
            break;
        case 1:
            count = atoi(S);
            state = 2;
            break;
        case 2:
            strcpy(courseDatabase[i].department, dep);
            courseDatabase[i].year_standing = atoi(S);
            state = 3;
            break;
        case 3:
            courseDatabase[i].courseID = atoi(S);
            state = 4;
            break;
        case 4:
            courseDatabase[i].classType = atoi(S);
            state = 5;
            break;
        case 5:
            strcpy(courseDatabase[i].courseTitle, S);
            state = 6;
            break;
        case 6:
            strcpy(courseDatabase[i].instructor, S);
            state = 7;
            break;
        case 7:
            courseDatabase[i].credit = atoi(S);
            state = 8;
            break;
        case 8:
            strcpy(courseDatabase[i].creditType, S);
            state = 9;
            break;
        case 9:
            strcpy(courseDatabase[i].period, S);
            state = 10;
            break;
        case 10:
            strcpy(courseDatabase[i].classRoom, S);
            state = 11;
            break;
        case 11:
            courseDatabase[i].studentLimit = atoi(S);
            count--;
            // i++ ;
            if (count == 0)
                state = 0;
            else
                state = 2;

            i++;
            break;
        }
    }
    fclose(fptr);
}
