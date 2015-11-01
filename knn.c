/**************************************************************************/
/* Name:         K Nearest Neighbor Classifier                            */
/* Author: xxxxx xxxx                                                     */
/* The KNN Classifier is a lazy Machine Learning Algorithm                */
/* The KNN is amnong the simplest of all machine learning algorithms      */
/*                                                                        */
/* The training examples are vecotrs in a multidimensional space,         */
/* Each with a class label.                                               */
/* The training phase of the algorithm consists of storing the feature    */
/* vectors and class labels of the training samples.                      */
/*                                                                        */
/* In the classification phase, k is a user defined constant, and an      */
/* unlabeled vector (a query or test point) is classified by assigning    */
/* the label which is most frequent amont the k training samples          */
/* nearest to that query point.                                           */
/*                                                                        */
/**************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "knn.h"

/* Tranining File */
FILE *fp_training;       

/* Testing File */
FILE *fp_testing;       

int training_size;
int testing_size;

struct item 
{
 float distance;
 char classlabel;
};


/* global variable,the training set */
struct vector training_set[MAXSZ];

/* global variable,the training set */
struct vector testing_set[MAXSZ];


/********************************************/
/*      Calculate the distance              */
/********************************************/
float Distance(struct vector v1,struct vector v2)
{ 
  int i;
  float tem = 0;
  for(i = 0;i < NATTRS;i++)
  {
     tem += (v1.attributes[i]-v2.attributes[i])*(v1.attributes[i]-v2.attributes[i]);
  } 

  return tem;
}

/*****************************************************************************/
/*                  Finding the Nearest Nighbour                             */
/* Returns the no. of items which have the largest distance                  */
/*****************************************************************************/
char Find_Majority(item knn[K]) 
{ 
  int i;
  int Count_2 = 0;
 
    for(i = 1;i < K;i++)
    {
       if(knn[i].classlabel==0)
           Count_2++;
    }
   
    if(Count_2 >= (K/2)) 
       return 0;
 
    return 1;
}


/************************************************/
/*       Classify and Labeling                  */
/* decide which class label will be assigned to */
/* a given input vetor with the knn method      */
/************************************************/
int Classify(void)
{
	 int index_test=0,index_train=0,n,i,j;
	 float distance_t = 0;
	 int Error=0;
	 struct item KNN[K];
         struct vector testing_point;
	 struct item Test;

	 /* the class label appears most frequently */
	 double mfreqC = 0;
	 
	 for(index_test=0;index_test<testing_size;index_test++)
	 {
		 testing_point=testing_set[index_test];
		 for(index_train = 0;index_train < K;index_train++)
		 {
			 KNN[index_train].distance=Distance(testing_point,training_set[index_train]);
			 KNN[index_train].classlabel=training_set[index_train].Class;
		 }
		 for(;index_train<training_size;index_train++)
		 {

		     distance_t=Distance(testing_point,training_set[index_train]);
		     for(i = 0;i < K;i++)
		     {
			 if(distance_t<KNN[i].distance)
			 {
				KNN[i].distance=distance_t;
				KNN[i].classlabel=training_set[index_train].Class;
			 }
		     }
		 }
		 if (Find_Majority(KNN)!=testing_point.Class)
		 {
		    Error++; 
		    /* printf("%d",Find_Majority(KNN)); */
	         }
	 }
	 return Error;
}

/**********************************************/
/*           Main program                     */
/* 1. Reads data from two files               */
/*    a. training file                        */
/*    b. testing file                         */
/* 2. Calls Classify()                        */
/* 3. Calculates the accuracy                 */
/**********************************************/
int main()
{
 float E;
 char fp_training_name[150]="./event_more_reduced_bad_fields_combined.txt";
 char fpt_testing_name[150]="./event_more_reduced_bad_fields_combined.txt";
 //int ID;
 float Feature1,Feature2,Feature3,Feature4,Feature5,Feature6,Feature7,Feature8,Feature9,Feature10,Feature11,Feature12,Feature13,Feature14,Class;
 training_size=0;
 testing_size=0;

        if ((fp_training = fopen(fp_training_name, "r"))==NULL) 
        {
	    printf("\n I can not read rule database");
	    exit(0);
        }
        if ((fp_testing = fopen(fpt_testing_name, "r"))==NULL) 
        {
	    printf("\n I can not read trace database");
	    exit(0);
        }

        int ID = 0;
        while(1)
        {
	    if(fscanf(fp_testing,"%f %f %f %f\n", 
	            &Feature1,&Feature2,&Feature3,&Class)!= 4)
	        break;
	    testing_set[testing_size].ID=ID++;
	    testing_set[testing_size].attributes[0]=Feature1;
	    testing_set[testing_size].attributes[1]=Feature2;
	    testing_set[testing_size].attributes[2]=Feature3;
	    testing_set[testing_size].Class=Class;
	    testing_size++;
        }
        ID = 0;
        while(1)
        {
	    if(fscanf(fp_training,"%f %f %f %f\n", 
	        &Feature1,&Feature2,&Feature3,&Class)!= 4)
	        break;
	    training_set[training_size].ID=ID++;
	    training_set[training_size].attributes[0]=Feature1;
	    training_set[training_size].attributes[1]=Feature2;
	    training_set[training_size].attributes[2]=Feature3;
	    training_set[training_size].Class=Class;
	    training_size++;
        }
  
        printf("The total size of the training set is %d\n", training_size);
        printf("The total size of the testing  set is %d\n", testing_size);
        E=Classify();
        float nn=((testing_size-E)*100.0)/testing_size;
        printf("The classification accuracy =  %f%%\n",nn);
}