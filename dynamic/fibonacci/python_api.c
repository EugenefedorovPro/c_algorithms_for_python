#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>

#include "declarations.h"

static PyObject *py_fibonacci(PyObject *self, PyObject *args) {
  int number_to_fib;

  if (!PyArg_ParseTuple(args, "i", &number_to_fib)) {
    fprintf(stderr, "Error: number_to_fib failed to parse");
    return NULL;
  }

  int result = fibonacci(number_to_fib);

  return PyLong_FromLong(result);
}


static PyMethodDef FibonacciMethods[] = {
  {"fibonacci", py_fibonacci, METH_VARARGS, "calculating fibonacci with cache"}, 
  {NULL, NULL, 0, NULL},
};

static struct PyModuleDef fibonaccimodule = {
  PyModuleDef_HEAD_INIT, 
  "fibonacci",
  NULL,
  -1,
  FibonacciMethods,
};

PyMODINIT_FUNC PyInit_fibonacci(void) {
  return PyModule_Create(&fibonaccimodule);
};
