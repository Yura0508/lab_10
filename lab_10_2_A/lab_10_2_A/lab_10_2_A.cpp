// lab_10_2_A.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
		int informatika;
	} subject;
};

void Create(Student* students, int N);
void Print(const Student* students, int N);
void Create(Student* students, int N);
void Print(const Student* students, int N);
void Sort(Student* students, int N);
int* IndexSort(Student* students, const int N);
void PrintIndexSorted(Student* students, int* I, const int N);
int BinSearch(Student* students, const int N, const string prizv, const Specialnost spec, int informatika);
int main() {
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість студентів: ";
	cin >> N;
	Student* students = new Student[N];
	int menuItem;

	string prizv;
	int informatika;
	int spec;
	int found;
	do {
		cout << endl << "Виберіть дію:" << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних ( 2 )" << endl;   
		cout << " [4] - бінарний пошук студента за спецальністю, 3 предметом та прізвищем ( 3 )" << endl;
		cout << " [5] - індексне впорядкування та вивід даних  ( 1 ) " << endl; 
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
			Sort(students, N);
			break;
		case 4:
		
			cout << "Введіть прізвище студента: "; cin >> prizv;
			cout << "Введіть спеціальність (0-Інформатика, 1-Комп’ютерні науки, 2-Математика та економіка, 3-Фізика та інформатика, 4-Трудове навчання): "; cin >> spec;
			cout << "Введіть оцінку з інформатики: "; cin >> informatika;
		    found = BinSearch(students, N, prizv, static_cast<Specialnost>(spec), informatika);
			if (found != -1)
				cout << "Студента знайдено на позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 5:
			PrintIndexSorted(students, IndexSort(students, N), N);
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
		cout << " Оцінка з інформатики: "; cin >> students[i].subject.informatika;
	}
}

void Print(const Student* students, int N) {
	cout << "=============================================================================================" << endl;
	cout << "| №   | Прізвище      | Курс |        Спеціальність     | Фізика | Математика | Інформатика |" << endl;
	cout << "---------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < N; i++) {
		cout << "| " << setw(3) << i + 1 << " | "
			<< setw(13) << students[i].prizv << " | "
			<< setw(4) << students[i].kurs << " | "
			<< setw(24) << specialnostStr[students[i].spec] << " | "
			<< setw(6) << students[i].subject.fizika << " | "
			<< setw(10) << students[i].subject.matematika << " | "
			<< setw(11) << students[i].subject.informatika << " |" << endl;
	}
	cout << "=============================================================================================" << endl;
}
void Sort(Student* students, int N) {
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((students[i1].spec > students[i1 + 1].spec)
				|| (students[i1].spec == students[i1 + 1].spec &&
					students[i1].subject.informatika < students[i1 + 1].subject.informatika)
				|| (students[i1].spec == students[i1 + 1].spec &&
					students[i1].subject.informatika == students[i1 + 1].subject.informatika &&
					students[i1].prizv > students[i1 + 1].prizv)) {
				tmp = students[i1];
				students[i1] = students[i1 + 1];
				students[i1 + 1] = tmp;
			}
}

int* IndexSort(Student* students, const int N) {
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value;
	for (i = 1; i < N; i++) {
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((students[I[j]].spec > students[value].spec) ||
				(students[I[j]].spec == students[value].spec &&
					students[I[j]].subject.informatika < students[value].subject.informatika) ||
				(students[I[j]].spec == students[value].spec &&
					students[I[j]].subject.informatika == students[value].subject.informatika &&
					students[I[j]].prizv > students[value].prizv));
			j--) {
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* students, int* I, const int N) {
	cout << "=============================================================================================" << endl;
	cout << "| №   | Прізвище      | Курс |        Спеціальність     | Фізика | Математика | Інформатика |" << endl;
	cout << "---------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < N; i++) {
		cout << "| " << setw(3) << i + 1 << " | "
			<< setw(13) << students[I[i]].prizv << " | "
			<< setw(4) << students[I[i]].kurs << " | "
			<< setw(24) << specialnostStr[students[I[i]].spec] << " | "
			<< setw(6) << students[I[i]].subject.fizika << " | "
			<< setw(10) << students[I[i]].subject.matematika << " | "
			<< setw(11) << students[I[i]].subject.informatika << " |" << endl;
	}
	cout << "=============================================================================================" << endl;
}

int BinSearch(Student* students, const int N, const string prizv, const Specialnost spec, int informatika) {
	int low = 0, high = N - 1, mid;


	do {
		mid = (low + high) / 2;
		if (students[mid].prizv == prizv && students[mid].spec == spec &&
			students[mid].subject.informatika == informatika)
			return mid;
		else if (students[mid].prizv < prizv || (students[mid].prizv == prizv && students[mid].spec < spec) ||
			(students[mid].prizv == prizv && students[mid].spec == spec && students[mid].subject.informatika < informatika))
			low = mid + 1;
		else
			high = mid - 1;

	} while (low <= high);


	return -1;
}