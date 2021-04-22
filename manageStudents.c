#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define ARG_NUM_VAL 2
#define MAX_LINE_LENGTH 60
#define MAX_VAR_LENGTH 20
#define DECIMAL 10
#define ID_LEN 10
#define MIN_AGE 18
#define MAX_AGE 120
#define MIN_GRADE 0
#define MAX_GRADE 100
#define BUBBLE_CHAR 's'
#define QUICK_CHAR 'q'
#define BEST_CHAR 'b'
#define BEST "best"
#define QUICK "quick"
#define BUBBLE "bubble"
#define ARGS_ERR "Usage: <best|quick|bubble>\n"
#define STUDENTS_NUM_REQUEST "Enter the number of students. Then enter\n"
#define STUDENTS_INFO_REQUEST "Enter student info. Then enter\n"

#define INVALID_STUDENTS_NUM "ERROR: Number should be a natural number\n"
#define INVALID_ID "ERROR: ID should be in a format of 10 digits, when the \
first digit is not a 0\n"
#define INVALID_AGE "ERROR: Age should be an integer between 18 and 120 "\
"(includes)\n"
#define INVALID_GRADE "ERROR: Grade should be an integer between 0 and 100\
(includes)\n"

typedef struct Student {
    long int _id;
    int _grade, _age;
    float _ageGradeQuotient;
} Student;

/**
 * this function checks if s consists of digits only.
 * @param s - string to be checked.
 * @return 1 upon success, 0 for failure.
 */
int hasJustDigits (const char *string)
{

  for (int i = 0; i < strlen (string); i++)
    {
      if (!isdigit(string[i]))
        return 0;
    }
  return 1;
}

long getStudentsNum ()
{
  char studNumString[MAX_LINE_LENGTH];
  long stdNum;
  while (true)
    {
      printf (STUDENTS_NUM_REQUEST);
      char input[MAX_LINE_LENGTH];
      fgets (input, MAX_LINE_LENGTH, stdin);
      sscanf (input, "%s", studNumString);// Check if only digits and if positive
      //check validity:
      if (!hasJustDigits (studNumString))
        {
          fprintf (stdout, INVALID_STUDENTS_NUM);
          continue;
        }
      stdNum = strtol (studNumString, NULL, DECIMAL);
      if (stdNum <= 0)
        {
          fprintf (stdout, INVALID_STUDENTS_NUM);
          continue;
        }
      break;
    }
  return stdNum;
}

int isValidId (const char *id)
{
 int len =  strlen(id);
  if (len != ID_LEN || id[0] == '0') //check first char
    return 0;
  return hasJustDigits (id);
}
int isValidRangedNum (const char *s, int minVal, int maxVal)
{
  if (hasJustDigits (s) == 0)
    return 0;
  long nGrade = strtol (s, NULL, DECIMAL);
  if (nGrade <= maxVal && nGrade >= minVal)
    return 1;
  return 0;
}

int isValidGrade (const char *grade)
{
  return isValidRangedNum (grade, MIN_GRADE, MAX_GRADE);
}

int isValidAge (const char *age)
{
  return isValidRangedNum (age, MIN_AGE, MAX_AGE);
}

Student *getStudentsInfo (long stdNum)
{
  Student *studentArr = malloc (stdNum * sizeof (Student));
  if (studentArr == NULL)
    exit (EXIT_FAILURE);
  int i = 0;
  while (i < stdNum)
    {
      printf (STUDENTS_INFO_REQUEST);
      char input[MAX_LINE_LENGTH], age[MAX_VAR_LENGTH],
          grade[MAX_VAR_LENGTH], id[MAX_VAR_LENGTH];
      fgets (input, MAX_LINE_LENGTH, stdin);
      if (sscanf (input, "%[^,],%[^,],%s", id, grade, age))
        if (!isValidId (id))
          {
            fprintf (stdout, INVALID_ID);
            continue;
          }
      if (!isValidGrade (grade))
        {
          fprintf (stdout, INVALID_GRADE);
          continue;
        }
      if (!isValidAge (age))
        {
          fprintf (stdout, INVALID_AGE);
          continue;
        }
      studentArr[i]._id = strtol (id, NULL, DECIMAL);
      studentArr[i]._age = (int) strtol (age, NULL, DECIMAL);
      studentArr[i]._grade = (int) strtol (grade, NULL, DECIMAL);
      studentArr[i]._ageGradeQuotient =
          (float) studentArr[i]._grade / (float) studentArr[i]._age;
      ++i; //next line
    }
  return studentArr;
}

