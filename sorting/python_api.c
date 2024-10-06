#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>
#include "declarations.h"

static PyObject *py_factory(PyObject *self, PyObject *args) {
  const char *name_sort_alg;
  PyObject *input_list;

  // Parse input arguments
  if (!PyArg_ParseTuple(args, "sO", &name_sort_alg, &input_list)) {
    PyErr_SetString(PyExc_TypeError,
                    "Invalid args: expected a string and a list");
    return NULL;
  }

  size_t size = PyList_Size(input_list);
  if (size == 0) {
    PyErr_SetString(PyExc_ValueError, "List cannot be empty");
    return NULL;
  }

  // Allocate memory for the input array
  int *arr = malloc(sizeof(int) * size);
  if (arr == NULL) {
    PyErr_SetString(PyExc_MemoryError,
                    "Memory allocation failed for the input_list");
    return NULL;
  }

  // Populate the array from the Python list
  for (size_t i = 0; i < size; i++) {
    PyObject *item = PyList_GetItem(input_list, i);
    arr[i] = (int)PyLong_AsLong(item);
    if (PyErr_Occurred()) {
      free(arr);
      return NULL;
    }
  }

  // Call the sorting function
  int *sorted_arr = factory((char *)name_sort_alg, arr, size);
  /* free(arr); // Free the original array after sorting */ // does not work: double free error
  if (sorted_arr == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "Sorting function failed");
    return NULL;
  }

  // Create a new Python list for the sorted results
  PyObject *result_list = PyList_New(size);
  if (result_list == NULL) {
    free(sorted_arr); // Free sorted array on failure
    PyErr_SetString(PyExc_MemoryError,
                    "Memory allocation failed for result_list");
    return NULL;
  }

  // Populate the result list with sorted items
  for (size_t i = 0; i < size; i++) {
    PyObject *sorted_item = PyLong_FromLong(sorted_arr[i]);
    if (sorted_item == NULL) {
      Py_DECREF(result_list); // Properly decrement reference count on error
      free(sorted_arr);
      return NULL;
    }
    // PyList_SetItem steals the reference, so no need for Py_DECREF
    PyList_SetItem(result_list, i, sorted_item);
  }

  free(sorted_arr);   // Free the sorted array after use
  return result_list; // Return the populated result list
}

static PyMethodDef FactoryMethods[] = {
    {"factory", py_factory, METH_VARARGS,
     "Factory to sort array by different methods"},
    {NULL, NULL, 0, NULL},
};

static struct PyModuleDef factorymodule = {
    PyModuleDef_HEAD_INIT,
    "factory",
    "Factory to sort array by different methods",
    -1,
    FactoryMethods,
};

PyMODINIT_FUNC PyInit_factory(void) {
    return PyModule_Create(&factorymodule);
}
