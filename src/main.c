#include "param.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef DBG_ALL
#define DBG_READ
#define DBG_STRCT
#define DBG_CP
#define DBG_DRV
#define DBG_CMP
#define DBG_WRITE
#define DBG_FREE
#endif

#ifdef DBG_STRCT
void debugCncl(Cncl *,int);
#endif

void error(char*);
Cncl* readCncl(char*);
void derivation(Cncl*, int);
void freeCncl(Cncl *);
void writeCncl(Cncl *, int);
DBExp *copyDBExp(DBExp *);
int cmpDBExp(DBExp *,DBExp *);


int main(int argc, char *argv[]){
    if(argc!=2)error("arg is not correct.\n");


    char *str = (char *)malloc(sizeof(char)*500);
    char *filename = argv[1];
    FILE *fp;
    if((fp = fopen(filename,"r"))==NULL){
        printf("fopen error.");
        exit(EXIT_FAILURE);
    }
    fgets(str,500,fp);


#ifdef DBG_READ
    printf("read start.\n");
#endif
    Cncl *cncl_ob = readCncl(str);
#ifdef DBG_READ
    printf("read complete.\n\n");
#endif


#ifdef DBG_CP
    printf("copy ans start.\n");
#endif
    DBExp *result = copyDBExp(cncl_ob->dbexp_);
#ifdef DBG_CP
    printf("copy ans complete.\n\n");
#endif


#ifdef DBG_STRCT
    printf("debug start.\n");
    debugCncl(cncl_ob,0);
    printf("debug complete.\n\n");
#endif


#ifdef DBG_DRV
    printf("derivation start.\n");
#endif
    derivation(cncl_ob,0);
#ifdef DBG_DRV
    printf("derivation complete.\n\n");
#endif


#ifdef DBG_CMP
    printf("cmp ans start.\n");
#endif
    if(cmpDBExp(cncl_ob->dbexp_,result)){
        error("result is not correct.\n");
    }
#ifdef DBG_CMP
    printf("cmp ans clmplete.\n\n");
#endif


#ifdef DBG_WRITE
    printf("write start.\n");
#endif
    writeCncl(cncl_ob,0);
#ifdef DBG_WRITE
    printf("\nwrite complete.\n\n");
#endif


#ifdef DBG_FREE
    printf("free start.\n");
#endif
    freeCncl(cncl_ob);
#ifdef DBG_FREE
    printf("free complete.\n\n");
#endif

    return 0;
}
