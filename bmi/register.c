#include <stdlib.h>

#include <glib.h>
#include <gmodule.h>

#include "bmilib.h"


typedef BMI_Model * (* RegisterBmiFunc) (BMI_Model * model);


BMI_Model *
register_bmi_model (const char * file, const char * func)
{
  BMI_Model * model = (BMI_Model*)malloc(sizeof(BMI_Model));
  RegisterBmiFunc register_bmi;
  GModule * module;

  module = g_module_open(file, G_MODULE_BIND_LAZY);
  if (!module)
    return NULL;

  g_module_make_resident(module);

  if (!g_module_symbol(module, func, (gpointer*)&register_bmi))
    return NULL;

  if (!register_bmi)
    return NULL;

  if (!g_module_close(module))
    return NULL;

  register_bmi(model);

  return model;
}
