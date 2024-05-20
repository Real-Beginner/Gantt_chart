#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define max_task_name_width 20

void add_tasks(void);
void removeNewLine(char str[]);


struct Task {
    char name[max_task_name_width];    // Name of the task
    int start_month;  // Start month (assuming 1 for January, 2 for February, etc.)
    int end_month;    // End month
    int num_of_dependencies;
    int dependencies[15];

};

//Do not put above struct code
void printDependentTasks(struct Task tasks[], int taskId, int visitedTasks[], int resetVisitedTasks[]);
void checkIfCircular(struct Task tasks[], int taskId, int resetVisitedTasks[], int visitedTasks);


int main(void) {



    enum month{january=1,february,march,april,may,june,july,august,september,october,november,december};

    char *month_names[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    // Print the enum months as strings

    struct Task tasks[15];
    char occupied[7] = "XXXXXX";
    char dependencies_string[] = "Dependencies";
    char blank_string[] = "";

    int tasks_index = 0;
    int max_tasks_index = sizeof(tasks)/sizeof(tasks[0]);

    int divider_length = max_task_name_width+150;
    char divider[divider_length+1];



    printf("\nWould you like to use a pre-generated gantt? (yes/no): ");
    fflush(stdout);
    char response[7];
    fgets(response, sizeof(response), stdin);
    response[strcspn(response, "\n")] = '\0'; // Remove newline character

    if (strcmp(response, "yes") == 0) {

        tasks[0] = (struct Task){"Task A", 1, 3, 0, {}};        // Task B starts in February and ends in April
        tasks[1] = (struct Task){"Task B", 2, 4, 1, {5}};       // Task C starts in May and ends in July
        tasks[2] = (struct Task){"Task C", 5, 7, 1, {1}};       // Task D starts in June and ends in August
        tasks[3] = (struct Task){"Task D", 6, 8, 1, {2}};       // Task A starts in January and ends in March
        tasks[4] = (struct Task){"Task E", 8, 10, 1, {4}};      // Task E starts in August and ends in October



    tasks_index = 5;

    }else {
        printf("\nHow many tasks would you like to add? (1-9)");
            fflush(stdout);
            int number_of_tasks_added;
            scanf("%d",&number_of_tasks_added);
            getchar(); // Consume the newline character left in the input buffer

            for(int i = 0;i<number_of_tasks_added;i++){

                printf("Enter name for Task %d: ", tasks_index+i); // Since the initial tasks are 5
                fflush(stdout);
                fgets(tasks[tasks_index+i].name, max_task_name_width, stdin);
                tasks[tasks_index+i].name[strcspn(tasks[tasks_index+i].name, "\n")] = '\0'; // Remove newline character

                printf("Enter start month for Task %d (1-12): ", tasks_index+i);
                fflush(stdout);
                scanf("%d", &tasks[tasks_index+i].start_month);
                getchar(); // Consume the newline character left in the input buffer

                printf("Enter end month for Task %d (1-12): ", tasks_index+i);
                fflush(stdout);
                scanf("%d", &tasks[tasks_index+i].end_month);
                getchar(); // Consume the newline character left in the input buffer


                printf("\nHow many dependencies would you like to add? (1-9)");
                fflush(stdout);
                scanf("%d",&tasks[tasks_index+i].num_of_dependencies);
                getchar(); // Consume the newline character left in the input buffer

                for(int j=0;j<tasks[tasks_index+i].num_of_dependencies;j++){
                    printf("Enter what months this is dependant on: %d: ", tasks_index+i);
                    fflush(stdout);
                    scanf("%d", &tasks[tasks_index+i].dependencies[j]);
                    getchar(); // Consume the newline character left in the input buffer
                }
            }
            // the scope of the variable is within the for loop i need to look at static vaariables

                tasks_index+=number_of_tasks_added;

    }


    while (1) {


        printf("\n");
        fflush(stdout);

        //printing top bar
        memset(divider,'-', divider_length);
        divider[divider_length-1] = '\0';
        printf("%*s|",max_task_name_width, blank_string);
        fflush(stdout);


        for (enum month i = january; i <= december; i++) {
            printf("%-10s|", month_names[i - 1]);
            fflush(stdout);
        }

        printf("%15s",dependencies_string);
        fflush(stdout);



        //Attempt to print under

        for(int i=0;i<tasks_index;i++){
        printf("\n%s\n",divider);
        fflush(stdout);
        printf("%*s|",max_task_name_width,tasks[i].name);
        fflush(stdout);
        for(int j=1;j<13;j++){
            if (j>=tasks[i].start_month && j<=tasks[i].end_month){
                printf("%2s%6s%2s|",blank_string,occupied,blank_string);
                fflush(stdout);
            }
            else{
                printf("%10s|",blank_string);
                fflush(stdout);

            }
        }
        for (int k = 0; k < tasks[i].num_of_dependencies; k++) {
                    printf("%d ", tasks[i].dependencies[k]);
                    fflush(stdout);
                }
        }

        char input[10];
        printf("\nEnter a command (add, edit, test, or quit): ");
        fflush(stdout);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        if (strcmp(input, "add") == 0) {
            printf("\nHow many tasks would you like to add? (1-9)");
            fflush(stdout);
            int number_of_tasks_added;
            scanf("%d",&number_of_tasks_added);
            getchar(); // Consume the newline character left in the input buffer

                // Remove newline character from input
                //number_of_tasks_added[strcspn(number_of_tasks_added, "\n")] = '\0';

            //int max_tasks_index = sizeof(tasks)/sizeof(tasks[0]);
                            //max_tasks_index += number_of_tasks_added;
            for(int i = 0;i<number_of_tasks_added;i++){

                printf("Enter name for Task %d: ", tasks_index+i); // Since the initial tasks are 5
                fflush(stdout);
                fgets(tasks[tasks_index+i].name, max_task_name_width, stdin);
                tasks[tasks_index+i].name[strcspn(tasks[tasks_index+i].name, "\n")] = '\0'; // Remove newline character

                printf("Enter start month for Task %d (1-12): ", tasks_index+i);
                fflush(stdout);
                scanf("%d", &tasks[tasks_index+i].start_month);
                getchar(); // Consume the newline character left in the input buffer

                printf("Enter end month for Task %d (1-12): ", tasks_index+i);
                fflush(stdout);
                scanf("%d", &tasks[tasks_index+i].end_month);
                getchar(); // Consume the newline character left in the input buffer


                printf("\nHow many dependencies would you like to add? (1-9)");
                fflush(stdout);
                scanf("%d",&tasks[tasks_index+i].num_of_dependencies);
                getchar(); // Consume the newline character left in the input buffer

                for(int j=0;j<tasks[tasks_index+i].num_of_dependencies;j++){
                    printf("Enter what months this is dependant on: %d: ", tasks_index+i);
                    fflush(stdout);
                    scanf("%d", &tasks[tasks_index+i].dependencies[j]);
                    getchar(); // Consume the newline character left in the input buffer
                }
            }
            // the scope of the variable is within the for loop i need to look at static vaariables

                tasks_index+=number_of_tasks_added;


        } else if (strcmp(input, "edit") == 0) {
            printf("\nWould you like to edit a task? (yes/no): ");
            fflush(stdout);

            fgets(response, sizeof(response), stdin);
            response[strcspn(response, "\n")] = '\0'; // Remove newline character

            if (strcmp(response, "yes") == 0) {
            //if (1==1) {
                char task_name[max_task_name_width];
                printf("Enter the name of the task you want to edit: ");
                fflush(stdout);
                fgets(task_name, sizeof(task_name), stdin);
                task_name[strcspn(task_name, "\n")] = '\0'; // Remove newline character

                // Search for the task to edit
                for (int i = 0; i < tasks_index; i++) {
                    if (strcmp(tasks[i].name, task_name) == 0) {

                        printf("Enter new name for Task %d: ", i); // Since the initial tasks are 5
                        fflush(stdout);
                        fgets(tasks[i].name, max_task_name_width, stdin);
                        tasks[i].name[strcspn(tasks[i].name, "\n")] = '\0'; // Remove newline character

                        printf("Enter new start month for Task %s (1-12): ", task_name);
                        fflush(stdout);
                        scanf("%d", &tasks[i].start_month);
                        getchar(); // Consume the newline character left in the input buffer

                        printf("Enter new end month for Task %s (1-12): ", task_name);
                        fflush(stdout);
                        scanf("%d", &tasks[i].end_month);
                        getchar(); // Consume the newline character left in the input buffer



                        printf("\nHow many dependencies would you like to add? (1-9)");
                        fflush(stdout);
                        scanf("%d",&tasks[i].num_of_dependencies);
                        getchar(); // Consume the newline character left in the input buffer

                        for(int j=0;j<tasks[i].num_of_dependencies;j++){
                        printf("Enter what months this is dependant on: %d: ", i);
                        fflush(stdout);
                        scanf("%d", &tasks[i].dependencies[j]);
                        getchar(); // Consume the newline character left in the input buffer
                        }

                        printf("Task %s has been edited.\n", task_name);
                        fflush(stdout);

                        break;

                    }
                }
            }
        } else if (strcmp(input, "test") == 0) {

        for(int i=tasks_index-1;i>-1;i--){
        int visitedTasks[15] = {0};
        int resetVisitedTasks[15] = {0};
        printf("\n");
        fflush(stdout);
        printDependentTasks(tasks, i, visitedTasks, resetVisitedTasks);
        printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------");
        fflush(stdout);
        }

            while (1) {
        printf("\nType \"exit test\" in order to return to commands\n");
        fflush(stdout);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        if (strcmp(input, "exit test") == 0) {
            break;
        } else {
            printf("Invalid command. Please enter \"exit test\"\n");
            fflush(stdout);
        }
        }


        } else if (strcmp(input, "quit") == 0) {
            printf("Exiting the program.\n");
            fflush(stdout);
            break; // Exit the loop
        } else {
            printf("Invalid command. Please enter add, edit, test, or quit.\n");
            fflush(stdout);
        }
    }
  return 0;
}


void printDependentTasks(struct Task tasks[], int taskId, int visitedTasks[], int resetVisitedTasks[])
{
    printf("%d -> ", taskId + 1);
    fflush(stdout);
    visitedTasks[taskId] = 1;

    for (int i = 0; i < tasks[taskId].num_of_dependencies; i++)
    {
        int dependentTaskId = tasks[taskId].dependencies[i]-1;

        if (visitedTasks[dependentTaskId] == 0)
        {
            printDependentTasks(tasks, dependentTaskId, visitedTasks, resetVisitedTasks);
        }
        else
        {

            printf("(!!!!!!!!!) warning potential circular dependency !!!!!!!!!!!!!)\n");
            fflush(stdout);
            resetVisitedTasks[dependentTaskId] = 1;
            checkIfCircular(tasks, taskId, resetVisitedTasks, visitedTasks);
        }
    }
}

void checkIfCircular(struct Task tasks[], int taskId, int resetVisitedTasks[], int visitedTasks){

    printf("Checking for circular dependencies\n");
    fflush(stdout);
    printf("%d -> ", taskId + 1);
    fflush(stdout);
    //visitedTasks[taskId] = 1;

    for (int i = 0; i < tasks[taskId].num_of_dependencies; i++)
    {
        int dependentTaskId = tasks[taskId].dependencies[i]-1;

        if (resetVisitedTasks[dependentTaskId] == 0)
        {
            checkIfCircular(tasks, dependentTaskId, visitedTasks, resetVisitedTasks);
            //Need to change this to the checkifcircular for the recursive call
        }
        else
        {
            printf("%d", dependentTaskId + 1);
            fflush(stdout);
            printf("\n(!!!!!!!!!)There is a loop  !!!!!!!!!!!!!)\n");
            fflush(stdout);

            //checkIfCircular(tasks, taskId, resetVisitedTasks, dependentTaskId);
        }
    }


}

