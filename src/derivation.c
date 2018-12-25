#include "param.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG

Int *copyInt(Int *);
Bool *copyBool(Bool *);
Exp *copyExp(Exp *);
Env *copyEnv(Env *);
Val *copyVal(Val *);
Var *copyVar(Var *);
int cmpVar(Var *, Var *);
#ifdef DEBUG
void writeInt(Int *);
void writeBool(Bool *);
void writeClsr(Clsr *);
void writeClsrRec(ClsrRec *);
void writeEnv(Env *);
void writeVal(Val *);
void writeFun(Fun *);
void writeApp(App *);
void writeLetRec(LetRec *);
void writeExp(Exp *);
void ind(int);
#endif

void derivation(Cncl *, int);


void B_Plus(Cncl *cncl_ob, int d){
    int i1 = cncl_ob->u.infr_->int1;
    int i2 = cncl_ob->u.infr_->int2;
#ifdef DEBUG
    ind(d);
    printf("B-Plus: ");
    printf("%d plus %d",i1,i2);
    printf("\n");
#endif
    Asmp *asmp_ob = NULL;
    Val *val_ob = (Val *)malloc(sizeof(Val));
    val_ob->val_type = INT_;
    val_ob->u.int_ = (Int *)malloc(sizeof(Int));
    val_ob->u.int_->i = i1 + i2;
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.infr_->val_ = val_ob;
    return;
}

void B_Minus(Cncl *cncl_ob, int d){
    int i1 = cncl_ob->u.infr_->int1;
    int i2 = cncl_ob->u.infr_->int2;
#ifdef DEBUG
    ind(d);
    printf("B-Minus: ");
    printf("%d minus %d",i1,i2);
    printf("\n");
#endif
    Asmp *asmp_ob = NULL;
    Val *val_ob = (Val *)malloc(sizeof(Val));
    val_ob->val_type = INT_;
    val_ob->u.int_ = (Int *)malloc(sizeof(Int));
    val_ob->u.int_->i = i1 - i2;
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.infr_->val_ = val_ob;
    return;
}

void B_Times(Cncl *cncl_ob, int d){
    int i1 = cncl_ob->u.infr_->int1;
    int i2 = cncl_ob->u.infr_->int2;
#ifdef DEBUG
    ind(d);
    printf("B-Times: ");
    printf("%d times %d",i1,i2);
    printf("\n");
#endif
    Asmp *asmp_ob = NULL;
    Val *val_ob = (Val *)malloc(sizeof(Val));
    val_ob->val_type = INT_;
    val_ob->u.int_ = (Int *)malloc(sizeof(Int));
    val_ob->u.int_->i = i1 * i2;
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.infr_->val_ = val_ob;
    return;
}

void B_Lt(Cncl *cncl_ob, int d){
    int i1 = cncl_ob->u.infr_->int1;
    int i2 = cncl_ob->u.infr_->int2;
#ifdef DEBUG
    ind(d);
    printf("B-Lt: ");
    printf("%d less than %d",i1,i2);
    printf("\n");
#endif
    Asmp *asmp_ob = NULL;
    Val *val_ob = (Val *)malloc(sizeof(Val));
    val_ob->val_type = BOOL_;
    val_ob->u.bool_ = (Bool *)malloc(sizeof(Bool));
    val_ob->u.bool_->b = i1 < i2;
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.infr_->val_ = val_ob;
    return;
}

void E_Int(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("E-Int: ");
    writeEnv(cncl_ob->u.eval_->env_);
    printf(" |- ");
    writeExp(cncl_ob->u.eval_->exp_);
    printf("\n");
#endif
    Int *i = cncl_ob->u.eval_->exp_->u.int_;
    Asmp *asmp_ob = NULL;
    Val *val_ob = (Val *)malloc(sizeof(Val));
    val_ob->val_type = INT_;
    val_ob->u.int_ = copyInt(i);
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.eval_->val_ = val_ob;
    return;
}

