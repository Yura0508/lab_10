// Lab_10_2_B.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // for Cyrillic output

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
void Sort(Student* students, int N);
int* IndexSort(Student* students, const int N);
void PrintIndexSorted(Student* students, int* I, const int N);
int BinSearch(Student* students, const int N, const string prizv, const Specialnost spec, int thirdSubjectGrade);

int main() {
    SetConsoleCP(1251); // set code page for input
    SetConsoleOutputCP(1251); // set code page for output

    int N;
    cout << "Введіть кількість студентів: ";
    cin >> N;
    Student* students = new Student[N];
    int menuItem;

    do {
        cout << endl << "Виберіть дію:" << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та виведення даних" << endl;
        cout << " [5] - бінарний пошук студента за спецальністю та оцінкою з третього предмету" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl;
        cout << "Введіть значення: "; cin >> menuItem;

        string prizv;
        int spec, thirdSubjectGrade;
        int found;
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
            PrintIndexSorted(students, IndexSort(students, N), N);
            break;
        case 5:
           
            cout << "Введіть прізвище студента: "; cin >> prizv;
            cout << "Введіть спеціальність (0-Інформатика, 1-Комп’ютерні науки, 2-Математика та економіка, 3-Фізика та інформатика, 4-Трудове навчання): "; cin >> spec;
            cout << "Введіть оцінку з третього предмету: "; cin >> thirdSubjectGrade;
             found = BinSearch(students, N, prizv, static_cast<Specialnost>(spec), thirdSubjectGrade);
            if (found != -1)
                cout << "Студента знайдено на позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
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
            cout << setw(18) << "           |   " << setw(11) << students[i].subject.numerical_methods << "   |" << setw(13) << "|" << endl;
            break;
        default:
            cout << setw(18) << "           |   " << setw(15) << "   |" << setw(12) << students[i].subject.pedagogy << "|" << endl;
            break;
        }
    }
    cout << "==============================================================================================================================" << endl;
}


void Sort(Student* students, int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            bool needSwap = false;

            if (students[i1].spec > students[i1 + 1].spec) {
                needSwap = true;
            }
            
            else if (students[i1].spec == students[i1 + 1].spec) {
                int grade1, grade2;
                switch (students[i1].spec) {
                case COMPUTER_SCIENCE:
                    grade1 = students[i1].subject.programming;
                    grade2 = students[i1 + 1].subject.programming;
                    break;
                case INFORMATIKA:
                    grade1 = students[i1].subject.numerical_methods;
                    grade2 = students[i1 + 1].subject.numerical_methods;
                    break;
                default:
                    grade1 = students[i1].subject.pedagogy;
                    grade2 = students[i1 + 1].subject.pedagogy;
                    break;
                }
                if (grade1 < grade2) {
                    needSwap = true;
                }
                else if (grade1 == grade2 && students[i1].prizv > students[i1 + 1].prizv) {
                    needSwap = true;
                }
            }
            if (needSwap) {
                tmp = students[i1];
                students[i1] = students[i1 + 1];
                students[i1 + 1] = tmp;
            }
        }
}




int* IndexSort(Student* students, const int N) {
    int* I = new int[N]; // Create an index array
    for (int i = 0; i < N; i++) I[i] = i; // Fill with initial data
    int i, j, value;
    for (i = 1; i < N; i++) {
        value = I[i];
        for (j = i - 1; j >= 0; j--) {
            bool needShift = false;
            switch (students[I[j]].spec) {
            case COMPUTER_SCIENCE:
                needShift = (students[I[j]].spec > students[value].spec) ||
                    (students[I[j]].spec == students[value].spec && students[I[j]].subject.programming < students[value].subject.programming) ||
                    (students[I[j]].spec == students[value].spec && students[I[j]].subject.programming == students[value].subject.programming && students[I[j]].prizv > students[value].prizv);
                break;
            case INFORMATIKA:
                needShift = (students[I[j]].spec > students[value].spec) ||
                    (students[I[j]].spec == students[value].spec && students[I[j]].subject.numerical_methods < students[value].subject.numerical_methods) ||
                    (students[I[j]].spec == students[value].spec && students[I[j]].subject.numerical_methods == students[value].subject.numerical_methods && students[I[j]].prizv > students[value].prizv);
                break;
             default:
                needShift = (students[I[j]].spec > students[value].spec) ||
                    (students[I[j]].spec == students[value].spec && students[I[j]].subject.pedagogy < students[value].subject.pedagogy) ||
                    (students[I[j]].spec == students[value].spec && students[I[j]].subject.pedagogy == students[value].subject.pedagogy && students[I[j]].prizv > students[value].prizv);
                break;
            }
            if (needShift) {
                I[j + 1] = I[j];
            }
            else {
                break;
            }
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(Student* students, int* I, const int N) {
    cout << "==============================================================================================================================" << endl;
    cout << "| №   | Прізвище      | Курс |        Спеціальність     | Фізика | Математика | програмування | чисельні методи | педагогіка |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        int index = I[i];
        cout << "| " << setw(3) << i + 1 << " | "
            << setw(13) << students[index].prizv << " | "
            << setw(4) << students[index].kurs << " | "
            << setw(24) << specialnostStr[students[index].spec] << " | "
            << setw(6) << students[index].subject.fizika << " | "
            << setw(10) << students[index].subject.matematika << " | ";

        switch (students[index].spec) {
        case COMPUTER_SCIENCE:
            cout << setw(11) << students[index].subject.programming << "   |     " << setw(13) << "    |" << setw(13) << " |" << endl;
            break;
        case INFORMATIKA:
            cout << setw(18) << "           |   " << setw(11) << students[index].subject.numerical_methods << "   |" << setw(13) << "|" << endl;
            break;
        default:
            cout << setw(18) << "           |   " << setw(15) << "   |" << setw(12) << students[index].subject.pedagogy << "|" << endl;
            break;
        }
    }
    cout << "==============================================================================================================================" << endl;
}

int BinSearch(Student* students, const int N, const string prizv, const Specialnost spec, int thirdSubjectGrade) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (students[mid].prizv == prizv && students[mid].spec == spec) {
            switch (spec) {
            case COMPUTER_SCIENCE:
                if (students[mid].subject.programming == thirdSubjectGrade)
                    return mid;
                break;
            case INFORMATIKA:
                if (students[mid].subject.numerical_methods == thirdSubjectGrade)
                    return mid;
                break;
            default:
                if (students[mid].subject.pedagogy == thirdSubjectGrade)
                    return mid;
                break;
            }
        }
        else if (prizv < students[mid].prizv || (students[mid].prizv == prizv && students[mid].spec < spec) ||
            (students[mid].prizv == prizv && students[mid].spec == spec && 
                ((spec == COMPUTER_SCIENCE && students[mid].subject.programming < thirdSubjectGrade) ||
                    (spec == INFORMATIKA && students[mid].subject.numerical_methods < thirdSubjectGrade) ||
                    (spec != COMPUTER_SCIENCE && spec != INFORMATIKA && students[mid].subject.pedagogy < thirdSubjectGrade))))
            right = mid + 1;
        else
            left = mid - 1;
    }
    return -1;
}