#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "import.h"
#include "Person.h"

extern class_time person_time;
extern person_course *head;
extern person_course *new;
extern recommand *value;

#define MAX_LEN 256
typedef struct person person;
struct person
{
    char department[MAX_LEN];  // 科系
    int year_standing;         // 年級
    int courseID;              // 課程ID
    int classType;             // 班別
    char courseTitle[MAX_LEN]; // 課程名稱
    char instructor[MAX_LEN];  // 教授名稱
    int credit;                // 學分數
    char creditType[MAX_LEN];  // 學分類別
    char period[MAX_LEN];      // 時段
    char classRoom[MAX_LEN];   // 教室
    int studentLimit;          // 修課人數上限
    person *next;
} *root, *current, *prev;

void list_course();
int main(int argc, char *argv[])
{
    (void)argc;
    readfile();
    initilize_course();
    readclass();
    int input;
    if (!strcmp(argv[1], "1")) // 找尋課程
    {
        input = atoi(argv[2]);
        searchCourses(0, 1853, input);
    }
    else if (!strcmp(argv[1], "2")) // 加入課程
    {
        course_time(atoi(argv[2]), atoi(argv[3]), argv[4], 1); // id, type, time
        output_courses(argv[1]);
    }
    else if (!strcmp(argv[1], "3")) // 預覽課程
    {
        output_courses(argv[1]);
    }
    else if (!strcmp(argv[1], "4")) // 推薦課程
    {
        sort_recommand(atoi(argv[2]), argv[3]);
    }
    else if (!strcmp(argv[1], "5")) // 列出課程
    {
        list_course();
    }
    else if (!strcmp(argv[1], "6")) // 刪除課程
    {
        delete_course(atoi(argv[2]), atoi(argv[3]));
        output_courses(argv[1]);
    }
    return 0;
}

void list_course()
{
    root = (person *)malloc(sizeof(person));
    int index;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (j <= 10)
            {
                if (person_time.letter_list[i][j] != 0)
                {
                    index = searchCourse(0, 1852, person_time.letter_list[i][j], person_time.letter_list_class[i][j]);
                    person *new = (person *)malloc(sizeof(person));
                    strcpy(new->classRoom, courseDatabase[index].classRoom);
                    new->classType = courseDatabase[index].classType;
                    new->courseID = courseDatabase[index].courseID;
                    strcpy(new->courseTitle, courseDatabase[index].courseTitle);
                    new->credit = courseDatabase[index].credit;
                    strcpy(new->creditType, courseDatabase[index].creditType);
                    strcpy(new->department, courseDatabase[index].department);
                    strcpy(new->instructor, courseDatabase[index].instructor);
                    strcpy(new->period, courseDatabase[index].period);
                    new->studentLimit = courseDatabase[index].studentLimit;
                    new->year_standing = courseDatabase[index].year_standing;
                    new->next = NULL;

                    current = root->next;
                    prev = root;
                    if (current == NULL)
                        root->next = new;
                    else
                    {
                        int flag = 0;
                        while (current != NULL)
                        {
                            if (current->courseID == new->courseID && current->classType == new->classType)
                            {
                                flag = 1;
                                break;
                            }
                            prev = current;
                            current = current->next;
                        }
                        if (!flag)
                        {
                            prev->next = new;
                        }
                    }
                }
            }
            if (person_time.number_list[i][j] != 0)
            {
                index = searchCourse(0, 1852, person_time.number_list[i][j], person_time.number_list_class[i][j]);
                person *new = (person *)malloc(sizeof(person));
                strcpy(new->classRoom, courseDatabase[index].classRoom);
                new->classType = courseDatabase[index].classType;
                new->courseID = courseDatabase[index].courseID;
                strcpy(new->courseTitle, courseDatabase[index].courseTitle);
                new->credit = courseDatabase[index].credit;
                strcpy(new->creditType, courseDatabase[index].creditType);
                strcpy(new->department, courseDatabase[index].department);
                strcpy(new->instructor, courseDatabase[index].instructor);
                strcpy(new->period, courseDatabase[index].period);
                new->studentLimit = courseDatabase[index].studentLimit;
                new->year_standing = courseDatabase[index].year_standing;
                new->next = NULL;

                current = root->next;
                prev = root;
                if (current == NULL)
                    root->next = new;
                else
                {
                    int flag = 0;
                    while (current != NULL)
                    {
                        if (current->courseID == new->courseID && current->classType == new->classType)
                        {
                            flag = 1;
                            break;
                        }
                        prev = current;
                        current = current->next;
                    }
                    if (!flag)
                    {
                        prev->next = new;
                    }
                }
            }
        }
    }
    current = root->next;
    while (current != NULL)
    {
        printf("Department :%s\nYear Standing: %d\nCourse ID: %d\nClass Type: %.2d\nCourse Title: %s\nPeroid: %s\nInstructor: %s\nClassroom: %s\nCredit: %d\nCredit Type: %s\nStudent Limit: %d\n", current->department, current->year_standing, current->courseID, current->classType, current->courseTitle, current->period, current->instructor, current->classRoom, current->credit, current->creditType, current->studentLimit);
        current = current->next;
    }
}