void E_Bool(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("E-Bool: ");
    writeEnv(cncl_ob->u.eval_->env_);
    printf(" |- ");
    writeExp(cncl_ob->u.eval_->exp_);
    printf("\n");
#endif
    Bool *b = cncl_ob->u.eval_->exp_->u.bool_;
    Asmp *asmp_ob = NULL;
    Val *val_ob = (Val *)malloc(sizeof(Val));
    val_ob->val_type = BOOL_;
    val_ob->u.bool_ = copyBool(b);
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.eval_->val_ = val_ob;
    return;
}

void E_Var1(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("E-Var1: ");
    writeEnv(cncl_ob->u.eval_->env_);
    printf(" |- ");
    writeExp(cncl_ob->u.eval_->exp_);
    printf("\n");
#endif
    Asmp *asmp_ob = NULL;
    Val *val_ob = copyVal(cncl_ob->u.eval_->env_->val_);
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.eval_->val_ = val_ob;
    return;
}

void E_Var2(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("E-Var2: ");
    writeEnv(cncl_ob->u.eval_->env_);
    printf(" |- ");
    writeExp(cncl_ob->u.eval_->exp_);
    printf("\n");
#endif
    Env *eps = cncl_ob->u.eval_->env_->prev;
    Exp *x = cncl_ob->u.eval_->exp_;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->cncl_type = EVAL;
    asmp_ob->cncl_->u.eval_ = (Eval *)malloc(sizeof(Eval));
    asmp_ob->cncl_->u.eval_->env_ = copyEnv(eps);
    asmp_ob->cncl_->u.eval_->exp_ = copyExp(x);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = NULL;

    Val *val_ob = copyVal(asmp_ob->cncl_->u.eval_->val_);
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.eval_->val_ = val_ob;
    return;
}

void E_var(Cncl *cncl_ob, int d){
    if(cmpVar(cncl_ob->u.eval_->env_->var_,cncl_ob->u.eval_->exp_->u.var_)==0){
        E_Var1(cncl_ob,d);
    }else{
        E_Var2(cncl_ob,d);
    }
    return;
}

void E_Op(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("E-Op: ");
    writeEnv(cncl_ob->u.eval_->env_);
    printf(" |- ");
    writeExp(cncl_ob->u.eval_->exp_);
    printf("\n");
#endif
    Env *eps = cncl_ob->u.eval_->env_;
    Exp *e1 = cncl_ob->u.eval_->exp_->u.op_->exp1_;
    Exp *e2 = cncl_ob->u.eval_->exp_->u.op_->exp2_;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->cncl_type = EVAL;
    asmp_ob->cncl_->u.eval_ = (Eval *)malloc(sizeof(Eval));
    asmp_ob->cncl_->u.eval_->env_ = copyEnv(eps);
    asmp_ob->cncl_->u.eval_->exp_ = copyExp(e1);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->cncl_->cncl_type = EVAL;
    asmp_ob->next->cncl_->u.eval_ = (Eval *)malloc(sizeof(Eval));
    asmp_ob->next->cncl_->u.eval_->env_ = copyEnv(eps);
    asmp_ob->next->cncl_->u.eval_->exp_ = copyExp(e2);
    derivation(asmp_ob->next->cncl_,d+1);
    asmp_ob->next->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->next->cncl_->cncl_type = INFR;
    asmp_ob->next->next->cncl_->u.infr_ = (Infr *)malloc(sizeof(Infr));

    InfrOpType tmp = cncl_ob->u.eval_->exp_->u.op_->op_type;
    if(tmp == PLUS){
        asmp_ob->next->next->cncl_->u.infr_->infr_type = PLUS;
    }else if(tmp == MINUS){
        asmp_ob->next->next->cncl_->u.infr_->infr_type = MINUS;
    }else if(tmp == TIMES){
        asmp_ob->next->next->cncl_->u.infr_->infr_type = TIMES;
    }else{
        asmp_ob->next->next->cncl_->u.infr_->infr_type = LT;
    }

    asmp_ob->next->next->cncl_->u.infr_->int1 = asmp_ob->cncl_->u.eval_->val_->u.int_->i;
    asmp_ob->next->next->cncl_->u.infr_->int2 = asmp_ob->next->cncl_->u.eval_->val_->u.int_->i;
    derivation(asmp_ob->next->next->cncl_,d+1);
    asmp_ob->next->next->next = NULL;

    Val *val_ob = copyVal(asmp_ob->next->next->cncl_->u.infr_->val_);
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.eval_->val_ = val_ob;
    return;
}

