#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct Employee {
    int id;
    string name;
    string position;
    string type;
    string startDate;
    double basicSalary;
    double hourlyWage;
    double workingHours;
    int leaveDays;
    double overtimeHours;
};

const int MAX_EMPLOYEES = 100; // Maximum number of employees

// Function to calculate salary
double calculateSalary(const Employee& emp) {
    double salary = emp.basicSalary;
    double bonus = 0;
    double overtimePay = 0;
    double dailyWage = emp.basicSalary / 30.0;
    double tax = 0;
    double socialSecurity = 10.0;
    double netSalary = 0;

    if (emp.leaveDays == 0) {
        bonus = 150;
    } else if (emp.leaveDays == 1) {
        bonus = 100;
    } else if (emp.leaveDays == 2) {
        bonus = 50;
    }

    if (emp.overtimeHours > 0) {
        overtimePay = emp.overtimeHours * (2 * dailyWage);
    }

    if (emp.leaveDays > 4 && emp.overtimeHours > 0) {
        salary *= 0.99;
    }

    tax = salary * 0.02;

    netSalary = salary + bonus + overtimePay - tax - socialSecurity;
    return netSalary;
}

// Merge sort (modified for arrays)
void merge(Employee arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Employee L[n1];
    Employee R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i].id <= R[j].id) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Employee arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Function to add employee
void addEmployee(Employee employees[], int& count) {
    if (count >= MAX_EMPLOYEES) {
        cout << "Maximum employee limit reached.\n";
        return;
    }

    cout << "Enter Employee ID: ";
    cin >> employees[count].id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Employee Name: ";
    getline(cin, employees[count].name);
    cout << "Enter Position (Teacher, Administrator, Janitor, Librarian): ";
    getline(cin, employees[count].position);
    cout << "Enter Type (Full-time, Part-time, Contract): ";
    getline(cin, employees[count].type);
    cout << "Enter Start Date: ";
    getline(cin, employees[count].startDate);
    cout << "Enter Basic Salary: ";
    cin >> employees[count].basicSalary;
    cout << "Enter Hourly Wage: ";
    cin >> employees[count].hourlyWage;
    cout << "Enter Total Working Hours: ";
    cin >> employees[count].workingHours;
    cout << "Enter Leave Days Taken: ";
    cin >> employees[count].leaveDays;
    cout << "Enter Overtime Hours: ";
    cin >> employees[count].overtimeHours;

    count++;
    cout << "Employee added successfully!\n";
}

// Function to update employee information
void updateEmployee(Employee employees[], int count) {
    int id;
    cout << "Enter Employee ID to update: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            cout << "Enter new Employee Name: ";
            getline(cin, employees[i].name);
            cout << "Enter new Position: ";
            getline(cin, employees[i].position);
            cout << "Enter new Type: ";
            getline(cin, employees[i].type);
            cout << "Enter new Start Date: ";
            getline(cin, employees[i].startDate);
            cout << "Enter new Basic Salary: ";
            cin >> employees[i].basicSalary;
            cout << "Enter new Hourly Wage: ";
            cin >> employees[i].hourlyWage;
            cout << "Enter new Total Working Hours: ";
            cin >> employees[i].workingHours;
            cout << "Enter new Leave Days Taken: ";
            cin >> employees[i].leaveDays;
            cout << "Enter new Overtime Hours: ";
            cin >> employees[i].overtimeHours;
            cout << "Employee information updated successfully!\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}

// Function to view employee salary
void viewEmployeeSalary(Employee employees[], int count) {
    int id;
    cout << "Enter Employee ID to view salary: ";
    cin >> id;
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            cout << fixed << setprecision(2);
            cout << "Employee ID: " << employees[i].id << endl;
            cout << "Employee Name: " << employees[i].name << endl;
            cout << "Net Salary: $" << calculateSalary(employees[i]) << endl;
            return;
        }
    }
    cout << "Employee not found.\n";
}

// Function to view all employee information
void viewAllEmployees(Employee employees[], int count) {
    cout << fixed << setprecision(2);
    cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(15) << "Position" << setw(15) << "Type" << setw(15) << "Salary" << endl;
    cout << string(70, '-') << endl;
    for (int i = 0; i < count; i++) {
        cout << left << setw(5) << employees[i].id << setw(20) << employees[i].name << setw(15) << employees[i].position << setw(15) << employees[i].type << setw(15) << calculateSalary(employees[i]) << endl;
    }
}

int main() {
    Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;
    int choice;

    do {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. Update Employee\n";
        cout << "3. View Employee Salary\n";
        cout << "4. View All Employees\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addEmployee(employees, employeeCount);
                break;
            case 2:
                updateEmployee(employees, employeeCount);
                break;
            case 3:
                viewEmployeeSalary(employees, employeeCount);
                break;
            case 4:
                mergeSort(employees, 0, employeeCount - 1);
                viewAllEmployees(employees, employeeCount);
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
