/*********************                                                        */
/*! \file cvc4.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Morgan Deters, Tim King, Paul Meng
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2017 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief Main header file for CVC4 library functionality
 **
 ** Main header file for CVC4 library functionality.  Includes the
 ** most-commonly used CVC4 public-facing class interfaces.
 **/

#ifndef __CVC4__CVC4_H
#define __CVC4__CVC4_H

// added to CVC4 source tree due to gcc compatibility bug
// see https://gcc.gnu.org/gcc-4.9/porting_to.html
// under heading "Header <cstddef> changes"
#include <cstddef>

#include <cvc4/base/configuration.h>
#include <cvc4/base/exception.h>
#include <cvc4/expr/datatype.h>
#include <cvc4/expr/expr.h>
#include <cvc4/expr/expr_manager.h>
#include <cvc4/options/options.h>
#include <cvc4/parser/parser.h>
#include <cvc4/parser/parser_builder.h>
#include <cvc4/smt/command.h>
#include <cvc4/smt/smt_engine.h>
#include <cvc4/util/integer.h>
#include <cvc4/util/rational.h>

#endif /* __CVC4__CVC4_H */
