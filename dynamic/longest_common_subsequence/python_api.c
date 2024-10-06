#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>

#include "declarations.h"

static PyObject *py_lcs(PyObject *self, PyObject *args) {
  const char *str1;
  const char *str2;

  if (!(PyArg_ParseTuple(args, "ss", &str1, &str2))) {
    fprintf(stderr, "ERROR: args are not parsed");
    return NULL;
  }

  size_t size1 = strlen(str1);
  size_t size2 = strlen(str2);

  int result = lcs((char *)str1, size1, (char *)str2, size2);

  return PyLong_FromLong(result);
}

static PyMethodDef LcsMethods[] = {
    {
        "lcs",
        py_lcs,
        METH_VARARGS,
        "find the longest common subsequence by dynamic programming",
    },
    {NULL, NULL, 0, NULL},
};

static struct PyModuleDef lcsmodule = {
    PyModuleDef_HEAD_INIT,
    "lcs",
    "find the longest common subsequence by dynamic programming",
    -1,
    LcsMethods,
};

PyMODINIT_FUNC PyInit_lcs(void) {
  return PyModule_Create(&lcsmodule);
}
