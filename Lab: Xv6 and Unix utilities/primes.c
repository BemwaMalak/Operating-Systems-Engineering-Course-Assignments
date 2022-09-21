#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void cull(int p, int read_d, int write_d){
    int n;
    /*
        Read all numbers from old pipe and write only ones that
        are not divisible by p
    */ 
    while(read(read_d, &n, sizeof(n))){
    	if(n % p != 0){
    	    write(write_d, &n, sizeof(n));
    	}
    }
}
void right(int read_d){
    int p;
    // Read the current prime number from the stream initialy read 2
    if(read(read_d, &p, sizeof(p))){
    	printf("prime %d\n", p);
    	
    	/*
    	    Creating another pipe to read from and write to it a filtered
    	    stream of numbers which are not divisible by our prime
    	*/ 
    	int cull_pipe[2];
    	pipe(cull_pipe);
    	
    	if(fork()){
    	    close(cull_pipe[1]);
    	    // Calling right again but with the the new pipe read side
    	    right(cull_pipe[0]);
    	}else{
    	    close(cull_pipe[0]);
    	    /*
    	        Calling the filtration function that will filter old pipe
    	        from numbers divisible by p
    	    */ 
    	    cull(p, read_d, cull_pipe[1]);
    	    close(cull_pipe[1]);
    	}
    }
}
int main(){	
   int pd[2];
   pipe(pd);
   
   if(fork()){
   	// Parent (fork() returned number greater than zero)
   	// Closing the write side of the pipe because we will not use it
   	close(pd[1]);
   	/*
   	   Calling right() with the read side of the pipe to read the
   	   numbers stream from the child 2 -> 35 
   	*/
   	right(pd[0]);
   }else{
   	// Child
   	// Closing the read side of the pipe because we will not use it
   	close(pd[0]);
   	// Write numbers 2 -> 35 to the write side of the pipe
   	for(int i = 2; i <= 35; i++){
   	    write(pd[1], &i, sizeof(i));
   	}
   	// Closing the write side after finishing writing the stream
   	close(pd[1]);
   }

   
   return 0;
}
