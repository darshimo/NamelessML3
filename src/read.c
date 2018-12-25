#include "param.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#define DEBUG

#ifdef DEBUG
#include <stdio.h>
void ind(int d);
#endif


void error(char *);
Var *copyVar(Var *);

VarList *readVarList(char *);

Int *readInt(char *);
Bool *readBool(char *);

Var *readVar(char *);
If *readIf(char *);
Op *readOp(char *);
Let *readLet(char *);
Fun *readFun(char *);
App *readApp(char *);
LetRec *readLetRec(char *);
Exp *readExp(char *);

DBVar *readDBVar(char *);
DBIf *readDBIf(char *);
DBOp *readDBOp(char *);
DBLet *readDBLet(char *);
DBFun *readDBFun(char *);
DBApp *readDBApp(char *);
DBLetRec *readDBLetRec(char *);
DBExp *readDBExp(char *);

Cncl *readCncl(char *);


Int *readInt(char *str){
#ifdef DEBUG
    printf("int : %s\n",str);
#endif
    Int *int_ob = (Int *)malloc(sizeof(Int));
    int_ob->i = atoi(str);
    return int_ob;
}


Bool *readBool(char *str){
#ifdef DEBUG
    printf("bool : %s\n",str);
#endif
    Bool *bool_ob = (Bool *)malloc(sizeof(Bool));
    if(str[0]=='t')bool_ob->b = 1;
    else bool_ob->b = 0;
    return bool_ob;
}


VarList *readVarList(char *str){
    if(*str=='\0')return NULL;

    VarList *varlist_ob = (VarList *)malloc(sizeof(VarList));

    VarList *varlist_tmp = NULL;

    char *tmp = str;
    str = strrchr(tmp,',');

    if(str==NULL){
        str = tmp;
    }else{
        *str = '\0';
        str++;
        str+=strspn(str," ");
        varlist_tmp = readVarList(tmp);
    }

#ifdef DEBUG
    printf("varlist : %s\n",str);
#endif

    varlist_ob->var_ = readVar(str);
    varlist_ob->prev = varlist_tmp;

    return varlist_ob;
}


Var *readVar(char *str){
#ifdef DEBUG
    printf("var : %s\n",str);
#endif
    Var *var_ob = (Var *)malloc(sizeof(Var));
    *(str+strcspn(str," "))='\0';
    var_ob->var_name = (char *)malloc(sizeof(char)*(strlen(str)+1));
    strcpy(var_ob->var_name,str);
    return var_ob;
}

DBVar *readDBVar(char *str){
#ifdef DEBUG
    printf("dbvar : %s\n",str);
#endif
    DBVar *dbvar_ob = (DBVar *)malloc(sizeof(DBVar));
    str++;
    *(str+strcspn(str," "))='\0';
    dbvar_ob->n = atoi(str);
    return dbvar_ob;
}


If *readIf(char *str){
#ifdef DEBUG
    printf("if  : %s\n",str);
#endif
    If *if_ob = (If *)malloc(sizeof(If));

    int count = 0;
    char *str1,*str2,*str3;
    str+=strcspn(str," ");
    str+=strspn(str," ");
    str1 = str;
    while(*str!='\0'){
        if(strncmp(str-1," if ", 4)==0){
            count++;
        }else if(strncmp(str-1," then ",6)==0){
            if(count){
                count--;
            }else{
                *str = '\0';
                str++;
                break;
            }
        }
        str+=strcspn(str," ");
        str+=strspn(str," ");
    }
    str+=strcspn(str," ");
    str+=strspn(str," ");
    str2 = str;
    while(*str!='\0'){
        if(strncmp(str-1," if ",4)==0){
            count++;
        }else if(strncmp(str-1," else ",6)==0){
            if(count){
                count--;
            }else{
                *str = '\0';
                str++;
                break;
            }
        }
        str+=strcspn(str," ");
        str+=strspn(str," ");
    }
    str+=strcspn(str," ");
    str+=strspn(str," ");
    str3 = str;

    if_ob->exp1_ = readExp(str1);
    if_ob->exp2_ = readExp(str2);
    if_ob->exp3_ = readExp(str3);

    return if_ob;
}

