#include "param.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG

VarList *copyVarList(VarList *);

Int *copyInt(Int *);
Bool *copyBool(Bool *);
Exp *copyExp(Exp *);
Var *copyVar(Var *);
DBExp *copyDBExp(DBExp *);
int cmpVar(Var *, Var *);

#ifdef DEBUG
void writeVarList(VarList *);
void writeInt(Int *);
void writeBool(Bool *);
void writeFun(Fun *);
void writeApp(App *);
void writeLetRec(LetRec *);
void writeExp(Exp *);
void ind(int);
#endif

void derivation(Cncl *, int);


void Tr_Int(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("Tr-Int: ");
    writeVarList(cncl_ob->varlist_);
    printf(" |- ");
    writeExp(cncl_ob->exp_);
    printf("\n");
#endif
    Int *i = cncl_ob->exp_->u.int_;

    cncl_ob->rule_type = TR_INT;

    Asmp *asmp_ob = NULL;

    DBExp *dbexp_ob = (DBExp *)malloc(sizeof(DBExp));
    dbexp_ob->exp_type = INT;
    dbexp_ob->u.int_ = copyInt(i);

    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->dbexp_ = dbexp_ob;
    return;
}

void Tr_Bool(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("Tr-Bool: ");
    writeVarList(cncl_ob->varlist_);
    printf(" |- ");
    writeExp(cncl_ob->exp_);
    printf("\n");
#endif
    Bool *b = cncl_ob->exp_->u.bool_;

    cncl_ob->rule_type = TR_BOOL;

    Asmp *asmp_ob = NULL;

    DBExp *dbexp_ob = (DBExp *)malloc(sizeof(DBExp));
    dbexp_ob->exp_type = BOOL;
    dbexp_ob->u.bool_ = copyBool(b);

    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->dbexp_ = dbexp_ob;
    return;
}

void Tr_Var(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("Tr-Var: ");
    writeVarList(cncl_ob->varlist_);
    printf(" |- ");
    writeExp(cncl_ob->exp_);
    printf("\n");
#endif
    Exp *x = cncl_ob->exp_;
    Var *y = cncl_ob->varlist_->var_;
    VarList *chi = cncl_ob->varlist_->prev;

    Asmp *asmp_ob;
    DBExp *dbexp_ob = (DBExp *)malloc(sizeof(DBExp));
    if(cmpVar(x->u.var_,y)==0){
        cncl_ob->rule_type = TR_VAR1;

        asmp_ob = NULL;

        dbexp_ob->exp_type = VAR;
        dbexp_ob->u.dbvar_ = (DBVar *)malloc(sizeof(DBVar));
        dbexp_ob->u.dbvar_->n = 1;
    }else{
        cncl_ob->rule_type = TR_VAR2;

        asmp_ob = (Asmp *)malloc(sizeof(Asmp));
        asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
        asmp_ob->cncl_->varlist_ = copyVarList(chi);
        asmp_ob->cncl_->exp_ = copyExp(x);
        derivation(asmp_ob->cncl_,d+1);
        asmp_ob->next = NULL;

        dbexp_ob->exp_type = VAR;
        dbexp_ob->u.dbvar_ = (DBVar *)malloc(sizeof(DBVar));
        dbexp_ob->u.dbvar_->n = asmp_ob->cncl_->dbexp_->u.dbvar_->n + 1;
    }

    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->dbexp_ = dbexp_ob;
    return;
}

void Tr_Op(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("Tr-Op: ");
    writeVarList(cncl_ob->varlist_);
    printf(" |- ");
    writeExp(cncl_ob->exp_);
    printf("\n");
#endif
    VarList *chi = cncl_ob->varlist_;
    Exp *e1 = cncl_ob->exp_->u.op_->exp1_;
    Exp *e2 = cncl_ob->exp_->u.op_->exp2_;

    OpType tmp = cncl_ob->exp_->u.op_->op_type;
    if(tmp==PLUS)cncl_ob->rule_type = TR_PLUS;
    else if(tmp==MINUS)cncl_ob->rule_type = TR_MINUS;
    else if(tmp==TIMES)cncl_ob->rule_type = TR_TIMES;
    else cncl_ob->rule_type = TR_LT;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->varlist_ = copyVarList(chi);
    asmp_ob->cncl_->exp_ = copyExp(e1);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->cncl_->varlist_ = copyVarList(chi);
    asmp_ob->next->cncl_->exp_ = copyExp(e2);
    derivation(asmp_ob->next->cncl_,d+1);
    asmp_ob->next->next = NULL;

    DBExp *dbexp_ob = (DBExp *)malloc(sizeof(DBExp));
    dbexp_ob->exp_type = OP;
    dbexp_ob->u.dbop_ = (DBOp *)malloc(sizeof(DBOp));
    dbexp_ob->u.dbop_->op_type = cncl_ob->exp_->u.op_->op_type;
    dbexp_ob->u.dbop_->dbexp1_ = copyDBExp(asmp_ob->cncl_->dbexp_);
    dbexp_ob->u.dbop_->dbexp2_ = copyDBExp(asmp_ob->next->cncl_->dbexp_);

    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->dbexp_ = dbexp_ob;
    return;
}

