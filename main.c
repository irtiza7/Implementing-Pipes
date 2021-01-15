#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
 
//checking if the number is prime or not 
int isPrime(int n){
 	if(n<=1)
 		return 0;	
 	for (int i = 2; i < n; i++){
 		if(n%i == 0)
 			return 0;
 	return 1;
 	}
 }
 
int main(void) {
   
   char bufin[20] = "nothing";
   int bytesin;
   
   //reading a string from the user
   char string[20];
   printf("\nEnter a String (less than 20 characters): ");
   fgets(string, 20, stdin);
      
   //reading an unsigned integer from user
   unsigned int num;
   printf("Enter an Unsigned Integer: ");
   scanf("%u", &num);
   
   //calling system call and checking if it was successful
   int fd[2];
   if (pipe(fd) == -1) {
      perror("Pipe not created"); 
      return 1; 
   }
   
   //calling system call to create a child process and verifying it
   pid_t childpid;
   childpid = fork();
   if(childpid == -1){
   	perror("Fork failed");
   	return 1;
   }
   
   //if statements writes data into the pipe
   //if statements are parent's code and else statements are child's code 
   if(childpid){
   	write(fd[1], string, strlen(string)+1);
   	fprintf(stderr, "I am Parent and my ID is [%ld]\n", (long)getpid());
   }else{
   	//checking if the number is Prime or not inside Child process and working accordingly
   	if(isPrime(num) == 1){
   		bytesin = read(fd[0], bufin, 20);
   		fprintf(stderr, "I am Child and my ID is [%ld]\n", (long)getpid());
   		fprintf(stderr, "Your Number: Prime and Your String: %s\n",bufin);
   	}else{
   		bytesin = read(fd[0], bufin, 20);
   		FILE *fptr;
   		fptr = fopen("my.file", "w");
   		if(fptr == NULL){
   			printf("File not opened\n");
   		}
   		fprintf(fptr, "%s", bufin);
   		fclose(fptr);
   		fprintf(stderr, "I am Child and my ID is [%ld]\n", (long)getpid());
   		fprintf(stderr, "Your Number: Non-Prime and Your String is stored in my.file.txt\n");
   	}
   }
   
   return 0;
}
