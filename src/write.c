#include "param.h"
#include <stdio.h>

void writeVarList(VarList *);

void writeInt(Int *);
void writeBool(Bool *);

void writeVar(Var *);
void writeOp(Op *);
void writeIf(If *);
void writeLet(Let *);
void writeFun(Fun *);
void writeApp(App *);
void writeLetRec(LetRec *);
void writeExp(Exp *);

void writeDBVar(DBVar *);
void writeDBOp(DBOp *);
void writeDBIf(DBIf *);
void writeDBLet(DBLet *);
void writeDBFun(DBFun *);
void writeDBApp(DBApp *);
void writeDBLetRec(DBLetRec *);
void writeDBExp(DBExp *);

void writeAsmp(Asmp *, int);
void writeCncl(Cncl *, int);

void ind(int);
void writeRuleName(Cncl *);


void writeInt(Int *int_ob){
    printf("%d",int_ob->i);
    return;
}

void writeBool(Bool *bool_ob){
    if(bool_ob->b)printf("true");
    else printf("false");
    return;
}

void writeVarList(VarList *varlist_ob){
    if(varlist_ob==NULL)return;
    if(varlist_ob->prev!=NULL){
        writeVarList(varlist_ob->prev);
        printf(", ");
    }
    writeVar(varlist_ob->var_);
    return;
}

void writeVar(Var *var_ob){
    printf("%s",var_ob->var_name);
    return;
}

void writeDBVar(DBVar *dbvar_ob){
    printf("#%d",dbvar_ob->n);
    return;
}

void writeOp(Op *op_ob){
    char paren1 = 0;
    char paren2 = 0;

    if(op_ob->exp1_->exp_type==IF || op_ob->exp1_->exp_type==LET || op_ob->exp1_->exp_type==LETREC){
        paren1 = 1;
    }
    if(op_ob->exp2_->exp_type==IF || op_ob->exp2_->exp_type==LET || op_ob->exp2_->exp_type==LETREC){
        paren2 = 1;
    }
    if(op_ob->op_type==TIMES && op_ob->exp1_->exp_type==OP){
        if(op_ob->exp1_->u.op_->op_type==PLUS || op_ob->exp1_->u.op_->op_type==MINUS){
            paren1 = 1;
        }
    }
    if(op_ob->op_type==TIMES && op_ob->exp2_->exp_type==OP){
        if(op_ob->exp2_->u.op_->op_type==PLUS || op_ob->exp2_->u.op_->op_type==MINUS){
            paren2 = 1;
        }
    }

    if(paren1)printf("(");
    writeExp(op_ob->exp1_);
    if(paren1)printf(")");
    if(op_ob->op_type==PLUS){
        printf(" + ");
    }else if(op_ob->op_type==TIMES){
        printf(" * ");
    }else if(op_ob->op_type==MINUS){
        printf(" - ");
    }else{
        printf(" < ");
    }
    if(paren2)printf("(");
    writeExp(op_ob->exp2_);
    if(paren2)printf(")");
    return;
}

void writeDBOp(DBOp *dbop_ob){
    char paren1 = 0;
    char paren2 = 0;

    if(dbop_ob->dbexp1_->exp_type==IF || dbop_ob->dbexp1_->exp_type==LET || dbop_ob->dbexp1_->exp_type==LETREC){
        paren1 = 1;
    }
    if(dbop_ob->dbexp2_->exp_type==IF || dbop_ob->dbexp2_->exp_type==LET || dbop_ob->dbexp2_->exp_type==LETREC){
        paren2 = 1;
    }
    if(dbop_ob->op_type==TIMES && dbop_ob->dbexp1_->exp_type==OP){
        if(dbop_ob->dbexp1_->u.dbop_->op_type==PLUS || dbop_ob->dbexp1_->u.dbop_->op_type==MINUS){
            paren1 = 1;
        }
    }
    if(dbop_ob->op_type==TIMES && dbop_ob->dbexp2_->exp_type==OP){
        if(dbop_ob->dbexp2_->u.dbop_->op_type==PLUS || dbop_ob->dbexp2_->u.dbop_->op_type==MINUS){
            paren2 = 1;
        }
    }

    if(paren1)printf("(");
    writeDBExp(dbop_ob->dbexp1_);
    if(paren1)printf(")");
    if(dbop_ob->op_type==PLUS){
        printf(" + ");
    }else if(dbop_ob->op_type==TIMES){
        printf(" * ");
    }else if(dbop_ob->op_type==MINUS){
        printf(" - ");
    }else{
        printf(" < ");
    }
    if(paren2)printf("(");
    writeDBExp(dbop_ob->dbexp2_);
    if(paren2)printf(")");
    return;
}

void writeIf(If *if_ob){
    printf("if ");
    writeExp(if_ob->exp1_);
    printf(" then ");
    writeExp(if_ob->exp2_);
    printf(" else ");
    writeExp(if_ob->exp3_);
    return;
}

void writeDBIf(DBIf *dbif_ob){
    printf("if ");
    writeDBExp(dbif_ob->dbexp1_);
    printf(" then ");
    writeDBExp(dbif_ob->dbexp2_);
    printf(" else ");
    writeDBExp(dbif_ob->dbexp3_);
    return;
}

void writeLet(Let *let_ob){
    printf("let ");
    writeVar(let_ob->var_);
    printf (" = ");
    writeExp(let_ob->exp1_);
    printf (" in ");
    writeExp(let_ob->exp2_);
    return;
}

void writeDBLet(DBLet *dblet_ob){
    printf("let . = ");
    writeDBExp(dblet_ob->dbexp1_);
    printf (" in ");
    writeDBExp(dblet_ob->dbexp2_);
    return;
}

