#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define ARG_NUM_VAL 2
#define BEST "best"
#define QUICK "quick"
#define BUBBLE "bubble"
#define ARGS_ERR "Usage: <best|quick|bubble>\n"
#define STUDENTS_NUM_REQUEST "Enter the number of students. Then enter"

typedef struct Student {
    int id, grade, age;
} Student;

void best_student (Student *start, Student *end);
void bubble_sort (Student *start, Student *end);
void quick_sort (Student *start, Student *end);
Student *partition (Student *start, Student *end);


int main (int argc, char *argv[])
{
  if (argc != ARG_NUM_VAL)
    {
      fprintf (stdout, ARGS_ERR);
      return EXIT_FAILURE;
    }
  char *argument = argv[1];
  if (strcmp (argument, BEST) == 0)
    {

    }
  else if (strcmp (argument, QUICK) == 0)
    {

    }

  else if (strcmp (argument, BUBBLE) == 0)
    {

    }
  else      //wrong argument
  {
      fprintf (stdout, ARGS_ERR);
      return EXIT_FAILURE;
    }
}