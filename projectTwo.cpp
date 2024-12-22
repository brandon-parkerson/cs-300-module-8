#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
// Brandon Parkerson
// snhu
// cs-300
// 12.15.2024

// Structure to hold course details
struct Course {
    std::string courseNumber;
    std::string courseName;
    std::vector<std::string> prerequisites;
};

// Function declarations
void loadCourses(const std::string& filename, std::map<std::string, Course>& courses);
void printCourseList(const std::map<std::string, Course>& courses);
void printCourseDetails(const std::map<std::string, Course>& courses, const std::string& courseNumber);

int main() {
    std::map<std::string, Course> courses;
    int choice = 0;

    std::cout << "Welcome to the course planner." << std::endl;

    do {
        std::cout << "\n1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "\nWhat would you like to do? ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string filename;
                std::cout << "Enter the file name to load: ";
                std::cin >> filename;
                loadCourses(filename, courses);
                break;
            }
            case 2:
                printCourseList(courses);
                break;
            case 3: {
                std::string courseNumber;
                std::cout << "What course do you want to know about? ";
                std::cin >> courseNumber;
                printCourseDetails(courses, courseNumber);
                break;
            }
            case 9:
                std::cout << "Thank you for using the course planner!" << std::endl;
                break;
            default:
                std::cout << choice << " is not a valid option." << std::endl;
        }
    } while (choice != 9);

    return 0;
}

// Function to load courses from a CSV file
void loadCourses(const std::string& filename, std::map<std::string, Course>& courses) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string courseNumber, courseName, prereq;

        std::getline(ss, courseNumber, ',');
        std::getline(ss, courseName, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.courseName = courseName;

        while (std::getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses[courseNumber] = course;
    }

    file.close();
    std::cout << "Courses loaded successfully!" << std::endl;
}

// Function to print the course list in alphanumeric order
void printCourseList(const std::map<std::string, Course>& courses) {
    if (courses.empty()) {
        std::cout << "No courses loaded. Please load the data structure first." << std::endl;
        return;
    }

    std::cout << "\nHere is a sample schedule: " << std::endl;
    for (const auto& pair : courses) {
        std::cout << pair.first << ", " << pair.second.courseName << std::endl;
    }
}

// Function to print course details
void printCourseDetails(const std::map<std::string, Course>& courses, const std::string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it == courses.end()) {
        std::cout << "Course not found." << std::endl;
        return;
    }

    const Course& course = it->second;
    std::cout << course.courseNumber << ", " << course.courseName << std::endl;

    if (course.prerequisites.empty()) {
        std::cout << "Prerequisites: None" << std::endl;
    } else {
        std::cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            std::cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}
