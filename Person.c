#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "import.h"
#include "Person.h"

class_time person_time;
person_course *head;
person_course *new;
recommand *value;

void delete_course(int target_id, int target_type)
{
    int success = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (j <= 10)
            {
                if (person_time.letter_list[i][j] == target_id && person_time.letter_list_class[i][j] == target_type)
                {
                    person_time.letter_list[i][j] = 0;
                    person_time.letter_list_class[i][j] = 0;
                    success++;
                }
            }
            if (person_time.number_list[i][j] == target_id && person_time.number_list_class[i][j] == target_type)
            {
                person_time.number_list[i][j] = 0;
                person_time.number_list_class[i][j] = 0;
                success++;
            }
        }
    }
    if (!success)
        printf("Error! Class ID: %d, Type:%.2d is not in your schedule\n", target_id, target_type);
    else
        printf("Success Delete: Class ID: %d, Type:%.2d\n", target_id, target_type);
}

int cmpfunc(const void *a, const void *b)
{
    const recommand *dataA = (const recommand *)a;
    const recommand *dataB = (const recommand *)b;
    if (dataA->vector > dataB->vector)
        return -1;
    else if (dataA->vector < dataB->vector)
        return 1;
    else
        return 0;
}

void sort_recommand(int num, char *vec)
{
    const char s[2] = " ";
    char *token;
    token = strtok(vec, s);
    int count = 0;

    value = (recommand *)malloc(sizeof(recommand) * num);
    while (token != NULL)
    {
        // printf("%s\n", token);
        value[count].array = atoi(token);
        token = strtok(NULL, s);
        value[count++].vector = atof(token);
        token = strtok(NULL, s);
    }
    qsort(value, num, sizeof(recommand), cmpfunc);
    for (int i = 0; i < num; i++)
    {
        int start = value[i].array;
        if (num < 3 || (i <= 5 && value[i].vector >= 0.75))
            printf("Department :%s\nYear Standing: %d\nCourse ID: %d\nClass Type: %.2d\nCourse Title: %s\nPeroid: %s\nInstructor: %s\nClassroom: %s\nCredit: %d\nCredit Type: %s\nStudent Limit: %d\n", courseDatabase[start].department, courseDatabase[start].year_standing, courseDatabase[start].courseID, courseDatabase[start].classType, courseDatabase[start].courseTitle, courseDatabase[start].period, courseDatabase[start].instructor, courseDatabase[start].classRoom, courseDatabase[start].credit, courseDatabase[start].creditType, courseDatabase[start].studentLimit);
    }
}

