// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define N  1000

void
forktest(void)
{
  int n, pid;

  printf(1, "fork test\n");

  for(n=0; n<N; n++){
    pid = fork();
    if(pid < 0)
      break;
    if(pid == 0)
    {
      printf(1,"create a new fork with ID: %d\n",n);  
      sleep(1000);
    }
  }

  if(n == N){
    printf(1, "fork claimed to work %d times!\n", N);
    exit();
  }

  for(; n > 0; n--){
    if(wait() < 0)
    {
      printf(1, "wait stopped early\n");
      exit();
    }
  }

  if(wait() != -1)
  {
    printf(1, "wait got too many\n");
    exit();
  }

  printf(1, "fork test OK\n");
}

int
main(void)
{
  forktest();
  exit();
}