#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"

// Cleanup function for PyCapsule
static void capsule_cleanup(PyObject *capsule) {
    Node **root = (Node **)PyCapsule_GetPointer(capsule, "RBT");
    if (root) {
        free_tree(*root); // Free the tree nodes
        free(root);       // Free the root pointer
    }
}

// Python wrapper for creating a tree
static PyObject* py_create_tree(PyObject* self, PyObject* args) {
    Node **root = (Node **)malloc(sizeof(Node *));
    if (!root) {
        PyErr_NoMemory();
        return NULL;
    }

    *root = NULL; // Initialize the root as NULL

    PyObject *capsule = PyCapsule_New(root, "RBT", capsule_cleanup);
    if (!capsule) {
        free(root); // Free memory if capsule creation fails
        PyErr_SetString(PyExc_RuntimeError, "Failed to create capsule.");
        return NULL;
    }

    return capsule;
}

// Python wrapper for inserting into the tree
static PyObject* py_insert_rbt(PyObject* self, PyObject* args) {
    PyObject *capsule;
    int key;
    const char *value;

    if (!PyArg_ParseTuple(args, "Ois", &capsule, &key, &value)) {
        return NULL; // Error parsing arguments
    }

    Node **root = (Node **)PyCapsule_GetPointer(capsule, "RBT");
    if (!root) {
        PyErr_SetString(PyExc_ValueError, "Invalid Red-Black Tree capsule.");
        return NULL;
    }

    insert_rbt(root, key, (char *)value);
    Py_RETURN_NONE;
}

// Python wrapper for removing from the tree
static PyObject* py_remove_rbt(PyObject* self, PyObject* args) {
    PyObject *capsule;
    int key;

    if (!PyArg_ParseTuple(args, "Oi", &capsule, &key)) {
        return NULL; // Error parsing arguments
    }

    Node **root = (Node **)PyCapsule_GetPointer(capsule, "RBT");
    if (!root) {
        PyErr_SetString(PyExc_ValueError, "Invalid Red-Black Tree capsule.");
        return NULL;
    }

    remove_rbt(root, key);
    Py_RETURN_NONE;
}

// Python wrapper for traversing the tree in level order
static PyObject* py_traverse_level_order(PyObject* self, PyObject* args) {
    PyObject *capsule;

    if (!PyArg_ParseTuple(args, "O", &capsule)) {
        return NULL; // Error parsing arguments
    }

    Node **root = (Node **)PyCapsule_GetPointer(capsule, "RBT");
    if (!root) {
        PyErr_SetString(PyExc_ValueError, "Invalid Red-Black Tree capsule.");
        return NULL;
    }

    printf("Level order traversal: ");
    traverse_level_order(*root);
    printf("\n");

    Py_RETURN_NONE;
}

// Python wrapper for searching in the tree
static PyObject* py_search_rbt(PyObject* self, PyObject* args) {
    PyObject *capsule;
    int key;

    if (!PyArg_ParseTuple(args, "Oi", &capsule, &key)) {
        return NULL; // Error parsing arguments
    }

    Node **root = (Node **)PyCapsule_GetPointer(capsule, "RBT");
    if (!root) {
        PyErr_SetString(PyExc_ValueError, "Invalid Red-Black Tree capsule.");
        return NULL;
    }

    char *result = search_rbt(*root, key);
    if (result) {
        return Py_BuildValue("s", result);
    } else {
        Py_RETURN_NONE;
    }
}

// Define methods in the module
static PyMethodDef TreeMethods[] = {
    {"create_tree", py_create_tree, METH_NOARGS, "Create a new Red-Black Tree capsule."},
    {"insert_rbt", py_insert_rbt, METH_VARARGS, "Insert a node into the Red-Black Tree.\nArgs: capsule, key (int), value (str)"},
    {"remove_rbt", py_remove_rbt, METH_VARARGS, "Remove a node from the Red-Black Tree.\nArgs: capsule, key (int)"},
    {"traverse_level_order", py_traverse_level_order, METH_VARARGS, "Traverse the Red-Black Tree in level order.\nArgs: capsule"},
    {"search_rbt", py_search_rbt, METH_VARARGS, "Search for a key in the Red-Black Tree.\nArgs: capsule, key (int)"},
    {NULL, NULL, 0, NULL} // Sentinel
};

// Module definition
static struct PyModuleDef treemodule = {
    PyModuleDef_HEAD_INIT,
    "tree_module",
    NULL,
    -1,
    TreeMethods
};

// Module initialization function
PyMODINIT_FUNC PyInit_tree_module(void) {
    return PyModule_Create(&treemodule);
}
