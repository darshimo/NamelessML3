#include "param.h"
#include <stdlib.h>
#include <string.h>

//#define DEBUG
#ifdef DEBUG
#include <stdio.h>
void writeDBExp(DBExp *);
#endif

Int *copyInt(Int *);
Bool *copyBool(Bool *);

VarList *copyVarList(VarList *);

Var *copyVar(Var *);
Op *copyOp(Op *);
If *copyIf(If *);
Let *copyLet(Let *);
Fun *copyFun(Fun *);
App *copyApp(App *);
LetRec *copyLetRec(LetRec *);
Exp *copyExp(Exp *);

DBVar *copyDBVar(DBVar *);
DBOp *copyDBOp(DBOp *);
DBIf *copyDBIf(DBIf *);
DBLet *copyDBLet(DBLet *);
DBFun *copyDBFun(DBFun *);
DBApp *copyDBApp(DBApp *);
DBLetRec *copyDBLetRec(DBLetRec *);
DBExp *copyDBExp(DBExp *);


Int *copyInt(Int *sample){
#ifdef DEBUG
    printf("copyInt start\n");
#endif
    Int *ob = (Int *)malloc(sizeof(Int));
    ob->i = sample->i;
#ifdef DEBUG
    printf("copyInt end\n");
#endif
    return ob;
}

Bool *copyBool(Bool *sample){
#ifdef DEBUG
    printf("copyBool start\n");
#endif
    Bool *ob = (Bool *)malloc(sizeof(Bool));
    ob->b = sample->b;
#ifdef DEBUG
    printf("copyBool end\n");
#endif
    return ob;
}

VarList *copyVarList(VarList *sample){
    if(sample==NULL)return NULL;
#ifdef DEBUG
    printf("copyVarList start\n");
#endif
    VarList *ob = (VarList *)malloc(sizeof(VarList));
    ob->var_ = copyVar(sample->var_);
    ob->prev = copyVarList(sample->prev);
#ifdef DEBUG
    printf("copyVarList end\n");
#endif
    return ob;
}

Var *copyVar(Var *sample){
#ifdef DEBUG
    printf("copyVar start\n");
#endif
    Var *ob = (Var *)malloc(sizeof(Var));
    ob->var_name = (char *)malloc(sizeof(char)*(strlen(sample->var_name)+1));
    strcpy(ob->var_name, sample->var_name);
#ifdef DEBUG
    printf("copyVar end\n");
#endif
    return ob;
};

DBVar *copyDBVar(DBVar *sample){
#ifdef DEBUG
    printf("copyDBVar start\n");
#endif
    DBVar *ob = (DBVar *)malloc(sizeof(DBVar));
    ob->n = sample->n;
#ifdef DEBUG
    printf("copyDBVar end\n");
#endif
    return ob;
};

Op *copyOp(Op *sample){
#ifdef DEBUG
    printf("copyOp start\n");
#endif
    Op *ob = (Op *)malloc(sizeof(Op));
    ob->op_type = sample->op_type;
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
#ifdef DEBUG
    printf("copyOp end\n");
#endif
    return ob;
}

DBOp *copyDBOp(DBOp *sample){
#ifdef DEBUG
    printf("copyDBOp start\n");
#endif
    DBOp *ob = (DBOp *)malloc(sizeof(DBOp));
    ob->op_type = sample->op_type;
    ob->dbexp1_ = copyDBExp(sample->dbexp1_);
    ob->dbexp2_ = copyDBExp(sample->dbexp2_);
#ifdef DEBUG
    printf("copyDBOp end\n");
#endif
    return ob;
}

If *copyIf(If *sample){
#ifdef DEBUG
    printf("copyIf start\n");
#endif
    If *ob = (If *)malloc(sizeof(If));
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
    ob->exp3_ = copyExp(sample->exp3_);
#ifdef DEBUG
    printf("copyIf end\n");
#endif
    return ob;
}

DBIf *copyDBIf(DBIf *sample){
#ifdef DEBUG
    printf("copyDBIf start\n");
#endif
    DBIf *ob = (DBIf *)malloc(sizeof(DBIf));
    ob->dbexp1_ = copyDBExp(sample->dbexp1_);
    ob->dbexp2_ = copyDBExp(sample->dbexp2_);
    ob->dbexp3_ = copyDBExp(sample->dbexp3_);
#ifdef DEBUG
    printf("copyDBIf end\n");
#endif
    return ob;
}

Let *copyLet(Let *sample){
#ifdef DEBUG
    printf("copyLet start\n");
#endif
    Let *ob = (Let *)malloc(sizeof(Let));
    ob->var_ = copyVar(sample->var_);
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
#ifdef DEBUG
    printf("copyLet end\n");
#endif
    return ob;
}

DBLet *copyDBLet(DBLet *sample){
#ifdef DEBUG
    printf("copyDBLet start\n");
#endif
    DBLet *ob = (DBLet *)malloc(sizeof(DBLet));
    ob->dbexp1_ = copyDBExp(sample->dbexp1_);
    ob->dbexp2_ = copyDBExp(sample->dbexp2_);
#ifdef DEBUG
    printf("copyDBLet end\n");
#endif
    return ob;
}

