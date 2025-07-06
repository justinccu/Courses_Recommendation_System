#ifndef import
#define import

#define MAX_LEN 256

typedef struct course course;

typedef struct course
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
} course;
course courseDatabase[1853];

void readfile();
void readclass();

#endif
