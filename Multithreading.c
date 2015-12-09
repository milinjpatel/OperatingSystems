#include <pthread.h>
#include <stdio.h>

int z1=0;
int z2=0;
int z3=0;
int z4=0;
int z5=0;
int z6=0;
int z7=0;
int z8=0;
int z9=0;
int row1col1[6] = {1, 2, 3, 2, 8, 14};
int row1col2[6] = {1, 2, 3, 4, 10, 16};
int row1col3[6] = {1, 2, 3, 6, 12, 18};
int row2col1[6] = {4, 5, 6, 2, 8, 14};
int row2col2[6] = {4, 5, 6, 4, 10, 16};
int row2col3[6] = {4, 5, 6, 6, 12, 18};
int row3col1[6] = {7, 8, 9, 2, 8, 14};
int row3col2[6] = {7, 8, 9, 4, 10, 16};
int row3col3[6] = {7, 8, 9, 6, 12, 18};

void *matrix_multiply(int param);

int main()
{
	pthread_t tid1; 
	pthread_attr_t attr1; 
	pthread_t tid2; 
	pthread_attr_t attr2; 
	pthread_t tid3; 
	pthread_attr_t attr3; 
	pthread_t tid4; 
	pthread_attr_t attr4; 
	pthread_t tid5; 
	pthread_attr_t attr5; 
	pthread_t tid6; 
	pthread_attr_t attr6; 
	pthread_t tid7; 
	pthread_attr_t attr7; 
	pthread_t tid8; 
	pthread_attr_t attr8; 
	pthread_t tid9; 
	pthread_attr_t attr9;

	/* get the default attributes */
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	pthread_attr_init(&attr3);
	pthread_attr_init(&attr4);
	pthread_attr_init(&attr5);
	pthread_attr_init(&attr6);
	pthread_attr_init(&attr7);
	pthread_attr_init(&attr8);
	pthread_attr_init(&attr9);

	/* create the thread */
	pthread_create(&tid1,&attr1,matrix_multiply,1);
	pthread_create(&tid2,&attr2,matrix_multiply,2);
	pthread_create(&tid3,&attr3,matrix_multiply,3);
	pthread_create(&tid4,&attr4,matrix_multiply,4);
	pthread_create(&tid5,&attr5,matrix_multiply,5);
	pthread_create(&tid6,&attr6,matrix_multiply,6);
	pthread_create(&tid7,&attr7,matrix_multiply,7);
	pthread_create(&tid8,&attr8,matrix_multiply,8);
	pthread_create(&tid9,&attr9,matrix_multiply,9);

	/* now wait for the thread to exit */
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid4,NULL);
	pthread_join(tid5,NULL);
	pthread_join(tid6,NULL);
	pthread_join(tid7,NULL);
	pthread_join(tid8,NULL);
	pthread_join(tid9,NULL);

	printf("%d %d %d\n%d %d %d\n%d %d %d\n", z1, z2, z3, z4, z5, z6, z7, z8, z9);
}

/**
 * The thread will begin control in this function
 */
void *matrix_multiply(int param) 
{
	switch (param)
	{
	case 1: z1 = (row1col1[0]*row1col1[3]) + (row1col1[1]*row1col1[4]) + (row1col1[2]*row1col1[5]);
	case 2: z2 = (row1col2[0]*row1col2[3]) + (row1col2[1]*row1col2[4]) + (row1col2[2]*row1col2[5]);
	case 3: z3 = (row1col3[0]*row1col3[3]) + (row1col3[1]*row1col3[4]) + (row1col3[2]*row1col3[5]);
	case 4: z4 = (row2col1[0]*row2col1[3]) + (row2col1[1]*row2col1[4]) + (row2col1[2]*row2col1[5]);
	case 5: z5 = (row2col2[0]*row2col2[3]) + (row2col2[1]*row2col2[4]) + (row2col2[2]*row2col2[5]);
	case 6: z6 = (row2col3[0]*row2col3[3]) + (row2col3[1]*row2col3[4]) + (row2col3[2]*row2col3[5]);
	case 7: z7 = (row3col1[0]*row3col1[3]) + (row3col1[1]*row3col1[4]) + (row3col1[2]*row3col1[5]);
	case 8: z8 = (row3col2[0]*row3col2[3]) + (row3col2[1]*row3col2[4]) + (row3col2[2]*row3col2[5]);
	case 9: z9 = (row3col3[0]*row3col3[3]) + (row3col3[1]*row3col3[4]) + (row3col3[2]*row3col3[5]);
	}
	pthread_exit(0);
}
