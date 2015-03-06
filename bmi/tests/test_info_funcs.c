#include <glib.h>

#include "bmi.h"


void test_info_funcs(BMI_Model * model);


static void
test_get_component_name(gconstpointer data)
{
  BMI_Model * model = (BMI_Model*) data;
  char name[2048];

  g_assert_nonnull(model->get_component_name);
  g_assert_cmpint(model->get_component_name(model->self, name), ==, BMI_SUCCESS);
  g_assert_cmpstr(name, !=, "");
}


void
test_info_funcs(BMI_Model * model)
{
  g_test_add_data_func("/info/component_name", model, &test_get_component_name);
}
