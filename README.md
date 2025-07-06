---
# Course Recommendation & Scheduling System

A Python + C-based system for smart course searching, recommendation, and visual class scheduling.

---
## Quick Start
> make  
## or if make doesn't work  
> gcc -o test.out main.c Person.c import.c  
## Then
> python gui.py  

# Program_Final
The user interface allow as to search courses, and add courses you want, if you don't satisfied the course, you also can delete the courses. After you have selected your course done, you can preview the classtable and save it. There is a manual about the system.

# Searching
If you want to search a course, just need to enter the ID of this course on the interface and click the searching button, we will find the course and display, notice that if you enter wrong course ID, we will have a notification that tell you we can't find the ID you typed.

# Add Course
After you have seen the course you want, you can click the add_course button, and we will record the course information, so that if you want to check the courses you have selected, we can show it to you.

# List Course & Delete Course
If you have chosen a course that you don't want, you can list the course first and choose the course you want to drop, and just need to click the delete_coucrse button, we will help you to drop this course.

# Recommand Course
No idea what course you want to study? just put the keyword of this course, we will help you to list all of the courses about this keyword. For example, if you want to study the course about music, and you just need to enter keyword 'music', and we will list all the courses about music. But if you want to use this function, you have to download the model first, we will attach it on github.

# Preview Course
If you want to check courses you select, just need to click preview_class button, we will show you the classtable and the course name will listed on the position base on the time of the course. 

# Save Classtable 
If you have checked the classtable, you can click save_class button, and we will help you to save the classtable as a .jpg file, and you can share your calsstable to your friends and discuss together!
