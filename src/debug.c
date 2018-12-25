#include "param.h"
#include <stdio.h>

void debugVarList(VarList *, int);

void debugInt(Int *, int);
void debugBool(Bool *, int);

void debugVar(Var *, int);
void debugOp(Op *, int);
void debugIf(If *, int);
void debugLet(Let *, int);
void debugFun(Fun *, int);
void debugApp(App *, int);
void debugLetRec(LetRec *, int);
void debugExp(Exp *, int);

void debugDBVar(DBVar *, int);
void debugDBOp(DBOp *, int);
void debugDBIf(DBIf *, int);
void debugDBLet(DBLet *, int);
void debugDBFun(DBFun *, int);
void debugDBApp(DBApp *, int);
void debugDBLetRec(DBLetRec *, int);
void debugDBExp(DBExp *, int);

void debugCncl(Cncl *, int);

void tree(int);


void debugInt(Int *int_ob, int d){
    tree(d);
    printf("int\n");
    tree(d+1);
    printf("%d\n",int_ob->i);
    return;
}

void debugBool(Bool *bool_ob, int d){
    tree(d);
    printf("bool\n");
    tree(d+1);
    if(bool_ob->b)printf("true\n");
    else printf("false\n");
    return;
}

void debugVarList(VarList *varlist_ob, int d){
    if(varlist_ob==NULL){
        tree(d);
        printf("varlist\n");
        return;
    }
    debugVarList(varlist_ob->prev,d);
    debugVar(varlist_ob->var_,d+1);
    return;
};

void debugVar(Var *var_ob, int d){
    tree(d);
    printf("var\n");
    tree(d+1);
    printf("%s\n",var_ob->var_name);
    return;
}

void debugDBVar(DBVar *dbvar_ob, int d){
    tree(d);
    printf("dbvar\n");
    tree(d+1);
    printf("#%d\n",dbvar_ob->n);
    return;
}

void debugOp(Op *op_ob, int d){
    tree(d);
    if(op_ob->op_type==PLUS)printf("op(+)\n");
    else if(op_ob->op_type==TIMES)printf("op(*)\n");
    else if(op_ob->op_type==MINUS)printf("op(-)\n");
    else printf("op(<)\n");
    debugExp(op_ob->exp1_,d+1);
    debugExp(op_ob->exp2_,d+1);
    return;
};

void debugDBOp(DBOp *dbop_ob, int d){
    tree(d);
    if(dbop_ob->op_type==PLUS)printf("dbop(+)\n");
    else if(dbop_ob->op_type==TIMES)printf("dbop(*)\n");
    else if(dbop_ob->op_type==MINUS)printf("dbop(-)\n");
    else printf("dbop(<)\n");
    debugDBExp(dbop_ob->dbexp1_,d+1);
    debugDBExp(dbop_ob->dbexp2_,d+1);
    return;
};


void debugIf(If *if_ob, int d){
    tree(d);
    printf("if\n");
    debugExp(if_ob->exp1_,d+1);
    debugExp(if_ob->exp2_,d+1);
    debugExp(if_ob->exp3_,d+1);
    return;
};

void debugDBIf(DBIf *dbif_ob, int d){
    tree(d);
    printf("dbif\n");
    debugDBExp(dbif_ob->dbexp1_,d+1);
    debugDBExp(dbif_ob->dbexp2_,d+1);
    debugDBExp(dbif_ob->dbexp3_,d+1);
    return;
};

void debugLet(Let *let_ob, int d){
    tree(d);
    printf("let\n");
    debugVar(let_ob->var_,d+1);
    debugExp(let_ob->exp1_,d+1);
    debugExp(let_ob->exp2_,d+1);
    return;
}

void debugDBLet(DBLet *dblet_ob, int d){
    tree(d);
    printf("dblet\n");
    debugDBExp(dblet_ob->dbexp1_,d+1);
    debugDBExp(dblet_ob->dbexp2_,d+1);
    return;
}

