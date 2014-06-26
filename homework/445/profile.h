#ifndef PROFILER
#define PROFILER
unsigned long long t1, t2;
typedef struct {
char op[40],
	 fname[20];
FILE * fp;
unsigned long long cycles; 
} operation;
void init(operation *o, char *s);
void do_fopen(operation *o, int n); // fopen a file; filepointer inside struct p.fp
void do_fwrite(operation *o, int n);
void do_fread(operation *o, int n);
void do_fclose(operation *o, int n);
static inline unsigned long long upCycle(void)
{
  unsigned long long int x;
     __asm__ volatile (".byte 0x0F, 0x31" : "=A" (x));
     return x;
}
void init(operation *o, char *s)
{
	int i;
	static const char op[4][9]	= {"fopen \t\t","fwrite\t\t","fread \t\t","fclose\t\t"};
	for(i=0;i<4;i++) {
		strcpy(o[i].op,op[i]);
		//strcat(o[i].op,s);		
		strcpy(o[i].fname,s);
	}
}
void do_fwrite(operation *o, int n) {
	unsigned long t1, t2;
	const char s[250] = "This is a random text file used as\nan example\n\nof a file\nfor \n\nprograms to\n\n\n";
	unsigned long l=0;
	o[n].fp = fopen(o[n].fname,"w+"); //write plus update
	if (o[n].fp!=NULL)
	{
		t1 = upCycle();
		fwrite(s, sizeof(char), sizeof(s), o[n].fp);
		t2 = upCycle();
		o[n].cycles = t2-t1;
	}
	else
	{
		strcat(o[n].op," err"); 
		o[n].cycles = 0;
	}
	fclose(o[n].fp);
}
void do_fopen(operation *o, int n) {
	t1 = upCycle();
	o[n].fp = fopen(o[n].fname,"r"); //write plus update
	t2 = upCycle();

	if (o[n].fp!=NULL)
		o[n].cycles = t2 - t1;
	else
	{
		strcat(o[n].op," err"); 
		o[n].cycles = 0;
	}
	fclose(o[n].fp);
}
void do_fread(operation *o, int n) {
	char s[250];
	o[n].fp = fopen(o[n].fname,"r"); //write plus update
	if (o[n].fp!=NULL)
	{
		t1 = upCycle();
		fread(s, sizeof(char), sizeof(s), o[n].fp);
		t2 = upCycle();
		o[n].cycles = t2 - t1;
	}
	else
	{
		strcat(o[n].op," err"); 
		o[n].cycles = 0;
	}
	fclose(o[n].fp);
}
void do_fclose(operation *o, int n) {
	o[n].fp = fopen(o[n].fname,"r"); //write plus update
	if (o[n].fp!=NULL);
	else
	{
		strcat(o[n].op," err"); 
		o[n].cycles = 0;
	}

	t1 = upCycle();
	fclose(o[n].fp);
	t2 = upCycle();
	o[n].cycles = t2 - t1;
}
#endif