void output_courses(char *ctl)
{
    FILE *file;
    
    char path[256];
    getcwd(path, sizeof(path));
    strcat(path, "/output.txt");
    file = fopen(path, "w+");
    
    // file = fopen("/Users/justinkim/Desktop/Courses_Recommendation_System/Final_Project/output.txt", "w+");
    if (file == NULL)
    {
        printf("can't open file\n");
        return;
    }

    int id, type;
    // printf("%d %d", id, type) ;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            // printf("%d\n", person_time.number_list[i][j]) ;
            if (person_time.number_list[i][j] != 0 || (j < 11 && person_time.letter_list[i][j] != 0))
            {
                if (person_time.number_list[i][j] != 0)
                {
                    id = person_time.number_list[i][j];
                    type = person_time.number_list_class[i][j];
                    // printf("##n:%d %d %d %d\n",i, j, id, type) ;
                }
                else if (person_time.letter_list[i][j] != 0 && j < 11)
                {
                    id = person_time.letter_list[i][j];
                    type = person_time.letter_list_class[i][j];
                    // printf("##l:%d %d %d %d\n",i, j, id, type) ;
                }

                int left = 0, right = 1853;

                while (left <= right)
                { // search course
                    int mid = left + (right - left) / 2;
                    // Check if the target is present at the middle
                    if (courseDatabase[mid].courseID == id)
                    {
                        while (courseDatabase[mid].classType != type)
                        {
                            if (courseDatabase[mid].classType > type)
                            {
                                mid--;
                            }
                            else if (courseDatabase[mid].classType < type)
                            {
                                mid++;
                            }
                        }
                        // printf("%d\n",j) ;
                        fprintf(file, "%d\n%.2d\n%s\n", courseDatabase[mid].courseID, courseDatabase[mid].classType, courseDatabase[mid].period);
                        if (!strcmp(ctl, "3"))
                        {
                            printf("%s\n%s\n", courseDatabase[mid].courseTitle, courseDatabase[mid].period);
                        }

                        // printf("write success!\n") ;
                        break;
                    }
                    else if (courseDatabase[mid].courseID < id)
                        left = mid + 1;
                    // If the target is smaller, ignore the right half
                    else
                        right = mid - 1;
                }

                // printf("!!%d %d\n", id, type) ;
                for (int m = 0; m < 6; m++)
                {
                    for (int n = 0; n < 16; n++)
                    {

                        if (((person_time.number_list[m][n] == id) && (person_time.number_list_class[m][n] == type)) || ((n < 11) && (person_time.letter_list[m][n] == id) && (person_time.letter_list_class[m][n] == type)))
                        {
                            // printf("@@%d %d %d %d\n", person_time.number_list[m][n], person_time.number_list_class[m][n], id, type) ;
                            if (person_time.number_list[m][n] == id && person_time.number_list_class[m][n] == type)
                            {
                                person_time.number_list[m][n] = 0;
                                person_time.number_list_class[m][n] = 0;
                            }
                            else if (person_time.letter_list[m][n] == id && person_time.letter_list_class[m][n] == type)
                            {
                                person_time.letter_list[m][n] = 0;
                                person_time.letter_list_class[m][n] = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(file);
}

void searchCourses(int left, int right, int target_id)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        // Check if the target is present at the middle
        if (courseDatabase[mid].courseID == target_id)
        {
            while (1)
            {
                mid--;
                if (courseDatabase[mid].courseID != target_id)
                {
                    printCourses(mid + 1, target_id);
                    return;
                }
            }
        }
        // If the target is greater, ignore the left half
        if (courseDatabase[mid].courseID < target_id)
            left = mid + 1;
        // If the target is smaller, ignore the right half
        else
            right = mid - 1;
    }
    // Target element is not present in the array
    printf("-1");
}

int searchCourse(int left, int right, int target_id, int target_type)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        // Check if the target is present at the middle
        if (courseDatabase[mid].courseID == target_id)
        {
            while (courseDatabase[mid].classType != target_type)
            {
                if (courseDatabase[mid].classType > target_type)
                    mid--;
                else if (courseDatabase[mid].classType < target_type)
                    mid++;
            }
            return mid;
        }
        // If the target is greater, ignore the left half
        if (courseDatabase[mid].courseID < target_id)
            left = mid + 1;
        // If the target is smaller, ignore the right half
        else
            right = mid - 1;
    }
    return -1;
}

void printCourses(int start, int target_id)
{
    while (courseDatabase[start].courseID == target_id)
    {
        // print課程資訊
        printf("Department :%s\nYear Standing: %d\nCourse ID: %d\nClass Type: %.2d\nCourse Title: %s\nPeroid: %s\nInstructor: %s\nClassroom: %s\nCredit: %d\nCredit Type: %s\nStudent Limit: %d\n", courseDatabase[start].department, courseDatabase[start].year_standing, courseDatabase[start].courseID, courseDatabase[start].classType, courseDatabase[start].courseTitle, courseDatabase[start].period, courseDatabase[start].instructor, courseDatabase[start].classRoom, courseDatabase[start].credit, courseDatabase[start].creditType, courseDatabase[start].studentLimit);
        start++;
    }
}

void initilize_course()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (j <= 10)
            {
                person_time.letter_list[i][j] = 0;
                person_time.letter_list_class[i][j] = 0;
            }
            person_time.number_list[i][j] = 0;
            person_time.number_list_class[i][j] = 0;
        }
    }
}