void Tr_If(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("Tr-If: ");
    writeVarList(cncl_ob->varlist_);
    printf(" |- ");
    writeExp(cncl_ob->exp_);
    printf("\n");
#endif
    VarList *chi = cncl_ob->varlist_;
    Exp *e1 = cncl_ob->exp_->u.if_->exp1_;
    Exp *e2 = cncl_ob->exp_->u.if_->exp2_;
    Exp *e3 = cncl_ob->exp_->u.if_->exp3_;

    cncl_ob->rule_type = TR_IF;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->varlist_ = copyVarList(chi);
    asmp_ob->cncl_->exp_ = copyExp(e1);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->cncl_->varlist_ = copyVarList(chi);
    asmp_ob->next->cncl_->exp_ = copyExp(e2);
    derivation(asmp_ob->next->cncl_,d+1);
    asmp_ob->next->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->next->cncl_->varlist_ = copyVarList(chi);
    asmp_ob->next->next->cncl_->exp_ = copyExp(e3);
    derivation(asmp_ob->next->next->cncl_,d+1);
    asmp_ob->next->next->next = NULL;

    DBExp *dbexp_ob = (DBExp *)malloc(sizeof(DBExp));
    dbexp_ob->exp_type = IF;
    dbexp_ob->u.dbif_ = (DBIf *)malloc(sizeof(DBIf));
    dbexp_ob->u.dbif_->dbexp1_ = copyDBExp(asmp_ob->cncl_->dbexp_);
    dbexp_ob->u.dbif_->dbexp2_ = copyDBExp(asmp_ob->next->cncl_->dbexp_);
    dbexp_ob->u.dbif_->dbexp3_ = copyDBExp(asmp_ob->next->next->cncl_->dbexp_);

    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->dbexp_ = dbexp_ob;
    return;
}

void Tr_Let(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("Tr-Let: ");
    writeVarList(cncl_ob->varlist_);
    printf(" |- ");
    writeExp(cncl_ob->exp_);
    printf("\n");
#endif
    VarList *chi = cncl_ob->varlist_;
    Var *x = cncl_ob->exp_->u.let_->var_;
    Exp *e1 = cncl_ob->exp_->u.let_->exp1_;
    Exp *e2 = cncl_ob->exp_->u.let_->exp2_;

    cncl_ob->rule_type = TR_LET;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->varlist_ = copyVarList(chi);
    asmp_ob->cncl_->exp_ = copyExp(e1);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->cncl_->varlist_ = (VarList *)malloc(sizeof(VarList));
    asmp_ob->next->cncl_->varlist_->prev = copyVarList(chi);
    asmp_ob->next->cncl_->varlist_->var_ = copyVar(x);
    asmp_ob->next->cncl_->exp_ = copyExp(e2);
    derivation(asmp_ob->next->cncl_,d+1);
    asmp_ob->next->next = NULL;

    DBExp *dbexp_ob = (DBExp *)malloc(sizeof(DBExp));
    dbexp_ob->exp_type = LET;
    dbexp_ob->u.dblet_ = (DBLet *)malloc(sizeof(DBLet));
    dbexp_ob->u.dblet_->dbexp1_ = copyDBExp(asmp_ob->cncl_->dbexp_);
    dbexp_ob->u.dblet_->dbexp2_ = copyDBExp(asmp_ob->next->cncl_->dbexp_);

    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->dbexp_ = dbexp_ob;
    return;
}

void Tr_Fun(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("Tr-Fun: ");
    writeVarList(cncl_ob->varlist_);
    printf(" |- ");
    writeExp(cncl_ob->exp_);
    printf("\n");
#endif
    VarList *chi = cncl_ob->varlist_;
    Var *x = cncl_ob->exp_->u.fun_->arg;
    Exp *e = cncl_ob->exp_->u.fun_->exp_;

    cncl_ob->rule_type = TR_FUN;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->varlist_ = (VarList *)malloc(sizeof(VarList));
    asmp_ob->cncl_->varlist_->prev = copyVarList(chi);
    asmp_ob->cncl_->varlist_->var_ = copyVar(x);
    asmp_ob->cncl_->exp_ = copyExp(e);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = NULL;

    DBExp *dbexp_ob = (DBExp *)malloc(sizeof(DBExp));
    dbexp_ob->exp_type = FUN;
    dbexp_ob->u.dbfun_ = (DBFun *)malloc(sizeof(DBFun));
    dbexp_ob->u.dbfun_->dbexp_ = copyDBExp(asmp_ob->cncl_->dbexp_);

    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->dbexp_ = dbexp_ob;
    return;
}

