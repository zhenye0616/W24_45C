// compute_grades.cpp
#include "compute_grades.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <ranges>

void Student::validate() const {
    // Implementation of validation logic
}

void Student::compute_grade() {
    // Call the compute methods for each component
    compute_quiz_avg();
    compute_hw_avg();
    compute_course_score();
    compute_final_grade();
}

std::strong_ordering Student::operator<=>(const Student& other) const {
    // Implementation of comparison for sorting
}

bool Student::operator==(const Student& other) const {
    // Implementation of equality check
}

std::istream& operator>>(std::istream& in, Student& s) {
    // Implementation of input stream extraction for Student
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    // Implementation of output stream insertion for Student
}

void Gradebook::compute_grades() {
    // Compute grades for all students
    for (Student& s : students) {
        s.compute_grade();
    }
}

void Gradebook::sort() {
    // Sort students using the defined operator<=> in Student
}

void Gradebook::validate() const {
    // Validate each student
    for (const Student& s : students) {
        s.validate();
    }
}

std::istream& operator>>(std::istream& in, Gradebook& b) {
    // Implementation of input stream extraction for Gradebook
}

std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    // Implementation of output stream insertion for Gradebook
}
