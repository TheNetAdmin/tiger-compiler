typedef struct F_frame_ * F_frame;/*format-params & local-var info in stack-frame*/
typedef struct F_access_ * F_access;/*format-params & local-vat info in register or stack*/
typedef struct F_accessList_ * F_accessList;

struct F_accessList_ {F_access head; F_accessList tail;};

F_frame F_newFrame(Temp_label name, U_boolList formals); /*construct-func -> stack-frame*/
Temp_label F_name(F_frame f);
F_accessList F_formals(F_frame f);/**/
F_access F_allocLocal(F_frame f, bool escape);/*alloc a new local-var*/

/**********/
void display_f(F_frame);
void dis_ac(F_access);
