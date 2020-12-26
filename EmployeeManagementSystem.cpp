// 1. Struct Declaration        =====   Line 30-53
// 2. Pointer Declaration       =====   Line 39-43
// 3. 2D Array Declaration      =====   Line 24
// 4. Stack Declaration         =====   Line 26
// 5. Queue Declaration         =====   Line 27

#include <iostream>
#include <queue>
#include <stack>
#include <string> //Package to convert int to string
#include <sstream> //Package to convert string to int
#include <time.h> //Packages for random number
#include <math.h> //Packages for random number
using namespace std;
#define MAX_EMPLOYEE_SIZE 100 // DEFINING MAX SIZE OF THE EMPLOYEE YOU CAN INPUT

void createEmployee(); // Function to create Employee Data
void readEmployee(); // Function to diplay the table of employees
void updateEmployee(); // Function to update a Employee Data
void deleteEmployee(); // Function to Delete Employee Data
void menu(); // Function to display the selection
int main();

string EMPLOYEES[MAX_EMPLOYEE_SIZE][5]; // Multidimensional Array Declaration: Container of the Employee Data
int numberOfEmployees; // counter of the how many employees has been created
stack<int> uniqueEmployeeIdStack; // Stack Declaration: Container of the unique ID that can be passed to the employees
queue<string> employeeIdQueue; // Queue Declaration: Container of the Active Employees ID

//Structure declaration
struct Employee
{
    string id;
    string firstName;
    string lastName;
    string salary;
    string position;

    //Pointer declaration
    string *id_pointer = &id;
    string *firstName_pointer = &firstName;
    string *lastName_pointer = &lastName;
    string *salary_pointer = &salary;
    string *position_pointer = &position;

    void returnEmployees(string _id, string _firstName, string _lastName, string _salary, string _position)
    {
        *id_pointer = _id;
        *firstName_pointer = _firstName;
        *lastName_pointer = _lastName;
        *salary_pointer = _salary;
        *position_pointer = _position;
    }
};

void randomNum(int randomNumber[], int elements);

int main()
{
    system("CLS"); // To Clear the Console
    int numbers[100] = {0}; // Number of unique ID
    srand(static_cast<int>(time(0)));
    randomNum(numbers, 100); // Generating Random 100 Unique ID

    //To generate new Unique ID if the stack of Unique ID is empty
    if (uniqueEmployeeIdStack.empty())
    {
        randomNum(numbers, 100);  // Generating Random 100 Unique ID
    }

    menu(); // To display Create, Read, Update and Delete Option Menu
    return 0;
}

void menu()
{
    system("CLS"); // To Clear the Console
    cout << "\n================================  Employee Management System  ================================\n\n";
    int option;

    cout << "Press 1 Create Employee\n";
    cout << "Press 2 Read Employees\n";
    cout << "Press 3 Update Employee\n";
    cout << "Press 4 Delete Employee\n";
    cout << "Press Any Key To Quit the Program\n\n";

    cout << "Enter option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        createEmployee();
        break;
    case 2:
        readEmployee();
        break;

    case 3:
        updateEmployee();
        break;

    case 4:
        deleteEmployee();
        break;
    default:
        break;
    }
}

// Function to create Employee Data
void createEmployee()
{
    system("CLS"); // To Clear the Console
    int option;
    numberOfEmployees += 1;

    cout << "\n================================  Create Employee  ================================\n\n";

    Employee EmployeeMember;
    string employeeId = to_string(uniqueEmployeeIdStack.top()); // Converting the INT Unique ID number to String so that it can be store to the string multidimentional array
    string firstName;
    string lastName;
    string salary;
    string position;

    cout << "Enter First Name: ";
    cin.sync(); // this is to avoid immidiate capture of enter key when using getline
    getline(cin, firstName);// Inputing First Name
    cout << "Enter Last Name: ";
    getline(cin, lastName);  // Inputing Last Name
    cin.sync(); 
    cout << "Enter Salary: ";
    cin >> salary; // Inputing Salary
    cin.sync();
    cout << "Enter Position: ";
    getline(cin, position);   // Inputing Position
    cin.sync();

    EmployeeMember.returnEmployees(employeeId, firstName, lastName, salary, position); // Returning the value that has been inputed to the Employee Structure

    employeeIdQueue.push(EmployeeMember.id); // Pushing the Unique ID to the Queue as a Record
    EMPLOYEES[numberOfEmployees - 1][0] = EmployeeMember.id; // Creating Employee ID
    EMPLOYEES[numberOfEmployees - 1][1] = EmployeeMember.firstName; // Creating Employee First Name
    EMPLOYEES[numberOfEmployees - 1][2] = EmployeeMember.lastName; // Creating Employee Last Name
    EMPLOYEES[numberOfEmployees - 1][3] = EmployeeMember.salary; // Creating Employee Salary
    EMPLOYEES[numberOfEmployees - 1][4] = EmployeeMember.position; // Creating Employee Postion
    uniqueEmployeeIdStack.pop(); // Removing the Unique ID to the queue that has been used by the employee that has been created to maintain uniqueness of ID 
    system("CLS"); // To Clear the Console

    cout << "\n-------------   STATUS:OK     -------------\n";
    cout << "\nEmployee has been Successfully Created!\n";
    cout << "\n-------------   STATUS:OK    -------------\n";
    cout << "\n\nPress 0 to Go Back to Menu\n";
    cout << "Press 1 to Enter Another Employee\n"
         << "\nEnter Option:";
    cin >> option;

    switch (option)
    {
    case 0:
        menu();
        break;
    case 1:
        createEmployee();
    default:
        menu();
    }
}

