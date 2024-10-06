#include <Python.h>

int multiply(const int a, const int b) {
    int result = a * b;
    return result;
}

static PyMethodDef multiply_methods[] = {
    {"multiply", (PyCFunction)multiply, METH_VARARGS, "Multiply two integers."},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC PyInit_multiply_module(void) {
    return PyModule_Create(&multiply_module);
}
