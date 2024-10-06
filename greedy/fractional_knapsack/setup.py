from setuptools import setup, Extension

module = Extension('f_knapsack', sources=['f_knapsack.c', 'python_api.c'])

setup(
    name='f_knapsack',
    version='0.1',
    description='fractional knapsack problem in dynamic programming and recursion',
    ext_modules=[module],
)

