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
        printf("\x1b[%dm",(i%6)+31);
        if(i<d-1)printf("│ ");
        else printf("├─");
    }
    printf("\x1b[39m");
    return;
}

void writeRuleName(Cncl *cncl_ob){
    RuleType tmp = cncl_ob->rule_type;
    if(tmp==TR_INT)printf("Tr-Int");
    else if(tmp==TR_INT)printf("Tr-Bool");
    else if(tmp==TR_IF)printf("Tr-If");
    else if(tmp==TR_PLUS)printf("Tr-Plus");
    else if(tmp==TR_MINUS)printf("Tr-Minus");
    else if(tmp==TR_TIMES)printf("Tr-Times");
    else if(tmp==TR_LT)printf("Tr-Lt");
    else if(tmp==TR_VAR1)printf("Tr-Var1");
    else if(tmp==TR_VAR2)printf("Tr-Var2");
    else if(tmp==TR_LET)printf("Tr-Let");
    else if(tmp==TR_FUN)printf("Tr-Fun");
    else if(tmp==TR_APP)printf("Tr-App");
    else printf("Tr-LetRec");
}
