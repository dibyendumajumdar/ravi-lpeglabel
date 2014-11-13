/*
** $Id: lpvm.h,v 1.2 2013/04/03 20:37:18 roberto Exp $
*/

#if !defined(lpvm_h)
#define lpvm_h

#include "lpcap.h"


/* Virtual Machine's instructions */
typedef enum Opcode {
  IAny, /* if no char, fail */
  IChar,  /* if char != aux, fail */
  ISet,  /* if char not in buff, fail */
  ITestAny,  /* in no char, jump to 'offset' */
  ITestChar,  /* if char != aux, jump to 'offset' */
  ITestSet,  /* if char not in buff, jump to 'offset' */
  ISpan,  /* read a span of chars in buff */
  IBehind,  /* walk back 'aux' characters (fail if not possible) */
  IRet,  /* return from a rule */
  IEnd,  /* end of pattern */
  IChoice,  /* stack a choice; next fail will jump to 'offset' */
  IJmp,  /* jump to 'offset' */
  ICall,  /* call rule at 'offset' */
  IOpenCall,  /* call rule number 'key' (must be closed to a ICall) */
  ICommit,  /* pop choice and jump to 'offset' */
  IPartialCommit,  /* update top choice to current position and jump */
  IBackCommit,  /* "fails" but jump to its own 'offset' */
  IFailTwice,  /* pop one choice and then fail */
  IFail,  /* go back to saved state on choice and jump to saved offset */
  IGiveup,  /* internal use */
  IFullCapture,  /* complete capture of last 'off' chars */
  IOpenCapture,  /* start a capture */
  ICloseCapture,
  ICloseRunTime,
	IThrow,   /* "fails" with a specific label labeled failure */
	ILabChoice   /* labeled choice */
} Opcode;



typedef union Instruction {
  struct Inst {
    byte code;
    byte aux;
    short key;
  } i;
  int offset;
  Labelset labels; /* labeled failure */
  byte buff[1];
} Instruction;


int getposition (lua_State *L, int t, int i);
void printpatt (Instruction *p, int n);
const char *match (lua_State *L, const char *o, const char *s, const char *e,
                   Instruction *op, Capture *capture, int ptop, Labelset *labelf);
int verify (lua_State *L, Instruction *op, const Instruction *p,
            Instruction *e, int postable, int rule);
void checkrule (lua_State *L, Instruction *op, int from, int to,
                int postable, int rule);


#endif

