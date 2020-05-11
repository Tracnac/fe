#include "fe_math.h"

_entrymodule _entry[] = {
  /*{opcode,cfunc,doc}*/
    {"pow","f_pow","Doc for opcode"},
    {NULL,NULL,NULL}
};

fe_Object* f_pow(fe_Context *ctx, fe_Object *arg) {
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  float y = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, pow(x, y));
}
