# contrib/twopc_aux_tester_callback/meson.build

twopc_aux_tester_callback_sources = files(
  'twopc_aux_tester_callback.c',
)

twopc_aux_tester_callback = shared_module('twopc_aux_tester_callback',
  twopc_aux_tester_callback_sources,
  kwargs: contrib_mod_args,
)

contrib_targets += twopc_aux_tester_callback

install_data(
  'twopc_aux_tester_callback.control',
  'twopc_aux_tester_callback--1.0.sql',
  kwargs: contrib_data_args,
)

tests += {
  'name': 'twopc_aux_tester_callback',
  'sd': meson.current_source_dir(),
  'bd': meson.current_build_dir(),
  'regress': {
    'sql': [
      'twopc_aux_tester_callback',
    ],
  },
}

