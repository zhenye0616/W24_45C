// compute_grades.cpp
#include "compute_grades.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <ranges>
#include <fstream>
#include <sstream>


double average(const std::vector<int>& scores) {
    if (scores.empty()) return 0.0;
    return static_cast<double>(std::accumulate(scores.begin(), scores.end(), 0)) / scores.size();
}



// Student class member functions

void Student::validate() const {
    auto is_score_valid = [](int score) { return score >= 0 && score <= 100; };

    if (!std::all_of(quiz.begin(), quiz.end(), is_score_valid) ||
        !std::all_of(hw.begin(), hw.end(), is_score_valid) ||
        final_score < 0 || final_score > 100) {
        throw std::invalid_argument("Invalid scores found for student.");
    }
}

void Student::compute_grade() {
    compute_quiz_avg();
    compute_hw_avg();
    compute_course_score();
    compute_final_grade();
}

void Student::compute_quiz_avg() {
    if (quiz.empty()) {
        quiz_avg = 0;
    } else if (quiz.size() == 1) {
        quiz_avg = quiz.front();
    } else {
        // Find the minimum quiz score
        auto min_score = std::min_element(quiz.begin(), quiz.end());
        // Compute the sum of quiz scores excluding the minimum score
        int sum = std::accumulate(quiz.begin(), quiz.end(), 0) - *min_score;
        quiz_avg = sum / static_cast<int>(quiz.size() - 1);
    }
}


void Student::compute_hw_avg() {
    hw_avg = average(hw);
}

void Student::compute_course_score() {
    double hw_avg = !hw.empty() ? 
                    std::accumulate(hw.begin(), hw.end(), 0.0) / hw.size() 
                    : 0.0;

    double weighted_score = (quiz_avg * 0.4) + (hw_avg * 0.3) + (final_score * 0.3);

    course_score = std::round(weighted_score);
}

void Student::compute_final_grade() {
    if (course_score >= 97) course_grade = "A+";
    else if (course_score >= 93) course_grade = "A";
    else if (course_score >= 90) course_grade = "A-";
    else if (course_score >= 87) course_grade = "B+";
    else if (course_score >= 83) course_grade = "B";
    else if (course_score >= 80) course_grade = "B-";
    else if (course_score >= 77) course_grade = "C+";
    else if (course_score >= 73) course_grade = "C";
    else if (course_score >= 70) course_grade = "C-";
    else if (course_score >= 67) course_grade = "D+";
    else if (course_score >= 63) course_grade = "D";
    else if (course_score >= 60) course_grade = "D-";
    else course_grade = "F";
}



 std::strong_ordering Student::operator<=>(const Student& other) const {
        auto last_name_comparison = last_name <=> other.last_name;
        if (last_name_comparison != std::strong_ordering::equal) {
            return last_name_comparison;
        }

        // Last names are equal, compare first names
        return first_name <=> other.first_name;
    }


bool Student::operator==(const Student& other) const {
    return last_name == other.last_name && first_name == other.first_name;
}

std::istream& operator>>(std::istream& in, Student& s) {
    // Clear previous data
    s.first_name.clear();
    s.last_name.clear();
    s.quiz.clear();
    s.hw.clear();
    s.final_score = 0;

    std::string line;
    // Read the name line
    if (!std::getline(in, line) || !line.starts_with("Name"))
        return in;
    
    // Extract first and last names
    std::istringstream name_stream(line.substr(5));
    name_stream >> s.first_name;
    // Read remaining as last names
    std::string last_name_part;
    while (name_stream >> last_name_part) {
        s.last_name += last_name_part + " ";
    }
    // Remove the trailing space
    if (!s.last_name.empty()) {
        s.last_name.pop_back();
    }

    // Read the quiz scores line
    if (!std::getline(in, line) || !line.starts_with("Quiz"))
        return in;
    std::istringstream quiz_stream(line.substr(5));
    int score;
    while (quiz_stream >> score) {
        s.quiz.push_back(score);
    }

    // Read the homework scores line
    if (!std::getline(in, line) || !line.starts_with("HW"))
        return in;
    std::istringstream hw_stream(line.substr(3));
    while (hw_stream >> score) {
        s.hw.push_back(score);
    }

    // Read the final exam score line
    if (!std::getline(in, line) || !line.starts_with("Final"))
        return in;
    std::istringstream final_stream(line.substr(6));
    final_stream >> s.final_score;

    // After all the data has been read, compute the student's grade
    s.compute_grade();

    return in;
}


std::ostream& operator<<(std::ostream& out, const Student& s) {
    // Write data in the specified format with left alignment and field width of 8
    out << std::left << std::setw(8) << "Name: " << std::setw(0) << s.first_name << " " << s.last_name << "\n"
        << std::setw(8) << "HW Ave: " << std::setw(0) << static_cast<int>(s.hw_avg) << "\n"
        << std::setw(8) << "QZ Ave: " << std::setw(0) << static_cast<int>(s.quiz_avg) << "\n"
        << std::setw(8) << "Final: " << std::setw(0) << static_cast<int>(s.final_score) << "\n"
        << std::setw(8) << "Total: " << std::setw(0) << static_cast<int>(s.course_score) << "\n"
        << std::setw(8) << "Grade: " << std::setw(0) << s.course_grade << "\n";
    return out;
}





// Gradebook class member functions

void Gradebook::compute_grades() {
    std::for_each(students.begin(), students.end(), [](Student& student) {
        student.compute_grade();
    });
}

void Gradebook::sort() {
    std::sort(students.begin(), students.end());
}


void Gradebook::validate() const {
    std::for_each(students.begin(), students.end(), [](const Student& student) {
        student.validate();
    });
}



std::ostream& operator<<(std::ostream& out, const Gradebook& gb) {
    // Open the file "course_grades.txt" for writing
    std::ofstream outputFile("course_grades.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file course_grades.txt for writing." << std::endl;
        return out; // Return the original output stream if file opening fails
    }

    // Iterate over each student in the Gradebook and write them to the file
    for (const Student& student : gb.students) {
        outputFile << student; // Use existing operator<< for Student
    }

    // Close the file stream
    outputFile.close();

    return out; // Return the original output stream
}


std::istream& operator>>(std::istream& in, Gradebook& gb) {
    gb.students.clear();
    Student s;
    while (in >> s) {
        gb.students.push_back(s);
        s = Student();
    }
    return in;
}