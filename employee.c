#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 100
#define NAME_LEN 64

char emp_id[MAX_EMPLOYEES][NAME_LEN];
char emp_name[MAX_EMPLOYEES][NAME_LEN];
char emp_dept[MAX_EMPLOYEES][NAME_LEN];
char emp_email[MAX_EMPLOYEES][NAME_LEN];
char emp_phone[MAX_EMPLOYEES][NAME_LEN];
char emp_address[MAX_EMPLOYEES][NAME_LEN];
char emp_payroll_id[MAX_EMPLOYEES][NAME_LEN];
double emp_salary[MAX_EMPLOYEES];
int    emp_working_days[MAX_EMPLOYEES];
int    emp_leaves[MAX_EMPLOYEES];
double emp_net_pay[MAX_EMPLOYEES];
double emp_bonus[MAX_EMPLOYEES];
double emp_deductions[MAX_EMPLOYEES];
char   emp_status[MAX_EMPLOYEES][NAME_LEN];
int    emp_count = 0;

int find_by_id(const char id[]) {
    for (int i = 0; i < emp_count; i++) {
        if (strcmp(emp_id[i], id) == 0) return i;
    }
    return -1;
}

void add_employee(void) {
    int ret = 0;
    double wages = 0;
    if (emp_count >= MAX_EMPLOYEES) {
        printf("Cannot add: storage full (max %d).\n", MAX_EMPLOYEES);
        return;
    }

    printf("Enter Employee ID: ");
    scanf(" %63s", emp_id[emp_count]);

    if (find_by_id(emp_id[emp_count]) != -1) {
        printf("ID already exists. Cancelled.\n");
        return;
    }

    int idx = emp_count;

    printf("Enter Name: ");
    scanf(" %63s", emp_name[idx]);

    printf("Enter Department: ");
    scanf(" %63s", emp_dept[idx]);

    printf("Enter Email: ");
    scanf(" %63s", emp_email[idx]);

    printf("Enter Phone: ");
    scanf(" %63s", emp_phone[idx]);
    while (strlen(emp_phone[idx]) != 10) {
        printf("Invalid Phone number , Enter again: ");
        scanf(" %63s", emp_phone[idx]);
    }

    printf("Enter Address (): ");
    scanf(" %63[^\n]s", emp_address[idx]);
    if (strlen(emp_address[idx]) > 0)
        emp_address[idx][strlen(emp_address[idx]) - 1] = '\0';

    printf("Enter Payroll ID: ");
    scanf(" %63s", emp_payroll_id[idx]);

    printf("Enter Salary(Per month): ");
    scanf(" %lf", &emp_salary[idx]);
    while (emp_salary[idx] < 0) {
        printf("Invalid Salary , Enter again: ");
        scanf(" %lf", &emp_salary[idx]);
    }

    printf("Enter No. of Working Days: ");
    scanf(" %d", &emp_working_days[idx]);
    while (emp_working_days[idx] < 0 || emp_working_days[idx] > 28) {
        printf("Invalid Working days , Enter again: ");
        scanf(" %d", &emp_working_days[idx]);
    }

    printf("Enter No. of Leaves: ");
    scanf(" %d", &emp_leaves[idx]);
    while (emp_leaves[idx] < 0 || emp_leaves[idx] > 28) {
        printf("Invalid Leaves , Enter again: ");
        scanf(" %d", &emp_leaves[idx]);
    }

    printf("Enter Bonus: ");
    scanf(" %lf", &emp_bonus[idx]);
    while (emp_bonus[idx] < 0) {
        printf("Invalid Bonus , Enter again: ");
        scanf(" %lf", &emp_bonus[idx]);
    }

    printf("Enter Deductions: ");
    scanf(" %lf", &emp_deductions[idx]);
    while (emp_deductions[idx] < 0) {
        printf("Invalid Deductions , Enter again: ");
        scanf(" %lf", &emp_deductions[idx]);
    }

    wages = emp_salary[idx] / 28.0;
    emp_net_pay[idx] = (wages * emp_working_days[idx]) + emp_bonus[idx] - emp_deductions[idx];

    printf("Enter Status: ");
    scanf(" %63s", emp_status[idx]);

    emp_count++;
    printf("Employee added. Total employees: %d\n", emp_count);
}

