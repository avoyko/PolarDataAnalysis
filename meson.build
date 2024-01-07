project('proj', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

message('hello, world!')

fit_path = 'fit_lib'
decoder_path = 'src/decoder.cpp'

fit_lib = library(
  'fit_lib', fit_path + '/fit.cpp',
  include_directories: 'fit_lib',
)

decoder = library(
  'decoder', decoder_path,
  include_directories: 'src',
)

proj_exec = executable(
  'proj', 'main.cpp',
  link_with: [fit_lib, decoder],
)

test('IT\'S ALIVE!', proj_exec)
test('IT\'S ALIVE! 2.0', proj_exec)
test('IT\'S ALIVE! 3.0', proj_exec)