DBIf *readDBIf(char *str){
#ifdef DEBUG
    printf("dbif  : %s\n",str);
#endif
    DBIf *dbif_ob = (DBIf *)malloc(sizeof(DBIf));

    int count = 0;
    char *str1,*str2,*str3;
    str+=strcspn(str," ");
    str+=strspn(str," ");
    str1 = str;
    while(*str!='\0'){
        if(strncmp(str-1," if ", 4)==0){
            count++;
        }else if(strncmp(str-1," then ",6)==0){
            if(count){
                count--;
            }else{
                *str = '\0';
                str++;
                break;
            }
        }
        str+=strcspn(str," ");
        str+=strspn(str," ");
    }
    str+=strcspn(str," ");
    str+=strspn(str," ");
    str2 = str;
    while(*str!='\0'){
        if(strncmp(str-1," if ",4)==0){
            count++;
        }else if(strncmp(str-1," else ",6)==0){
            if(count){
                count--;
            }else{
                *str = '\0';
                str++;
                break;
            }
        }
        str+=strcspn(str," ");
        str+=strspn(str," ");
    }
    str+=strcspn(str," ");
    str+=strspn(str," ");
    str3 = str;

    dbif_ob->dbexp1_ = readDBExp(str1);
    dbif_ob->dbexp2_ = readDBExp(str2);
    dbif_ob->dbexp3_ = readDBExp(str3);

    return dbif_ob;
}


Op *readOp(char* str){
#ifdef DEBUG
    printf("op  : %s\n",str);
#endif
    Op *op_ob = (Op *)malloc(sizeof(Op));

    int count = 0;
    op_ob->op_type = TIMES;
    char *str1, *str2;
    str1 = str;
    str2 = NULL;
    while(1){
        str += strcspn(str,"(+-*<)i");
        if(str[0]=='('){
            count++;
        }else if(str[0]==')'){
            count--;
        }else if(count==0){
            if(strncmp(str-1," if ",4)==0){
                break;
            }else if(strncmp(str-1," + ",3)==0){
                op_ob->op_type=PLUS;
                str2 = str;
            }else if(strncmp(str-1," - ",3)==0){
                if(str==str1){
                    str++;
                    continue;
                }
                op_ob->op_type=MINUS;
                str2 = str;
            }else if(strncmp(str-1," < ",3)==0){
                op_ob->op_type=LT;
                str2 = str;
                break;
            }else if(strncmp(str-1," * ",3)==0){
                if(op_ob->op_type==TIMES){
                    str2 = str;
                }
            }else if(*str=='\0'){
                break;
            }
        }
        str++;
    }

    if(str2==NULL)error("invalid.");

    *str2 = '\0';
    str2++;
    str2 += strspn(str2," ");
    op_ob->exp1_ = readExp(str1);
    op_ob->exp2_ = readExp(str2);

    return op_ob;
}

DBOp *readDBOp(char* str){
#ifdef DEBUG
    printf("dbop  : %s\n",str);
#endif
    DBOp *dbop_ob = (DBOp *)malloc(sizeof(DBOp));

    int count = 0;
    dbop_ob->op_type = TIMES;
    char *str1, *str2;
    str1 = str;
    str2 = NULL;
    while(1){
        str += strcspn(str,"(+-*<)il");
        if(str[0]=='('){
            count++;
        }else if(str[0]==')'){
            count--;
        }else if(count==0){
            if(strncmp(str-1," if ",4)*strncmp(str-1," let ",5)==0){
                break;
            }else if(strncmp(str-1," + ",3)==0){
                dbop_ob->op_type=PLUS;
                str2 = str;
            }else if(strncmp(str-1," - ",3)==0){
                if(str==str1){
                    str++;
                    continue;
                }
                dbop_ob->op_type=MINUS;
                str2 = str;
            }else if(strncmp(str-1," < ",3)==0){
                dbop_ob->op_type=LT;
                str2 = str;
                break;
            }else if(strncmp(str-1," * ",3)==0){
                if(dbop_ob->op_type==TIMES){
                    str2 = str;
                }
            }else if(*str=='\0'){
                break;
            }
        }
        str++;
    }

    if(str2==NULL)error("invalid.");

    *str2 = '\0';
    str2++;
    str2 += strspn(str2," ");
    dbop_ob->dbexp1_ = readDBExp(str1);
    dbop_ob->dbexp2_ = readDBExp(str2);

    return dbop_ob;
}


Let *readLet(char *str){
#ifdef DEBUG
    printf("let : %s\n",str);
#endif
    Let *let_ob = (Let *)malloc(sizeof(Let));

    char *str1, *str2;

    str += strcspn(str," ");
    str += strspn(str," ");
    str1 = str;
    str1 += strcspn(str1," ");
    str1 += strspn(str1," ");
    str1 += strcspn(str1," ");
    str1 += strspn(str1," ");
    str2 = str1;

    int count = 0;
    while(1){
        str2+=strcspn(str2,"li");
        if(strncmp(str2-1," let ",5)==0){
            count++;
        }else if(strncmp(str2-1," in ",4)==0){
            if(count==0){
                break;
            }
            count--;
        }else if(*str2=='\0'){
            error("2mismatch let and in.");
        }
        str2++;
    }

    *str2 = '\0';
    str2++;
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");

    let_ob->var_ = readVar(str);
    let_ob->exp1_ = readExp(str1);
    let_ob->exp2_ = readExp(str2);

    return let_ob;
}


