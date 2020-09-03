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

#include <algorithm>
#include <cassert>

#include "bitboard.h"
#include "pawns.h"
#include "position.h"
#include "thread.h"

namespace {

  #define V Value
  #define S(mg, eg) make_score(mg, eg)

  // Pawn penalties
<<<<<<< HEAD
  constexpr Score Isolated[VARIANT_NB] = {
    S( 5, 15),
#ifdef ANTI
    S(54, 69),
#endif
#ifdef ATOMIC
    S(24, 14),
#endif
#ifdef CRAZYHOUSE
    S(30, 27),
#endif
#ifdef EXTINCTION
    S(13, 16),
#endif
#ifdef GRID
    S(13, 16),
#endif
#ifdef HORDE
    S(16, 38),
#endif
#ifdef KOTH
    S(30, 27),
#endif
#ifdef LOSERS
    S(53, 69),
=======
  constexpr Score Backward[VARIANT_NB] = {
    S( 8, 27),
#ifdef ANTI
    S(26, 50),
#endif
#ifdef ATOMIC
    S(35, 15),
#endif
#ifdef CRAZYHOUSE
    S(41, 19),
#endif
#ifdef EXTINCTION
    S(17, 11),
#endif
#ifdef GRID
    S(17, 11),
#endif
#ifdef HORDE
    S(78, 14),
#endif
#ifdef KOTH
    S(41, 19),
#endif
#ifdef LOSERS
    S(26, 49),
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
#endif
#ifdef RACE
    S(0, 0),
#endif
#ifdef THREECHECK
<<<<<<< HEAD
    S(30, 27),
#endif
#ifdef TWOKINGS
    S(13, 16),
#endif
  };
  constexpr Score Backward[VARIANT_NB] = {
    S(9, 24),
#ifdef ANTI
    S(26, 50),
#endif
#ifdef ATOMIC
    S(35, 15),
#endif
#ifdef CRAZYHOUSE
    S(41, 19),
#endif
#ifdef EXTINCTION
    S(17, 11),
#endif
#ifdef GRID
    S(17, 11),
#endif
#ifdef HORDE
    S(78, 14),
#endif
#ifdef KOTH
    S(41, 19),
#endif
#ifdef LOSERS
    S(26, 49),
#endif
#ifdef RACE
    S(0, 0),
#endif
#ifdef THREECHECK
    S(41, 19),
#endif
#ifdef TWOKINGS
    S(17, 11),
#endif
  };
  // Doubled pawn penalty
  constexpr Score Doubled[VARIANT_NB] = {
    S(11, 56),
=======
    S(41, 19),
#endif
#ifdef TWOKINGS
    S(17, 11),
#endif
  };
  constexpr Score Doubled[VARIANT_NB] = {
    S(11, 55),
#ifdef ANTI
    S( 4, 51),
#endif
#ifdef ATOMIC
    S( 0,  0),
#endif
#ifdef CRAZYHOUSE
    S(13, 40),
#endif
#ifdef EXTINCTION
    S(13, 40),
#endif
#ifdef GRID
    S(13, 40),
#endif
#ifdef HORDE
    S(11, 83),
#endif
#ifdef KOTH
    S(13, 40),
#endif
#ifdef LOSERS
    S( 4, 54),
#endif
#ifdef RACE
    S( 0,  0),
#endif
#ifdef THREECHECK
    S(13, 40),
#endif
#ifdef TWOKINGS
    S(13, 40),
#endif
  };
  constexpr Score Isolated[VARIANT_NB] = {
    S( 5, 17),
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
#ifdef ANTI
    S(54, 69),
#endif
#ifdef ATOMIC
    S(24, 14),
#endif
#ifdef CRAZYHOUSE
<<<<<<< HEAD
    S(13, 40),
#endif
#ifdef EXTINCTION
    S(13, 40),
#endif
#ifdef GRID
    S(13, 40),
#endif
#ifdef HORDE
    S(11, 83),
#endif
#ifdef KOTH
    S(13, 40),
#endif
#ifdef LOSERS
    S( 4, 54),
#endif
#ifdef RACE
    S( 0,  0),
#endif
#ifdef THREECHECK
    S(13, 40),
#endif
#ifdef TWOKINGS
    S(13, 40),
=======
    S(30, 27),
#endif
#ifdef EXTINCTION
    S(13, 16),
#endif
#ifdef GRID
    S(13, 16),
#endif
#ifdef HORDE
    S(16, 38),
#endif
#ifdef KOTH
    S(30, 27),
#endif
#ifdef LOSERS
    S(53, 69),
#endif
#ifdef RACE
    S(0, 0),
#endif
#ifdef THREECHECK
    S(30, 27),
#endif
#ifdef TWOKINGS
    S(13, 16),
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
#endif
  };
  constexpr Score WeakLever     = S( 2, 54);
  constexpr Score WeakUnopposed = S(15, 25);

<<<<<<< HEAD
  // Connected pawn bonus by opposed, phalanx, #support and rank
  Score Connected[VARIANT_NB][2][2][3][RANK_NB];

=======
  // Bonus for blocked pawns at 5th or 6th rank
  constexpr Score BlockedPawn[2] = { S(-13, -4), S(-4, 3) };

  constexpr Score BlockedStorm[RANK_NB] = {
    S(0, 0), S(0, 0), S(76, 78), S(-10, 15), S(-7, 10), S(-4, 6), S(-1, 2)
  };

  // Connected pawn bonus
  constexpr int Connected[RANK_NB] = { 0, 7, 8, 11, 24, 45, 85 };

>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
  // Strength of pawn shelter for our king by [distance from edge][rank].
  // RANK_1 = 0 is used for files where we have no pawn, or pawn is behind our king.
  constexpr Value ShelterStrength[VARIANT_NB][int(FILE_NB) / 2][RANK_NB] = {
  {
<<<<<<< HEAD
    { V( -3), V(81), V( 93), V( 58), V( 39), V( 18), V(  25) },
    { V(-40), V(61), V( 35), V(-49), V(-29), V(-11), V(-63) },
    { V(-7), V(75), V( 23), V(-2), V( 32), V( 3), V(-45) },
    { V(-36), V(-13), V(-29), V(-52), V(-48), V(-67), V(-166) }
=======
    { V( -6), V( 81), V( 93), V( 58), V( 39), V( 18), V(  25) },
    { V(-43), V( 61), V( 35), V(-49), V(-29), V(-11), V( -63) },
    { V(-10), V( 75), V( 23), V( -2), V( 32), V(  3), V( -45) },
    { V(-39), V(-13), V(-29), V(-52), V(-48), V(-67), V(-166) }
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
  },
#ifdef ANTI
  {},
#endif
#ifdef ATOMIC
  {
    { V( 7), V(76), V(84), V( 38), V( 7), V( 30), V(-19) },
    { V(-3), V(93), V(52), V(-17), V(12), V(-22), V(-35) },
    { V(-6), V(83), V(25), V(-24), V(15), V( 22), V(-39) },
    { V(11), V(83), V(19), V(  8), V(18), V(-21), V(-30) }
  },
#endif
#ifdef CRAZYHOUSE
  {
    { V(-48), V(138), V(80), V( 48), V( 5), V( -7), V(  9) },
    { V(-78), V(116), V(20), V( -2), V(14), V(  6), V(-36) },
    { V(-69), V( 99), V(12), V(-19), V(38), V( 22), V(-50) },
    { V( -6), V( 95), V( 9), V(  4), V(-2), V(  2), V(-37) }
  },
#endif
#ifdef EXTINCTION
  {},
#endif
#ifdef GRID
  {
    { V( 7), V(76), V(84), V( 38), V( 7), V( 30), V(-19) },
    { V(-3), V(93), V(52), V(-17), V(12), V(-22), V(-35) },
    { V(-6), V(83), V(25), V(-24), V(15), V( 22), V(-39) },
    { V(11), V(83), V(19), V(  8), V(18), V(-21), V(-30) }
  },
#endif
#ifdef HORDE
  {
    { V( 7), V(76), V(84), V( 38), V( 7), V( 30), V(-19) },
    { V(-3), V(93), V(52), V(-17), V(12), V(-22), V(-35) },
    { V(-6), V(83), V(25), V(-24), V(15), V( 22), V(-39) },
    { V(11), V(83), V(19), V(  8), V(18), V(-21), V(-30) }
  },
#endif
#ifdef KOTH
  {
    { V( 7), V(76), V(84), V( 38), V( 7), V( 30), V(-19) },
    { V(-3), V(93), V(52), V(-17), V(12), V(-22), V(-35) },
    { V(-6), V(83), V(25), V(-24), V(15), V( 22), V(-39) },
    { V(11), V(83), V(19), V(  8), V(18), V(-21), V(-30) }
  },
#endif
#ifdef LOSERS
  {
    { V( 7), V(76), V(84), V( 38), V( 7), V( 30), V(-19) },
    { V(-3), V(93), V(52), V(-17), V(12), V(-22), V(-35) },
    { V(-6), V(83), V(25), V(-24), V(15), V( 22), V(-39) },
    { V(11), V(83), V(19), V(  8), V(18), V(-21), V(-30) }
  },
#endif
#ifdef RACE
  {}, // There are no pawns in Racing Kings
#endif
#ifdef THREECHECK
  {
    { V( 7), V(76), V(84), V( 38), V( 7), V( 30), V(-19) },
    { V(-3), V(93), V(52), V(-17), V(12), V(-22), V(-35) },
    { V(-6), V(83), V(25), V(-24), V(15), V( 22), V(-39) },
    { V(11), V(83), V(19), V(  8), V(18), V(-21), V(-30) }
  },
#endif
#ifdef TWOKINGS
  {
    { V( 7), V(76), V(84), V( 38), V( 7), V( 30), V(-19) },
    { V(-3), V(93), V(52), V(-17), V(12), V(-22), V(-35) },
    { V(-6), V(83), V(25), V(-24), V(15), V( 22), V(-39) },
    { V(11), V(83), V(19), V(  8), V(18), V(-21), V(-30) }
  },
#endif
  };

  // Danger of enemy pawns moving toward our king by [distance from edge][rank].
  // RANK_1 = 0 is used for files where the enemy has no pawn, or their pawn
<<<<<<< HEAD
  // is behind our king.
  constexpr Value UnblockedStorm[int(FILE_NB) / 2][RANK_NB] = {
    { V(89), V( 107), V( 123), V(93), V(57), V( 45), V( 51) },
    { V(44), V( -18), V(123), V(46), V(39), V(-7), V(  23) },
    { V(4), V( 52), V( 162), V(37), V(7), V(-14), V(-2) },
    { V(-10), V( -14), V( 90), V(15), V( 2), V( -7), V(-16) }
  };

  // Danger of blocked enemy pawns storming our king, by rank
  constexpr Value BlockedStorm[RANK_NB] =
    { V(0), V(0), V( 66), V(6), V(5), V(1), V(15) };

#ifdef HORDE
  constexpr Score ImbalancedHorde = S(49, 39);
#endif

=======
  // is behind our king. Note that UnblockedStorm[0][1-2] accommodate opponent pawn
  // on edge, likely blocked by our king.
  constexpr Value UnblockedStorm[int(FILE_NB) / 2][RANK_NB] = {
    { V( 85), V(-289), V(-166), V(97), V(50), V( 45), V( 50) },
    { V( 46), V( -25), V( 122), V(45), V(37), V(-10), V( 20) },
    { V( -6), V(  51), V( 168), V(34), V(-2), V(-22), V(-14) },
    { V(-15), V( -11), V( 101), V( 4), V(11), V(-15), V(-29) }
  };

#ifdef HORDE
  constexpr Score ImbalancedHorde = S(49, 39);
#endif
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
  #undef S
  #undef V


  /// evaluate() calculates a score for the static pawn structure of the given position.
  /// We cannot use the location of pieces or king in this function, as the evaluation
  /// of the pawn structure will be stored in a small cache for speed reasons, and will
  /// be re-used even when the pieces have moved.

  template<Color Us>
  Score evaluate(const Position& pos, Pawns::Entry* e) {

<<<<<<< HEAD
    constexpr Color     Them = (Us == WHITE ? BLACK : WHITE);
    constexpr Direction Up   = (Us == WHITE ? NORTH : SOUTH);

    Bitboard b, neighbours, stoppers, doubled, supported, phalanx;
    Bitboard lever, leverPush;
=======
    constexpr Color     Them = ~Us;
    constexpr Direction Up   = pawn_push(Us);

    Bitboard neighbours, stoppers, support, phalanx, opposed;
    Bitboard lever, leverPush, blocked;
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
    Square s;
    bool backward, passed, doubled;
    Score score = SCORE_ZERO;
    const Square* pl = pos.squares<PAWN>(Us);

    Bitboard ourPawns   = pos.pieces(  Us, PAWN);
    Bitboard theirPawns = pos.pieces(Them, PAWN);

<<<<<<< HEAD
    e->passedPawns[Us] = e->pawnAttacksSpan[Us] = e->weakUnopposed[Us] = 0;
    e->semiopenFiles[Us] = 0xFF;
    e->kingSquares[Us]   = SQ_NONE;
    e->pawnAttacks[Us]   = pawn_attacks_bb<Us>(ourPawns);
    e->pawnsOnSquares[Us][BLACK] = popcount(ourPawns & DarkSquares);
#ifdef CRAZYHOUSE
    if (pos.is_house())
        e->pawnsOnSquares[Us][WHITE] = popcount(ourPawns & ~DarkSquares);
    else
#endif
    e->pawnsOnSquares[Us][WHITE] = pos.count<PAWN>(Us) - e->pawnsOnSquares[Us][BLACK];
=======
    Bitboard doubleAttackThem = pawn_double_attacks_bb<Them>(theirPawns);

    e->passedPawns[Us] = 0;
    e->kingSquares[Us] = SQ_NONE;
    e->pawnAttacks[Us] = e->pawnAttacksSpan[Us] = pawn_attacks_bb<Us>(ourPawns);
    e->blockedCount += popcount(shift<Up>(ourPawns) & (theirPawns | doubleAttackThem));
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1

#ifdef HORDE
    if (pos.is_horde() && pos.is_horde_color(Us))
    {
<<<<<<< HEAD
        int l = 0, m = 0, r = popcount(ourPawns & FileBB[FILE_A]);
        for (File f1 = FILE_A; f1 <= FILE_H; ++f1)
        {
            l = m; m = r; r = f1 < FILE_H ? popcount(ourPawns & FileBB[f1 + 1]) : 0;
=======
        int l = 0, m = 0, r = popcount(ourPawns & file_bb(FILE_A));
        for (File f1 = FILE_A; f1 <= FILE_H; ++f1)
        {
            l = m; m = r; r = popcount(ourPawns & shift<EAST>(file_bb(f1)));
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
            score -= ImbalancedHorde * m / (1 + l * r);
        }
    }
#endif
<<<<<<< HEAD

=======
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
    // Loop through all pawns of the current color and score each pawn
    while ((s = *pl++) != SQ_NONE)
    {
        assert(pos.piece_on(s) == make_piece(Us, PAWN));

        Rank r = relative_rank(Us, s);

        // Flag the pawn
        opposed    = theirPawns & forward_file_bb(Us, s);
<<<<<<< HEAD
        stoppers   = theirPawns & passed_pawn_mask(Us, s);
        lever      = theirPawns & PawnAttacks[Us][s];
        leverPush  = theirPawns & PawnAttacks[Us][s + Up];
=======
        blocked    = theirPawns & (s + Up);
        stoppers   = theirPawns & passed_pawn_span(Us, s);
        lever      = theirPawns & pawn_attacks_bb(Us, s);
        leverPush  = theirPawns & pawn_attacks_bb(Us, s + Up);
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
#ifdef HORDE
        if (pos.is_horde() && relative_rank(Us, s) == RANK_1)
            doubled = 0;
        else
#endif
        doubled    = ourPawns   & (s - Up);
<<<<<<< HEAD
        neighbours = ourPawns   & adjacent_files_bb(f);
        phalanx    = neighbours & rank_bb(s);
#ifdef HORDE
        if (pos.is_horde() && relative_rank(Us, s) == RANK_1)
            supported = 0;
        else
#endif
        supported  = neighbours & rank_bb(s - Up);

        // A pawn is backward when it is behind all pawns of the same color
        // on the adjacent files and cannot be safely advanced.
        backward =  !(ourPawns & pawn_attack_span(Them, s + Up))
                  && (stoppers & (leverPush | (s + Up)));

        // Passed pawns will be properly scored in evaluation because we need
        // full attack info to evaluate them. Include also not passed pawns
        // which could become passed after one or two pawn pushes when are
        // not attacked more times than defended.
        if (   !(stoppers ^ lever ^ leverPush)
            && !(ourPawns & forward_file_bb(Us, s))
            && popcount(supported) >= popcount(lever) - 1
            && popcount(phalanx)   >= popcount(leverPush))
            e->passedPawns[Us] |= s;

        else if (   stoppers == SquareBB[s + Up]
                 && relative_rank(Us, s) >= RANK_5)
        {
            b = shift<Up>(supported) & ~theirPawns;
            while (b)
                if (!more_than_one(theirPawns & PawnAttacks[Us][pop_lsb(&b)]))
                    e->passedPawns[Us] |= s;
        }

        // Score this pawn
#ifdef HORDE
        if (pos.is_horde() && relative_rank(Us, s) == RANK_1) {} else
#endif
        if (supported | phalanx)
            score += Connected[pos.variant()][opposed][bool(phalanx)][popcount(supported)][relative_rank(Us, s)];

        else if (!neighbours)
            score -= Isolated[pos.variant()], e->weakUnopposed[Us] += !opposed;

        else if (backward)
            score -= Backward[pos.variant()], e->weakUnopposed[Us] += !opposed;

#ifdef HORDE
        if (doubled && (!supported || pos.is_horde()))
#else
        if (doubled && !supported)
#endif
            score -= Doubled[pos.variant()];
=======
        neighbours = ourPawns   & adjacent_files_bb(s);
        phalanx    = neighbours & rank_bb(s);
#ifdef HORDE
        if (pos.is_horde() && relative_rank(Us, s) == RANK_1)
            support = 0;
        else
#endif
        support    = neighbours & rank_bb(s - Up);

        // A pawn is backward when it is behind all pawns of the same color on
        // the adjacent files and cannot safely advance.
        backward =  !(neighbours & forward_ranks_bb(Them, s + Up))
                  && (leverPush | blocked);

        // Compute additional span if pawn is not backward nor blocked
        if (!backward && !blocked)
            e->pawnAttacksSpan[Us] |= pawn_attack_span(Us, s);

        // A pawn is passed if one of the three following conditions is true:
        // (a) there is no stoppers except some levers
        // (b) the only stoppers are the leverPush, but we outnumber them
        // (c) there is only one front stopper which can be levered.
        //     (Refined in Evaluation::passed)
        passed =   !(stoppers ^ lever)
                || (   !(stoppers ^ leverPush)
                    && popcount(phalanx) >= popcount(leverPush))
                || (   stoppers == blocked && r >= RANK_5
                    && (shift<Up>(support) & ~(theirPawns | doubleAttackThem)));

        passed &= !(forward_file_bb(Us, s) & ourPawns);

        // Passed pawns will be properly scored later in evaluation when we have
        // full attack info.
        if (passed)
            e->passedPawns[Us] |= s;

        // Score this pawn
        if (support | phalanx)
        {
            int v =  Connected[r] * (2 + bool(phalanx) - bool(opposed))
                   + 21 * popcount(support);

            score += make_score(v, v * (r - 2) / 4);
        }

        else if (!neighbours)
        {
            if (     opposed
                &&  (ourPawns & forward_file_bb(Them, s))
                && !(theirPawns & adjacent_files_bb(s)))
                score -= Doubled[pos.variant()];
            else
                score -=  Isolated[pos.variant()]
                        + WeakUnopposed * !opposed;
        }

        else if (backward)
            score -=  Backward[pos.variant()]
                    + WeakUnopposed * !opposed;

#ifdef HORDE
        if (!support || pos.is_horde())
#else
        if (!support)
#endif
            score -=  Doubled[pos.variant()] * doubled
                    + WeakLever * more_than_one(lever);

        if (blocked && r > RANK_4)
            score += BlockedPawn[r-4];
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
    }

    return score;
  }

} // namespace

namespace Pawns {

<<<<<<< HEAD
/// Pawns::init() initializes some tables needed by evaluation. Instead of using
/// hard-coded tables, when makes sense, we prefer to calculate them with a formula
/// to reduce independent parameters and to allow easier tuning and better insight.

void init() {

  static constexpr int Seed[VARIANT_NB][RANK_NB] = {
    { 0, 13, 24, 18, 65, 100, 175, 330 },
#ifdef ANTI
    { 0, 8, 19, 13, 71, 94, 169, 324 },
#endif
#ifdef ATOMIC
    { 0,18, 11, 14, 82,109, 170, 315 },
#endif
#ifdef CRAZYHOUSE
    { 0, 8, 19, 13, 71, 94, 169, 324 },
#endif
#ifdef EXTINCTION
    { 0, 13, 24, 18, 65, 100, 175, 330 },
#endif
#ifdef GRID
    { 0, 13, 24, 18, 65, 100, 175, 330 },
#endif
#ifdef HORDE
    { 37, 29, 3, 1, 105,  99, 343, 350 },
#endif
#ifdef KOTH
    { 0, 8, 19, 13, 71, 94, 169, 324 },
#endif
#ifdef LOSERS
    { 0, 8, 20, 11, 69, 91, 183, 310 },
#endif
#ifdef RACE
    {},
#endif
#ifdef THREECHECK
    { 0, 8, 19, 13, 71, 94, 169, 324 },
#endif
#ifdef TWOKINGS
    { 0, 13, 24, 18, 65, 100, 175, 330 },
#endif
  };

  for (Variant var = CHESS_VARIANT; var < VARIANT_NB; ++var)
  for (int opposed = 0; opposed <= 1; ++opposed)
      for (int phalanx = 0; phalanx <= 1; ++phalanx)
          for (int support = 0; support <= 2; ++support)
              for (Rank r = RANK_2; r < RANK_8; ++r)
  {
      int v = 17 * support;
      v += (Seed[var][r] + (phalanx ? (Seed[var][r + 1] - Seed[var][r]) / 2 : 0)) >> opposed;

#ifdef HORDE
      if (var == HORDE_VARIANT)
          Connected[var][opposed][phalanx][support][r] = make_score(v, v);
      else
#endif
      Connected[var][opposed][phalanx][support][r] = make_score(v, v * (r - 2) / 4);
  }
}

=======
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1

/// Pawns::probe() looks up the current position's pawns configuration in
/// the pawns hash table. It returns a pointer to the Entry if the position
/// is found. Otherwise a new Entry is computed and stored there, so we don't
/// have to recompute all when the same pawns configuration occurs again.

Entry* probe(const Position& pos) {

  Key key = pos.pawn_key();
  Entry* e = pos.this_thread()->pawnsTable[key];

  if (e->key == key)
      return e;

  e->key = key;
<<<<<<< HEAD
  e->scores[WHITE] = evaluate<WHITE>(pos, e);
  e->scores[BLACK] = evaluate<BLACK>(pos, e);
  e->openFiles = popcount(e->semiopenFiles[WHITE] & e->semiopenFiles[BLACK]);
  e->asymmetry = popcount(  (e->passedPawns[WHITE]   | e->passedPawns[BLACK])
                          | (e->semiopenFiles[WHITE] ^ e->semiopenFiles[BLACK]));
=======
  e->blockedCount = 0;
  e->scores[WHITE] = evaluate<WHITE>(pos, e);
  e->scores[BLACK] = evaluate<BLACK>(pos, e);
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1

  return e;
}


/// Entry::evaluate_shelter() calculates the shelter bonus and the storm
/// penalty for a king, looking at the king file and the two closest files.

template<Color Us>
<<<<<<< HEAD
Value Entry::evaluate_shelter(const Position& pos, Square ksq) {

  constexpr Color     Them = (Us == WHITE ? BLACK : WHITE);
  constexpr Direction Down = (Us == WHITE ? SOUTH : NORTH);
  constexpr Bitboard  BlockRanks = (Us == WHITE ? Rank1BB | Rank2BB : Rank8BB | Rank7BB);

  Bitboard b = pos.pieces(PAWN) & (forward_ranks_bb(Us, ksq) | rank_bb(ksq));
  Bitboard ourPawns = b & pos.pieces(Us);
  Bitboard theirPawns = b & pos.pieces(Them);

  Value safety = (ourPawns & file_bb(ksq)) ? Value(5) : Value(-5);

  if (shift<Down>(theirPawns) & (FileABB | FileHBB) & BlockRanks & ksq)
      safety += Value(374);

  File center = std::max(FILE_B, std::min(FILE_G, file_of(ksq)));
  for (File f = File(center - 1); f <= File(center + 1); ++f)
  {
      b = ourPawns & file_bb(f);
      int ourRank = b ? relative_rank(Us, backmost_sq(Us, b)) : 0;
=======
Score Entry::evaluate_shelter(const Position& pos, Square ksq) const {

  constexpr Color Them = ~Us;

  Bitboard b = pos.pieces(PAWN) & ~forward_ranks_bb(Them, ksq);
  Bitboard ourPawns = b & pos.pieces(Us) & ~pawnAttacks[Them];
  Bitboard theirPawns = b & pos.pieces(Them);

  Score bonus = make_score(5, 5);

  File center = std::clamp(file_of(ksq), FILE_B, FILE_G);
  for (File f = File(center - 1); f <= File(center + 1); ++f)
  {
      b = ourPawns & file_bb(f);
      int ourRank = b ? relative_rank(Us, frontmost_sq(Them, b)) : 0;
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1

      b = theirPawns & file_bb(f);
      int theirRank = b ? relative_rank(Us, frontmost_sq(Them, b)) : 0;

<<<<<<< HEAD
      int d = std::min(f, ~f);
      safety += ShelterStrength[pos.variant()][d][ourRank];
      safety -= (ourRank && (ourRank == theirRank - 1)) ? BlockedStorm[theirRank]
                                                        : UnblockedStorm[d][theirRank];
=======
      int d = edge_distance(f);
      bonus += make_score(ShelterStrength[pos.variant()][d][ourRank], 0);

      if (ourRank && (ourRank == theirRank - 1))
          bonus -= BlockedStorm[theirRank];
      else
          bonus -= make_score(UnblockedStorm[d][theirRank], 0);
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
  }

  return bonus;
}


/// Entry::do_king_safety() calculates a bonus for king safety. It is called only
/// when king square changes, which is about 20% of total king_safety() calls.

template<Color Us>
Score Entry::do_king_safety(const Position& pos) {

  Square ksq = pos.square<KING>(Us);
  kingSquares[Us] = ksq;
<<<<<<< HEAD
  castlingRights[Us] = pos.can_castle(Us);
  int minKingPawnDistance = 0;
=======
  castlingRights[Us] = pos.castling_rights(Us);
  auto compare = [](Score a, Score b) { return mg_value(a) < mg_value(b); };
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1

  Score shelter = evaluate_shelter<Us>(pos, ksq);

<<<<<<< HEAD
  Value bonus = evaluate_shelter<Us>(pos, ksq);

  // If we can castle use the bonus after the castling if it is bigger
  if (pos.can_castle(MakeCastling<Us, KING_SIDE>::right))
      bonus = std::max(bonus, evaluate_shelter<Us>(pos, relative_square(Us, SQ_G1)));

  if (pos.can_castle(MakeCastling<Us, QUEEN_SIDE>::right))
      bonus = std::max(bonus, evaluate_shelter<Us>(pos, relative_square(Us, SQ_C1)));

#ifdef CRAZYHOUSE
  if (pos.is_house())
      return make_score(bonus, bonus);
#endif
  return make_score(bonus, -16 * minKingPawnDistance);
=======
  // If we can castle use the bonus after castling if it is bigger

  if (pos.can_castle(Us & KING_SIDE))
      shelter = std::max(shelter, evaluate_shelter<Us>(pos, relative_square(Us, SQ_G1)), compare);

  if (pos.can_castle(Us & QUEEN_SIDE))
      shelter = std::max(shelter, evaluate_shelter<Us>(pos, relative_square(Us, SQ_C1)), compare);

  // In endgame we like to bring our king near our closest pawn
  Bitboard pawns = pos.pieces(Us, PAWN);
  int minPawnDist = 6;

  if (pawns & attacks_bb<KING>(ksq))
      minPawnDist = 1;
  else while (pawns)
      minPawnDist = std::min(minPawnDist, distance(ksq, pop_lsb(&pawns)));

  return shelter - make_score(0, 16 * minPawnDist);
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
}

// Explicit template instantiation
template Score Entry::do_king_safety<WHITE>(const Position& pos);
template Score Entry::do_king_safety<BLACK>(const Position& pos);

} // namespace Pawns