void E_If(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("E-If: ");
    writeEnv(cncl_ob->u.eval_->env_);
    printf(" |- ");
    writeExp(cncl_ob->u.eval_->exp_);
    printf("\n");
#endif
    Env *eps = cncl_ob->u.eval_->env_;
    Exp *e1 = cncl_ob->u.eval_->exp_->u.if_->exp1_;
    Exp *e2 = cncl_ob->u.eval_->exp_->u.if_->exp2_;
    Exp *e3 = cncl_ob->u.eval_->exp_->u.if_->exp3_;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->cncl_type = EVAL;
    asmp_ob->cncl_->u.eval_ = (Eval *)malloc(sizeof(Eval));
    asmp_ob->cncl_->u.eval_->env_ = copyEnv(eps);
    asmp_ob->cncl_->u.eval_->exp_ = copyExp(e1);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->cncl_->cncl_type = EVAL;
    asmp_ob->next->cncl_->u.eval_ = (Eval *)malloc(sizeof(Eval));
    asmp_ob->next->cncl_->u.eval_->env_ = copyEnv(eps);

    if(asmp_ob->cncl_->u.eval_->val_->u.bool_->b){
        asmp_ob->next->cncl_->u.eval_->exp_ = copyExp(e2);
    }else{
        asmp_ob->next->cncl_->u.eval_->exp_ = copyExp(e3);
    }
    derivation(asmp_ob->next->cncl_,d+1);
    asmp_ob->next->next = NULL;

    Val *val_ob = copyVal(asmp_ob->next->cncl_->u.eval_->val_);
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.eval_->val_ = val_ob;
    return;
}

void E_Let(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("E-Let: ");
    writeEnv(cncl_ob->u.eval_->env_);
    printf(" |- ");
    writeExp(cncl_ob->u.eval_->exp_);
    printf("\n");
#endif
    Env *eps = cncl_ob->u.eval_->env_;
    Var *x = cncl_ob->u.eval_->exp_->u.let_->var_;
    Exp *e1 = cncl_ob->u.eval_->exp_->u.let_->exp1_;
    Exp *e2 = cncl_ob->u.eval_->exp_->u.let_->exp2_;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->cncl_type = EVAL;
    asmp_ob->cncl_->u.eval_ = (Eval *)malloc(sizeof(Eval));
    asmp_ob->cncl_->u.eval_->env_ = copyEnv(eps);
    asmp_ob->cncl_->u.eval_->exp_ = copyExp(e1);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->cncl_->cncl_type = EVAL;
    asmp_ob->next->cncl_->u.eval_ = (Eval *)malloc(sizeof(Eval));
    asmp_ob->next->cncl_->u.eval_->env_ = (Env *)malloc(sizeof(Env));
    asmp_ob->next->cncl_->u.eval_->env_->prev = copyEnv(eps);
    asmp_ob->next->cncl_->u.eval_->env_->var_ = copyVar(x);
    asmp_ob->next->cncl_->u.eval_->env_->val_ = copyVal(asmp_ob->cncl_->u.eval_->val_);
    asmp_ob->next->cncl_->u.eval_->exp_ = copyExp(e2);
    derivation(asmp_ob->next->cncl_,d+1);
    asmp_ob->next->next = NULL;

    Val *val_ob = copyVal(asmp_ob->next->cncl_->u.eval_->val_);
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.eval_->val_ = val_ob;
    return;
}

