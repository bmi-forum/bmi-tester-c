#include <stdio.h>
#include <stdlib.h>

#include <glib.h>
#include <glib/gstdio.h>

#include "bmilib.h"


void test_info_funcs(BMI_Model *);
void test_time_funcs(BMI_Model *);


static gchar **
get_args_from_input_file(const char * fname)
{
  gchar **lines = NULL;
  gchar *contents = NULL;
  gchar **line;
  gsize len = 0;

  if (!g_file_get_contents(fname, &contents, &len, NULL))
    return NULL;

  lines = g_strsplit_set(contents, ",\n", -1);
  for (line=lines; *line; line++)
    g_strstrip(*line);

  return lines;
}


int
main(int argc, char *argv[])
{
  BMI_Model * model = NULL;

  g_test_init(&argc, &argv, NULL);

  if (argc == 3) {
    model = register_bmi_model(argv[1], argv[2]);
  } else {
    char **args = get_args_from_input_file("args.txt");

    if (!args) {
      fprintf(stderr, "Unable to read args.txt.\n");
      return EXIT_FAILURE;
    }

    model = register_bmi_model(args[0], args[1]);
    g_strfreev(args);
  }
  
  if (model->initialize(NULL, &(model->self)) == BMI_FAILURE) {
    fprintf(stderr, "Failed to initialize model.\n");
    return EXIT_FAILURE;
  }

  test_info_funcs(model);
  test_time_funcs(model);

  g_test_run();

  return EXIT_SUCCESS;
}
