from setuptools import setup, Extension

module = Extension('rename', sources=['rename.c', 'python_api.c'])

setup(
    name='rename',
    version='0.1',
    description='doc description',
    ext_modules=[module],
)

