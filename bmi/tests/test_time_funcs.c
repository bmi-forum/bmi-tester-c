#include <glib.h>

#include "bmi.h"


void test_time_funcs(BMI_Model * model);


static void
test_get_start_time(gconstpointer data)
{
  BMI_Model * model = (BMI_Model *)data;
  double time;

  g_assert_nonnull(model->get_start_time);
  g_assert_cmpint(model->get_start_time(model->self, &time), ==, BMI_SUCCESS);
  g_assert_cmpfloat(time, ==, 0.);
}


static void
test_get_end_time(gconstpointer data)
{
  BMI_Model * model = (BMI_Model *)data;
  double time;

  g_assert_nonnull(model->get_end_time);
  g_assert_cmpint(model->get_end_time(model->self, &time), ==, BMI_SUCCESS);
}


static void
test_get_current_time(gconstpointer data)
{
  BMI_Model * model = (BMI_Model *)data;
  double time;

  g_assert_nonnull(model->get_current_time);
  g_assert_cmpint(model->get_current_time(model->self, &time), ==, BMI_SUCCESS);
}


static void
test_get_time_step(gconstpointer data)
{
  BMI_Model * model = (BMI_Model *)data;
  double dt;

  g_assert_nonnull(model->get_time_step);
  g_assert_cmpint(model->get_time_step(model->self, &dt), ==, BMI_SUCCESS);
}


static void
test_get_time_units(gconstpointer data)
{
  BMI_Model * model = (BMI_Model *)data;
  char units[2048];

  g_assert_nonnull(model->get_time_units);
  g_assert_cmpint(model->get_time_units(model->self, units), ==, BMI_SUCCESS);
  g_assert_cmpstr(units, !=, "");
}


void
test_time_funcs(BMI_Model * model)
{
  g_test_add_data_func("/time/start", model, &test_get_start_time);
  g_test_add_data_func("/time/end", model, &test_get_end_time);
  g_test_add_data_func("/time/current", model, &test_get_current_time);
  g_test_add_data_func("/time/dt", model, &test_get_time_step);
  g_test_add_data_func("/time/units", model, &test_get_time_units);
}