void course_time(int id, int type, char *date, int check)
{
    char *day;
    day = malloc(sizeof(char) * 5);
    int session;
    int flag = 0, available = 0;
run:
    strncpy(day, date, 3);
    *(day + 3) = '\0';
    int len = (int)strlen(date);
    for (int i = 3; i < len; i++)
    {
        if (date[i] == '\n') // end of line
            break;
        if (date[i] == ' ') // if there's space means there's another day
        {
            day[0] = date[++i];
            day[1] = date[++i];
            day[2] = date[++i];
            continue;
        }
        // printf("~%s\n", day);
        if (date[i] == '.' || date[i] == ',') // ignore '.' and ','
            continue;
        if (date[i] >= '1' && date[i] <= '9') // course 1 to 9
        {
            session = date[i] - 48;
            if (date[i + 1] >= '0' && date[i + 1] <= '9') // 10 to 15
            {
                session *= 10;
                session += date[++i] - 48;
            }
            if (!check_course(day, session) && !available)
            {
                printf("Already have course in %s %d.\n", day, session);
                flag++;
            }
            else if (available)
                // printf("aaa %s %d\n",day,  session) ;
                add_courses(id, type, day, session); // successfully add course
        }
        else if (date[i] >= 'A' && date[i] <= 'J') // course A to J
        {
            session = (int)date[i] - 49; // A represent 16 in 課表 to check course
            if (!check_course(day, session) && !available)
            {
                session = (int)date[i] - 64; // A represent 1 in 課表
                printf("Already have course in %s %c.\n", day, date[i]);
                flag++;
            }
            else if (available)
            {
                session = (int)date[i] - 49;         // A represent 16 in add course
                add_courses(id, type, day, session); // successfully add course
            }
        }
    }
    if (available && check)
    { // end adding course
        printf("Success!!\n");
        return;
    }
    else if (available)
        return;

    if (!flag)
    {
        available = 1; // available to add this course
        goto run;      // go back to add course
    }
}