DBLet *readDBLet(char *str){
#ifdef DEBUG
    printf("dblet : %s\n",str);
#endif
    DBLet *dblet_ob = (DBLet *)malloc(sizeof(DBLet));

    char *str1, *str2;

    str1 = str;
    for(int i=0;i<3;i++){
        str1 += strcspn(str1," ");
        str1 += strspn(str1," ");
    }
    str2 = str1;

    int count = 0;
    while(1){
        str2+=strcspn(str2,"li");
        if(strncmp(str2-1," let ",5)==0){
            count++;
        }else if(strncmp(str2-1," in ",4)==0){
            if(count==0){
                break;
            }
            count--;
        }else if(*str2=='\0'){
            error("2mismatch let and in.");
        }
        str2++;
    }

    *str2 = '\0';
    str2++;
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");

    dblet_ob->dbexp1_ = readDBExp(str1);
    dblet_ob->dbexp2_ = readDBExp(str2);

    return dblet_ob;
}


Fun *readFun(char *str){
#ifdef DEBUG
    printf("fun : %s\n",str);
#endif
    Fun *fun_ob = (Fun *)malloc(sizeof(Fun));
    char *tmp;
    str += strcspn(str," ");
    str += strspn(str," ");
    tmp = str;
    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");
    *(tmp+strcspn(tmp," "))='\0';

    fun_ob->arg = (Var *)malloc(sizeof(Var));
    fun_ob->arg->var_name = (char *)malloc(sizeof(char)*(strlen(tmp)+1));
    strcpy(fun_ob->arg->var_name,tmp);
    fun_ob->exp_ = readExp(str);

    return fun_ob;
}


DBFun *readDBFun(char *str){
#ifdef DEBUG
    printf("dbfun : %s\n",str);
#endif
    DBFun *dbfun_ob = (DBFun *)malloc(sizeof(DBFun));

    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");

    dbfun_ob->dbexp_ = readDBExp(str);

    return dbfun_ob;
}


App *readApp(char *str){
#ifdef DEBUG
    printf("app : %s\n",str);
#endif
    App *app_ob = (App *)malloc(sizeof(App));
    char *str1 = str;
    char *str2 = NULL;
    int count;

    while(1){
        if(*str=='('){
            count = 0;
            str++;
            while(1){
                str+=strcspn(str,"()");
                if(*str=='('){
                    count++;
                }else if(*str==')'){
                    if(count==0){
                        break;
                    }
                    count--;
                }else{
                    error("3mismatch parentheses.");
                }
                str++;
            }
            str++;
        }else{
            str+=strcspn(str," ");
        }
        str+=strspn(str," ");
        if(*str=='\0'){
            break;
        }else{
            str2 = str;
        }
    }

    if(str2==NULL)error("sole app.");

    *(str2-1)='\0';

    app_ob->exp1_ = readExp(str1);
    app_ob->exp2_ = readExp(str2);
    return app_ob;
}


DBApp *readDBApp(char *str){
#ifdef DEBUG
    printf("dbapp : %s\n",str);
#endif
    DBApp *dbapp_ob = (DBApp *)malloc(sizeof(DBApp));
    char *str1 = str;
    char *str2 = NULL;
    int count;

    while(1){
        if(*str=='('){
            count = 0;
            str++;
            while(1){
                str+=strcspn(str,"()");
                if(*str=='('){
                    count++;
                }else if(*str==')'){
                    if(count==0){
                        break;
                    }
                    count--;
                }else{
                    error("3mismatch parentheses.");
                }
                str++;
            }
            str++;
        }else{
            str+=strcspn(str," ");
        }
        str+=strspn(str," ");
        if(*str=='\0'){
            break;
        }else{
            str2 = str;
        }
    }

    if(str2==NULL)error("sole dbapp.");

    *(str2-1)='\0';

    dbapp_ob->dbexp1_ = readDBExp(str1);
    dbapp_ob->dbexp2_ = readDBExp(str2);
    return dbapp_ob;
}


