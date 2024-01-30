#include <stdio.h>

int main(void)
{
	// Declare variables
	float assignment_grade = 0.0f, lab_exam_grade = 0.0f, final_exam_grade = 0.0f;
	float overall_grade = 0.0f;

	// Handle input of grades
	printf("Please enter the assignment grade of the student: ");
	scanf("%f", &assignment_grade);

	printf("Please enter the lab exam grade of the student: ");
	scanf("%f", &lab_exam_grade);

	printf("Please enter the final exam grade of the student: ");
	scanf("%f", &final_exam_grade);

	// Calculate overall grade
	overall_grade = (assignment_grade + lab_exam_grade + final_exam_grade * 2)/4.0f;

	char grade_letter = 'A';

	if(overall_grade < 40) grade_letter = 'E';
	else if(overall_grade < 50) grade_letter = 'D';
	else if(overall_grade < 60) grade_letter = 'C';
	else if(overall_grade < 70) grade_letter = 'B';

	// Display the overall mark and grade
	printf("The overall mark is: %.2f%%, and the grade is: %c\n", overall_grade, grade_letter);
}
