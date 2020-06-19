#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include<string.h>
typedef struct __myarg_t 
{
int a;
char *b;
} myarg_t;
typedef struct __myrg_t 
{
char *b;
char *c;
} myrg_t;
typedef struct __myrt_t 
{
char *y;
} myrt_t;
typedef struct __myret_t 
{
int x;
char *y;
} myret_t;
void * mythread(void * arg)
{
myarg_t * m = (myarg_t * ) arg;
int print_index=0;
for(print_index=0; print_index<m->a; print_index++)
{
printf("Printing %d th character %c\n", print_index, *(m->b+print_index));
}
myret_t * r = malloc(sizeof(myret_t));
r->x = 1;
r->y = m->b;
return (void * ) r;
}
void * frethread(void * arg)
{
myrg_t *m=(myrg_t * )arg;
myrt_t *r=malloc(sizeof(myrt_t));
r->y=(char *) malloc(sizeof(strlen(m->b)+strlen(m->c)+2));

printf("y in r-> y %s\n", r->y);

strcat(r->y,m->b);
strcat(r->y," ");
strcat(r->y,m->c);
printf("reached\n");

return (void * ) r;
}
int  main(int argc, char * argv[])
{
pthread_t p,p1,p2;
myret_t * m;

myrg_t gi;

myarg_t args,args1;
char a1[20];
args.a= strlen(argv[1]);
args.b=(char *)malloc(strlen(argv[1]+1));
strcpy(args.b,  argv[1]);
/**/
args1.a= strlen(argv[2]);
args1.b=(char *)malloc(strlen(argv[2])+1);
strcpy(args1.b,  argv[2]);
pthread_create(&p, NULL, mythread, &args);
pthread_join(p, (void ** ) &m);
printf("returned %d %s\n", m->x, m->y);
gi.b=m->y;
strcat(a1,m->y);
pthread_create(&p1, NULL, mythread, &args1);
pthread_join(p1, (void ** ) &m);

printf("returned %d %s\n", m->x, m->y);
gi.c=m->y;
printf("%s",gi.c);
strcat(a1,m->y);

myrt_t * n;


pthread_create(&p2, NULL, frethread, &gi);
pthread_join(p2, (void **) &n);
printf("%s",n->y);
return 0;
}

