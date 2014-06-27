// =====================================================================================
// 
//       Filename:  main.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2014-05-04 16时43分19秒
//       Revision:  none
// 
// =====================================================================================

#include <ucontext.h>
#include <stdio.h>

static ucontext_t ctx[3];

static void fun1 (long a0, long a1, long a2, long a3)
{
printf ("start run fun1(a0=%ld, a1=%ld, a2=%ld, a3=%ld)\n", a0, a1, a2, a3);
swapcontext(&ctx[1], &ctx[0]);
printf ("finish fun1\n");
}

int main (void)
{
char st1[10240];
char st2[10240];

printf ("making contexts\n\n");

getcontext (&ctx[1]);
ctx[1].uc_stack.ss_sp = st1;
ctx[1].uc_stack.ss_size = sizeof(st1);
ctx[1].uc_link = &ctx[0];
makecontext (&ctx[1], (void(*)(void))fun1, 4, 1, 2, 3, 4);

printf ("swapping contexts\n\n");
swapcontext (&ctx[0], &ctx[1]);

printf ("back at main program, test succeeded\n\n");

return 0;
}