void display_employees(void) {
    if (emp_count == 0) {
        printf("No employees to display.\n");
        return;
    }
    printf("\n%-4s %-12s %-20s %-12s %-10s %-8s\n",
           "No.", "ID", "Name", "PayrollID", "Salary", "NetPay");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < emp_count; i++) {
        printf("%-4d %-12s %-20s %-12s %-10.2f %-8.2f\n",
               i + 1, emp_id[i], emp_name[i], emp_payroll_id[i],
               emp_salary[i], emp_net_pay[i]);
    }
}

void search_employee(void) {
    char id[NAME_LEN];
    printf("Enter Employee ID to search: ");
    scanf(" %63s", id);
    int idx = find_by_id(id);
    if (idx == -1) {
        printf("Employee with ID '%s' not found.\n", id);
    } else {
        printf("\nEmployee found at index %d:\n", idx + 1);
        printf(" ID        : %s\n", emp_id[idx]);
        printf(" Name      : %s\n", emp_name[idx]);
        printf(" Department: %s\n", emp_dept[idx]);
        printf(" Email     : %s\n", emp_email[idx]);
        printf(" Phone     : %s\n", emp_phone[idx]);
        printf(" Address   : %s\n", emp_address[idx]);
        printf(" PayrollID : %s\n", emp_payroll_id[idx]);
        printf(" Salary    : %f\n", emp_salary[idx]);
        printf(" WorkDays  : %d\n", emp_working_days[idx]);
        printf(" Leaves    : %d\n", emp_leaves[idx]);
        printf(" Bonus     : %f\n", emp_bonus[idx]);
        printf(" Deductions: %f\n", emp_deductions[idx]);
        printf(" Net Pay   : %f\n", emp_net_pay[idx]);
        printf(" Status    : %s\n", emp_status[idx]);
    }
}

void delete_employee(void) {
    char id[NAME_LEN];
    printf("Enter Employee ID to delete: ");
    scanf(" %63s", id);
    int idx = find_by_id(id);
    if (idx == -1) {
        printf("Employee with ID '%s' not found.\n", id);
        return;
    }
    for (int i = idx; i < emp_count - 1; i++) {
        strcpy(emp_id[i],        emp_id[i + 1]);
        strcpy(emp_name[i],      emp_name[i + 1]);
        strcpy(emp_dept[i],      emp_dept[i + 1]);
        strcpy(emp_email[i],     emp_email[i + 1]);
        strcpy(emp_phone[i],     emp_phone[i + 1]);
        strcpy(emp_address[i],   emp_address[i + 1]);
        strcpy(emp_payroll_id[i],emp_payroll_id[i + 1]);

        emp_salary[i]        = emp_salary[i + 1];
        emp_working_days[i]  = emp_working_days[i + 1];
        emp_leaves[i]        = emp_leaves[i + 1];
        emp_net_pay[i]       = emp_net_pay[i + 1];
        emp_bonus[i]         = emp_bonus[i + 1];
        emp_deductions[i]    = emp_deductions[i + 1];
        strcpy(emp_status[i], emp_status[i + 1]);
    }
    emp_count--;
    printf("Employee with ID '%s' deleted. Total now %d\n", id, emp_count);
}

