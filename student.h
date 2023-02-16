#pragma once

#include <string>
#include <vector>
#include <iostream>


// represents a course and the grade student received in this course. The grade type is templated type T.
template<typename T>
struct Course
{
	std::string name;
	T grade;
	Course(std::string n = "CourseNameNotSet", T g = T{}) : name(n), grade(g) // this is also a default constructor
	{}  
};

// represents a student and its grades in all courses she has taken so far.
template<typename T, size_t NumCourses>
class Student 
{
	std::string name;  // student's name
	int id;       // student's id
	size_t numCoursesSet{}; // number of courses in the courses list that have been set so far.
	std::array<Course<T>, NumCourses> courses;
//	std::vector<Course<T>> courses;

	//Student()   // defauilt constructor is private, so only accessible inside the class
	//{}
public:

	Student(std::string n="NotSet", int d=-1) : name(n), id(d), numCoursesSet(0)
	{
		std::cout << "Student : ("<<name<<", "<<id<<") created\n"; 
	}
	
	void setCourseGrade(std::string courseName, T val)
	{
		for(auto i = 0; i < NumCourses; ++i)
		{
			if (courses[i].name == courseName)
			{
				courses[i].grade = val;
			}
		}
		
		
	}
	
	Course<T> getCourse(size_t idx) const
	{
		return courses.at(idx);
	}

	//THis method computes the average grade for all the courses for this student and return it.
	T computeAverage() const
	{
		T avg{};
		for (size_t i = 0; i < NumCourses; ++i)
		{
			avg += courses[i].grade;
		}
		// your code goes here.
		return avg / NumCourses;
	}

	void addCourse(std::string coursename, T g)
	{
		if (numCoursesSet < NumCourses)
		{
			courses[numCoursesSet] = Course<T>(coursename, g);
			++numCoursesSet;
		}
	}

	std::string getName() const
	{
		return name;
	}

	void setName(std::string n)
	{
		if(n.length() > 1)
			name = n;
	}

	void setID(int d)
	{
		if (d > 0)
			id = d;
	}

	size_t getID() const
	{
		return id;
	}
};
	
	
	
