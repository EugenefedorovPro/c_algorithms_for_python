from setuptools import setup, Extension

module = Extension('lcs', sources=['lcs.c', 'python_api.c'])

setup(
    name='lcs',
    version='0.1',
    description='dynamic programming on longest common subsequence recursion',
    ext_modules=[module],
)

