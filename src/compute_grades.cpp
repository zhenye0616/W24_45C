// compute_grades.cpp
#include "compute_grades.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <ranges>
#include <sstream>

// Helper function to calculate average of scores
double average(const std::vector<int>& scores) {
    if (scores.empty()) return 0.0;
    return std::accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
}

// Student class member functions

void Student::validate() const {
    auto is_score_valid = [](int score) { return score >= 0 && score <= 100; };

    if (!std::ranges::all_of(quiz, is_score_valid) || 
        !std::ranges::all_of(hw, is_score_valid) || 
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
    quiz_avg = average(quiz);
}

void Student::compute_hw_avg() {
    hw_avg = average(hw);
}

void Student::compute_course_score() {
    // Assuming the weights are as follows: 40% quizzes, 40% homework, 20% final exam
    course_score = quiz_avg * 0.4 + hw_avg * 0.4 + final_score * 0.2;
}

void Student::compute_final_grade() {
    // Assign a letter grade based on the course score
    if (course_score >= 90) course_grade = "A";
    else if (course_score >= 80) course_grade = "B";
    else if (course_score >= 70) course_grade = "C";
    else if (course_score >= 60) course_grade = "D";
    else course_grade = "F";
}

std::strong_ordering Student::operator<=>(const Student& other) const {
    if (course_score < other.course_score) {
        return std::strong_ordering::less;
    } else if (course_score > other.course_score) {
        return std::strong_ordering::greater;
    } else {
        return std::strong_ordering::equal;
    }
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
    s.final_score = 0.0;

    std::string line;
    // Read the name line
    if (!std::getline(in, line) || !line.starts_with("Name"))
        return in;
    std::istringstream name_stream(line.substr(5));
    name_stream >> s.first_name >> s.last_name; // Assuming two names only; if more, logic should be changed

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
    // Write data in the specified format
    out << "Name: " << s.first_name << " " << s.last_name << "\n"
        << "HW Ave: " << std::fixed << std::setprecision(2) << s.hw_avg << "\n"
        << "QZ Ave: " << std::fixed << std::setprecision(2) << s.quiz_avg << "\n"
        << "Final: " << std::fixed << std::setprecision(2) << s.final_score << "\n"
        << "Total: " << std::fixed << std::setprecision(2) << s.course_score << "\n"
        << "Grade: " << s.course_grade << "\n\n";
    return out;
}



// Gradebook class member functions

void Gradebook::compute_grades() {
    for (Student& student : students) {
        student.compute_grade();
    }
}

void Gradebook::sort() {
    std::sort(students.begin(), students.end());
}

void Gradebook::validate() const {
    for (const Student& student : students) {
        student.validate();
    }
}

std::ostream& operator<<(std::ostream& out, const Gradebook& gb) {
    for (const Student& student : gb.students) {
        out << student;
    }
    return out;
}


std::istream& operator>>(std::istream& in, Gradebook& gb) {
    Student s;
    while (in >> s) {  // Uses the overloaded operator>> for Student
        gb.students.push_back(s);
        // Clear the student data to prepare for the next record
        s = Student();
    }
    return in;
}