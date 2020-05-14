#include "fe_math.h"

_entrymodule _entry[] = {
    /* {opcode,cfunc,doc} */
    {"acos", "fn_acos", "Returns the arc cosine of x in radians."},
    {"asin", "fn_asin", "Returns the arc sine of x in radians."},
    {"atan", "fn_atan", "Returns the arc tangent of x in radians."},
    {"atan2", "fn_atan2", "Returns the arc tangent in radians of y/x based on the signs of both values to determine the correct quadrant."},
    {"cos", "fn_cos", "Returns the cosine of a radian angle x."},
    {"cosh", "fn_cosh", "Returns the hyperbolic cosine of x."},
    {"sin", "fn_sin", "Returns the sine of a radian angle x."},
    {"sinh", "fn_sinh", "Returns the hyperbolic sine of x."},
    {"tanh", "fn_tanh", "Returns the hyperbolic tangent of x."},
    {"exp", "fn_exp", "Returns the value of e raised to the xth power."},
    {"log", "fn_log", "Returns the natural logarithm (base-e logarithm) of x."},
    {"log10", "fn_log10", "Returns the common logarithm (base-10 logarithm) of x."},
    {"pow", "fn_pow", "Returns x raised to the power of y."},
    {"sqrt", "fn_sqrt", "Returns the square root of x."},
    {"ceil", "fn_ceil", "Returns the smallest integer value greater than or equal to x."},
    {"fabs", "fn_fabs", "Returns the absolute value of x."},
    {"floor", "fn_floor", "Returns the largest integer value less than or equal to x."},
    {NULL, NULL, NULL},

    /* NOT IMPLEMENTED YET See below */
    {"fmod", "fn_fmod", "Returns the remainder of x divided by y."},
    {"frexp", "fn_frexp", "The returned value is the mantissa and the integer pointed to by exponent is the exponent. The resultant value is x = mantissa * 2 ^ exponent."},
    {"ldexp", "fn_ldexp", "Returns x multiplied by 2 raised to the power of exponent."},
    {"modf", "fn_modf", "The returned value is the fraction component (part after the decimal), and sets integer to the integer component."}
};

/* TODO: Implement multiple return or need to manage type */

/* frexp(double x, int *exponent)
fe_Object *fn_frexp(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, frexp(x));
}
*/
/* ldexp(double x, int exponent)
    fe_Object *fn_ldexp(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, ldexp(x));
}
*/
/* modf(double x, double *integer)
    fe_Object *fn_modf(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, modf(x));
}
*/

/* acos(double x) */
fe_Object *fn_acos(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, acos(x));
}
/* asin(double x) */
fe_Object *fn_asin(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, asin(x));
}
/* atan(double x) */
fe_Object *fn_atan(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, atan(x));
}
/* atan2(double y, double x) */
fe_Object *fn_atan2(fe_Context *ctx, fe_Object *arg)
{
  float y = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, atan2(y, x));
}
/* ceil(double x) */
fe_Object *fn_ceil(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, ceil(x));
}
/* cos(double x) */
fe_Object *fn_cos(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, cos(x));
}
/* cosh(double x) */
fe_Object *fn_cosh(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, cosh(x));
}
/* exp(double x) */
fe_Object *fn_exp(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, exp(x));
}
/* fabs(double x) */
fe_Object *fn_fabs(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, fabs(x));
}
/* floor(double x) */
fe_Object *fn_floor(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, floor(x));
}
/* fmod(double x, double y) */
fe_Object *fn_fmod(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  float y = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, fmod(x, y));
}
/* log(double x) */
fe_Object *fn_log(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, log(x));
}
/* log10(double x) */
fe_Object *fn_log10(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, log10(x));
}
/* pow(double x, double y) */
fe_Object *fn_pow(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  float y = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, pow(x, y));
}
/* sin(double x) */
fe_Object *fn_sin(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, sin(x));
}
/* sinh(double x) */
fe_Object *fn_sinh(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, sinh(x));
}
/* sqrt(double x) */
fe_Object *fn_sqrt(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, sqrt(x));
}
/* tanh(double x) */
fe_Object *fn_tanh(fe_Context *ctx, fe_Object *arg)
{
  float x = fe_tonumber(ctx, fe_nextarg(ctx, &arg));
  return fe_number(ctx, tanh(x));
}