// Function to diplay the table of employees
void readEmployee()
{
    system("CLS"); // To Clear the Console
    cout << "\n================================  Employee Table  ================================\n\n";
    int option;
    cout << "ID\t\tFirst Name\tLast Name\tSalary\t\tPosition\t\n";
    cout << "-----------------------------------------------------------------------------------\n";

    //For Loop to create the table that displays the Employees
    for (int i = 0; i < numberOfEmployees; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << EMPLOYEES[i][j];
            cout<< "\t\t";
        }
        cout << "\n";
    }

    cout << "\n\nPress 0 to Go Back to Menu\n";
    cout << "\nEnter Option:";
    cin >> option;

    switch (option)
    {
    case 0:
        menu();
        break;
    default:
        menu();
    }
}

// Function to update a Employee Data
void updateEmployee()
{
    system("CLS"); // To Clear the Console
    int option;
    string employeeId; // The user will input the Employee ID to Update
    bool isFindEmployee = false; // Boolean that checks if the user input a valid employee ID
    Employee EmployeeMember;
    queue<string> employeeToEdit = employeeIdQueue; // Copying the Queue to manipulate the data
    cout << "\n================================  Update Employee  ================================\n\n";
    cout << "ID\t\tFirst Name\tLast Name\tSalary\t\tPosition\t\n";
    cout << "-----------------------------------------------------------------------------------\n";

    //Displaying the Employee Table
    for (int i = 0; i < numberOfEmployees; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << EMPLOYEES[i][j] << "\t\t";
        }
        cout << "\n";
    }

    cout << "\n\nEnter Employee ID: ";
    cin >> employeeId;
    int counter = 0; // counter that increments while the employeeToEdit is not emptied; it also matches the array position of the employeeId of the user want to update
    while (!employeeToEdit.empty())
    {
        counter++;  // increments while is not empty employeeToEdit; and it serves as the targeter index position of the selected Employee ID
        if (employeeToEdit.front() == employeeId)
        {
            cout << "Enter Updated First Name: ";
            cin >> EMPLOYEES[counter - 1][1]; // Updating Employee First Name
            cout << "Enter Updated Last Name: ";
            cin >> EMPLOYEES[counter - 1][2]; // Updating Employee Last Name
            cout << "Enter Updated Salary: ";
            cin >> EMPLOYEES[counter - 1][3]; // Updating Employee Salary
            cout << "Enter Updated Position: ";
            cin >> EMPLOYEES[counter - 1][4]; // Updating Employee Position
            isFindEmployee = true;  // setting the isFindEmployee to true because the user inputs valid Employee ID
        }
        employeeToEdit.pop(); 
    }
    system("CLS"); // To Clear the Console
    //If the user input a valid employeeId and successfully updated a employee
    if (isFindEmployee)
    {
        cout << "\n-------------   STATUS:OK     -------------\n";
        cout << "\nEmployee has been Successfully Updated!\n";
        cout << "\n-------------   STATUS:OK    -------------\n";
    }
    //If the user input a invalid employeeId
    else
    {
        cout << "\n----------- STATUS:Bad Request -----------\n";
        cout << "\nEmployee has been Unsuccessfully Removed!\n";
        cout << "\n----------- STATUS:Bad Request -----------\n";
    }

    cout << "\n\nPress 0 to Go Back to Menu\n";
    cout << "Press 1 to Update Another Employee\n"
         << "\nEnter Option:";
    cin >> option;

    switch (option)
    {
    case 0:
        menu();
        break;
    case 1:
        updateEmployee();
    default:
        menu();
    }
}

 // Function to Delete Employee Data
