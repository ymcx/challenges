project('main', 'c')
cc = meson.get_compiler('c')
math = cc.find_library('m')
executable('main', ['main.c'], dependencies: math)
