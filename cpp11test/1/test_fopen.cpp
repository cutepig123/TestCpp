#include <stdio.h>

void test_fopen()
{
	FILE *fp1=fopen("1.txt","a");
	FILE *fp2=fopen("1.txt","a");

	for(int i=0; i<100;i++)
	{
		fprintf(fp1,"%d\n",2*i); fflush(fp1);
		fprintf(fp2,"%d\n",2*i+1); fflush(fp2);
	}
	fclose(fp1);
	fclose(fp2);
}