LetRec *readLetRec(char *str){
#ifdef DEBUG
    printf("letrec : %s\n",str);
#endif
    LetRec *letrec_ob = (LetRec *)malloc(sizeof(LetRec));
    char *tmp1, *tmp2, *tmp3;
    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");
    tmp1 = str;
    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");
    tmp2 = str;
    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");
    tmp3 = str;
    *(tmp1+strcspn(tmp1," "))='\0';
    *(tmp2+strcspn(tmp2," "))='\0';

    letrec_ob->fun = (Var *)malloc(sizeof(Var));
    letrec_ob->fun->var_name = (char *)malloc(sizeof(char)*(strlen(tmp1)+1));
    strcpy(letrec_ob->fun->var_name,tmp1);
    letrec_ob->arg = (Var *)malloc(sizeof(Var));
    letrec_ob->arg->var_name = (char *)malloc(sizeof(char)*(strlen(tmp2)+1));
    strcpy(letrec_ob->arg->var_name,tmp2);

    int count = 0;
    while(1){
        str+=strcspn(str,"li");
        if(strncmp(str-1," let ",5)==0){
            count++;
        }else if(strncmp(str-1," in ",4)==0){
            if(count==0){
                break;
            }
            count--;
        }else if(*str=='\0'){
            error("4mismatch let and in.");
        }
        str++;
    }
    *str = '\0';
    str+=2;
    str += strspn(str," ");

    letrec_ob->exp1_ = readExp(tmp3);
    letrec_ob->exp2_ = readExp(str);

    return letrec_ob;
}


DBLetRec *readDBLetRec(char *str){
#ifdef DEBUG
    printf("dbletrec : %s\n",str);
#endif
    DBLetRec *dbletrec_ob = (DBLetRec *)malloc(sizeof(DBLetRec));
    char *str1, *str2;
    str1 = str;
    for(int i = 0;i<7;i++){
        str1 += strcspn(str1," ");
        str1 += strspn(str1," ");
    }
    str2 = str1;

    int count = 0;
    while(1){
        str2+=strcspn(str2,"li");
        if(strncmp(str2-1," let ",5)==0){
            count++;
        }else if(strncmp(str2-1," in ",4)==0){
            if(count==0){
                break;
            }
            count--;
        }else if(*str2=='\0'){
            error("4mismatch let and in.");
        }
        str2++;
    }

    *str2 = '\0';
    str2++;
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");

    dbletrec_ob->dbexp1_ = readDBExp(str1);
    dbletrec_ob->dbexp2_ = readDBExp(str2);

    return dbletrec_ob;
}


Exp *readExp(char* str){

    if(str[0]=='('){
        int count = 0;
        char *tmp1, *tmp2;
        tmp1 = str+1;
        while(1){
            tmp1+=strcspn(tmp1,"()");
            if(*tmp1=='('){
                count++;
            }else if(*tmp1==')'){
                if(count==0){
                    break;
                }
                count--;
            }else{
                error("5mismatch parentheses.");
            }
            tmp1++;
        }
        if(*tmp1=='\0')error("6mismatch parentheses.");
        tmp2=tmp1 + 1;
        if(*(tmp2+strspn(tmp2," "))=='\0'){
            str++;
            *tmp1 = '\0';
            return readExp(str);
        }
    }

#ifdef DEBUG
    //printf("exp : %s\n",str);
#endif

    Exp *exp_ob = (Exp *)malloc(sizeof(Exp));

    if(strncmp(str,"let rec ",8)==0){//when exp is letrec
        exp_ob->exp_type = LETREC;
        exp_ob->u.letrec_ = readLetRec(str);
    }else if(strncmp(str,"let ",4)==0){//when exp is let
        exp_ob->exp_type = LET;
        exp_ob->u.let_ = readLet(str);
    }else if(strncmp(str,"fun ",4)==0){//when exp is fun
        exp_ob->exp_type = FUN;
        exp_ob->u.fun_ = readFun(str);
    }else if(strncmp(str,"if ",3)==0){//when exp is if
        exp_ob->exp_type = IF;
        exp_ob->u.if_ = readIf(str);
    }else if(strncmp(str,"true",4)*strncmp(str,"false",5)==0){//when exp is bool
        exp_ob->exp_type = BOOL;
        exp_ob->u.bool_ = readBool(str);
    }else{

        char *tmp;
        tmp = str;
        tmp += strspn(tmp,"0123456789");
        tmp += strspn(tmp," ");
        if(*tmp=='\0'){//when exp is int
            exp_ob->exp_type = INT;
            exp_ob->u.int_ = readInt(str);
        }else{

            tmp = str;
            tmp += strcspn(tmp," ()+-*<");
            tmp += strspn(tmp," ");
            if(*tmp=='\0'){//when exp is var
                exp_ob->exp_type = VAR;
                exp_ob->u.var_ = readVar(str);
            }else{

                tmp = str;
                int count = 0;
                while(1){
                    tmp+=strcspn(tmp,"()+-*<");
                    if(*tmp=='('){
                        count++;
                    }else if(*tmp==')'){
                        count--;
                    }else if(*tmp!='\0'){
                        if(count==0)break;
                    }else{
                        break;
                    }
                    tmp++;
                }
                if(*tmp=='\0'){//when exp is app
                    exp_ob->exp_type = APP;
                    exp_ob->u.app_ = readApp(str);
                }else{//when exp is op
                    exp_ob->exp_type = OP;
                    exp_ob->u.op_ = readOp(str);
                }
            }
        }
    }

    return exp_ob;
}


