#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define MAX_LINE 80 //Max length of command

struct History
{
	int hist_num;
	char command[80];
};

int main()
{	
	char *args[10]; //command line arguments
	int should_run = 1; //flag to determine when to exit program
	char in_command[80]; //user input
	pid_t pid;
	struct History comm_hist[15]; //hold up to 15 commands in history
	int i = 0; //Variable for parsing user input
	int j = 0; //Variable to control while loops
	int hist_count = 0; //Number of commands count
	int hist_temp1 = 0; //Used to index hist_count
	int error = 0; //used if the Nth command in !N does not exist

	while (should_run) 
	{
		*args = NULL;
		i = 0;
		j = 0;
		hist_temp1 = 0;
		printf("osh>");
		fgets(in_command, MAX_LINE, stdin);
		hist_count++;
		if (hist_count <= 15) //If history count < 15, then add directly into the array
		{
			comm_hist[hist_count-1].hist_num = hist_count;
			strcpy(comm_hist[hist_count-1].command, in_command);
		}
		else //otherwise shift the oldest one out and put in the latest command
		{
			while (j < 14) //shift oldest command
			{
				comm_hist[j].hist_num = comm_hist[j+1].hist_num;
				strcpy(comm_hist[j].command, comm_hist[j+1].command);
				j++;
			}
			comm_hist[j].hist_num = hist_count; //Put in the latest command
			strcpy(comm_hist[j].command, in_command);
		}
		char *parse = strtok(in_command,"\n");
		while (parse!=NULL) //Separate the user input for args
		{
			args[i] = parse;
			i++;
			parse = strtok(NULL,"\n");
		}
		args[i] = NULL;
		if (strcmp(args[0], "history") == 0) //If user inputs history as command
		{
			hist_count--; //Don't add history to the commands history
			j = 0;
			if (hist_count < 15) //Print 10 latest commands depending on how many commands are in history
			{
				hist_temp1 = hist_count-1;
				while (j < hist_count && j < 10) //Run 10 times to get 10 latest commands
				{
					printf("%d %s\n", comm_hist[hist_temp1].hist_num, comm_hist[hist_temp1].command);	
					hist_temp1--;
					j++;
				}
				j = 0;
			}	
			else //Print out 10 latest commands (comm_hist[5] to comm_hist[14])
			{
				hist_temp1 = 5;
				while (hist_temp1 < 15)
				{
					printf("%d %s", comm_hist[hist_temp1].hist_num, comm_hist[hist_temp1].command);
					hist_temp1++;
				}
			}
		}
		else if (strcmp(args[0], "!!") == 0) //Enter here if user enters "!!"
		{
			hist_count--; //Don't add "!!" to the history
			if (hist_count == 1) //Error if there are no commands in the history
			{
				printf("No commands in the history.");
			}
			else 
			{
				i = 0;
				printf("%s", comm_hist[hist_count-1].command); //Print out the latest command
				char *parse1 = strtok(comm_hist[hist_count-1].command,"\n"); 
				while (parse1!=NULL) //Parse the latest command into args
				{
					args[i] = parse1;
					i++;
					parse1 = strtok(NULL,"\n");
				}
				args[i] = NULL;
			}
		}
		else
		{
			char *comm_num = args[0];
			if (strncmp(args[0], "!", 1) == 0)  //Enter here if users enters "!N"
			{
				comm_num++; //String to contain "N" instead of "!N"
				int arg_int = atoi(comm_num); //Convert string to integer
				char for_hist[80];
				j = 0;
				i = 0;
				int k = 0;
				error = 2; //Print out an error message if "N" doesn't exist
				while(j < 15) //Check all 15 commands in history to find a match
				{
					if (comm_hist[j].hist_num == arg_int) //Match found
					{
						printf("%s\n", comm_hist[j].command); //Print out the command to the user
						char *parse2 = strtok(comm_hist[j].command,"\n");
						error = 1; //Don't print out error message because "N" is found
						while (parse2!=NULL) //Parse the Nth command in args
						{
							args[i] = parse2;
							i++;
							parse2 = strtok(NULL,"\n");
						}
						args[i] = NULL;
						if (hist_count <= 15) //Add the Nth command as the latest in history
						{
							comm_hist[hist_count-1].hist_num = hist_count;
							strcpy(comm_hist[hist_count-1].command, comm_hist[j].command);
						}
						else
						{
							while (k < 14)
							{
								comm_hist[k].hist_num = comm_hist[k+1].hist_num;
								strcpy(comm_hist[k].command, comm_hist[k+1].command);
								k++;
							}
							comm_hist[k].hist_num = hist_count;
							strcpy(comm_hist[k].command, comm_hist[j].command);
						}
					}
					j++;
				}
				
			}
		}
		if (error == 2) //Print this out of Nth command didn't exist
		{
			printf("%s", "No such command in history");
		}		
		pid = fork();
		if (pid == 0) //child process
		{
			if (strcmp(args[i-1], "&") == 0)
				args[i-1] = NULL;
			execvp(args[0], args);
		}
		if (pid > 0) //parent process
		{
			if (strcmp(args[i-1], "&") == 0)
				continue;
			else
				wait(NULL);
		}
		if (strcmp(args[0], "exit") == 0)
			should_run = 0;
	}
	return 0;
}
