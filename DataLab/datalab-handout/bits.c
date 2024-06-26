/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int one_only_in_x = x & (~y);
  int one_only_in_y = y & (~x);
  return ~((~one_only_in_x) & (~one_only_in_y));
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) { return 1 << 31; }
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) { return !(x ^ 0x7fffffff); }
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int mask = 0xAAAAAAAA;
  int mask_in_x = x & mask;
  return !(mask_in_x ^ mask);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { return ~x + 1; }
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int prefix_mask = 0x3;
  int prefix_flag = (x >> 4) ^ prefix_mask; // need prefix_flag == 0
  int suffix_mask1 = 0xa;
  int suffix_mask2 = 0xc;
  int suffix_flag = !(x & suffix_mask1 ^ suffix_mask1) |
                    !(x & suffix_mask2 ^ suffix_mask2); // need suffix_flag == 0
  return !(prefix_flag | suffix_flag);
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int x_all_zero = !(x ^ 0);
  int mask = (x_all_zero << 31) >> 31;
  int res1 = (mask & z);
  int res2 = (~mask & y);
  return (res1 ^ res2);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // sign bit, if x < 0, x_sign = 1, else x_sign = 0
  int x_sign = (x >> 31) & 1;
  int y_sign = (y >> 31) & 1;
  // if sign same, compare x and y
  int sign_same = !(x_sign ^ y_sign); // if sign same, sign_same = 1

  /**
   * general we use  x+(~y+1) to present x-y, however, in that case,
   * when x = y, x_less_y would be 0, makes judgement complicated;
   * so, here we use x+(~y), which equals x - y -1
   * when y > x, x_less_y = 1, when y = x, x_less_y = 1, when y < x,
   * x_less_y !=1 this makes judgement simple
   */
  int x_less_y = (x + (~y)) >> 31; // if x <= y, x_less_y = 1

  int flag1 = sign_same & x_less_y;

  // if sign not same, if x < 0, then x < y, else x > y
  int flag2 = (!sign_same) &
              (x_sign & (!y_sign)); // if sign not same and x < 0, flag2 = 1

  return flag1 | flag2;
  //   return ret;
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  // if x != 0, then ~(-x) and ~x are start with 1
  int neg = ~(~x + 1);
  int flag = neg & (~x);
  return flag >> 31 & 0x01;
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int sign, bit16, bit8, bit4, bit2, bit1;
  sign = x >> 31;
  // -5 1011

  x = (sign & ~x) | (~sign & x);

  bit16 = !!(x >> 16) << 4;
  x = x >> bit16;
  bit8 = !!(x >> 8) << 3;
  x = x >> bit8;
  bit4 = !!(x >> 4) << 2;
  x = x >> bit4;
  bit2 = !!(x >> 2) << 1;
  x = x >> bit2;
  bit1 = !!(x >> 1);
  x = x >> bit1;

  return bit16 + bit8 + bit4 + bit2 + bit1 + x + 1;
}
// float
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  unsigned sign = uf & 0x80000000; // 1000 ...
  unsigned exp = uf & 0x7f800000;  // 0111 1111 1000 0...
  unsigned frac = uf & 0x007fffff; // 0000 0000 0111 1111...

  // if exp = 0, uf is denormalized
  if (exp == 0) {
    return frac << 1 | sign;
  }

  // if exp = 0x7f800000, uf is NaN or infinity, return uf
  if (exp == 0x7f800000) {
    return uf;
  }

  // twice
  exp = ((exp >> 23) + 1) << 23;

  // if exp = 0x7f800000 res is infinity
  if (exp == 0x7f800000) {
    return exp | sign;
  }

  return sign | exp | frac;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  /**
   * 1. decide sign bit
   * 2. decide exp
   * 3. decide frac
   */
  if (x == 0) {
    return 0;
  }

  int sign, exp, frac;
  int bias = 127;

  // decide sign bit
  if (x < 0) {
    sign = 0x80000000;
    frac = (~x) + 1;
  } else {
    sign = 0x00000000;
    frac = x;
  }

  // decide exp
  int digit = 0;
  for (unsigned i = frac; i > 0; i = i >> 1) {
    digit++;
  }
  digit -= 1;
  exp = digit + bias;

  // decide frac
  frac = frac & (~(1 << digit)); // ignore first bit which is 1

  if (digit <= 23) {
    frac = frac << (23 - digit);
  } else {
    int bit_count = 0;
    while (digit > 24) {
      if (frac & 0x01) {
        bit_count++;
      }
      frac = frac >> 1;
      digit--;
    }

    unsigned next_bit_value = frac & 0x01;
    frac = frac >> 1;
    if (next_bit_value) {
      if (bit_count > 0) {
        // bigger than median value, round to upper
        frac += 1;
      } else if (frac & 0x01) {
        // equal to median value and LSB is odd, round to even
        frac += 1;
      }
    }

    if (frac >> 23) {
      exp += 1;
      frac = frac & 0x7fffff;
    }
  }
  return sign | (exp << 23) | frac;
}

/*
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  int sign, exp, frac;
  sign = uf & 0x80000000;
  exp = (uf & 0x7f800000) >> 23;
  frac = uf & 0x007fffff;

  int E = exp - 127;

  if (exp == 0) {
    return 0;
  }

  if (exp == 255) {
    if (frac & (~0x0)) {
      return 0;
    }
    if (sign) {
      return 0x80000000;
    } else {
      return 0x7fffffff;
    }
  }

  if (E > 32) {
    if (sign) {
      return 0x80000000;
    } else {
      return 0x7fffffff;
    }
  }

  if (E < 0) {
    return 0;
  }
  unsigned M = frac | (1 << 23); // 1 + frac

  int V = (E > 23 ? M << (E - 23) : M >> (23 - E));

  if (sign) {
    V *= -1;
  }

  return V;
}
