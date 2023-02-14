#pragma once
// using 2 dimensional array to store student test grades.
#include <array>
#include <string>
#include <iostream>
#include <iomanip>

#include "student.h"
using namespace std;


// Gradebook class definition
template<typename T, size_t NumStudents, size_t NumCourses>
class Gradebook
{
	std::string gradebookId;  // a name that represents a cohort of students in a program, like CSTP202240 which represent spring cohort for CST program
	size_t numGradesSet{};  // represent how many students' grades have been set so far.
	std::array<Student<T, NumCourses>, NumStudents> grades; // 2D array

public:
	using StudentGrades = Student<T, NumCourses>;  // represent one student
	using CohortGrades  = std::array<StudentGrades, NumStudents>;
	using CourseGrades  = std::array<T, NumStudents>; // represents one course's grades for all students.

	// constructors
	Gradebook(std::string gbID="") : gradebookId(gbID), numGradesSet{0}
	{
		std::cout << "Gradebook created.\n";
		//grades.fill(Student<T, NumCourses>());
	}

	Gradebook() = delete;  // default constructor is not available

	void addStudent(StudentGrades aStudentGrades)
	{
		if (numGradesSet < grades.size())
		{
			grades[numGradesSet] = aStudentGrades;
			++numGradesSet;
		}
	}
	~Gradebook() 
	{
		std::cout << "gradebook destroyed. TotalNumGradebooks="
			<< getGradebookId() << std::endl;
	}

	void setGradebookId(std::string id)
	{
		gradebookId = id;
	}
	std::string getGradebookId() const
	{
		return gradebookId;
	}

	CourseGrades getACourseGrades(std::string courseName) const
	{
		return grades;
	}

	void displayMessage() const
	{
		std::cout << "Welcome to the grade book for cohort " << gradebookId << "\n";
	}

	// return the name of a course usign idx into grades array of first student
	std::string getCourseNameFromIdx(size_t idx) const
	{
		return grades[0].getCourse(idx).name;
	}
	// output to commandline students grades for all courses, one student per row, like:
	// 1- studentName studentID  grade1 grade2 grade3 ....
	// 2- studentName studentID  grade1 grade2 grade3 ....
	// 
	void outputGradesPerStudent() const
	{
		std::cout << std::setw(15) << "Student Name" << std::setw(15) << "Student ID";
		for (int i = 0; i < NumCourses; ++i)
		{
			std::string courseName = getCourseNameFromIdx(i);
			std::cout << std::setw(15) << courseName;
		}
		std::cout << std::endl;

		for (int i = 0; i < NumStudents; ++i)
		{
			StudentGrades student = grades[i];
			std::cout << std::setw(15) << student.getName() << std::setw(15) << student.getId();
			for (int j = 0; j < NumCourses; ++j)
			{
				std::cout << std::setw(15) << student.getCourse(j);
			}
			std::cout << std::endl;
		
		}
		 // your code for output student grades goes here
		for (int i = 0; i < NumCourses; ++i)
		{
			std::string courseName = getCourseNameFromIdx(i);
			std::cout << "\n Lowest grade for course " << courseName << " is " << getMinimum(courseName);
			std::cout << "\n Highetst grade for course " << courseName << " is " << getMaximum(courseName);
		}
	}

	// Find and return minimum grade for a course:
	T getMinimum(std::string courseName) const
	{
		T lowGrade{};
		lowGrade = grades[0].getCourse(courseName);

		for (const auto& studentGrades : grades)
		{
			T courseGrade = studentGrades.getCourse(courseName);

			if (courseGrade < lowGrade)
			{
				lowGrade = courseGrade;
			}
		}
		// you code goes here for finding lowGrade.

		return lowGrade;
	}

	// Find and return max grade for a course:
	T getMaximum(std::string courseName) const
	{
		T highGrade{};
		highGrade = grades[0].getCourse(courseName);

		for (const auto& studentGrades : grades)
		{
			T courseGrade = studentGrades.getCourse(courseName);
			
			if (courseGrade > highGrade)
			{
				highGrade = courseGrade;
			}
		}
		// you code goes here for finding highGrade.

		return highGrade;
	}

	// find the average grade for each course an print it using a star bar, like the following:
	//	CouseName			Average (from 0 to 10)
	//	WebSiteDevelpment	********    // means average grade is 8 x 10 = 80
	//	ComputerAdmin		*********	// means average grade is 9 x 10 = 90
	//	IntroToProgramming	******		// means average grade is 6 x 10 = 60
	// 
	// You should use setw(20) to aling the stars on column 20 on each row.
	void outputGradeAveragePerCourseBarChart() const
	{
		// your code goes here.
	}
	
	// determine average grade for a particular student
	T getAverageGradePerStudent(size_t studentID) const
	{
		// your code goes here.
		return T{};
	}
	T getAverageGradePerStudent(std::string studentName) const
	{
		// your code goes here.
		return T{};
	}

	int getStudentID(std::string studentName)
	{
		// your code goes here
		return 0;
	}
	// determine average grade for a particular test
	T getAverageGradePerCourse(std::string courseName) const
	{
		T avg{};
		// your code goes here
		return avg;
	}

	T getStudentGradeForCourse(std::string studentName, std::string courseName)
	{
		T grade{};
		// your code goes here
		return grade;
	}
	// update the grade for a given student for a given course to the newgrade.
	void updateStudentCourseGrade(std::string courseName, std::string studentName, T newgrade)
	{
		// your code goes here
	}

	
	void setStudentGrade(std::string studentName, int studentID, std::string courseName, T grade)
	{
		// your code goes here.
	}

	// This function builds a gradebook using the data in the inputfile. The type of grades is given as template argument T
	static Gradebook buildGradeBookFromFile(std::string inputfile)
	{
		// your code goes here
		// the following return is just an example. YOu must modify it once 
		// the loading of the datafile is done properly.
		return Gradebook<T, 5, 5>("DummyGradebook");
	}

};