void best_student (Student *start, Student *end)
{
  float max = 0;
  Student *toReturn;
  for (int i = 0; i < end - start; i++)
    {
      if (start[i]._ageGradeQuotient > max)
        {
          max = (start->_ageGradeQuotient);
          toReturn = &start[i];
        }
    }
  printf ("best student info is: %ld,%d,%d\n", toReturn->_id, toReturn->_grade,
          toReturn->_age);
}
/**
 * Swaps two Students
 * @param xp first Student
 * @param yp Second student
 */
void swap (Student *xp, Student *yp)
{
  Student temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void bubbleSort (Student *start, Student *end)
{
  int i, j;
  long n = end - start;
  for (i = 0; i < n - 1; i++)
    {
      for (j = 0; j < n - i - 1; j++)
        {
          if ((((start + j))->_grade) > (((start + j + 1))->_grade))
            swap ((start + j), (start + j + 1));
        }
    }
}

void printStudents (Student *students, long totalNum)
{
  for (int i = 0; i < totalNum; ++i)
    {
      printf ("%lu,%d,%d\n",
               students[i]._id,
               students[i]._grade,
               students[i]._age);
    }
}




Student *partition (Student *start, Student *end){
//  Student *pivot = getPivot (start,end);
Student *pivot = end;
//  swap (start,pivot);
  Student *border = start-1;
  for (int i = 0; i <=end-start ; i++) //age
    {
      if ((((start + i))->_age) < (((pivot))->_age))
        swap (start+i,++border);
    }
  swap (border+1,end);
  return border+1;
}

void quickSort (Student *start, Student *end)
{
  if ((end - start) > 0)
    {
      Student *p = partition (start, end);
      quickSort (start, p - 1);
      quickSort (p + 1, end);
    }
}

int main (int argc, char *argv[])
{
  if (argc != ARG_NUM_VAL)
    {
      fprintf (stdout, ARGS_ERR);
      return EXIT_FAILURE;
    }
  char check = 0;
  char *argument = argv[1]; //read only
  if (strcmp (argument, BEST) == 0)
    check = BEST_CHAR;
  else if (strcmp (argument, QUICK) == 0)
    check = QUICK_CHAR;
  else if (strcmp (argument, BUBBLE) == 0)
    check = BUBBLE_CHAR;
  if (check == 0)
    {
      fprintf (stdout, ARGS_ERR);
      return EXIT_FAILURE;
    }

  long studsNum = 0;
  studsNum = getStudentsNum (); //num of students
  Student *studs;
  studs = getStudentsInfo (studsNum);
  switch (check)
    {
      case BEST_CHAR:
        {
          best_student (studs, studs + studsNum);
          break;
        }
      case BUBBLE_CHAR:
        {
          bubbleSort (studs, studs + studsNum);
          printStudents (studs, studsNum);
          break;
        }
      case QUICK_CHAR:
        {
          quickSort (studs, studs + studsNum);
          printStudents (studs, studsNum);
          break;
        }
      default:
        return EXIT_FAILURE;
    }
  free (studs);
  return EXIT_SUCCESS;
}


//Student *getPivot(Student *start,Student *end){
//  long length =end-start;
//  Student *pivot;
//  pivot = (start+(random()%(length-1)));
//  return pivot;
//}