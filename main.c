#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define clear() printf("\033[H\033[J") /* Clears screen */
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x)) /* Repositions cursor */

/* Variables for student information */
struct StudentInfo {
    char lastName[50], firstName[50], middleName[50];
    char studentNo[15], course[50], yearLevel[10];
};
/* Variables for semester data */
struct SemesterValue {
    char semesterNo[15], academicYear1[15], academicYear2[15];
};
/* Variables for student grade */
struct StudentGrade {
    char semesterYearID[15];
    char subject[50][10], grade[10][10];
    float unit[10];
    int subjectAmount;
};
/* Variables for input semester & year */
struct InputValue {
    char inputYear1[5], inputYear2[5], inputSemester[5], inputID[15];
};

int semesterYearValue; /* Value for printing desired semester & year */
int semesterYearCount = 0; /* Semester count for StudentGrade array */
bool withStudentInfo = false; /* Indicates if StudentInfo has values */
bool gradeIsValid; /* Indicates if the program has errors */

struct StudentInfo StudentInfo;
struct SemesterValue SemesterValue;
struct StudentGrade StudentGrade[15];
struct InputValue InputValue;

void mainMenu(); // Shows the Main Menu (Screen 0)
void semestralData(); // Shows Semestral Data (Screen 1)
void generateGWA(); // Shows Generate Semestral GWA Report (Screen 2)
void gradeReport(); // Shows Semestral Grade Report (Report Screen)
void unavailable(); // Shows when screen is unavailable
void gradeIncrementError(); // Shows when inputted grade is invalid

int main() {
    mainMenu();
    return 0;
}

/* Shows the Main Menu (Screen 0) */
void mainMenu() {
    /* Checks if the user has already inputted student information */
    if(withStudentInfo == false) {
        /* Display interface */
        clear();
        printf("Student Checklist and Transcript Generator\n");
        printf("Main Menu\n\n");
        printf("\nStudent Name\n");
        printf("\tLast Name =>  _______________\n");
        printf("\tFirst Name => _______________\n");
        printf("\tMiddle Name => ______________\n");
        printf("Student Number => ___________________\n");
        printf("Course => ___________________________\n");
        printf("Year Level => _\n\n");
        printf("Please Choose Option => _\n");
        printf("\t1 - Enter Semestral Data\n");
        printf("\t2 - Generate Semestral GWA Report\n");
        printf("\t3 - Generate Full Transcript\n");
        printf("\t4 - Generate Full Checklist *\n");
        printf("\tX - Exit Program");

        /* Gets student information */
        gotoxy(22, 6);
        fgets(StudentInfo.lastName, 50, stdin);
        StudentInfo.lastName[strcspn(StudentInfo.lastName, "\n")] = 0;
        gotoxy(23, 7);
        fgets(StudentInfo.firstName, 50, stdin);
        StudentInfo.firstName[strcspn(StudentInfo.firstName, "\n")] = 0;
        gotoxy(24, 8);
        fgets(StudentInfo.middleName, 50, stdin);
        StudentInfo.middleName[strcspn(StudentInfo.middleName, "\n")] = 0;
        gotoxy(19, 9);
        fgets(StudentInfo.studentNo, 15, stdin);
        StudentInfo.studentNo[strcspn(StudentInfo.studentNo, "\n")] = 0;
        gotoxy(11, 10);
        fgets(StudentInfo.course, 50, stdin);
        StudentInfo.course[strcspn(StudentInfo.course, "\n")] = 0;
        gotoxy(15, 11);
        fgets(StudentInfo.yearLevel, 10, stdin);
        StudentInfo.yearLevel[strcspn(StudentInfo.yearLevel, "\n")] = 0;

        /* Indicates user has already inputted student information */
        withStudentInfo = true;
    } else {
        /* Display interface with student information */
        clear();
        printf("Student Checklist and Transcript Generator\n");
        printf("Main Menu\n\n");
        printf("\nStudent Name\n");
        printf("\tLast Name => %s\n", StudentInfo.lastName);
        printf("\tFirst Name => %s\n", StudentInfo.firstName);
        printf("\tMiddle Name => %s\n", StudentInfo.middleName);
        printf("Student Number => %s\n", StudentInfo.studentNo);
        printf("Course => %s\n", StudentInfo.course);
        printf("Year Level => %s\n\n", StudentInfo.yearLevel);
        printf("Please Choose Option => \n");
        printf("\t1 - Enter Semestral Data\n");
        printf("\t2 - Generate Semestral GWA Report\n");
        printf("\t3 - Generate Full Transcript\n");
        printf("\t4 - Generate Full Checklist *\n");
        printf("\tX - Exit Program");
    }

    /* Takes user response to go to next screen */
    char response;
    gotoxy(25, 13);
    scanf(" %c", &response);
    response = toupper(response);
    switch(response) {
        case '1':
            semestralData();
            break;
        case '2':
            generateGWA();
            break;
        case '3':
            unavailable();
            break;
        case '4':
            unavailable();
            break;
        case 'X':
            clear();
            exit(0);
            break;
        default:
            printf("\n\n\n\n\nInvalid Input.");
            break;
    }
}

