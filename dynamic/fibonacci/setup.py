from setuptools import setup, Extension

module = Extension('fibonacci', sources=['fibonacci.c', 'python_api.c'])

setup(
    name='fibonacci',
    version='0.1',
    description='dynamic programming on fibonacci recursion',
    ext_modules=[module],
)

