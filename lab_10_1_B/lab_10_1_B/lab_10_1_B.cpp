// lab_10_1_B.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці

using namespace std;

enum Specialnost {
	INFORMATIKA, COMPUTER_SCIENCE, MATHEMATICS_AND_ECONOMICS,
	PHYSICS_AND_INFORMATICS, TECHNICAL_EDUCATION
};
string specialnostStr[] = { "Інформатика", "Комп’ютерні науки", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student {
	string prizv;
	int kurs;
	Specialnost spec;
	struct subject {
		int fizika;
		int matematika;
		union {
			int programming; 
			int numerical_methods;
			int pedagogy;
		};
	} subject;
};

void Create(Student* students, int N);
void Print(const Student* students, int N);
void PrintStudentAverage(const Student* students, int N);
double CalcPhysicsHighGrades(const Student* students, int N);

int main() {
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість студентів: ";
	cin >> N;
	Student* students = new Student[N];
	int menuItem;
	do {
		cout << endl << "Виберіть дію:" << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід середнього балу кожного студента" << endl;
		cout << " [4] - обчислення процента студентів, які отримали з фізики оцінки '5' або '4'" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl;
		cout << "Введіть значення: "; cin >> menuItem;

		switch (menuItem) {
		case 1:
			Create(students, N);
			break;
		case 2:
			Print(students, N);
			break;
		case 3:
			PrintStudentAverage(students, N);
			break;
		case 4:
			double percentHighGrades;
			percentHighGrades = CalcPhysicsHighGrades(students, N);
			cout << "Процент студентів, які отримали з фізики оцінки '5' або '4': " << percentHighGrades << "%" << endl;
			break;
		case 0:
			cout << "Завершення програми." << endl;
			break;
		default:
			cout << "Ви ввели помилкове значення! Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);

	delete[] students;
	return 0;
}

void Create(Student* students, int N) {
	for (int i = 0; i < N; i++) {
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.ignore();
		cout << " Прізвище: "; getline(cin, students[i].prizv);
		cout << " Курс: "; cin >> students[i].kurs;
		int spec;
		cout << " Спеціальність (0-Інформатика,1-Комп’ютерні науки,2-Математика та економіка,3-Фізика та інформатика,4-Трудове навчання): ";
		cin >> spec;
		students[i].spec = static_cast<Specialnost>(spec);
		cout << " Оцінка з фізики: "; cin >> students[i].subject.fizika;
		cout << " Оцінка з математики: "; cin >> students[i].subject.matematika;
		switch (students[i].spec) {
		case COMPUTER_SCIENCE:
			cout << " Оцінка з програмування: "; cin >> students[i].subject.programming;
			break;
		case INFORMATIKA:
			cout << " Оцінка з чисельних методів: "; cin >> students[i].subject.numerical_methods;
			break;
		default:
			cout << " Оцінка з педагогіки: "; cin >> students[i].subject.pedagogy;
			break;
		}
	}
}

void Print(const Student* students, int N) {
	cout << "==============================================================================================================================" << endl;
	cout << "| №   | Прізвище      | Курс |        Спеціальність     | Фізика | Математика | програмування | чисельні методи | педагогіка |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < N; i++) {
		cout << "| " << setw(3) << i + 1 << " | "
			<< setw(13) << students[i].prizv << " | "
			<< setw(4) << students[i].kurs << " | "
			<< setw(24) << specialnostStr[students[i].spec] << " | "
			<< setw(6) << students[i].subject.fizika << " | "
			<< setw(10) << students[i].subject.matematika << " | ";

		switch (students[i].spec) {
		case COMPUTER_SCIENCE:
			cout << setw(11) << students[i].subject.programming << "   |     " << setw(13) << "    |" << setw(13) << " |" << endl;
			break;
		case INFORMATIKA:
			cout << setw(18) << "           |   " << setw(11) << students[i].subject.numerical_methods << "   |" << setw(13)  << "|" << endl;
			break;
		default:
			cout << setw(18) << "           |   " << setw(15) << "   |" << setw(12) << students[i].subject.pedagogy << "|" << endl;
			break;
		}
	}
	cout << "==============================================================================================================================" << endl;
}

void PrintStudentAverage(const Student* students, int N) {
	cout << "=========================================" << endl;
	cout << "| Прізвище      |Середній бал студентів |" << endl;
	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < N; i++) {
		double average;
		switch (students[i].spec) {
		case COMPUTER_SCIENCE:
			average = (students[i].subject.fizika + students[i].subject.matematika + students[i].subject.programming) / 3.0;
			break;
		case INFORMATIKA:
			average = (students[i].subject.fizika + students[i].subject.matematika + students[i].subject.numerical_methods) / 3.0;
			break;
		default:
			average = (students[i].subject.fizika + students[i].subject.matematika + students[i].subject.pedagogy) / 3.0 ;
			break;
		}
		cout << "|  " << setw(13) << students[i].prizv << "|" << setw(23) << setprecision(2) << average << "|" << endl;
	}
	cout << "=========================================" << endl;
}

double CalcPhysicsHighGrades(const Student* students, int N) {
	int countHighGrades = 0, totalStudents = 0;
	for (int i = 0; i < N; i++) {
		if (students[i].subject.fizika == 4 || students[i].subject.fizika == 5) {
			countHighGrades++;
		}
		totalStudents++;
	}
	return 100.0 * countHighGrades / totalStudents;
}