project('main', 'c')
add_project_arguments(
  '-fsanitize=address,undefined',
  '-fno-omit-frame-pointer',
  '-g',
  language: 'c'
)

add_project_link_arguments(
  '-fsanitize=address,undefined',
  language: 'c'
)

executable('main', ['main.c'])
