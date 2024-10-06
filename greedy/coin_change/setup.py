from setuptools import setup, Extension

module = Extension('coin_change', sources=['coin_change.c', 'merge_sort.c', 'python_api.c'])

setup(
    name='coin_change',
    version='0.1',
    description='Coin change problem solver',
    ext_modules=[module],
)

