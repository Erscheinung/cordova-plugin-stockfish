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

#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include <atomic>
#include <condition_variable>
#include <mutex>
#ifdef _WIN32
#include <thread>
#else
#include <pthread.h>
#endif
#include <vector>

#include "material.h"
#include "movepick.h"
#include "pawns.h"
#include "position.h"
#include "search.h"
#include "thread_win32_osx.h"


/// Thread class keeps together all the thread-related stuff. We use
/// per-thread pawn and material hash tables so that once we get a
/// pointer to an entry its life time is unlimited and we don't have
/// to care about someone changing the entry under our feet.

class Thread {

<<<<<<< HEAD
  Mutex mutex;
  ConditionVariable cv;
  size_t idx;
  bool exit = false, searching = true; // Set before starting std::thread
#ifdef _WIN32
  std::thread stdThread;
=======
  std::mutex mutex;
  std::condition_variable cv;
  size_t idx;
  bool exit = false, searching = true; // Set before starting std::thread
#ifdef _WIN32
  NativeThread stdThread;
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
#else
  pthread_t nativeThread;
#endif

public:
  explicit Thread(size_t);
  virtual ~Thread();
  virtual void search();
  void clear();
  void idle_loop();
  void start_searching();
  void wait_for_search_finished();

  Pawns::Table pawnsTable;
  Material::Table materialTable;
<<<<<<< HEAD
  Endgames endgames;
  size_t pvIdx, pvLast;
  int selDepth, nmpMinPly;
  Color nmpColor;
  std::atomic<uint64_t> nodes, tbHits;
=======
  size_t pvIdx, pvLast;
  uint64_t ttHitAverage;
  int selDepth, nmpMinPly;
  Color nmpColor;
  std::atomic<uint64_t> nodes, tbHits, bestMoveChanges;
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1

  Position rootPos;
  StateInfo rootState;
  Search::RootMoves rootMoves;
  Depth rootDepth, completedDepth;
  CounterMoveHistory counterMoves;
  ButterflyHistory mainHistory;
<<<<<<< HEAD
  CapturePieceToHistory captureHistory;
  ContinuationHistory contHistory;
=======
  LowPlyHistory lowPlyHistory;
  CapturePieceToHistory captureHistory;
  ContinuationHistory continuationHistory[2][2];
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
  Score contempt;
};


/// MainThread is a derived class specific for main thread

struct MainThread : public Thread {

  using Thread::Thread;

  void search() override;
  void check_time();

<<<<<<< HEAD
  double bestMoveChanges, previousTimeReduction;
  Value previousScore;
  int callsCnt;
=======
  double previousTimeReduction;
  Value bestPreviousScore;
  Value iterValue[4];
  int callsCnt;
  bool stopOnPonderhit;
  std::atomic_bool ponder;
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1
};


/// ThreadPool struct handles all the threads-related stuff like init, starting,
/// parking and, most importantly, launching a thread. All the access to threads
/// is done through this class.

struct ThreadPool : public std::vector<Thread*> {

  void start_thinking(Position&, StateListPtr&, const Search::LimitsType&, bool = false);
  void clear();
  void set(size_t);
<<<<<<< HEAD

  MainThread* main()        const { return static_cast<MainThread*>(front()); }
  uint64_t nodes_searched() const { return accumulate(&Thread::nodes); }
  uint64_t tb_hits()        const { return accumulate(&Thread::tbHits); }

  std::atomic_bool stop, ponder, stopOnPonderhit;
=======

  MainThread* main()        const { return static_cast<MainThread*>(front()); }
  uint64_t nodes_searched() const { return accumulate(&Thread::nodes); }
  uint64_t tb_hits()        const { return accumulate(&Thread::tbHits); }
  Thread* get_best_thread() const;
  void start_searching();
  void wait_for_search_finished() const;

  std::atomic_bool stop, increaseDepth;
>>>>>>> 589074cdd6ee02f29fe107f5db82561fbe9e30c1

private:
  StateListPtr setupStates;

  uint64_t accumulate(std::atomic<uint64_t> Thread::* member) const {

    uint64_t sum = 0;
    for (Thread* th : *this)
        sum += (th->*member).load(std::memory_order_relaxed);
    return sum;
  }
};

extern ThreadPool Threads;

#endif // #ifndef THREAD_H_INCLUDED