int check_course(char *time, int session)
{
    int day = -1;
    if (!strcmp(time, "Mon"))
        day = Mon;
    else if (!strcmp(time, "Tue"))
        day = Tue;
    else if (!strcmp(time, "Wed"))
        day = Wed;
    else if (!strcmp(time, "Thu"))
        day = Thu;
    else if (!strcmp(time, "Fri"))
        day = Fri;
    else
    {
        printf("Time Occur Error, Please Check !\n");
        return 0;
    }

    switch (session)
    {
    case 1:
        if (person_time.number_list[day][1] == 0 && person_time.letter_list[day][1] == 0)
            return 1;
        else
            return 0;
    case 2:
        if (person_time.number_list[day][2] == 0 && person_time.letter_list[day][1] == 0 && person_time.letter_list[day][2] == 0)
            return 1;
        else
            return 0;
    case 3:
        if (person_time.number_list[day][3] == 0 && person_time.letter_list[day][2] == 0)
            return 1;
        else
            return 0;
    case 4:
        if (person_time.number_list[day][4] == 0 && person_time.letter_list[day][3] == 0)
            return 1;
        else
            return 0;
    case 5:
        if (person_time.number_list[day][5] == 0 && person_time.letter_list[day][3] == 0 && person_time.letter_list[day][4] == 0)
            return 1;
        else
            return 0;
    case 6:
        if (person_time.number_list[day][6] == 0 && person_time.letter_list[day][4] == 0)
            return 1;
        else
            return 0;
    case 7:
        if (person_time.number_list[day][7] == 0 && person_time.letter_list[day][5] == 0)
            return 1;
        else
            return 0;
    case 8:
        if (person_time.number_list[day][8] == 0 && person_time.letter_list[day][5] == 0 && person_time.letter_list[day][6] == 0)
            return 1;
        else
            return 0;
    case 9:
        if (person_time.number_list[day][9] == 0 && person_time.letter_list[day][6] == 0)
            return 1;
        else
            return 0;
    case 10:
        if (person_time.number_list[day][10] == 0 && person_time.letter_list[day][7] == 0)
            return 1;
        else
            return 0;
    case 11:
        if (person_time.number_list[day][11] == 0 && person_time.letter_list[day][7] == 0 && person_time.letter_list[day][8] == 0)
            return 1;
        else
            return 0;
    case 12:
        if (person_time.number_list[day][12] == 0 && person_time.letter_list[day][8] == 0)
            return 1;
        else
            return 0;
    case 13:
        if (person_time.number_list[day][13] == 0 && person_time.letter_list[day][9] == 0)
            return 1;
        else
            return 0;
    case 14:
        if (person_time.number_list[day][14] == 0 && person_time.letter_list[day][9] == 0 && person_time.letter_list[day][10] == 0)
            return 1;
        else
            return 0;
    case 15:
        if (person_time.number_list[day][15] == 0 && person_time.letter_list[day][10] == 0)
            return 1;
        else
            return 0;
    case A:
        if (person_time.letter_list[day][1] == 0 && person_time.number_list[day][1] == 0 && person_time.number_list[day][2] == 0)
            return 1;
        else
            return 0;
    case B:
        if (person_time.letter_list[day][2] == 0 && person_time.number_list[day][2] == 0 && person_time.number_list[day][3] == 0)
            return 1;
        else
            return 0;
    case C:
        if (person_time.letter_list[day][3] == 0 && person_time.number_list[day][4] == 0 && person_time.number_list[day][5] == 0)
            return 1;
        else
            return 0;
    case D:
        if (person_time.letter_list[day][4] == 0 && person_time.number_list[day][5] == 0 && person_time.number_list[day][6] == 0)
            return 1;
        else
            return 0;
    case E:
        if (person_time.letter_list[day][5] == 0 && person_time.number_list[day][7] == 0 && person_time.number_list[day][8] == 0)
            return 1;
        else
            return 0;
    case F:
        if (person_time.letter_list[day][6] == 0 && person_time.number_list[day][8] == 0 && person_time.number_list[day][9] == 0)
            return 1;
        else
            return 0;
    case G:
        if (person_time.letter_list[day][7] == 0 && person_time.number_list[day][10] == 0 && person_time.number_list[day][11] == 0)
            return 1;
        else
            return 0;
    case H:
        if (person_time.letter_list[day][8] == 0 && person_time.number_list[day][11] == 0 && person_time.number_list[day][12] == 0)
            return 1;
        else
            return 0;
    case I:
        if (person_time.letter_list[day][9] == 0 && person_time.number_list[day][13] == 0 && person_time.number_list[day][14] == 0)
            return 1;
        else
            return 0;
    case J:
        if (person_time.letter_list[day][10] == 0 && person_time.number_list[day][14] == 0 && person_time.number_list[day][15] == 0)
            return 1;
        else
            return 0;
    default:
        printf("Time Occur Error, Please Check !\n");
        return 0;
    }
};

void add_courses(int id, int type, char *time, int session)
{
    int day = -1;
    if (!strcmp(time, "Mon"))
        day = Mon;
    else if (!strcmp(time, "Tue"))
        day = Tue;
    else if (!strcmp(time, "Wed"))
        day = Wed;
    else if (!strcmp(time, "Thu"))
        day = Thu;
    else if (!strcmp(time, "Fri"))
        day = Fri;
    if (session >= 1 && session <= 15)
    {
        // printf("Session one, %d %d %d %d\n", day, session, id, type);
        person_time.number_list[day][session] = id;
        person_time.number_list_class[day][session] = type;
    }
    else
    {
        session -= 15; // A represent 1
        // printf("Session two, %d %d\n", day, session);
        person_time.letter_list[day][session] = id;
        person_time.letter_list_class[day][session] = type;
    }
}