/* Shows Semestral Data (Screen 1) */
void semestralData() {
    /* Display interface */
    clear();
    printf("Student Checklist and Transcript Generator\n");
    printf("Enter Semestral Data\n\n");
    printf("Enter Semester (1/2/S) => ___\n");
    printf("Enter Academic Year => 20__ to 20__\n");
    printf("Enter Total Number of Subjects => __\n\n");

    /* Gets semester values */
    gotoxy(28, 4);
    scanf("%s", &SemesterValue.semesterNo);
    gotoxy(26, 5);
    scanf("%s", &SemesterValue.academicYear1);
    gotoxy(34, 5);
    scanf("%s", &SemesterValue.academicYear2);
    gotoxy(35, 6);
    scanf("%i", &StudentGrade[semesterYearCount].subjectAmount);

    /* Display interface for subject amount */
    printf("\nSubject\t\tUnits\t\tGrade");
    for(int i = 0; i < StudentGrade[semesterYearCount].subjectAmount; i++) {
        printf("\n__________\t_____\t\t____");
    }

    /* Sets valid grade increments */
    char validGrades[15][15] = {"1.00", "1.25", "1.50", "1.75", "2.00", "2.25", "2.50", "2.75", "3.00", "4.00", "5.00", "INC", "DRP"};

    /* Gets student grades per subject */
    for(int i = 0; i < StudentGrade[semesterYearCount].subjectAmount; i++) {
        gotoxy(1, 9 + i);
        scanf("%s", &StudentGrade[semesterYearCount].subject[i]);
        gotoxy(19, 9 + i);
        scanf("%f", &StudentGrade[semesterYearCount].unit[i]);
        gotoxy(33, 9 + i);
        scanf("%s", &StudentGrade[semesterYearCount].grade[i]);

        /* Checks if inputted grades is within accepted increments */
        for(int j = 0; j < 13; j++) {
            if(strcmp(StudentGrade[semesterYearCount].grade[i], validGrades[j]) == 0) {
                gradeIsValid = true;
                break;
            }
        }

        /* Shows error message if grade has an invalid increment */
        if(!gradeIsValid) {
            gradeIncrementError();
        }
    }

    if(gradeIsValid) {
        /* Copies and combines semester values into one variable "semesterYearID" */
        strcpy(StudentGrade[semesterYearCount].semesterYearID, SemesterValue.academicYear1);
        strcat(StudentGrade[semesterYearCount].semesterYearID, SemesterValue.academicYear2);
        strcat(StudentGrade[semesterYearCount].semesterYearID, SemesterValue.semesterNo);

        /* Display interface */
        printf("\n\nPlease Choose Option => \n");
        printf("\t1 - Enter Semestral Data\n");
        printf("\tM - Exit to Main Menu");

        /* Takes user response to go to next screen */
        char response;
        gotoxy(25, 11 + StudentGrade[semesterYearCount].subjectAmount);
        scanf(" %c", &response);
        response = toupper(response);

        /* Increment number of semesters in the array */
        semesterYearCount++;

        /* Takes user response to go to next screen */
        switch(response) {
            case '1':
                semestralData();
                break;
            case 'M':
                mainMenu();
                break;
            default:
                printf("\n\n\n\n\nInvalid Input.");
                break;
        }
    }
}

/* Shows Generate Semestral GWA Report (Screen 2) */
void generateGWA() {
    /* Display interface */
    clear();
    printf("Student Checklist and Transcript Generator\n");
    printf("Generate Semestral GWA Report\n\n");
    printf("Enter AY and Semester to Generate:\n");
    printf("\tAY 20__ to 20__\n");
    printf("\tSEMESTER => ___");
    printf("\n\nPlease Choose Option => \n");
    printf("\t1 - Generate Report\n");
    printf("\tM - Exit to Main Menu");

    /* Get input for which semester & year to display */
    gotoxy(14, 5);
    scanf("%s", &InputValue.inputYear1);
    gotoxy(22, 5);
    scanf("%s", &InputValue.inputYear2);
    gotoxy(22, 6);
    scanf("%s", &InputValue.inputSemester);

    /* Copies and combines input values into one variable "inputID" */
    strcpy(InputValue.inputID, InputValue.inputYear1);
    strcat(InputValue.inputID, InputValue.inputYear2);
    strcat(InputValue.inputID, InputValue.inputSemester);

    /* Determines which semester & year to display */
    for(int i = 0; i < semesterYearCount; i++) {
        if(StudentGrade[i].semesterYearID == InputValue.inputID) {
            semesterYearValue = i;
        }
    }

    /* Takes user response to go to next screen */
    char response;
    gotoxy(25, 8);
    scanf(" %c", &response);
    response = toupper(response);
    switch(response) {
        case '1':
            gradeReport();
            break;
        case 'M':
            mainMenu();
            break;
        default:
            printf("\n\n\n\n\n\n\n\nInvalid Input.");
            break;
    }
}