void E_Fun(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("E-Fun: ");
    writeEnv(cncl_ob->u.eval_->env_);
    printf(" |- ");
    writeExp(cncl_ob->u.eval_->exp_);
    printf("\n");
#endif
    Env *eps = cncl_ob->u.eval_->env_;
    Var *x = cncl_ob->u.eval_->exp_->u.fun_->arg;
    Exp *e = cncl_ob->u.eval_->exp_->u.fun_->exp_;

    Asmp *asmp_ob = NULL;
    Val *val_ob = (Val *)malloc(sizeof(Val));
    val_ob->val_type = CLSR;
    val_ob->u.clsr_ = (Clsr *)malloc(sizeof(Clsr));
    val_ob->u.clsr_->env_ = copyEnv(eps);
    val_ob->u.clsr_->arg = copyVar(x);
    val_ob->u.clsr_->exp_ = copyExp(e);

    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.eval_->val_ = val_ob;
    return;
}

void E_App(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("E-App: ");
    writeEnv(cncl_ob->u.eval_->env_);
    printf(" |- ");
    writeExp(cncl_ob->u.eval_->exp_);
    printf("\n");
#endif
    Env *eps = cncl_ob->u.eval_->env_;
    Exp *e1 = cncl_ob->u.eval_->exp_->u.app_->exp1_;
    Exp *e2 = cncl_ob->u.eval_->exp_->u.app_->exp2_;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->cncl_type = EVAL;
    asmp_ob->cncl_->u.eval_ = (Eval *)malloc(sizeof(Eval));
    asmp_ob->cncl_->u.eval_->env_ = copyEnv(eps);
    asmp_ob->cncl_->u.eval_->exp_ = copyExp(e1);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->cncl_->cncl_type = EVAL;
    asmp_ob->next->cncl_->u.eval_ = (Eval *)malloc(sizeof(Eval));
    asmp_ob->next->cncl_->u.eval_->env_ = copyEnv(eps);
    asmp_ob->next->cncl_->u.eval_->exp_ = copyExp(e2);
    derivation(asmp_ob->next->cncl_,d+1);
    asmp_ob->next->next = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->next->next->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->next->next->cncl_->cncl_type = EVAL;
    asmp_ob->next->next->cncl_->u.eval_ = (Eval *)malloc(sizeof(Eval));

    if(asmp_ob->cncl_->u.eval_->val_->val_type==CLSR){
        Env *eps2 = asmp_ob->cncl_->u.eval_->val_->u.clsr_->env_;
        Var *x = asmp_ob->cncl_->u.eval_->val_->u.clsr_->arg;
        Val *v2 = asmp_ob->next->cncl_->u.eval_->val_;
        Exp *e0 = asmp_ob->cncl_->u.eval_->val_->u.clsr_->exp_;

        asmp_ob->next->next->cncl_->u.eval_->env_ = (Env *)malloc(sizeof(Env));
        asmp_ob->next->next->cncl_->u.eval_->env_->prev = copyEnv(eps2);
        asmp_ob->next->next->cncl_->u.eval_->env_->var_ = copyVar(x);
        asmp_ob->next->next->cncl_->u.eval_->env_->val_ = copyVal(v2);
        asmp_ob->next->next->cncl_->u.eval_->exp_ = copyExp(e0);
    }else{
        Env *eps2 = asmp_ob->cncl_->u.eval_->val_->u.clsrrec_->env_;
        Var *x = asmp_ob->cncl_->u.eval_->val_->u.clsrrec_->fun;
        Var *y = asmp_ob->cncl_->u.eval_->val_->u.clsrrec_->arg;
        Val *v2 = asmp_ob->next->cncl_->u.eval_->val_;
        Exp *e0 = asmp_ob->cncl_->u.eval_->val_->u.clsrrec_->exp_;

        asmp_ob->next->next->cncl_->u.eval_->env_ = (Env *)malloc(sizeof(Env));
        asmp_ob->next->next->cncl_->u.eval_->env_->prev = (Env *)malloc(sizeof(Env));
        asmp_ob->next->next->cncl_->u.eval_->env_->prev->prev = copyEnv(eps2);
        asmp_ob->next->next->cncl_->u.eval_->env_->prev->var_ = copyVar(x);
        asmp_ob->next->next->cncl_->u.eval_->env_->prev->val_ = copyVal(asmp_ob->cncl_->u.eval_->val_);
        asmp_ob->next->next->cncl_->u.eval_->env_->var_ = copyVar(y);
        asmp_ob->next->next->cncl_->u.eval_->env_->val_ = copyVal(v2);
        asmp_ob->next->next->cncl_->u.eval_->exp_ = copyExp(e0);
    }

    derivation(asmp_ob->next->next->cncl_,d+1);
    asmp_ob->next->next->next = NULL;

    Val *val_ob = copyVal(asmp_ob->next->next->cncl_->u.eval_->val_);
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.eval_->val_ = val_ob;
    return;
}

