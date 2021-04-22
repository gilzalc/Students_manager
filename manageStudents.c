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

#define STUDENTS_NUM_REQUEST "Enter number of students. Then enter\n"
#define STUDENTS_INFO_REQUEST "Enter student info. Then enter\n"

#define INVALID_STUDENTS_NUM "ERROR: Number should be a natural number\n"
#define INVALID_ID "ERROR: ID should be in a format of 10 digits, when the \
first digit is not a 0\n"
#define INVALID_AGE "ERROR: Age should be an integer between 18 and 120 "\
"(includes)\n"
#define INVALID_GRADE "ERROR: Grade should be an integer between 0 and 100\
(includes)\n"

/**
 * @brief represents a student of the hebrew university of jerusalem
 */
typedef struct Student {
    long int _id;
    int _grade, _age;
    float _ageGradeQuotient;
} Student;

/**
 * this function checks if a string is composed by merely digits chars.
 * @param string to be checked.
 * @return 1 if it has only digits ,0 o.w
 */
int has_just_digits (const char *string)
{

  for (int i = 0; i < (int) strlen (string); i++)
    {
      if (!isdigit(string[i]))
        return 0;
    }
  return 1;
}
/**
 * @brief gets the number of students in the university from the user
 * @return number of students
 */
long get_students_num ()
{
  char stud_num_string[MAX_LINE_LENGTH];
  long std_num;
  while (true)
    {
      printf (STUDENTS_NUM_REQUEST);
      char input[MAX_LINE_LENGTH];
      if (fgets (input, MAX_LINE_LENGTH, stdin) == NULL)
        exit (EXIT_FAILURE);
      if (sscanf (input, "%s", stud_num_string) != 1)
        exit (EXIT_FAILURE);
      // Check if only digits and if positive
      if (!has_just_digits (stud_num_string))
        {
          fprintf (stdout, INVALID_STUDENTS_NUM);
          continue;
        }
      std_num = strtol (stud_num_string, NULL, DECIMAL);
      if (std_num <= 0)
        {
          fprintf (stdout, INVALID_STUDENTS_NUM);
          continue;
        }
      break;
    }
  return std_num;
}
/**
 * @brief checks if a given string is a valid id
 * @param id string to check
 * @return 1 if valid,0 o.w
 */
int is_valid_id (const char *id)
{
  int len = (int) strlen (id);
  if (len != ID_LEN || id[0] == '0') //check first char
    return 0;
  return has_just_digits (id);
}
/**
 * @brief checks if a string is a number, and a positive one, within a valid
 * range
 * @param s string to check
 * @param minVal - minimal value
 * @param maxVal maximal value
 * @return
 */
int is_valid_ranged (const char *s, int minVal, int maxVal)
{
  if (has_just_digits (s) == 0)
    return 0;
  long n_grade = strtol (s, NULL, DECIMAL);
  if (n_grade <= maxVal && n_grade >= minVal)
    return 1;
  return 0;
}
/**
 * @brief checks if a given string is a valid grade
 * @param grade string to check
 * @return 1 if valid,0 o.w
 */
int is_valid_grade (const char *grade)
{
  return is_valid_ranged (grade, MIN_GRADE, MAX_GRADE);
}
/**
 * @brief checks if a given string is a valid age
 * @param age string to check
 * @return 1 if valid,0 o.w
 */
int is_valid_age (const char *age)
{
  return is_valid_ranged (age, MIN_AGE, MAX_AGE);
}
/*
 * function that gets the information about the students of the school
 */
