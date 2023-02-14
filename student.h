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
	Course(std::string n = "CourseNotSet", T g = T{}) : name(n), grade(g) {}
};

// represents a student and its grades in all courses she has taken so far.
template<typename T, size_t NumGrades>
class Student 
{
	std::string name;
	int id;
	size_t numCoursesSet{};
	std::array<Course<T>, NumGrades> courses;

	//Student()   // defauilt constructor is private, so only accessible inside the class
	//{}
public:

	Student(std::string n="NotSet", int d=-1) : name(n), id(d), numCoursesSet(0)
	{
		std::cout << "Student : ("<<name<<", "<<id<<") created\n"; 
	}

	Course<T> getCourse(size_t idx) const
	{
		return courses.at(idx);
	}

	//THis method computes the average grade for all the courses for this student and return it.
	T computeAverage()
	{
		T avg{};
		// your code goes here.
		for (size_t i = 0; i < numCoursesSet; ++i)
		{
			avg += courses[i].grade;
		}
		return avg / static_cast<T>(numCoursesSet);
	}

	void addCourse(std::string coursename, T g)
	{
		if(numCoursesSet < NumGrades)
			courses[numCoursesSet++] = Course<T>(coursename, g);
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

	int getId() const
	{
		return id;
	}

	void setId(int id)
	{
		id = id;
	}
};
	
	
	