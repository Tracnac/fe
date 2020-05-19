#ifndef FE_MATH_H
#define FE_MATH_H
#include "fe.h"
#include <math.h>

fe_Object* f_pow(fe_Context *ctx, fe_Object *arg);
fe_Object *fn_frexp(fe_Context *ctx, fe_Object *arg);                                                                            
fe_Object *fn_acos(fe_Context *ctx, fe_Object *arg);                                                                             
fe_Object *fn_asin(fe_Context *ctx, fe_Object *arg);                                                                             
fe_Object *fn_atan(fe_Context *ctx, fe_Object *arg);                                                                             
fe_Object *fn_atan2(fe_Context *ctx, fe_Object *arg);                                                                            
fe_Object *fn_ceil(fe_Context *ctx, fe_Object *arg);                                                                             
fe_Object *fn_cos(fe_Context *ctx, fe_Object *arg);                                                                              
fe_Object *fn_cosh(fe_Context *ctx, fe_Object *arg);                                                                             
fe_Object *fn_exp(fe_Context *ctx, fe_Object *arg);                                                                              
fe_Object *fn_fabs(fe_Context *ctx, fe_Object *arg);                                                                             
fe_Object *fn_floor(fe_Context *ctx, fe_Object *arg);                                                                            
fe_Object *fn_fmod(fe_Context *ctx, fe_Object *arg);                                                                             
fe_Object *fn_log(fe_Context *ctx, fe_Object *arg);                                                                              
fe_Object *fn_log10(fe_Context *ctx, fe_Object *arg);                                                                            
fe_Object *fn_pow(fe_Context *ctx, fe_Object *arg);                                                                              
fe_Object *fn_sin(fe_Context *ctx, fe_Object *arg);                                                                              
fe_Object *fn_sinh(fe_Context *ctx, fe_Object *arg);                                                                             
fe_Object *fn_sqrt(fe_Context *ctx, fe_Object *arg);                                                                             
fe_Object *fn_tanh(fe_Context *ctx, fe_Object *arg);                                                                             

#endif