Fun *copyFun(Fun *sample){
#ifdef DEBUG
    printf("copyFun start\n");
#endif
    Fun *ob = (Fun *)malloc(sizeof(Fun));
    ob->arg = copyVar(sample->arg);
    ob->exp_ = copyExp(sample->exp_);
#ifdef DEBUG
    printf("copyFun end\n");
#endif
    return ob;
}

DBFun *copyDBFun(DBFun *sample){
#ifdef DEBUG
    printf("copyDBFun start\n");
#endif
    DBFun *ob = (DBFun *)malloc(sizeof(DBFun));
    ob->dbexp_ = copyDBExp(sample->dbexp_);
#ifdef DEBUG
    printf("copyDBFun end\n");
#endif
    return ob;
}

App *copyApp(App *sample){
#ifdef DEBUG
    printf("copyApp start\n");
#endif
    App *ob = (App *)malloc(sizeof(App));
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
#ifdef DEBUG
    printf("copyApp end\n");
#endif
    return ob;
}

DBApp *copyDBApp(DBApp *sample){
#ifdef DEBUG
    printf("copyDBApp start\n");
#endif
    DBApp *ob = (DBApp *)malloc(sizeof(DBApp));
    ob->dbexp1_ = copyDBExp(sample->dbexp1_);
    ob->dbexp2_ = copyDBExp(sample->dbexp2_);
#ifdef DEBUG
    printf("copyDBApp end\n");
#endif
    return ob;
}

LetRec *copyLetRec(LetRec *sample){
#ifdef DEBUG
    printf("copyLetRec start\n");
#endif
    LetRec *ob = (LetRec *)malloc(sizeof(LetRec));
    ob->fun = copyVar(sample->fun);
    ob->arg = copyVar(sample->arg);
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
#ifdef DEBUG
    printf("copyLetRec end\n");
#endif
    return ob;
}

DBLetRec *copyDBLetRec(DBLetRec *sample){
#ifdef DEBUG
    printf("copyDBLetRec start\n");
#endif
    DBLetRec *ob = (DBLetRec *)malloc(sizeof(DBLetRec));
    ob->dbexp1_ = copyDBExp(sample->dbexp1_);
    ob->dbexp2_ = copyDBExp(sample->dbexp2_);
#ifdef DEBUG
    printf("copyDBLetRec end\n");
#endif
    return ob;
}

Exp *copyExp(Exp *sample){
#ifdef DEBUG
    printf("copyExp start\n");
#endif
    Exp *ob = (Exp *)malloc(sizeof(Exp));
    ob->exp_type = sample->exp_type;
    if(ob->exp_type==INT)ob->u.int_ = copyInt(sample->u.int_);
    else if(ob->exp_type==BOOL)ob->u.bool_ = copyBool(sample->u.bool_);
    else if(ob->exp_type==VAR)ob->u.var_ = copyVar(sample->u.var_);
    else if(ob->exp_type==OP)ob->u.op_ = copyOp(sample->u.op_);
    else if(ob->exp_type==IF)ob->u.if_ = copyIf(sample->u.if_);
    else if(ob->exp_type==LET)ob->u.let_ = copyLet(sample->u.let_);
    else if(ob->exp_type==FUN)ob->u.fun_ = copyFun(sample->u.fun_);
    else if(ob->exp_type==APP)ob->u.app_ = copyApp(sample->u.app_);
    else ob->u.letrec_ = copyLetRec(sample->u.letrec_);
#ifdef DEBUG
    printf("copyExp end\n");
#endif
    return ob;
}

DBExp *copyDBExp(DBExp *sample){
#ifdef DEBUG
    printf("copyDBExp start\n");
#endif
    DBExp *ob = (DBExp *)malloc(sizeof(DBExp));
    ob->exp_type = sample->exp_type;
    if(ob->exp_type==INT)ob->u.int_ = copyInt(sample->u.int_);
    else if(ob->exp_type==BOOL)ob->u.bool_ = copyBool(sample->u.bool_);
    else if(ob->exp_type==VAR)ob->u.dbvar_ = copyDBVar(sample->u.dbvar_);
    else if(ob->exp_type==OP)ob->u.dbop_ = copyDBOp(sample->u.dbop_);
    else if(ob->exp_type==IF)ob->u.dbif_ = copyDBIf(sample->u.dbif_);
    else if(ob->exp_type==LET)ob->u.dblet_ = copyDBLet(sample->u.dblet_);
    else if(ob->exp_type==FUN)ob->u.dbfun_ = copyDBFun(sample->u.dbfun_);
    else if(ob->exp_type==APP)ob->u.dbapp_ = copyDBApp(sample->u.dbapp_);
    else ob->u.dbletrec_ = copyDBLetRec(sample->u.dbletrec_);
#ifdef DEBUG
    printf("copyDBExp end\n");
#endif
    return ob;
}
