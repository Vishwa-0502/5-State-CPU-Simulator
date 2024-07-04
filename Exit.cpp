/*#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <chrono> 
#include <ctime>  
#include "Queue.h"
#include "Procs.h"

using namespace std;

#define newline write(fd, "\n", 1)
#define writevalue write(fd, to_string(value).c_str(), strlen(to_string(value).c_str()))
#define writetab write(fd, "\t", 1)

int value;
int fd;

// Function to print current timestamp
void printWithTimestamp(const string &message)
{
    auto now = chrono::system_clock::now();
    time_t time_now = chrono::system_clock::to_time_t(now);
    string timestamp = ctime(&time_now);
    timestamp.erase(timestamp.find_last_not_of(" \n\r\t") + 1);
    cout << message << " " << timestamp << " " << endl;
}

int main(int argc, char *argv[])
{
    int run_exit_fd[2];
    int n_e_status_fd[2];
    int e_n_status_fd[2];

    run_exit_fd[0] = atoi(argv[1]);
    run_exit_fd[1] = atoi(argv[2]);

    n_e_status_fd[0] = atoi(argv[3]);
    n_e_status_fd[1] = atoi(argv[4]);

    e_n_status_fd[0] = atoi(argv[5]);
    e_n_status_fd[1] = atoi(argv[6]);

    Procs current;

    cout << "I AM EXIT PROCESS\n";

    sleep(1);

    // Open file and error handling
    fd = open("processes_stats.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1)
    {
        cerr << "Error opening or creating file." << endl;
        exit(1);
    }

    // Print timestamp at the beginning
    printWithTimestamp("Stats of Timestamp:");

    //making pipe unblocking
    fcntl(n_e_status_fd[0], F_SETFL, O_NONBLOCK);

    int totalprocs = 0;
    int receivedprocs = 0;

    // Total turnaround time and total waiting time
    float totalTAT = 0;
    float totalWT = 0;

    //writing to file
    char message[100]; // Increased buffer size

    // Write column headers
    write(fd, "PROC_NAME\tArrival_Time\tBurst_Time\tTurnaround_Time\tWaiting_Time\n", strlen("PROC_NAME\tArrival_Time\tBurst_Time\tTurnaround_Time\tWaiting_Time\n"));

    while (1)
    {
        read(run_exit_fd[0], &current, sizeof(current));

        receivedprocs++;

        read(n_e_status_fd[0], &totalprocs, sizeof(int));

        current.turn_around_time = current.waiting_time + current.given_time;

        cout << current.name << " EXITED" << endl;
        printWithTimestamp("Process exited");

        // Calculate total turnaround time and total waiting time
        totalTAT += current.turn_around_time;
        totalWT += current.waiting_time;


        //writing other info for Gantt chart
        sprintf(message, "%s\t\t%d\t\t%d\t\t%d\t\t%d", current.name, current.arrival_time, current.burst_time,      current.turn_around_time, current.waiting_time);
        write(fd, message, strlen(message));
        newline;

        if (receivedprocs == totalprocs)
            break;
    }

    // Calculate average turnaround time and average waiting time
    float avgTAT = totalTAT / totalprocs;
    float avgWT = totalWT / totalprocs;

    // Write average turnaround time and average waiting time to the file
    char message2[100];
    sprintf(message2, "avg TAT: %.2f", avgTAT);
    write(fd, message2, strlen(message2));
    newline;

    char message3[100];
    sprintf(message3, "avg WT: %.2f", avgWT);
    write(fd, message3, strlen(message3));
    newline;

    // Print timestamp at the end
    printWithTimestamp("Process finished");

    bool exitstatus = true;
    write(e_n_status_fd[1], &exitstatus, sizeof(bool));

    close(fd);

    cout << endl
         << "//////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "EXIT PROCESS EXITING" << endl;
    cout << "//////////////////////////////////////////////////////////////////////////////" << endl
         << endl;
    printWithTimestamp("Exit process exiting");

    exit(0);
}

*/

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <chrono> 
#include <ctime>  
#include "Queue.h"
#include "Procs.h"

using namespace std;

#define newline write(fd, "\n", 1)
#define writevalue write(fd, to_string(value).c_str(), strlen(to_string(value).c_str()))
#define writetab write(fd, "\t", 1)