void E_LetRec(Cncl *cncl_ob, int d){
#ifdef DEBUG
    ind(d);
    printf("E-LetRec: ");
    writeEnv(cncl_ob->u.eval_->env_);
    printf(" |- ");
    writeExp(cncl_ob->u.eval_->exp_);
    printf("\n");
#endif
    Env *eps = cncl_ob->u.eval_->env_;
    Var *x = cncl_ob->u.eval_->exp_->u.letrec_->fun;
    Var *y = cncl_ob->u.eval_->exp_->u.letrec_->arg;
    Exp *e1 = cncl_ob->u.eval_->exp_->u.letrec_->exp1_;
    Exp *e2 = cncl_ob->u.eval_->exp_->u.letrec_->exp2_;

    Asmp *asmp_ob = (Asmp *)malloc(sizeof(Asmp));
    asmp_ob->cncl_ = (Cncl *)malloc(sizeof(Cncl));
    asmp_ob->cncl_->cncl_type = EVAL;
    asmp_ob->cncl_->u.eval_ = (Eval *)malloc(sizeof(Eval));
    asmp_ob->cncl_->u.eval_->env_ = (Env *)malloc(sizeof(Env));
    asmp_ob->cncl_->u.eval_->env_->prev = copyEnv(eps);
    asmp_ob->cncl_->u.eval_->env_->var_ = copyVar(x);
    asmp_ob->cncl_->u.eval_->env_->val_ = (Val *)malloc(sizeof(Var));
    asmp_ob->cncl_->u.eval_->env_->val_->val_type = CLSRREC;
    asmp_ob->cncl_->u.eval_->env_->val_->u.clsrrec_ = (ClsrRec *)malloc(sizeof(ClsrRec));
    asmp_ob->cncl_->u.eval_->env_->val_->u.clsrrec_->env_ = copyEnv(eps);
    asmp_ob->cncl_->u.eval_->env_->val_->u.clsrrec_->fun = copyVar(x);
    asmp_ob->cncl_->u.eval_->env_->val_->u.clsrrec_->arg = copyVar(y);
    asmp_ob->cncl_->u.eval_->env_->val_->u.clsrrec_->exp_ = copyExp(e1);
    asmp_ob->cncl_->u.eval_->exp_ = copyExp(e2);
    derivation(asmp_ob->cncl_,d+1);
    asmp_ob->next = NULL;

    Val *val_ob = copyVal(asmp_ob->cncl_->u.eval_->val_);
    cncl_ob->asmp_ = asmp_ob;
    cncl_ob->u.eval_->val_ = val_ob;
    return;
}

void derivation(Cncl *cncl_ob, int d){
    if(cncl_ob->cncl_type == INFR){
        InfrOpType tmp = cncl_ob->u.infr_->infr_type;
        if(tmp==PLUS) B_Plus(cncl_ob,d);
        else if(tmp==MINUS) B_Minus(cncl_ob,d);
        else if(tmp==TIMES) B_Times(cncl_ob,d);
        else B_Lt(cncl_ob,d);
    }else{
        ExpType tmp = cncl_ob->u.eval_->exp_->exp_type;
        if(tmp == INT) E_Int(cncl_ob,d);
        else if(tmp == BOOL) E_Bool(cncl_ob,d);
        else if(tmp == VAR) E_var(cncl_ob,d);
        else if(tmp == OP) E_Op(cncl_ob, d);
        else if(tmp == IF) E_If(cncl_ob, d);
        else if(tmp == LET) E_Let(cncl_ob,d);
        else if(tmp == FUN) E_Fun(cncl_ob,d);
        else if(tmp == APP) E_App(cncl_ob,d);
        else E_LetRec(cncl_ob,d);
    }
    return;
}
