#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#define MAX_EMPLOYEES 10

typedef struct Employee
{
char firstName[100];
char lastName[100];
char email[100];
char specialty[100];
double salary;
char phone[20];
} Employee;

// Function Prototypes
void addEmployee();
void displayEmployee();
void calculateSalary();
void removeEmployee();
void searchEmployee();

int main(){
int choice;
printf("Welcome to the Employee Database!\n");
printf("Please choose an option:\n");
printf("1. Add Employee\n");
printf("2. Display Employees\n");
printf("3. Calculate Salary\n");
printf("4. Remove Employee\n");
printf("5. Search Employee\n");
printf("6. Exit\n");
scanf("%d", &choice);
switch(choice){
case 1:
addEmployee();
break;
case 2:
displayEmployee();
break;
case 3:
calculateSalary();
break;
case 4:
removeEmployee();
break;
case 5:
searchEmployee();
break;
case 6:
printf("Thank you!\n");
break;
default:
printf("Invalid choice!\n");
break;
}
return 0;
}

// Function Definitions
void addEmployee(){
Employee employee;
printf("Enter the first name: ");
scanf("%s", employee.firstName);
printf("Enter the last name: ");
scanf("%s", employee.lastName);
printf("Enter the email address: ");
scanf("%s", employee.email);
printf("Enter the specialty: ");
scanf("%s", employee.specialty);
printf("Enter the salary: ");
scanf("%lf", &employee.salary);
printf("Enter the phone number: ");
scanf("%s", employee.phone);

// write data to file
FILE *fp;
fp = fopen("Employees Manager.xlsx", "a");
if (fp == NULL) {
printf("Could not open file\n");
exit(0);
}
fprintf(fp, "%s %s %s %s %lf %s\n",
employee.firstName,
employee.lastName,
employee.email,
employee.specialty,
employee.salary,
employee.phone);
fclose(fp);
printf("Employee added successfully!\n");
}

void displayEmployee(){
// read data from file
FILE *fp;
fp = fopen("Employees Manager.xlsx", "r");
if (fp == NULL) {
printf("Could not open file\n");
exit(0);
}
Employee employee;
printf("--------------------------------------------\n");
printf("Name\t\tEmail\t\tSpecialty\tSalary\t\tPhone\n");
printf("--------------------------------------------\n");
while(fscanf(fp, "%s %s %s %s %lf %s\n",
employee.firstName,
employee.lastName,
employee.email,
employee.specialty,
&employee.salary,
employee.phone) != EOF){
printf("%s %s\t%s\t%s\t%.2lf\t%s\n",
employee.firstName,
employee.lastName,
employee.email,
employee.specialty,
employee.salary,
employee.phone);
}
printf("--------------------------------------------\n");
fclose(fp);
}

void calculateSalary(){
FILE *fp;
fp = fopen("Employees Manager.xlsx", "r");
if (fp == NULL) {
printf("Could not open file\n");
exit(0);
}
Employee employee;
double total = 0;
while(fscanf(fp, "%s %s %s %s %lf %s\n",
employee.firstName,
employee.lastName,
employee.email,
employee.specialty,
&employee.salary,
employee.phone) != EOF){
total += employee.salary;
}
printf("Total salary of all employees: $%.2lf\n", total);
fclose(fp);
}

void removeEmployee(){
char name[100];
printf("Enter the first and last name of the employee: ");
scanf("%s", name);
FILE *fp;
fp = fopen("Employees Manager.xlsx", "r");
if (fp == NULL) {
printf("Could not open file\n");
exit(0);
}
Employee employee;
int found = 0;
while(fscanf(fp, "%s %s %s %s %lf %s\n",
employee.firstName,
employee.lastName,
employee.email,
employee.specialty,
&employee.salary,
employee.phone) != EOF){
if(strcmp(name, employee.firstName) == 0 || strcmp(name, employee.lastName) == 0){
found = 1;
break;
}
}
fclose(fp);
if(found == 0){
printf("Employee not found!\n");
return;
}
// remove from file
FILE *fp2;
fp2 = fopen("Employees Manager.xlsx", "r");
FILE *fp3;
fp3 = fopen("temp.txt", "w");
while(fscanf(fp2, "%s %s %s %s %lf %s\n",
employee.firstName,
employee.lastName,
employee.email,
employee.specialty,
&employee.salary,
employee.phone) != EOF){
if(strcmp(name, employee.firstName) != 0 && strcmp(name, employee.lastName) != 0){
fprintf(fp3, "%s %s %s %s %lf %s\n",
employee.firstName,
employee.lastName,
employee.email,
employee.specialty,
employee.salary,
employee.phone);
}
}
fclose(fp2);
fclose(fp3);
remove("Employees Manager.xlsx");
rename("temp.xlsx", "Employees Manager.xlsx");
printf("Employee removed successfully!\n");
}

void searchEmployee(){
char name[100];
printf("Enter the first and last name of the employee: ");
scanf("%s", name);
FILE *fp;
fp = fopen("Employees Manager.xlsx", "r");
if (fp == NULL) {
printf("Could not open file\n");
exit(0);
}
Employee employee;
int found = 0;
while(fscanf(fp, "%s %s %s %s %lf %s\n",
employee.firstName,
employee.lastName,
employee.email,
employee.specialty,
&employee.salary,
employee.phone) != EOF){
if(strcmp(name, employee.firstName) == 0 || strcmp(name, employee.lastName) == 0){
found = 1;
break;
}
}
fclose(fp);
if(found == 0){
printf("Employee not found!\n");
return;
}
printf("--------------------------------------------\n");
printf("Name\t\tEmail\t\tSpecialty\tSalary\t\tPhone\n");
printf("--------------------------------------------\n");
printf("%s %s\t%s\t%s\t%.2lf\t%s\n",
employee.firstName,
employee.lastName,
employee.email,
employee.specialty,
employee.salary,
employee.phone);
printf("--------------------------------------------\n");
}