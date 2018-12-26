#include "param.h"
#include <stdlib.h>

//#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#endif

void freeVarList(VarList *);

void freeInt(Int *);
void freeBool(Bool *);

void freeVar(Var *);
void freeOp(Op *);
void freeIf(If *);
void freeLet(Let *);
void freeFun(Fun *);
void freeApp(App *);
void freeLetRec(LetRec *);
void freeExp(Exp *);

void freeDBVar(DBVar *);
void freeDBOp(DBOp *);
void freeDBIf(DBIf *);
void freeDBLet(DBLet *);
void freeDBFun(DBFun *);
void freeDBApp(DBApp *);
void freeDBLetRec(DBLetRec *);
void freeDBExp(DBExp *);

void freeAsmp(Asmp *);
void freeCncl(Cncl *);


void freeInt(Int *int_ob){
#ifdef DEBUG
    printf("free int\n");
#endif
    free(int_ob);
    return;
}

void freeBool(Bool *bool_ob){
#ifdef DEBUG
    printf("free bool\n");
#endif
    free(bool_ob);
    return;
}

void freeVarList(VarList *varlist_ob){
    if(varlist_ob==NULL)return;
#ifdef DEBUG
    printf("free varlist\n");
#endif
    freeVar(varlist_ob->var_);
    freeVarList(varlist_ob->prev);
    free(varlist_ob);
    return;
}

void freeVar(Var *var_ob){
#ifdef DEBUG
    printf("free var\n");
#endif
    free(var_ob->var_name);
    free(var_ob);
    return;
}

void freeDBVar(DBVar *dbvar_ob){
#ifdef DEBUG
    printf("free dbvar\n");
#endif
    free(dbvar_ob);
    return;
}

void freeOp(Op *op_ob){
#ifdef DEBUG
    printf("free op\n");
#endif
    freeExp(op_ob->exp1_);
    freeExp(op_ob->exp2_);
    free(op_ob);
    return;
}

void freeDBOp(DBOp *dbop_ob){
#ifdef DEBUG
    printf("free dbop\n");
#endif
    freeDBExp(dbop_ob->dbexp1_);
    freeDBExp(dbop_ob->dbexp2_);
    free(dbop_ob);
    return;
}

void freeIf(If *if_ob){
#ifdef DEBUG
    printf("free if\n");
#endif
    freeExp(if_ob->exp1_);
    freeExp(if_ob->exp2_);
    freeExp(if_ob->exp3_);
    free(if_ob);
    return;
}

void freeDBIf(DBIf *dbif_ob){
#ifdef DEBUG
    printf("free dbif\n");
#endif
    freeDBExp(dbif_ob->dbexp1_);
    freeDBExp(dbif_ob->dbexp2_);
    freeDBExp(dbif_ob->dbexp3_);
    free(dbif_ob);
    return;
}

void freeLet(Let *let_ob){
#ifdef DEBUG
    printf("free let\n");
#endif
    freeVar(let_ob->var_);
    freeExp(let_ob->exp1_);
    freeExp(let_ob->exp2_);
    free(let_ob);
    return;
}

void freeDBLet(DBLet *dblet_ob){
#ifdef DEBUG
    printf("free dblet\n");
#endif
    freeDBExp(dblet_ob->dbexp1_);
    freeDBExp(dblet_ob->dbexp2_);
    free(dblet_ob);
    return;
}

void freeFun(Fun *fun_ob){
#ifdef DEBUG
    printf("free fun\n");
#endif
    freeVar(fun_ob->arg);
    freeExp(fun_ob->exp_);
    free(fun_ob);
    return;
}

void freeDBFun(DBFun *dbfun_ob){
#ifdef DEBUG
    printf("free dbfun\n");
#endif
    freeDBExp(dbfun_ob->dbexp_);
    free(dbfun_ob);
    return;
}

void freeApp(App *app_ob){
#ifdef DEBUG
    printf("free app\n");
#endif
    freeExp(app_ob->exp1_);
    freeExp(app_ob->exp2_);
    free(app_ob);
    return;
}

void freeDBApp(DBApp *dbapp_ob){
#ifdef DEBUG
    printf("free dbapp\n");
#endif
    freeDBExp(dbapp_ob->dbexp1_);
    freeDBExp(dbapp_ob->dbexp2_);
    free(dbapp_ob);
    return;
}

void freeLetRec(LetRec *letrec_ob){
#ifdef DEBUG
    printf("free letrec\n");
#endif
    freeVar(letrec_ob->fun);
    freeVar(letrec_ob->arg);
    freeExp(letrec_ob->exp1_);
    freeExp(letrec_ob->exp2_);
    return;
}

void freeDBLetRec(DBLetRec *dbletrec_ob){
#ifdef DEBUG
    printf("free dbletrec\n");
#endif
    freeDBExp(dbletrec_ob->dbexp1_);
    freeDBExp(dbletrec_ob->dbexp2_);
    return;
}

void freeExp(Exp *exp_ob){
#ifdef DEBUG
    printf("free exp\n");
#endif
    if(exp_ob->exp_type==INT)freeInt(exp_ob->u.int_);
    else if(exp_ob->exp_type==BOOL)freeBool(exp_ob->u.bool_);
    else if(exp_ob->exp_type==VAR)freeVar(exp_ob->u.var_);
    else if(exp_ob->exp_type==OP)freeOp(exp_ob->u.op_);
    else if(exp_ob->exp_type==IF)freeIf(exp_ob->u.if_);
    else if(exp_ob->exp_type==LET)freeLet(exp_ob->u.let_);
    else if(exp_ob->exp_type==FUN)freeFun(exp_ob->u.fun_);
    else if(exp_ob->exp_type==APP)freeApp(exp_ob->u.app_);
    else freeLetRec(exp_ob->u.letrec_);
    free(exp_ob);
    return;
}

void freeDBExp(DBExp *dbexp_ob){
#ifdef DEBUG
    printf("free dbexp\n");
#endif
    if(dbexp_ob->exp_type==INT)freeInt(dbexp_ob->u.int_);
    else if(dbexp_ob->exp_type==BOOL)freeBool(dbexp_ob->u.bool_);
    else if(dbexp_ob->exp_type==VAR)freeDBVar(dbexp_ob->u.dbvar_);
    else if(dbexp_ob->exp_type==OP)freeDBOp(dbexp_ob->u.dbop_);
    else if(dbexp_ob->exp_type==IF)freeDBIf(dbexp_ob->u.dbif_);
    else if(dbexp_ob->exp_type==LET)freeDBLet(dbexp_ob->u.dblet_);
    else if(dbexp_ob->exp_type==FUN)freeDBFun(dbexp_ob->u.dbfun_);
    else if(dbexp_ob->exp_type==APP)freeDBApp(dbexp_ob->u.dbapp_);
    else freeDBLetRec(dbexp_ob->u.dbletrec_);
    free(dbexp_ob);
    return;
}

void freeAsmp(Asmp *asmp_ob){
    if(asmp_ob==NULL)return;
#ifdef DEBUG
    printf("free asmp\n");
#endif
    freeCncl(asmp_ob->cncl_);
    freeAsmp(asmp_ob->next);
    free(asmp_ob);
    return;
}

void freeCncl(Cncl *cncl_ob){
#ifdef DEBUG
    printf("free cncl\n");
#endif
    freeAsmp(cncl_ob->asmp_);
    freeVarList(cncl_ob->varlist_);
    freeExp(cncl_ob->exp_);
    freeDBExp(cncl_ob->dbexp_);
    free(cncl_ob);
    return;
}
