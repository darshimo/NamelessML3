#include <stdio.h>
#include "param.h"

int cmpVar(Var *, Var *);

void ind(int d){
    int i;
    for(i=0;i<d;i++){
        printf("  ");
    }
    return;
}

void tree(int d){
    int i;
    for(i=0;i<d;i++){
        if(i<d-1)printf("│ ");
        else printf("├─");
    }
    return;
}
/*

void writeRuleName(Cncl *cncl_ob){
    InfrOpType iot;
    ExpType ep;
    if(cncl_ob->cncl_type==INFR){
        iot = cncl_ob->u.infr_->infr_type;
        if(iot==PLUS)printf("B-Plus");
        else if(iot==MINUS)printf("B-Minus");
        else if(iot==TIMES)printf("B-Times");
        else printf("B-Lt");
    }else{
        ep = cncl_ob->u.eval_->exp_->exp_type;
        if(ep==INT)printf("E-Int");
        else if(ep==BOOL)printf("E-Bool");
        else if(ep==VAR){
            if(cmpVar(cncl_ob->u.eval_->env_->var_,cncl_ob->u.eval_->exp_->u.var_)==0)printf("E-Var1");
            else printf("E-Var2");
        }
        else if(ep==OP){
            iot = cncl_ob->u.eval_->exp_->u.op_->op_type;
            if(iot==PLUS)printf("E-Plus");
            else if(iot==MINUS)printf("E-Minus");
            else if(iot==TIMES)printf("E-Times");
            else printf("E-Lt");
        }
        else if(ep==IF){
            if(cncl_ob->asmp_->cncl_->u.eval_->val_->u.bool_->b)printf("E-IfT");
            else printf("E-IfF");
        }
        else if(ep==LET)printf("E-Let");
        else if(ep==FUN)printf("E-Fun");
        else if(ep==APP){
            if(cncl_ob->asmp_->cncl_->u.eval_->val_->val_type==CLSR)printf("E-App");
            else printf("E-AppRec");
        }
        else printf("E-LetRec");
    }
    return;
}
*/
