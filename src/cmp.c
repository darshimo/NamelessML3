#include <string.h>
#include "param.h"


int cmpVar(Var *,Var *);

int cmpInt(Int *,Int *);
int cmpBool(Bool *,Bool *);
int cmpDBVar(DBVar *,DBVar *);
int cmpDBOp(DBOp *,DBOp *);
int cmpDBIf(DBIf *,DBIf *);
int cmpDBLet(DBLet *,DBLet *);
int cmpDBFun(DBFun *,DBFun *);
int cmpDBApp(DBApp *,DBApp *);
int cmpDBLetRec(DBLetRec *,DBLetRec *);
int cmpDBExp(DBExp *,DBExp *);

void writegVar(Var *);

void writegInt(Int *);
void writegBool(Bool *);
void writegDBVar(DBVar *);
void writegDBOp(DBOp *);
void writegDBIf(DBIf *);
void writegDBLet(DBLet *);
void writegDBFun(DBFun *);
void writegDBApp(DBApp *);
void writegDBLetRec(DBLetRec *);
void writegDBExp(DBExp *);


//#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#endif


int cmpInt(Int *ob1, Int *ob2){
#ifdef DEBUG
    printf("cmpInt: ");
    writegInt(ob1);
    printf(" : ");
    writegInt(ob2);
    printf(" :\n");
#endif
    return (ob1->i!=ob2->i);
}

int cmpBool(Bool *ob1, Bool *ob2){
#ifdef DEBUG
    printf("cmpBool: ");
    writegBool(ob1);
    printf(" : ");
    writegBool(ob2);
    printf(" :\n");
#endif
    return (ob1->b!=ob2->b);
}

int cmpDBVar(DBVar *ob1, DBVar *ob2){
#ifdef DEBUG
    printf("cmpDBVar: ");
    writegDBVar(ob1);
    printf(" : ");
    writegDBVar(ob2);
    printf(" :\n");
#endif
    return ob1->n!=ob2->n;
}

int cmpDBOp(DBOp *ob1, DBOp *ob2){
#ifdef DEBUG
    printf("cmpDBOp: ");
    writegDBOp(ob1);
    printf(" : ");
    writegDBOp(ob2);
    printf(" :\n");
#endif
    if(ob1->op_type!=ob2->op_type)return 1;
    if(cmpDBExp(ob1->dbexp1_,ob2->dbexp1_))return 1;
    if(cmpDBExp(ob1->dbexp2_,ob2->dbexp2_))return 1;
    return 0;
}

int cmpDBIf(DBIf *ob1, DBIf *ob2){
#ifdef DEBUG
    printf("cmpDBIf: ");
    writegDBIf(ob1);
    printf(" : ");
    writegDBIf(ob2);
    printf(" :\n");
#endif
    if(cmpDBExp(ob1->dbexp1_,ob2->dbexp1_))return 1;
    if(cmpDBExp(ob1->dbexp2_,ob2->dbexp2_))return 1;
    if(cmpDBExp(ob1->dbexp3_,ob2->dbexp3_))return 1;
    return 0;
}

int cmpDBLet(DBLet *ob1, DBLet *ob2){
#ifdef DEBUG
    printf("cmpDBLet: ");
    writegDBLet(ob1);
    printf(" : ");
    writegDBLet(ob2);
    printf(" :\n");
#endif
    if(cmpDBExp(ob1->dbexp1_,ob2->dbexp1_))return 1;
    if(cmpDBExp(ob1->dbexp2_,ob2->dbexp2_))return 1;
    return 0;
}

int cmpDBFun(DBFun *ob1, DBFun *ob2){
#ifdef DEBUG
    printf("cmpDBFun: ");
    writegDBFun(ob1);
    printf(" : ");
    writegDBFun(ob2);
    printf(" :\n");
#endif
    if(cmpDBExp(ob1->dbexp_,ob2->dbexp_))return 1;
    return 0;
}

int cmpDBApp(DBApp *ob1, DBApp *ob2){
#ifdef DEBUG
    printf("cmpDBApp: ");
    writegDBApp(ob1);
    printf(" : ");
    writegDBApp(ob2);
    printf(" :\n");
#endif
    if(cmpDBExp(ob1->dbexp1_,ob2->dbexp1_))return 1;
    if(cmpDBExp(ob1->dbexp2_,ob2->dbexp2_))return 1;
    return 0;
}

int cmpDBLetRec(DBLetRec *ob1, DBLetRec *ob2){
#ifdef DEBUG
    printf("cmpDBLetRec: ");
    writegDBLetRec(ob1);
    printf(" : ");
    writegDBLetRec(ob2);
    printf(" :\n");
#endif
    if(cmpDBExp(ob1->dbexp1_,ob2->dbexp1_))return 1;
    if(cmpDBExp(ob1->dbexp2_,ob2->dbexp2_))return 1;
    return 0;
}

int cmpDBExp(DBExp *ob1, DBExp *ob2){
    if(ob1->exp_type!=ob2->exp_type)return 1;
    if(ob1->exp_type==INT)return cmpInt(ob1->u.int_,ob2->u.int_);
    if(ob1->exp_type==BOOL)return cmpBool(ob1->u.bool_,ob2->u.bool_);
    if(ob1->exp_type==VAR)return cmpDBVar(ob1->u.dbvar_,ob2->u.dbvar_);
    if(ob1->exp_type==OP)return cmpDBOp(ob1->u.dbop_,ob2->u.dbop_);
    if(ob1->exp_type==IF)return cmpDBIf(ob1->u.dbif_,ob2->u.dbif_);
    if(ob1->exp_type==LET)return cmpDBLet(ob1->u.dblet_,ob2->u.dblet_);
    if(ob1->exp_type==FUN)return cmpDBFun(ob1->u.dbfun_,ob2->u.dbfun_);
    if(ob1->exp_type==APP)return cmpDBApp(ob1->u.dbapp_,ob2->u.dbapp_);
    return cmpDBLetRec(ob1->u.dbletrec_,ob2->u.dbletrec_);
}
