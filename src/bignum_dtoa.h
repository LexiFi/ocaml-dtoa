/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * Copyright (c) 2010, the V8 project authors.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef OCAML_DTOA_BIGNUM_DTOA_H_
#define OCAML_DTOA_BIGNUM_DTOA_H_

#include "utils.h"

typedef enum {
  // Return the shortest correct representation.
  // For example the output of 0.299999999999999988897 is (the less accurate but
  // correct) 0.3.
  BIGNUM_DTOA_SHORTEST,
  // Same as BIGNUM_DTOA_SHORTEST but for single-precision floats.
  BIGNUM_DTOA_SHORTEST_SINGLE,
  // Return a fixed number of digits after the decimal point.
  // For instance fixed(0.1, 4) becomes 0.1000
  // If the input number is big, the output will be big.
  BIGNUM_DTOA_FIXED,
  // Return a fixed number of digits, no matter what the exponent is.
  BIGNUM_DTOA_PRECISION
} BignumDtoaMode;

// Converts the given double 'v' to ascii.
// The result should be interpreted as buffer * 10^(point-length).
// The buffer will be null-terminated.
//
// The input v must be > 0 and different from NaN, and Infinity.
//
// The output depends on the given mode:
//  - SHORTEST: produce the least amount of digits for which the internal
//   identity requirement is still satisfied. If the digits are printed
//   (together with the correct exponent) then reading this number will give
//   'v' again. The buffer will choose the representation that is closest to
//   'v'. If there are two at the same distance, than the number is round up.
//   In this mode the 'requested_digits' parameter is ignored.
//  - FIXED: produces digits necessary to print a given number with
//   'requested_digits' digits after the decimal point. The produced digits
//   might be too short in which case the caller has to fill the gaps with '0's.
//   Example: toFixed(0.001, 5) is allowed to return buffer="1", point=-2.
//   Halfway cases are rounded up. The call toFixed(0.15, 2) thus returns
//     buffer="2", point=0.
//   Note: the length of the returned buffer has no meaning wrt the significance
//   of its digits. That is, just because it contains '0's does not mean that
//   any other digit would not satisfy the internal identity requirement.
//  - PRECISION: produces 'requested_digits' where the first digit is not '0'.
//   Even though the length of produced digits usually equals
//   'requested_digits', the function is allowed to return fewer digits, in
//   which case the caller has to fill the missing digits with '0's.
//   Halfway cases are again rounded up.
// 'bignum_dtoa' expects the given buffer to be big enough to hold all digits
// and a terminating null-character.
void bignum_dtoa(
  double v,
  BignumDtoaMode mode,
  int requested_digits,
  char* buffer,
  int* length,
  int* decimal_point
);

#endif  // OCAML_DTOA_BIGNUM_DTOA_H_