void deleteEmployee()
{
    system("CLS"); // To Clear the Console
    int option;
    string employeeId; // The user will input the Employee ID to Delete
    bool isFindEmployee = false; // Boolean that checks if the user input a valid employee ID
    Employee EmployeeMember;
    queue<string> employeeToRemove = employeeIdQueue;  // Copying the Queue to manipulate the data
    queue<string> employeeToRetain; // Container to push the Unique ID that has not been removed then pass it to the original queue
    cout << "\n================================  Delete Employee  ================================\n\n";
    cout << "ID\t\tFirst Name\tLast Name\tSalary\t\tPosition\t\n";
    cout << "-----------------------------------------------------------------------------------\n";

    //Displaying the Employee Table
    for (int i = 0; i < numberOfEmployees; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << EMPLOYEES[i][j] << "\t\t";
        }
        cout << "\n";
    }

    cout << "\n\nEnter Employee ID: ";
    cin >> employeeId;
    stringstream geek(employeeId); // Converting string to int
    int employeeIdInt; // container for the employeeId that has will be converted to int
    geek >> employeeIdInt; // Converting string to int

    int counter = 0;  // counter that increments while the employeeToEdit is not emptied; it also matches the array position of the employeeId of the user want to update
    
    while (!employeeToRemove.empty())
    {
        counter++;  // increments while is not empty employeeToRemove; and it serves as the targeter index position of the selected Employee ID
        // If the employeeToRemove(employeeIdQueue) matches the ID of the users inputed
        if (employeeToRemove.front() == employeeId)
        {
            // Loop that removing the element in the Multidimensional Array of the Employee ID that the user inputed 
            for (int i = counter - 1; i < numberOfEmployees - 1; i++)
            {
                EMPLOYEES[i][0] = EMPLOYEES[i + 1][0]; // Copying the next array element Employee ID to current element
                EMPLOYEES[i][1] = EMPLOYEES[i + 1][1]; // Copying the next array element First Name to current element
                EMPLOYEES[i][2] = EMPLOYEES[i + 1][2]; // Copying the next array element Last Name to current element
                EMPLOYEES[i][3] = EMPLOYEES[i + 1][3]; // Copying the next array element Salary to current element
                EMPLOYEES[i][4] = EMPLOYEES[i + 1][4]; // Copying the next array element Position to current element
            }

            numberOfEmployees--; // Decerementing the number of employees
            isFindEmployee = true; // setting the isFindEmployee to true because the user inputs valid Employee ID
        }
        else
        {
            employeeToRetain.push(employeeToRemove.front()); // adding the employees that has not been remove to the employeeToRetain
        }

        employeeToRemove.pop();
    }
    system("CLS"); // To Clear the Console
     //If the user input a valid employeeId and successfully updated a employee
    if (isFindEmployee)
    {
        cout << "\n-------------   STATUS:OK     -------------\n";
        cout << "\nEmployee has been Successfully Removed!\n";
        cout << "\n-------------   STATUS:OK    -------------\n";
    }
     //If the user input a invalid employeeId
    else
    {
        cout << "\n----------- STATUS:Bad Request -----------\n";
        cout << "\nEmployee has been Unsuccessfully Removed!\n";
        cout << "\n----------- STATUS:Bad Request -----------\n";
    }

    employeeIdQueue = employeeToRetain; // returning to the employeeIdQueue all the employee that has been retain and that has been properly arrange/sort
    cout << "\n\nPress 0 to Go Back to Menu\n";
    cout << "Press 1 to Remove Another Employee\n"
         << "\nEnter Option:";
    cin >> option;

    switch (option)
    {
    case 0:
        menu();
        break;
    case 1:
        deleteEmployee();
    default:
        menu();
    }
}

//Generating Unique ID Number for Employees
void randomNum(int randomNumber[], int elements)
{
    srand(time(NULL));
    for (int i = 0; i < elements; i++)
    {
        bool same;
        do
        {
            int result, digitIndex, currentDigit;
            int resultNum;
            int numberOfUniqueID = 100; // Number of Unique ID that will be generated
            same = false;

            //Generate 100 Unique ID
            for (resultNum = 0; resultNum < numberOfUniqueID; resultNum++)
            {
                result = 0;
                //Loop that generate 5 digits and adds to result
                for (digitIndex = 0; digitIndex < 5; digitIndex++)
                {
                    currentDigit = rand() % 10;
                    currentDigit *= pow(10, digitIndex);
                    result += currentDigit;
                }
            }

            uniqueEmployeeIdStack.push(result); // Pushing the Unique ID to the Container
            randomNumber[i] = result; // Temporary container for the Unique ID

            // Loop to check if the newly generated number is a duplicate:
            for (int check = 0; check < i; check++)
            {
                if (randomNumber[i] == randomNumber[check])
                {
                    same = true;
                    break;
                }
            }
        } while (same);
    }
}