void writeFun(Fun *fun_ob){
    printf("fun ");
    writeVar(fun_ob->arg);
    printf(" -> ");
    writeExp(fun_ob->exp_);
    return;
}

void writeDBFun(DBFun *dbfun_ob){
    printf("fun . -> ");
    writeDBExp(dbfun_ob->dbexp_);
    return;
}

void writeApp(App *app_ob){
    char paren1 = 0;
    char paren2 = 0;

    if(app_ob->exp1_->exp_type == IF || app_ob->exp1_->exp_type == LET || app_ob->exp1_->exp_type == FUN || app_ob->exp1_->exp_type == LETREC)paren1 = 1;
    if(app_ob->exp2_->exp_type == OP || app_ob->exp2_->exp_type == IF || app_ob->exp2_->exp_type == LET || app_ob->exp2_->exp_type == FUN || app_ob->exp2_->exp_type == LETREC || app_ob->exp2_->exp_type == APP)paren2 = 1;

    if(paren1)printf("(");
    writeExp(app_ob->exp1_);
    if(paren1)printf(")");
    printf(" ");
    if(paren2)printf("(");
    writeExp(app_ob->exp2_);
    if(paren2)printf(")");
    return;
}

void writeDBApp(DBApp *dbapp_ob){
    char paren1 = 0;
    char paren2 = 0;

    if(dbapp_ob->dbexp1_->exp_type == IF || dbapp_ob->dbexp1_->exp_type == LET || dbapp_ob->dbexp1_->exp_type == FUN || dbapp_ob->dbexp1_->exp_type == LETREC)paren1 = 1;
    if(dbapp_ob->dbexp2_->exp_type == OP || dbapp_ob->dbexp2_->exp_type == IF || dbapp_ob->dbexp2_->exp_type == LET || dbapp_ob->dbexp2_->exp_type == FUN || dbapp_ob->dbexp2_->exp_type == LETREC || dbapp_ob->dbexp2_->exp_type == APP)paren2 = 1;

    if(paren1)printf("(");
    writeDBExp(dbapp_ob->dbexp1_);
    if(paren1)printf(")");
    printf(" ");
    if(paren2)printf("(");
    writeDBExp(dbapp_ob->dbexp2_);
    if(paren2)printf(")");
    return;
}

void writeLetRec(LetRec *letrec_ob){
    printf("let rec ");
    writeVar(letrec_ob->fun);
    printf(" = fun ");
    writeVar(letrec_ob->arg);
    printf(" -> ");
    writeExp(letrec_ob->exp1_);
    printf(" in ");
    writeExp(letrec_ob->exp2_);
    return;
}

void writeDBLetRec(DBLetRec *dbletrec_ob){
    printf("let rec . = fun . -> ");
    writeDBExp(dbletrec_ob->dbexp1_);
    printf(" in ");
    writeDBExp(dbletrec_ob->dbexp2_);
    return;
}

void writeExp(Exp *exp_ob){
    if(exp_ob->exp_type==INT){
        writeInt(exp_ob->u.int_);
    }else if(exp_ob->exp_type==BOOL){
        writeBool(exp_ob->u.bool_);
    }else if(exp_ob->exp_type==VAR){
        writeVar(exp_ob->u.var_);
    }else if(exp_ob->exp_type==OP){
        writeOp(exp_ob->u.op_);
    }else if(exp_ob->exp_type==IF){
        writeIf(exp_ob->u.if_);
    }else if(exp_ob->exp_type==LET){
        writeLet(exp_ob->u.let_);
    }else if(exp_ob->exp_type==FUN){
        writeFun(exp_ob->u.fun_);
    }else if(exp_ob->exp_type==APP){
        writeApp(exp_ob->u.app_);
    }else{
        writeLetRec(exp_ob->u.letrec_);
    }
    return;
}

void writeDBExp(DBExp *dbexp_ob){
    if(dbexp_ob->exp_type==INT){
        writeInt(dbexp_ob->u.int_);
    }else if(dbexp_ob->exp_type==BOOL){
        writeBool(dbexp_ob->u.bool_);
    }else if(dbexp_ob->exp_type==VAR){
        writeDBVar(dbexp_ob->u.dbvar_);
    }else if(dbexp_ob->exp_type==OP){
        writeDBOp(dbexp_ob->u.dbop_);
    }else if(dbexp_ob->exp_type==IF){
        writeDBIf(dbexp_ob->u.dbif_);
    }else if(dbexp_ob->exp_type==LET){
        writeDBLet(dbexp_ob->u.dblet_);
    }else if(dbexp_ob->exp_type==FUN){
        writeDBFun(dbexp_ob->u.dbfun_);
    }else if(dbexp_ob->exp_type==APP){
        writeDBApp(dbexp_ob->u.dbapp_);
    }else{
        writeDBLetRec(dbexp_ob->u.dbletrec_);
    }
    return;
}

void writeAsmp(Asmp *asmp_ob, int d){
    if(asmp_ob==NULL)return;
    printf("\n");
    writeCncl(asmp_ob->cncl_, d);
    if(asmp_ob->next!=NULL)printf(";");
    else printf("\n");
    writeAsmp(asmp_ob->next, d);
    return;
}

void writeCncl(Cncl *cncl_ob, int d){
    ind(d);

    writeVarList(cncl_ob->varlist_);
    if(cncl_ob->varlist_!=NULL)printf(" ");
    printf("|- ");
    writeExp(cncl_ob->exp_);
    printf(" ==> ");
    writeDBExp(cncl_ob->dbexp_);

    printf(" by ");
    writeRuleName(cncl_ob);
    printf(" {");
    writeAsmp(cncl_ob->asmp_, d+1);
    if(cncl_ob->asmp_!=NULL)ind(d);
    printf("}");
    return;
}
