/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

//Provides: flow_shortest_string_of_float const
//Requires: caml_js_from_float, caml_string_of_jsbytes
function flow_shortest_string_of_float(num) {
  // TODO: shorten string (drop +, leading 0, shift ., etc)
  return caml_string_of_jsbytes(caml_js_from_float(num).toString());
}

//Provides: flow_ecma_string_of_float const
//Requires: caml_js_from_float, caml_string_of_jsbytes
function flow_ecma_string_of_float(num) {
  return caml_string_of_jsbytes(caml_js_from_float(num).toString());
}

//Provides: flow_g_fmt const
//Requires: caml_js_from_float, caml_string_of_jsbytes
function flow_g_fmt(num) {
  // TODO: shorten string
  return caml_string_of_jsbytes(caml_js_from_float(num).toString());
}
