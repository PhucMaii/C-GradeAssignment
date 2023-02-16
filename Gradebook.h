#pragma once
// using 2 dimensional array to store student test grades.
#include <array>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "student.h"
using namespace std;
// Gradebook class template definition
template<typename T, size_t NumStudents, size_t NumCourses>
class Gradebook
{

	std::string gradebookId;  // a name that represents a cohort of students in a program, like CSTP202240 which represent spring cohort for CST program
	size_t numStudentSet{};  // represent how many students' grades have been set so far.
	std::array<Student<T, NumCourses>, NumStudents> students; // 2D array

public:
	using StudentGrades = Student<T, NumCourses>;  // represent one student
	using CohortGrades  = std::array<StudentGrades, NumStudents>;
	using CourseGrades  = std::array<T, NumStudents>; // represents one course's grades for all students.

	// constructors
	Gradebook(std::string gbID="GradebookIdNotSet") : gradebookId(gbID), numStudentSet{0}
	{
		std::cout << "Gradebook created.\n";
	}

	void addStudent(StudentGrades aStudentGrades)
	{
		if (numStudentSet < students.size())
		{
			students[numStudentSet] = aStudentGrades;
			++numStudentSet;
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
		CourseGrades theCourseGrades;
		// your code goes here to fill up theCourseGrades for courseName
		for (int i = 0; i < NumCourses; ++i)
		{

			if (students[0].getCourse(i).name == courseName )
			{
				for (int j = 0; j < NumStudents; ++j)
				{
					theCourseGrades[j] = students[j].getCourse(i).grade;
				}
				break;
			} 
		}
		return theCourseGrades;
	}

	void displayMessage() const
	{
		std::cout << "Welcome to the grade book for cohort " << gradebookId << "\n";
	}

	// return the name of a course usign idx into grades array of first student
	std::string getCourseNameFromIdx(size_t idx) const
	{
		return students[0].getCourse(idx).name;
	}

	// output to commandline students grades for all courses, one student per row, like:
	// 1- studentName studentID  grade1 grade2 grade3 ....
	// 2- studentName studentID  grade1 grade2 grade3 ....
	// .....
	void outputGradesPerStudent() const
	{
		 //1- your code for output student grades goes here. 

		for (int i = 0; i < NumStudents; ++i)
		{
			cout << students[i].getName() << setw(10) << students[i].getID() << setw(10);
			for (int j = 0; j < NumCourses; ++j)
			{
				cout << students[i].getCourse(j).grade << setw(10);
			}
			cout << endl;
		}
		// 2- output minimum and maximum grades for each course.
		for (int i = 0; i < NumCourses; ++i)
		{
			std::string courseName = getCourseNameFromIdx(i);
			std::cout << "\n Lowest grade for course " << courseName << " is " << getMinimum(courseName);
			std::cout << "\n Highetst grade for course " << courseName << " is " << getMaximum(courseName) << endl;
		}
	}

	// Find and return minimum grade for a course:
	T getMinimum(std::string courseName) const
	{
		T lowGrade{};
		lowGrade = 100;
		CourseGrades theCourseGrades = getACourseGrades(courseName);
		for (auto grade : theCourseGrades)
		{
			if (grade < lowGrade)
			{
				lowGrade = grade;
			}
		}
		

		return lowGrade;
	}

	// Find and return max grade for a course:
	T getMaximum(std::string courseName) const
	{
		T highGrade{};
		// you code goes here for finding highGrade.
		CourseGrades theCourseGrades = getACourseGrades(courseName);
		for (auto grade : theCourseGrades)
		{
			if (grade > highGrade)
			{
				highGrade = grade;
			}
		}

		return highGrade;
	}

	// find the average grade for each course an print it using a star bar, like the following:
	//	CouseName			Average (from 0 to 10)
	//	WebSiteDevelpment	********    // means average grade is between 70 and 8 x 10 = 80
	//	ComputerAdmin		*********	// means average grade is between 80 and 9 x 10 = 90
	//	IntroToProgramming	******		// means average grade is 6 x 10 = 60
	// 
	// You should use setw(20) to aling the stars on column 20 on each row.
	// note: use getAverageGradePerCourse() for each course.
	void outputGradeAveragePerCourseBarChart() const
	{
		for (int i = 0; i < NumCourses; ++i)
		{
			CourseGrades theCourseGrades =  getACourseGrades(students[0].getCourse(i).name);
			cout << students[0].getCourse(i).name << setw(10);
			// calculate average
			double avg = 0;
			for (auto grade : theCourseGrades)
			{
				avg += grade;
			}

			// printing stars
			avg /= (sizeof(theCourseGrades)/ sizeof(int)) * 10;
			for (int j = 0; j <= avg; ++j)
			{
				cout << "*";
			}

			cout << endl;
		}
		// your code goes here.
	}
	
	// determine average grade for a particular student
	T getAverageGradePerStudent(size_t studentID) const
	{
		T studentAvg{};
		// your code goes here for computing studentAvg
		for(size_t i = 0; i < NumStudents; ++i)
		{
			size_t stuID = students[i].getID();
			
			if (stuID == studentID)
			{
				studentAvg = students[i].computeAverage();
			}
			break;
		}
		return studentAvg;
	}
	T getAverageGradePerStudent(std::string studentName) const
	{
		T studentAvg{};
		// your code goes here for computing studentAvg
		for(size_t i = 0; i < NumStudents; ++i)
		{
			string stuName = students[i].getName();

			if (stuName == studentName)
			{
				studentAvg = students[i].computeAverage();
			}
		}
		return studentAvg;
	}

	size_t getStudentID(std::string studentName)
	{
		size_t studentId{};
		// your code goes here to figure out studentId
		for (int i = 0; i < NumStudents; ++i)
		{
			string stuName = students[i].getName();
			if (stuName == studentName)
			{
				studentId = students[i].getID();
			}
		}
		return studentId;
	}

	// determine average grade for a particular test
	T getAverageGradePerCourse(std::string courseName) const
	{
		T avg{};

		CourseGrades theCourseGrades = getACourseGrades(courseName);
		for (auto grade : theCourseGrades)
		{
			avg += grade; 
		}
		// your code goes here
		return avg / (sizeof(theCourseGrades)/ sizeof(int)) ;
	}

	T getStudentGradeForCourse(std::string studentName, std::string courseName) const
	{
		T grade{};
		// here goes your code to find grade.
		for (int i = 0; i < NumStudents; ++i)
		{	
			if (students[i].getName() == studentName)
			{
				for (int j = 0; j < NumCourses; ++j)
				{
					if (students[i].getCourse(j).name == courseName)
					{
						grade = students[i].getCourse(j).grade;
					}
				}
			}
		}


		return grade;
	}
	// update the grade for a given student for a given course to the newgrade.
	void setStudentCourseGrade(std::string courseName, std::string studentName, size_t studentID, T newgrade)
	{
		// your code goes here

		for (int i = 0; i < NumStudents; ++i)
		{
			if (students[i].getName() == studentName && students[i].getID() == studentID)
			{

				for (int j = 0; j < NumCourses; ++j)
				{
					if (students[i].getCourse(j).name == courseName)
					{
						
						students[i].setCourseGrade(courseName, newgrade);
					}
				}
			}
		}
	}

	// This function builds a gradebook using the data in the inputfile. The type of grades is given as template argument T
	static Gradebook buildGradeBookFromFile(std::string inputfile)
	{
		Gradebook<T, 5, 5> theGradebook;
		// your code goes here
		// the following return is just an example. YOu must modify it once 
		// the loading of the datafile is done properly.
		ifstream fs(inputfile);
		if (fs.is_open())
		{
			string firstLine;
			string gradebookId1;
			string gradebookId2;
			string gradebookId3;
			getline(fs, firstLine);
			stringstream ss(firstLine);
			ss >> gradebookId1 >> gradebookId2 >> gradebookId3;
			theGradebook.setGradebookId(gradebookId1 + " " + gradebookId2 + " " + gradebookId3);


			string aline{};
			while (getline(fs, aline))
			{
				cout << "Line read: " << aline << endl;
				string name;
				int id;

				stringstream ss(aline);
				ss >> name >> id;
				Student<T, NumCourses> student(name, id);
				for (int i = 0; i < 5; ++i)
				{
					string courseName;
					T grade;
					ss >> courseName >> grade;
					student.addCourse(courseName, grade);
					
				}
				theGradebook.addStudent(student);

			}
			fs.close();

		}
		else{
			cout << "Error opening file" << endl;
		}

		return theGradebook;
	}
};
