#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){	
   
   if(argc < 2){
   	printf("ERROR: You should enter an integer as an argument to sleep");
   	exit(1);
   }else if(argc > 2){
   	printf("ERROR: You should enter exactly one integer as an argument to sleep");
   	exit(1);
   }else{
   	int NUMBER_OF_SECONDS_TO_SLEEP = atoi(argv[1]);
   	sleep(NUMBER_OF_SECONDS_TO_SLEEP);
   	exit(0);
   }
   
   return 0;
}