void update_employee(void) {
    char id[NAME_LEN];
    printf("Enter Employee ID to update: ");
    scanf(" %63s", id);
    int idx = find_by_id(id);
    if (idx == -1) {
        printf("Employee with ID '%s' not found.\n", id);
        return;
    }
    printf("Updating employee %s (enter '-' to keep current)\n", id);
    char tmp[NAME_LEN];
    double dval;
    int ival;

    printf("Current Name: %s\nNew Name: ", emp_name[idx]);
    scanf(" %63s", tmp); if (strcmp(tmp, "-") != 0) strcpy(emp_name[idx], tmp);

    printf("Current Department: %s\nNew Department: ", emp_dept[idx]);
    scanf(" %63s", tmp); if (strcmp(tmp, "-") != 0) strcpy(emp_dept[idx], tmp);

    printf("Current Email: %s\nNew Email: ", emp_email[idx]);
    scanf(" %63s", tmp); if (strcmp(tmp, "-") != 0) strcpy(emp_email[idx], tmp);

    printf("Current Phone: %s\nNew Phone: ", emp_phone[idx]);
    scanf(" %63s", tmp); if (strcmp(tmp, "-") != 0) strcpy(emp_phone[idx], tmp);

    printf("Current Address: %s\nNew Address (single line): ", emp_address[idx]);
    while (getchar() != '\n');
    if (!fgets(tmp, NAME_LEN, stdin)) tmp[0] = '\0';
    if (strlen(tmp) > 0 && tmp[strlen(tmp) - 1] == '\n')
        tmp[strlen(tmp) - 1] = '\0';
    if (strcmp(tmp, "-") != 0 && tmp[0] != '\0') strcpy(emp_address[idx], tmp);

    printf("Current Payroll ID: %s\nNew Payroll ID: ", emp_payroll_id[idx]);
    scanf(" %63s", tmp); if (strcmp(tmp, "-") != 0) strcpy(emp_payroll_id[idx], tmp);

    printf("Current Salary: %.2f\nNew Salary (-1 to keep): ", emp_salary[idx]);
    scanf(" %lf", &dval); if (dval >= 0) emp_salary[idx] = dval;

    printf("Current Working Days: %d\nNew Working Days (-1 to keep): ", emp_working_days[idx]);
    scanf(" %d", &ival); if (ival >= 0) emp_working_days[idx] = ival;

    printf("Current Leaves: %d\nNew Leaves (-1 to keep): ", emp_leaves[idx]);
    scanf(" %d", &ival); if (ival >= 0) emp_leaves[idx] = ival;

    printf("Current Bonus: %.2f\nNew Bonus (-1 to keep): ", emp_bonus[idx]);
    scanf(" %lf", &dval); if (dval >= 0) emp_bonus[idx] = dval;

    printf("Current Deductions: %.2f\nNew Deductions (-1 to keep): ", emp_deductions[idx]);
    scanf(" %lf", &dval); if (dval >= 0) emp_deductions[idx] = dval;

    emp_net_pay[idx] = emp_salary[idx] + emp_bonus[idx] - emp_deductions[idx];

    printf("Current Status: %s\nNew Status: ", emp_status[idx]);
    scanf(" %63s", tmp); if (strcmp(tmp, "-") != 0) strcpy(emp_status[idx], tmp);

    printf("Employee updated.\n");
}

/* ========== NEW: CLI MODE FOR NODE BACKEND ========== */

int main(int argc, char *argv[]) {
    if (argc > 1) {
        /* Backend / API mode */

        if (strcmp(argv[1], "list") == 0) {
            /* For now, just output empty JSON array.
               You can extend this later to print real employees as JSON. */
            printf("[]\n");
            return 0;
        }

        if (strcmp(argv[1], "add") == 0) {
            /* Expected arguments order from Node:
               employee.exe add
                 2  emp_id
                 3  emp_name
                 4  emp_dept
                 5  emp_email
                 6  emp_phone
                 7  emp_payroll_id
                 8  emp_salary
                 9  emp_working_days
                10  emp_leaves
                11  emp_bonus
                12  emp_deductions
                13  emp_address
                14  emp_status
            */
            if (argc < 15) {
                fprintf(stderr, "Not enough arguments for add\n");
                return 1;
            }

            if (emp_count >= MAX_EMPLOYEES) {
                fprintf(stderr, "Storage full\n");
                return 1;
            }

            int idx = emp_count;

            strcpy(emp_id[idx],         argv[2]);
            strcpy(emp_name[idx],       argv[3]);
            strcpy(emp_dept[idx],       argv[4]);
            strcpy(emp_email[idx],      argv[5]);
            strcpy(emp_phone[idx],      argv[6]);
            strcpy(emp_payroll_id[idx], argv[7]);

            emp_salary[idx]       = atof(argv[8]);
            emp_working_days[idx] = atoi(argv[9]);
            emp_leaves[idx]       = atoi(argv[10]);
            emp_bonus[idx]        = atof(argv[11]);
            emp_deductions[idx]   = atof(argv[12]);
            strcpy(emp_address[idx],    argv[13]);
            strcpy(emp_status[idx],     argv[14]);

            double wages = emp_salary[idx] / 26.0;
            emp_net_pay[idx] = wages * emp_working_days[idx]
                             + emp_bonus[idx] - emp_deductions[idx];

            emp_count++;

            printf("{\"message\":\"added\",\"id\":\"%s\"}\n", emp_id[idx]);
            return 0;
        }

        fprintf(stderr, "Unknown command\n");
        return 1;
    }

    /* Interactive console mode */
    int choice;
    while (1) {
        printf("\n===== Employee Menu =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");
        printf("6. Exit\n");
        printf("Choose an option (1-6): ");
        scanf(" %d", &choice);

        switch (choice) {
            case 1: add_employee(); break;
            case 2: display_employees(); break;
            case 3: search_employee(); break;
            case 4: update_employee(); break;
            case 5: delete_employee(); break;
            case 6: printf("Goodbye!\n"); return 0;
            default: printf("Invalid option. Please choose 1-6.\n");
        }
    }
    return 0;
}