void Tr_App(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("Tr-App: ");
    writeVarList(cncl_ob->varlist_);
    printf(" |- ");
    writeExp(cncl_ob->exp_);
    printf("\n");
#endif
    VarList *chi = cncl_ob->varlist_;
    Exp *e1 = cncl_ob->exp_->u.app_->exp1_;
    Exp *e2 = cncl_ob->exp_->u.app_->exp2_;

    cncl_ob->rule_type = TR_APP;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->varlist_ = copyVarList(chi);
    asmp_ob->cncl_->exp_ = copyExp(e1);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->cncl_->varlist_ = copyVarList(chi);
    asmp_ob->next->cncl_->exp_ = copyExp(e2);
    derivation(asmp_ob->next->cncl_,d+1);
    asmp_ob->next->next = NULL;

    DBExp *dbexp_ob = (DBExp *)malloc(sizeof(DBExp));
    dbexp_ob->exp_type = APP;
    dbexp_ob->u.dbapp_ = (DBApp *)malloc(sizeof(DBApp));
    dbexp_ob->u.dbapp_->dbexp1_ = copyDBExp(asmp_ob->cncl_->dbexp_);
    dbexp_ob->u.dbapp_->dbexp2_ = copyDBExp(asmp_ob->next->cncl_->dbexp_);

    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->dbexp_ = dbexp_ob;
    return;
}

void Tr_LetRec(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("Tr-LetRec: ");
    writeVarList(cncl_ob->varlist_);
    printf(" |- ");
    writeExp(cncl_ob->exp_);
    printf("\n");
#endif
    VarList *chi = cncl_ob->varlist_;
    Var *x = cncl_ob->exp_->u.letrec_->fun;
    Var *y = cncl_ob->exp_->u.letrec_->arg;
    Exp *e1 = cncl_ob->exp_->u.letrec_->exp1_;
    Exp *e2 = cncl_ob->exp_->u.letrec_->exp2_;

    cncl_ob->rule_type = TR_LETREC;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->varlist_ = (VarList *)malloc(sizeof(VarList));
    asmp_ob->cncl_->varlist_->prev = (VarList *)malloc(sizeof(VarList));
    asmp_ob->cncl_->varlist_->prev->prev = copyVarList(chi);
    asmp_ob->cncl_->varlist_->prev->var_ = copyVar(x);
    asmp_ob->cncl_->varlist_->var_ = copyVar(y);
    asmp_ob->cncl_->exp_ = copyExp(e1);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->cncl_->varlist_ = (VarList *)malloc(sizeof(VarList));
    asmp_ob->next->cncl_->varlist_->prev = copyVarList(chi);
    asmp_ob->next->cncl_->varlist_->var_ = copyVar(x);
    asmp_ob->next->cncl_->exp_ = copyExp(e2);
    derivation(asmp_ob->next->cncl_,d+1);
    asmp_ob->next->next = NULL;

    DBExp *dbexp_ob = (DBExp *)malloc(sizeof(DBExp));
    dbexp_ob->exp_type = LETREC;
    dbexp_ob->u.dbletrec_ = (DBLetRec *)malloc(sizeof(DBLetRec));
    dbexp_ob->u.dbletrec_->dbexp1_ = copyDBExp(asmp_ob->cncl_->dbexp_);
    dbexp_ob->u.dbletrec_->dbexp2_ = copyDBExp(asmp_ob->next->cncl_->dbexp_);

    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->dbexp_ = dbexp_ob;
    return;
}

void derivation(Cncl *cncl_ob, int d){
    ExpType tmp = cncl_ob->exp_->exp_type;
    if(tmp == INT) Tr_Int(cncl_ob,d);
    else if(tmp == BOOL) Tr_Bool(cncl_ob,d);
    else if(tmp == VAR) Tr_Var(cncl_ob,d);
    else if(tmp == OP) Tr_Op(cncl_ob, d);
    else if(tmp == IF) Tr_If(cncl_ob, d);
    else if(tmp == LET) Tr_Let(cncl_ob,d);
    else if(tmp == FUN) Tr_Fun(cncl_ob,d);
    else if(tmp == APP) Tr_App(cncl_ob,d);
    else Tr_LetRec(cncl_ob,d);
    return;
}
