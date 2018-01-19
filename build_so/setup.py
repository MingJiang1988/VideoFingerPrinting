from distutils.core import setup, Extension

module_hello = Extension('compare_videos',["interface.cpp"], libraries=['boost_python'])
setup(name='compare_videos',	version = '0.1', description = 'This is test of Boost.Python', ext_modules = [module_hello])
