/*typedef enum{ //cncl type
    INFR,
    EVAL
}CnclType;*/

/*typedef enum{ //val type
    INT_,
    BOOL_,
    CLSR,
    CLSRREC
}ValType;*/

typedef enum{ // exp type
    INT,
    BOOL,
    VAR,
    OP,
    IF,
    LET,
    FUN,
    APP,
    LETREC
}ExpType;

typedef enum{ // op type
    PLUS,
    MINUS,
    TIMES,
    LT
}OpType;



struct VarList_;

struct Int_;
struct Bool_;

struct Var_;
struct Op_;
struct If_;
struct Let_;
struct Fun_;
struct App_;
struct LetRec_;
struct DBVar_;
struct DBOp_;
struct DBIf_;
struct DBLet_;
struct DBFun_;
struct DBApp_;
struct DBLetRec_;

struct Exp_;
struct DBExp_;

struct Asmp_;

struct Cncl_;


typedef struct VarList_{
    struct Var_ *var_;
    struct VarList_ *prev;
}VarList;

typedef struct Int_{
    int i;
}Int;


typedef struct Bool_{
    int b;
}Bool;


typedef struct Var_{
    char *var_name;
}Var;

typedef struct Op_{
    OpType op_type;
    struct Exp_ *exp1_;
    struct Exp_ *exp2_;
}Op;

typedef struct If_{
    struct Exp_ *exp1_;
    struct Exp_ *exp2_;
    struct Exp_ *exp3_;
}If;

typedef struct Let_{
    struct Var_ *var_;
    struct Exp_ *exp1_;
    struct Exp_ *exp2_;
}Let;

typedef struct Fun_{
    struct Var_ *arg;
    struct Exp_ *exp_;
}Fun;

typedef struct App_{
    struct Exp_ *exp1_;
    struct Exp_ *exp2_;
}App;

typedef struct LetRec_{
    struct Var_ *fun;
    struct Var_ *arg;
    struct Exp_ *exp1_;
    struct Exp_ *exp2_;
}LetRec;

typedef struct Exp_{
    ExpType exp_type;
    union{
        struct Int_ *int_;
        struct Bool_ *bool_;
        struct Var_ *var_;
        struct Op_ *op_;
        struct If_ *if_;
        struct Let_ *let_;
        struct Fun_ *fun_;
        struct App_ *app_;
        struct LetRec_ *letrec_;
    }u;
}Exp;


typedef struct DBVar_{
    int n;
}DBVar;

typedef struct DBOp_{
    OpType op_type;
    struct DBExp_ *dbexp1_;
    struct DBExp_ *dbexp2_;
}DBOp;

typedef struct DBIf_{
    struct DBExp_ *dbexp1_;
    struct DBExp_ *dbexp2_;
    struct DBExp_ *dbexp3_;
}DBIf;

typedef struct DBLet_{
    struct DBExp_ *dbexp1_;
    struct DBExp_ *dbexp2_;
}DBLet;

typedef struct DBFun_{
    struct DBExp_ *dbexp_;
}DBFun;

typedef struct DBApp_{
    struct DBExp_ *dbexp1_;
    struct DBExp_ *dbexp2_;
}DBApp;

typedef struct DBLetRec_{
    struct DBExp_ *dbexp1_;
    struct DBExp_ *dbexp2_;
}DBLetRec;

typedef struct DBExp_{
    ExpType exp_type;
    union{
        struct Int_ *int_;
        struct Bool_ *bool_;
        struct DBVar_ *dbvar_;
        struct DBOp_ *dbop_;
        struct DBIf_ *dbif_;
        struct DBLet_ *dblet_;
        struct DBFun_ *dbfun_;
        struct DBApp_ *dbapp_;
        struct DBLetRec_ *dbletrec_;
    }u;
}DBExp;

typedef struct Asmp_{
    struct Cncl_ *cncl_;
    struct Asmp_ *next;
}Asmp;

typedef struct Cncl_{
    struct Asmp_ *asmp_;
    struct VarList_ *varlist_;
    struct Exp_ *exp_;
    struct DBExp_ *dbexp_;
}Cncl;
