/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
<<<<<<< HEAD
  Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
  Copyright (C) 2008-2015 Marco Costalba, Joona Kiiski, Tord Romstad
  Copyright (C) 2015-2018 Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad
=======
  Copyright (C) 2004-2020 The Stockfish developers (see AUTHORS file)
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef EVALUATE_H_INCLUDED
#define EVALUATE_H_INCLUDED

#include <atomic>
#include <string>

#include "types.h"

class Position;

namespace Eval {

<<<<<<< HEAD
constexpr Value Tempo[VARIANT_NB] = { // Must be visible to search
  Value(20),
#ifdef ANTI
  Value(20),
#endif
#ifdef ATOMIC
  Value(20),
#endif
#ifdef CRAZYHOUSE
  Value(100),
#endif
#ifdef EXTINCTION
  Value(20),
#endif
#ifdef GRID
  Value(20),
#endif
#ifdef HORDE
  Value(20),
#endif
#ifdef KOTH
  Value(20),
#endif
#ifdef LOSERS
  Value(20),
#endif
#ifdef RACE
  Value(100),
#endif
#ifdef THREECHECK
  Value(20),
#endif
#ifdef TWOKINGS
  Value(20),
#endif
};
=======
  std::string trace(const Position& pos);
  Value evaluate(const Position& pos);

#ifdef USE_NNUE
  extern bool useNNUE;
  extern std::string eval_file_loaded;
  void init_NNUE();
  void verify_NNUE();

  // The default net name MUST follow the format nn-[SHA256 first 12 digits].nnue
  // for the build process (profile-build and fishtest) to work. Do not change the
  // name of the macro, as it is used in the Makefile.
  #define EvalFileDefaultName   "nn-82215d0fd0df.nnue"
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1

  namespace NNUE {

    Value evaluate(const Position& pos);
    Value compute_eval(const Position& pos);
    void  update_eval(const Position& pos);
    bool  load_eval(std::string streamName, std::istream& stream);

  } // namespace NNUE
#endif

<<<<<<< HEAD
Value evaluate(const Position& pos);
}
=======
} // namespace Eval
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1

#endif // #ifndef EVALUATE_H_INCLUDED
