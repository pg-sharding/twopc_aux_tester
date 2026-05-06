# contrib/2pc_aux_tester_callback/meson.build

2pc_aux_tester_callback_sources = files(
  '2pc_aux_tester_callback.c',
)

2pc_aux_tester_callback = shared_module('2pc_aux_tester_callback',
  2pc_aux_tester_callback_sources,
  kwargs: contrib_mod_args,
)

contrib_targets += 2pc_aux_tester_callback

install_data(
  '2pc_aux_tester_callback.control',
  '2pc_aux_tester_callback--1.0.sql',
  kwargs: contrib_data_args,
)

tests += {
  'name': '2pc_aux_tester_callback',
  'sd': meson.current_source_dir(),
  'bd': meson.current_build_dir(),
  'regress': {
    'sql': [
      '2pc_aux_tester_callback',
    ],
  },
}

