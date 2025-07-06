#ifndef Person
#define Person

#define Mon 1
#define Tue 2
#define Wed 3
#define Thu 4
#define Fri 5
#define A 16
#define B 17
#define C 18
#define D 19
#define E 20
#define F 21
#define G 22
#define H 23
#define I 24
#define J 25

typedef struct class_time
{
    int number_list[6][16];
    int number_list_class[6][16];
    int letter_list[6][11];
    int letter_list_class[6][11];
} class_time;

typedef struct person_course
{
    int courseID;
    struct person_course *next;
} person_course;

typedef struct recommand recommand;
struct recommand
{
    int array;
    float vector;
};

void delete_course(int target_id, int target_type);
void list_course();
int cmpfunc(const void *a, const void *b);
void sort_recommand(int num, char *vec);
void output_courses(char *ctl);
void searchCourses(int left, int right, int target_id);
int searchCourse(int left, int right, int target_id, int target_type);
void printCourses(int start, int target_id);
void initilize_course();
void course_time(int id, int type, char *date, int check);
int check_course(char *time, int session);
void add_courses(int id, int type, char *time, int session);

#endif
