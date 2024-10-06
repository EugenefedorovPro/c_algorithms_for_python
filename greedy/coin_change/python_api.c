#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>

#include "declarations.h"

// Python binding for the coin_change function
static PyObject *py_coin_change(PyObject *self, PyObject *args) {
  PyObject *coins_list;
  int amount;

  // Parse Python arguments: O for a list, i for an integer
  if (!PyArg_ParseTuple(args, "Oi", &coins_list, &amount)) {
    fprintf(stderr, "Error: Args are not parsed\n");
    return NULL;
  }

  // Convert Python list to C array
  Py_ssize_t size = PyList_Size(coins_list); // Use Py_ssize_t for sizes
  int *coins = malloc(sizeof(int) * size);   // Allocate memory for coins array
  if (coins == NULL) {
    return PyErr_NoMemory(); // Return Python memory error
  }

  for (Py_ssize_t i = 0; i < size; i++) {
    PyObject *item = PyList_GetItem(coins_list, i);
    if (!PyLong_Check(item)) {
      free(coins); // Free allocated memory before returning
      PyErr_SetString(PyExc_TypeError, "List elements must be integers");
      return NULL;
    }
    coins[i] = (int)PyLong_AsLong(item); // Convert Python long to C int
  }

  // Call the C coin_change function
  int *result = coin_change(coins, (size_t)size, amount);
  free(coins); // Free the coins array

  if (result == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "coin_change function failed");
    return NULL;
  }

  // Create a Python list from the result array
  PyObject *result_list = PyList_New(0); // Create an empty Python list
  for (int i = 0; result[i] != 0; i++) { // Assuming result is zero-terminated
    PyList_Append(result_list, PyLong_FromLong(result[i]));
  }
  free(result); // Free the result array

  return result_list; // Return result list to Python
}

// Method table
static PyMethodDef CoinChangeMethods[] = {
    {"coin_change", py_coin_change, METH_VARARGS, "Calculate coin change"},
    {NULL, NULL, 0, NULL}, // Sentinel
};

// Module definition
static struct PyModuleDef coinchangemodule = {
    PyModuleDef_HEAD_INIT, "coin_change", NULL, -1, CoinChangeMethods};

// Initialization function for the module
PyMODINIT_FUNC PyInit_coin_change(void) {
  return PyModule_Create(&coinchangemodule);
}
