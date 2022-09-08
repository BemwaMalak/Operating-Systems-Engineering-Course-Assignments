#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){	
   char buf[512];
   int pipeIO[2];
   pipe(pipeIO);
   if(fork() == 0){
   	int NUMBER_OF_BYTES_READ = read(pipeIO[0], buf, 1);
   	close(pipeIO[0]);
   	if(NUMBER_OF_BYTES_READ != 0){
   	    printf("%d: received ping\n", getpid());
   	}
   	write(pipeIO[1], "P", 1);
   	close(pipeIO[1]);
   	exit(0);
   }else{
   	write(pipeIO[1], "P", 1);
   	close(pipeIO[1]);
   	int NUMBER_OF_BYTES_READ = read(pipeIO[0], buf, 1);
   	if(NUMBER_OF_BYTES_READ != 0){
   	    printf("%d: received pong\n", getpid());
   	}
   	close(pipeIO[0]);
   	exit(0);
   }
   
   return 0;
}