int value;
int fd;

// Function to print current timestamp
string getTimestamp() {
    auto now = chrono::system_clock::now();
    time_t time_now = chrono::system_clock::to_time_t(now);
    string timestamp = ctime(&time_now);
    timestamp.erase(timestamp.find_last_not_of(" \n\r\t") + 1);
    return timestamp;
}

// Function to print current timestamp
string printWithTimestamp(const string &message)
{
    auto now = chrono::system_clock::now();
    time_t time_now = chrono::system_clock::to_time_t(now);
    string timestamp = ctime(&time_now);
    timestamp.erase(timestamp.find_last_not_of(" \n\r\t") + 1);
    return message + " " + timestamp + " "; // Return the message with timestamp
}

int main(int argc, char *argv[]) {
    int run_exit_fd[2];
    int n_e_status_fd[2];
    int e_n_status_fd[2];

    run_exit_fd[0] = atoi(argv[1]);
    run_exit_fd[1] = atoi(argv[2]);

    n_e_status_fd[0] = atoi(argv[3]);
    n_e_status_fd[1] = atoi(argv[4]);

    e_n_status_fd[0] = atoi(argv[5]);
    e_n_status_fd[1] = atoi(argv[6]);

    Procs current;

    cout << "I AM EXIT PROCESS\n";

    sleep(1);

    // Open file and error handling
    fd = open("processes_stats.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        cerr << "Error opening or creating file." << endl;
        exit(1);
    }

    // Print timestamp at the beginning
    write(fd, printWithTimestamp("Stats of Timestamp").c_str(), strlen(printWithTimestamp("Stats of Timestamp").c_str()));
    write(fd, "\n", 1); // Assuming newline is defined elsewhere

    //making pipe unblocking
    fcntl(n_e_status_fd[0], F_SETFL, O_NONBLOCK);

    int totalprocs = 0;
    int receivedprocs = 0;

    // Total turnaround time and total waiting time
    float totalTAT = 0;
    float totalWT = 0;

    // Write column headers
    write(fd, "PROC_NAME\tArrival_Time\tBurst_Time\tTurnaround_Time\tWaiting_Time\n", strlen("PROC_NAME\tArrival_Time\tBurst_Time\tTurnaround_Time\tWaiting_Time\n"));

    while (1) {
        read(run_exit_fd[0], &current, sizeof(current));

        receivedprocs++;

        read(n_e_status_fd[0], &totalprocs, sizeof(int));

        current.turn_around_time = current.waiting_time + current.given_time;

        cout << current.name << " EXITED" << endl;
        printWithTimestamp("Process exited");

        // Calculate total turnaround time and total waiting time
        totalTAT += current.turn_around_time;
        totalWT += current.waiting_time;

        //writing other info for Gantt chart
        char message[100];
        sprintf(message, "%s\t\t%d\t\t%d\t\t%d\t\t%d", current.name, current.arrival_time, current.burst_time, current.turn_around_time, current.waiting_time);
        write(fd, message, strlen(message));
        write(fd, "\n", 1); // newline

        if (receivedprocs == totalprocs)
            break;
    }

    // Calculate average turnaround time and average waiting time
    float avgTAT = totalTAT / totalprocs;
    float avgWT = totalWT / totalprocs;

    // Write average turnaround time and average waiting time to the file
    char message2[100];
    sprintf(message2, "avg TAT: %.2f", avgTAT);
    write(fd, message2, strlen(message2));
    write(fd, "\n", 1); // newline

    char message3[100];
    sprintf(message3, "avg WT: %.2f", avgWT);
    write(fd, message3, strlen(message3));
    write(fd, "\n", 1); // newline

    // Print timestamp at the end
    write(fd, printWithTimestamp("Process finished").c_str(), strlen(printWithTimestamp("Process finished").c_str()));
    
    bool exitstatus = true;
    write(e_n_status_fd[1], &exitstatus, sizeof(bool));

    close(fd);

    cout << endl << "//////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "EXIT PROCESS EXITING" << endl;
    cout << "//////////////////////////////////////////////////////////////////////////////" << endl << endl;
    printWithTimestamp("Exit process exiting");

    return 0;
}

