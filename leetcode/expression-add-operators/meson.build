project(
  'main',
  'cpp',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++23'],
)

dependencies = [
]

sources = [
  'main.cpp',
]

exe = executable(
  'main',
  sources,
  install : true,
  dependencies : dependencies,
)

test('basic', exe)