void debugFun(Fun *fun_ob, int d){
    tree(d);
    printf("fun\n");
    debugVar(fun_ob->arg,d+1);
    debugExp(fun_ob->exp_,d+1);
    return;
}

void debugDBFun(DBFun *dbfun_ob, int d){
    tree(d);
    printf("dbfun\n");
    debugDBExp(dbfun_ob->dbexp_,d+1);
    return;
}

void debugApp(App *app_ob, int d){
    tree(d);
    printf("app\n");
    debugExp(app_ob->exp1_,d+1);
    debugExp(app_ob->exp2_,d+1);
    return;
}

void debugDBApp(DBApp *dbapp_ob, int d){
    tree(d);
    printf("dbapp\n");
    debugDBExp(dbapp_ob->dbexp1_,d+1);
    debugDBExp(dbapp_ob->dbexp2_,d+1);
    return;
}

void debugLetRec(LetRec *letrec_ob, int d){
    tree(d);
    printf("letrec\n");
    debugVar(letrec_ob->fun,d+1);
    debugVar(letrec_ob->arg,d+1);
    debugExp(letrec_ob->exp1_,d+1);
    debugExp(letrec_ob->exp2_,d+1);
    return;
}

void debugDBLetRec(DBLetRec *dbletrec_ob, int d){
    tree(d);
    printf("dbletrec\n");
    debugDBExp(dbletrec_ob->dbexp1_,d+1);
    debugDBExp(dbletrec_ob->dbexp2_,d+1);
    return;
}

void debugExp(Exp *exp_ob, int d){
    tree(d);
    printf("exp\n");
    if(exp_ob->exp_type==INT){
        debugInt(exp_ob->u.int_,d+1);
    }else if(exp_ob->exp_type==BOOL){
        debugBool(exp_ob->u.bool_,d+1);
    }else if(exp_ob->exp_type==VAR){
        debugVar(exp_ob->u.var_,d+1);
    }else if(exp_ob->exp_type==OP){
        debugOp(exp_ob->u.op_,d+1);
    }else if(exp_ob->exp_type==IF){
        debugIf(exp_ob->u.if_,d+1);
    }else if(exp_ob->exp_type==LET){
        debugLet(exp_ob->u.let_,d+1);
    }else if(exp_ob->exp_type==FUN){
        debugFun(exp_ob->u.fun_,d+1);
    }else if(exp_ob->exp_type==APP){
        debugApp(exp_ob->u.app_,d+1);
    }else{
        debugLetRec(exp_ob->u.letrec_,d+1);
    }
    return;
};

void debugDBExp(DBExp *dbexp_ob, int d){
    tree(d);
    printf("dbexp\n");
    if(dbexp_ob->exp_type==INT){
        debugInt(dbexp_ob->u.int_,d+1);
    }else if(dbexp_ob->exp_type==BOOL){
        debugBool(dbexp_ob->u.bool_,d+1);
    }else if(dbexp_ob->exp_type==VAR){
        debugDBVar(dbexp_ob->u.dbvar_,d+1);
    }else if(dbexp_ob->exp_type==OP){
        debugDBOp(dbexp_ob->u.dbop_,d+1);
    }else if(dbexp_ob->exp_type==IF){
        debugDBIf(dbexp_ob->u.dbif_,d+1);
    }else if(dbexp_ob->exp_type==LET){
        debugDBLet(dbexp_ob->u.dblet_,d+1);
    }else if(dbexp_ob->exp_type==FUN){
        debugDBFun(dbexp_ob->u.dbfun_,d+1);
    }else if(dbexp_ob->exp_type==APP){
        debugDBApp(dbexp_ob->u.dbapp_,d+1);
    }else{
        debugDBLetRec(dbexp_ob->u.dbletrec_,d+1);
    }
    return;
};

void debugCncl(Cncl *cncl_ob,int d){
    tree(d);
    printf("cncl\n");

    debugVarList(cncl_ob->varlist_,d+1);
    debugExp(cncl_ob->exp_,d+1);
    debugDBExp(cncl_ob->dbexp_,d+1);
    return;
}
