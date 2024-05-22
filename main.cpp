#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
class Student {
public:
    Student() = default;
    Student(const std::string& name, const std::string& group, const std::vector<int>& grades)
            : name(name), group(group), grades(grades) {}
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Name: " << student.name << ", Group: " << student.group  << ", Grades: ";
        for (int grade : student.grades) {
            os << grade << " ";
        }
        return os;
    }
    float averageGrade() const {
        if (grades.empty()) return 0.0f;
        float sum = 0.0f;
        for (int grade : grades) {
            sum += grade;
        }
        return sum / grades.size();
    }
private:
    std::string name;
    std::string group;
    std::vector<int> grades;
};
std::vector<Student> readStudentsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Student> students;
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return students;
    }
    std::string name, group;
    std::vector<int> grades;
    while (file >> name >> group) {
        grades.resize(4);
        for (int i = 0; i < 4; ++i) {
            file >> grades[i];
        }
        students.emplace_back(name, group, grades);
    }
    file.close();
    return students;
}
void writeStudentsToFile(const std::vector<Student>& students, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }
    for (const auto& student : students) {
        file << student << std::endl;
    }
    file.close();
}
void copyVectorToDeque(const std::vector<Student>& source, std::deque<Student>& destination) {
    destination.resize(source.size());
    std::copy(source.begin(), source.end(), destination.begin());
}
void sortStudentsByAverage(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.averageGrade() > b.averageGrade();
    });
}
int main() {
    std::vector<Student> students = readStudentsFromFile("input.txt");
    writeStudentsToFile(students, "output.txt");
    sortStudentsByAverage(students);
    writeStudentsToFile(students, "output.txt");
    std::deque<Student> copiedStudents;
    copyVectorToDeque(students, copiedStudents);
    writeStudentsToFile(std::vector<Student>(copiedStudents.begin(), copiedStudents.end()), "output.txt");
    return 0;
}
