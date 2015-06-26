#include "Opcodes.h"

int x86Opnum = 299;

const char* x86Opcodes[] = { 
           //数据传输指令28 
	         "mov", "movsx", "movzx", "push", "pop", "pusha", "popa", "pushad", "popad", "bswap", "xchg", 
	         "cmpxchg", "xadd", "xlat", "in", "out", "lea", "lds", "les", "lfs", "lgs", "lss", "lahf", 
           "sahf", "pushf", "popf", "pushd", "popd", "cmovz",
           //算术运算指令22
					 "add", "sub", "adc", "sbb", "inc", "dec", "aaa", "aas", "daa", "das", "nec", "cmp", 
           "mul", "imul", "aam", "div", "idiv", "aad", "cbw", "cwd", "cwde", "cdq",
				   //逻辑运算指令13
           "and", "or", "xor", "not", "test", "shl", "sal", "shr", "sar", "rol", "ror", "rcl", "rcr", "neg",
				   //程序转移指令58
				   "jmp", "call","leave", "ret", "retn", "retf", "ja", "jnbe", "jae", "jnb", "jb", "jnae", "jbe", "jna", 
				   "jg", "jnle", "jge", "jnl", "jl", "jnge", "jle", "jng", "je", "jz", "jne", "jnz", "jc", 
				   "jnc", "jno", "jnp", "jpo", "jns","jp", "jpe", "jo", "js", "loop", "loope", "loopz", 
				   "loopne", "loopnz", "jcxz", "jecxz", "int", "into", "iret", "hlt", "wait", "esc", "lock", 
				   "nop", "stc", "clc", "cmc", "std", "cld", "sti", "cli",  
				   //伪指令7
				   "dw", "proc", "endp", "segment", "assume", "ends", "end", "label",
				   //位操作指令6
				   "bt", "btc", "btr", "bts", "bsf", "bsr",
				   //set操作17
				   "setb", "setnb", "setbe", "setnbe", "setl", "setnl", "seto", "setno", "setp", "setnp", 
				   "sets", "setns", "setz", "setnz", "setle", "setnle", "align",
           //串指令27
				   "rep", "repe", "repz", "repne", "repnz", "repc", "repnc", "movs", "movsb", "movsw", "movsd",
				   "cmps", "cmpsb", "cmpsw", "cmpsd", "scas", "scasb", "scasw", "scasd", "lods", "lodsb", "lodsw", 
				   "lodsd","stos","stosb","stosw","stosd",
				   //浮点指令69
				   "f2xm1", "fabs", "fadd", "fsub", "faddp", "fsubp", "fiadd", "fchs", "fclex", "fnclex", "fcom",
				   "fcomp", "fcompp", "fcos", "fdiv", "fdivp", "fidiv", "fdivr","fdivrp", "fidivr",
				   "ficom", "ficomp", "fild", "fincstp", "finit", "fist", "fistp", "fld", "fld1", "fldl2t",
				   "fldl2e", "fldpi", "fldlg2", "fldln2", "fldz", "fldcw", "fmul", "fmulp", "fimul", "fnop",
				   "fpatan", "fprem", "fprem1", "fptan", "fscale",  "fsin", "fsincos", "fsqrt", "fst","fstp",
				   "fstcw", "fnstcw", "fstsw", "fnstsw", "fsubr", "fsubrp", "fisub", "fisubr", "ftst", "fucom",
				   "fucomi", "fucomp", "fucomip", "fucompp", "fwait", "fxch", "fyl2x", "fyl2xp1","frndint",
				   //MMX指令
				   "movq", "stmxcsr", "movdqa", "pxor", "cvttsd2si", "movapd", "pextrw", "unpcklpd", "mulpd", "addpd", "subpd",
				   "movlpd", "unpckhpd", "divsd", "shld", "mulsd", "addsd", "subsd", "andpd", "pinsrw", "pinsrw", "sqrtsd",
				   "psrlq", "psllq", "pshufd", "pmovmskb", "andnpd", "orpd", "xorpd", "movd", "cvtsd2si", "cmpltsd", "pand",
				   "paddq", "pandn", "comisd", "shufpd", "psubd", "shrd", "cpuid", "fnstenv", "fldenv", "fxam", "cvtsi2sd",
				   "cmpeqsd", "ucomisd", "ldmxcsr", "cvtsi2sd", "cmpeqsd"
};