DBExp *readDBExp(char* str){

    if(str[0]=='('){
        int count = 0;
        char *tmp1, *tmp2;
        tmp1 = str+1;
        while(1){
            tmp1+=strcspn(tmp1,"()");
            if(*tmp1=='('){
                count++;
            }else if(*tmp1==')'){
                if(count==0){
                    break;
                }
                count--;
            }else{
                error("7mismatch parentheses.");
            }
            tmp1++;
        }
        if(*tmp1=='\0')error("8mismatch parentheses.");
        tmp2=tmp1 + 1;
        if(*(tmp2+strspn(tmp2," "))=='\0'){
            str++;
            *tmp1 = '\0';
            return readDBExp(str);
        }
    }

#ifdef DEBUG
    //printf("dbexp : %s\n",str);
#endif

    DBExp *dbexp_ob = (DBExp *)malloc(sizeof(DBExp));

    if(strncmp(str,"let rec ",8)==0){//when exp is letrec
        dbexp_ob->exp_type = LETREC;
        dbexp_ob->u.dbletrec_ = readDBLetRec(str);
    }else if(strncmp(str,"let ",4)==0){//when exp is let
        dbexp_ob->exp_type = LET;
        dbexp_ob->u.dblet_ = readDBLet(str);
    }else if(strncmp(str,"fun ",4)==0){//when exp is fun
        dbexp_ob->exp_type = FUN;
        dbexp_ob->u.dbfun_ = readDBFun(str);
    }else if(strncmp(str,"if ",3)==0){//when exp is if
        dbexp_ob->exp_type = IF;
        dbexp_ob->u.dbif_ = readDBIf(str);
    }else if(strncmp(str,"true",4)*strncmp(str,"false",5)==0){//when exp is bool
        dbexp_ob->exp_type = BOOL;
        dbexp_ob->u.bool_ = readBool(str);
    }else{

        char *tmp;
        tmp = str;
        tmp += strspn(tmp,"0123456789");
        tmp += strspn(tmp," ");
        if(*tmp=='\0'){//when exp is int
            dbexp_ob->exp_type = INT;
            dbexp_ob->u.int_ = readInt(str);
        }else{

            tmp = str;
            tmp += strcspn(tmp," ()+-*<");
            tmp += strspn(tmp," ");
            if(*tmp=='\0'){//when exp is var
                dbexp_ob->exp_type = VAR;
                dbexp_ob->u.dbvar_ = readDBVar(str);
            }else{

                tmp = str;
                int count = 0;
                while(1){
                    tmp+=strcspn(tmp,"()+-*<");
                    if(*tmp=='('){
                        count++;
                    }else if(*tmp==')'){
                        count--;
                    }else if(*tmp!='\0'){
                        if(count==0)break;
                    }else{
                        break;
                    }
                    tmp++;
                }
                if(*tmp=='\0'){//when exp is app
                    dbexp_ob->exp_type = APP;
                    dbexp_ob->u.dbapp_ = readDBApp(str);
                }else{//when exp is op
                    dbexp_ob->exp_type = OP;
                    dbexp_ob->u.dbop_ = readDBOp(str);
                }
            }
        }
    }

    return dbexp_ob;
}


Cncl *readCncl(char* str){
#ifdef DEBUG
    printf("cncl: %s\n",str);
#endif
    Cncl *cncl_ob = (Cncl *)malloc(sizeof(Cncl));

    char *str1, *str2, *str3;
    str1 = str;
    str2 = strstr(str1,"|-");
    *str2 = '\0';
    str2+=2;
    str2+=strspn(str2," ");
    str3 = strstr(str2," ==> ");
    *str3 = '\0';
    str3+=5;
    str3+=strspn(str3," ");

    cncl_ob->varlist_ = readVarList(str1);
    cncl_ob->exp_ = readExp(str2);
    cncl_ob->dbexp_ = readDBExp(str3);

    return cncl_ob;
}