/* Shows Semestral Grade Report (Report Screen) */
void gradeReport() {
    /* Display interface */
    clear();
    printf("UNIVERSITY OF THE PHILIPPINES BAGUIO\n\n");
    printf("SEMESTRAL GRADE REPORT\n\n");
    printf("Name: %s, %s, %s", StudentInfo.lastName, StudentInfo.firstName, StudentInfo.middleName);
    printf("\nStudent Number: %s", StudentInfo.studentNo);
    printf("\nCourse: %s", StudentInfo.course);
    printf("\nYear Level: %s", StudentInfo.yearLevel);
    printf("\nAY: 20%s to 20%s", InputValue.inputYear1, InputValue.inputYear2);
    printf("\nSemester: %s\n", InputValue.inputSemester);
    printf("\nSubject\t\tUnits\t\tGrade");

    /* Print subjects grades for desired semester & year */
    for (int i = 0; i < StudentGrade[semesterYearValue].subjectAmount; i++) {
        printf("\n%s", StudentGrade[semesterYearValue].subject[i]);
        printf("\t\t%.2f", StudentGrade[semesterYearValue].unit[i]);
        printf("\t\t%s", StudentGrade[semesterYearValue].grade[i]);
    }

    double gradeNum = 0, gradeWeight = 0, totalGrade = 0;
    int unitSum = 0;
    float gwa;
    
    /* Multiplies and then sums unit and grade */
    for(int i = 0; i < StudentGrade[semesterYearValue].subjectAmount; i++) {
        /* Convert string grades into double grades */
        gradeNum = atof(StudentGrade[semesterYearValue].grade[i]);

        /* Sums valid numerical grades */
        if(gradeNum != 0) {
            gradeWeight = gradeNum * StudentGrade[semesterYearValue].unit[i];
            totalGrade = totalGrade + gradeWeight;
        }
    }

    /* Total amount of units */
    for(int i = 0; i < StudentGrade[semesterYearValue].subjectAmount; i++) {
        /* Convert string grades into double grades */
        gradeNum = atof(StudentGrade[semesterYearValue].grade[i]);

        /* Sums valid units */
        if(gradeNum != 0) {
            unitSum = unitSum + StudentGrade[semesterYearValue].unit[i];
        }
    }

    /* Calculates GWA of desired semester & year */
    gwa = totalGrade / unitSum;

    /* Checks if computed GWA is within bounds of being a scholar */
    int scholarCheck = 0;
    if(gwa <= 1.45) {
        // University Scholar
        scholarCheck = 1;
    } else if(gwa > 1.45 && gwa <= 1.75) {
        // College Scholar
        scholarCheck = 2;
    }

    /* Displays GWA as a valid increment */
    printf("\n\nGWA: %.2f", gwa);

    /* Displays congratulatory message according to raw GWA value */
    if(scholarCheck == 1) {
        printf("\n\nCONGRATULATIONS!");
        printf("\nYou have qualified as an University Scholar.");
    } else if(scholarCheck == 2) {
        printf("\n\nCONGRATULATIONS!");
        printf("\nYou have qualified as a College Scholar.");
    }

    /* Display interface */
    printf("\n\nPlease Choose Option => _\n");
    printf("\tM - Exit to Main Menu\n");
    printf("\tX - Exit Program");

    /* Takes user response to go to next screen */
    char response;
    if(scholarCheck == 1 || scholarCheck == 2) {
        gotoxy(25, 19 + StudentGrade[semesterYearValue].subjectAmount);
    } else {
        gotoxy(25, 16 + StudentGrade[semesterYearValue].subjectAmount);
    }
    scanf(" %c", &response);
    response = toupper(response);
    switch(response) {
        case 'M':
            mainMenu();
            break;
        case 'X':
            clear();
            exit(0);
            break;
        default:
            printf("\n\n\n\n\n\n\n\nInvalid Input.");
            break;
    }
}

/* Shows when screen is unavailable */
void unavailable() {
    clear();
    printf("UNDER CONSTRUCTION");

    /* Display interface */
    printf("\n\nPlease Choose Option => _\n");
    printf("\tM - Exit to Main Menu\n");
    printf("\tX - Exit Program");

    /* Takes user response to go to next screen */
    char response;
    gotoxy(25, 3);
    scanf(" %c", &response);
    response = toupper(response);
    switch(response) {
        case 'M':
            mainMenu();
            break;
        case 'X':
            clear();
            exit(0);
            break;
        default:
            printf("\n\n\n\n\n\n\n\nInvalid Input.");
            break;
    }    
}

void gradeIncrementError() {
    clear();
    printf("\nInvalid grade inputted.");

    printf("\n\nPlease Choose Option => _\n");
    printf("\tR - Retry Enter Semestral Data\n");
    printf("\tM - Exit to Main Menu");

    /* Takes user response to go to next screen */
    char response;
    gotoxy(25, 4);
    scanf(" %c", &response);
    response = toupper(response);
    switch(response) {
        case 'R':
            semestralData();
            break;
        case 'M':
            mainMenu();
            break;
        default:
            printf("\n\n\n\nInvalid Input.");
            break;
    }
}