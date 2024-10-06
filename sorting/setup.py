from setuptools import setup, Extension

module = Extension(
    'factory',
    sources=[
        './functions/factory.c',
        './functions/bubble.c',
        './functions/insertion.c',
        './functions/merge.c',
        './functions/quick.c',
        './functions/selection.c',
        'python_api.c'
    ]
)

setup(
    name='factory',
    version='0.1',
    description='doc description',
    ext_modules=[module],
)
