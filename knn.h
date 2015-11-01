#ifndef KNN_H_
#define KNN_H_

#ifndef NATTRS
#define  NATTRS 3 //number of attributes
#endif

#ifndef MAXSZ
#define  MAXSZ  2000 //max size of training set
#endif

#ifndef MAXVALUE
#define  MAXVALUE  50.0 //the biggest attribute's value is below 10000
#endif

#ifndef K
#define  K  1// the number of the neighbors
#endif


struct vector {
 int   ID;
 float attributes[NATTRS];
 char Class;
};

/* float knn(struct vector [MAXSZ],struct vector [MAXSZ], int , int ); */
#endif