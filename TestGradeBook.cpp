#include <array>
#include <random>
#include <time.h>

#include "student.h"
#include "Gradebook.h"

using namespace std;

using GradeBook10_3 = Gradebook<int, 10, 3>;
int getRandomID()
{
	return rand() % 9000 + 1000;  // generate a random int between 1000 and 9999
}
int main()
{
	srand(time(nullptr));
	constexpr size_t numStudents = 10;
	constexpr size_t numCourses = 3;
	array<string, numCourses> courseNames{ "Website Development", "Applied Mathematics", "Intro to Programming" };
	array< array<int, numCourses>, numStudents> grades
	{
		{{88, 90, 92},
		{39, 55, 67},
		{69, 49, 85},
		{70, 72, 77},
		{80, 81, 88},
		{91, 93, 90},
		{83, 89, 79},
		{90, 74, 77},
		{85, 67, 70},
		{55, 45, 35}}
	};

	array < string, numStudents> studentNames{ "Ali", "Xing", "Sam", "Rose", "Debbi", "Brett", "Prab", "Xu",
												"Komati", "Sid" };

	GradeBook10_3 testGradeBook("Spring 2022 CSTP");

	for (int i = 0; i < numStudents; ++i)
	{
		Student<int, numCourses> aStudent(studentNames[i], getRandomID());
		for (int j = 0; j < numCourses; ++j)
			aStudent.addCourse(courseNames[j], grades[i][j]);

		testGradeBook.addStudent(aStudent);

	}
	testGradeBook.displayMessage();
	cout << "Output grades per students:\n";
	testGradeBook.outputGradesPerStudent();

	cout << "output Average grade per course (Bar chart):";
	testGradeBook.outputGradeAveragePerCourseBarChart();

	cout << "Test average per student for Sam:\n";
	cout<<"Average for Sam is "<<testGradeBook.getAverageGradePerStudent("Sam")<<endl;

	cout << "Get Student ID:\n";
	cout << "Student ID for Xing is " << testGradeBook.getStudentID("Xing") << endl;

	cout << "Update AppliedMath grade for Xing: current grade: " <<
		testGradeBook.getStudentGradeForCourse("Xing", "Applied Mathematics");
	testGradeBook.updateStudentCourseGrade("Applied Mathematics", "Xing", 45);
	cout << "...grade after update: " << testGradeBook.getStudentGradeForCourse("Xing", "Applied Mathematics") << endl;

	// test getCourseNames:
	cout << "Print name of all courses:\n";
	for (int i = 0; i < numCourses; ++i)
		cout << testGradeBook.getCourseNameFromIdx(i) << ", ";

	cout << endl;


	cout << "\n\n End of part 1. Part 2 is about loading student data from studentData.txt and build "
		<< " a gradebook. Then perform the following tests:\n";
	const size_t NumStudents = 5;
	const size_t nNumCourses = 5;
	// 3- Load the datafile and build the gradebook:
	Gradebook<float, NumStudents, nNumCourses> theGradebook = Gradebook<float, NumStudents, nNumCourses>::buildGradeBookFromFile("studentData.txt");

	//test:
	theGradebook.displayMessage();
	cout << "Output grades per students:\n";
	theGradebook.outputGradesPerStudent();

	cout << "output Average grade per course (Bar chart):";
	theGradebook.outputGradeAveragePerCourseBarChart();

	cout << "Test average per student for Merry:\n";
	cout << "Average for Merry is " << theGradebook.getAverageGradePerStudent("Merry") << endl;

	cout << "Get Student ID:\n";
	cout << "Student ID for Sid is " << theGradebook.getStudentID("Sid") << endl;

	cout << "Print name of all courses:\n";
	for (int i = 0; i < numCourses; ++i)
		cout << theGradebook.getCourseNameFromIdx(i) << ", ";

	// set Ali's grade for WebsiteDevelopment to 80 and print his grades for all his courses:
	cout<<"Ali's grade for Web dev was "<<theGradebook.getStudentGradeForCourse("Ali", "WebsiteDevelopment");
	theGradebook.setStudentGrade("Ali", 4456, "WebsiteDevelopment", 80);
	cout << "\nAli's grade for Web dev now is " << theGradebook.getStudentGradeForCourse("Ali", "WebsiteDevelopment");
	cout << endl;

	cout << "End of Assignment\n";

	return 0;
}