Student *get_students_info (long stdNum)
{
  Student *student_arr = malloc (stdNum * sizeof (Student));
  if (student_arr == NULL)
    exit (EXIT_FAILURE);
  int i = 0;
  while (i < stdNum)
    {
      printf (STUDENTS_INFO_REQUEST);
      char input[MAX_LINE_LENGTH], age[MAX_VAR_LENGTH],
          grade[MAX_VAR_LENGTH], id[MAX_VAR_LENGTH];
      if (fgets (input, MAX_LINE_LENGTH, stdin) == NULL)
        exit (EXIT_FAILURE);
      if (sscanf (input, "%[^,],%[^,],%s", id, grade, age) != 3)
        exit (EXIT_FAILURE);
      if (!is_valid_id (id))
        {
          fprintf (stdout, INVALID_ID);
          continue;
        }
      if (!is_valid_grade (grade))
        {
          fprintf (stdout, INVALID_GRADE);
          continue;
        }
      if (!is_valid_age (age))
        {
          fprintf (stdout, INVALID_AGE);
          continue;
        }
      student_arr[i]._id = strtol (id, NULL, DECIMAL);
      student_arr[i]._age = (int) strtol (age, NULL, DECIMAL);
      student_arr[i]._grade = (int) strtol (grade, NULL, DECIMAL);
      student_arr[i]._ageGradeQuotient =
          (float) student_arr[i]._grade / (float) student_arr[i]._age;
      ++i; //next line
    }
  return student_arr;
}
/**
 * @brief returns the student with the best age/grade ratio
 * @param start pointer to the beginning of the array
 * @param end pointer to the end of the array
 */
void best_student (Student *start, Student *end)
{
  float max = 0;
  Student *to_return;
  for (int i = 0; i < end - start; i++)
    {
      if (start[i]._ageGradeQuotient > max)
        {
          max = (start->_ageGradeQuotient);
          to_return = &start[i];
        }
    }
  printf ("best student info is: %ld,%d,%d\n",
          to_return->_id, to_return->_grade, to_return->_age);
}
/**
 * Swaps two Students in an array
 * @param xp first Student (pointer)
 * @param yp Second student (pointer)
 */
void swap (Student *s1p, Student *s2p)
{
  Student temp = *s1p;
  *s1p = *s2p;
  *s2p = temp;
}
/**
 * @brief the old and famous bubble sort, with a twist - uses pointer
 * arithmetics instead of classic indexing
 * @param start pointer to the start of the arr
 * @param end pointer to the end of the arr
 */
void bubble_sort (Student *start, Student *end)
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
/**
 * @brief prints the students array
 * @param students students array
 * @param totalNum length of array (num of students in the school)
 */
void print_students (Student *students, long totalNum)
{
  for (int i = 0; i < totalNum; ++i)
    {
      printf ("%lu,%d,%d\n",
              students[i]._id,
              students[i]._grade,
              students[i]._age);
    }
}

Student *partition (Student *start, Student *end)
{
//  Student *pivot = getPivot (start,end);
  Student *pivot = end;
//  swap (start,pivot);
  Student *border = start;
  for (int i = 0; i <= end - start; i++) //age
    {
      if ((((start + i))->_age) < (((pivot))->_age))
        swap (start + i, ++border);
    }
  swap (border + 1, end);
  return border + 1;
}

void quick_sort (Student *start, Student *end)
{
  if ((end - start) > 0)
    {
      Student *p = partition (start, end);
      quick_sort (start, p - 1);
      quick_sort (p + 1, end);
    }
}

int main (int argc, char *argv[])
{
  if (argc != ARG_NUM_VAL)
    {
      fprintf (stdout, ARGS_ERR);
      return EXIT_FAILURE;
    }
  int check = 0;
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

  long studs_num;
  studs_num = get_students_num (); //num of students
  Student *studs;
  studs = get_students_info (studs_num);
  switch (check)
    {
      case BEST_CHAR:
        {
          best_student (studs, studs + studs_num);
          break;
        }
      case BUBBLE_CHAR:
        {
          bubble_sort (studs, studs + studs_num);
          print_students (studs, studs_num);
          break;
        }
      case QUICK_CHAR:
        {
          quick_sort (studs, studs + studs_num);
          print_students (studs, studs_num);
          break;
        }
      default:
        return EXIT_FAILURE;
    }
  free (studs);
  return EXIT_SUCCESS;
}
