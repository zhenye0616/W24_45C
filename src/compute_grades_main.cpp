// compute_grades_main.cpp
#include "compute_grades.hpp"
#include <fstream>

int main() {
    std::ifstream gradebook_file("gradebook.txt");  
    Gradebook b;
    gradebook_file >> b;

    b.validate();
    b.compute_grades();
    b.sort();

    std::ofstream course_grades_file("course_grades.txt");
    course_grades_file << b;

}
