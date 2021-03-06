### Overview

[![Build Status](https://travis-ci.org/ddugovic/Stockfish.svg?branch=master)](https://travis-ci.org/ddugovic/Stockfish)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/ddugovic/Stockfish?svg=true)](https://ci.appveyor.com/project/ddugovic/Stockfish)

Multi Variant Stockfish is a [Stockfish](https://github.com/official-stockfish/Stockfish) fork specialized to play chess and some chess [variants](https://lichess.org/variant):
- [Crazyhouse](https://lichess.org/variant/crazyhouse)
- [Atomic](https://lichess.org/variant/atomic)
- [Horde](https://lichess.org/variant/horde)
- [King of the Hill](https://lichess.org/variant/kingOfTheHill)
- [Racing Kings](https://lichess.org/variant/racingKings)
- [Giveaway](https://lichess.org/variant/antichess)
- [Three-Check](https://lichess.org/variant/threeCheck)
- [Chess960](https://lichess.org/variant/chess960) (played natively by Official Stockfish)
- Losers
- Suicide
- Loop
- Extinction
- Grid
- Two Kings

The project has the goal to develop and to improve the playing strength of some chess variants not already played natively by Stockfish. Once a month the maintainers will merge the new upstream Stockfish patches to also keep the playing strength for Chess and Chess960 up to date. If you are interested in playing only Chess and/or Chess960, or to play Chess and/or Chess960 at maximum strength possible, simply use Stockfish. Multi Variant Stockfish, though using the same code base for Chess and Chess960, is a bit slower.

Multi Variant Stockfish is currently used in these [lichess.org](https://lichess.org/) projects: 
- [lichess.org custom Stockfish](https://github.com/niklasf/Stockfish): as engine used to play against the users on lichess.org, also running on contributed remote servers for games analysis
- [PNaCl Stockfish](https://github.com/niklasf/stockfish.pexe): as engine running in Chrome browser for your personal games analysis
- [stockfish.js](https://github.com/niklasf/stockfish.js): compiled to JavaScript and WebAssembly for other browsers

To get more information please visit the [Multi Variant Stockfish Wiki](https://github.com/ddugovic/Stockfish/wiki)


### Download

There are precompiled [binary releases](https://github.com/ddugovic/Stockfish/releases) and the following development snapshots:

Operating System | Status | profile-build
--- | --- | ---
Linux | [![Travis CI](https://travis-ci.org/ddugovic/Stockfish.svg?branch=master)](https://travis-ci.org/ddugovic/Stockfish) | [x86_64](https://s3-us-west-2.amazonaws.com/variant-stockfish/ddugovic/master/stockfish-x86_64), [x86_64-modern](https://s3-us-west-2.amazonaws.com/variant-stockfish/ddugovic/master/stockfish-x86_64-modern), [x86_64-bmi2](https://s3-us-west-2.amazonaws.com/variant-stockfish/ddugovic/master/stockfish-x86_64-bmi2)
OS X | [![Travis CI](https://travis-ci.org/ddugovic/Stockfish.svg?branch=master)](https://travis-ci.org/ddugovic/Stockfish) | [x86_64](https://s3-us-west-2.amazonaws.com/variant-stockfish/ddugovic/master/stockfish-osx-x86_64)
Windows | [![Build status](https://ci.appveyor.com/api/projects/status/aeevqaqe30lrivka/branch/master?svg=true)](https://ci.appveyor.com/project/niklasf/stockfish-imnn1/branch/master) | [x86_64](https://s3-us-west-2.amazonaws.com/variant-stockfish/ddugovic/master/stockfish-windows-x86_64.exe), [x86_64-modern](https://s3-us-west-2.amazonaws.com/variant-stockfish/ddugovic/master/stockfish-windows-x86_64-modern.exe), [x86_64-bmi2](https://s3-us-west-2.amazonaws.com/variant-stockfish/ddugovic/master/stockfish-windows-x86_64-bmi2.exe)


### Stockfish

Stockfish is a free UCI chess engine derived from Glaurung 2.1. It is
not a complete chess program and requires some UCI-compatible GUI
(e.g. XBoard with PolyGlot, eboard, Arena, Sigma Chess, Shredder, Chess
Partner or Fritz) in order to be used comfortably. Read the
documentation for your GUI of choice for information about how to use
Stockfish with it.

This version of Stockfish supports up to 512 cores. The engine defaults
to one search thread, so it is therefore recommended to inspect the value of
the *Threads* UCI parameter, and to make sure it equals the number of CPU
cores on your computer.

This version of Stockfish has support for Syzygybases.


### Files

This distribution of Stockfish consists of the following files:

  * Readme.md, the file you are currently reading.

  * Copying.txt, a text file containing the GNU General Public License.

  * src, a subdirectory containing the full source code, including a Makefile
    that can be used to compile Stockfish on Unix-like systems.


### Syzygybases

**Configuration**

Syzygybases are configured using the UCI options "SyzygyPath",
"SyzygyProbeDepth", "Syzygy50MoveRule" and "SyzygyProbeLimit".

The option "SyzygyPath" should be set to the directory or directories that
contain the .rtbw and .rtbz files. Multiple directories should be
separated by ";" on Windows and by ":" on Unix-based operating systems.
**Do not use spaces around the ";" or ":".**

Example: `C:\tablebases\wdl345;C:\tablebases\wdl6;D:\tablebases\dtz345;D:\tablebases\dtz6`

It is recommended to store .rtbw files on an SSD. There is no loss in
storing the .rtbz files on a regular HD.

Increasing the "SyzygyProbeDepth" option lets the engine probe less
aggressively. Set this option to a higher value if you experience too much
slowdown (in terms of nps) due to TB probing.

Set the "Syzygy50MoveRule" option to false if you want tablebase positions
that are drawn by the 50-move rule to count as win or loss. This may be useful
for correspondence games (because of tablebase adjudication).

The "SyzygyProbeLimit" option should normally be left at its default value.

**What to expect**
If the engine is searching a position that is not in the tablebases (e.g.
a position with 7 pieces), it will access the tablebases during the search.
If the engine reports a very large score (typically 123.xx), this means
that it has found a winning line into a tablebase position.

If the engine is given a position to search that is in the tablebases, it
will use the tablebases at the beginning of the search to preselect all
good moves, i.e. all moves that preserve the win or preserve the draw while
taking into account the 50-move rule.
It will then perform a search only on those moves. **The engine will not move
immediately**, unless there is only a single good move. **The engine likely
will not report a mate score even if the position is known to be won.**

It is therefore clear that behaviour is not identical to what one might
be used to with Nalimov tablebases. There are technical reasons for this
difference, the main technical reason being that Nalimov tablebases use the
DTM metric (distance-to-mate), while Syzygybases use a variation of the
DTZ metric (distance-to-zero, zero meaning any move that resets the 50-move
counter). This special metric is one of the reasons that Syzygybases are
more compact than Nalimov tablebases, while still storing all information
needed for optimal play and in addition being able to take into account
the 50-move rule.


### Compiling it yourself

On Unix-like systems, it should be possible to compile Stockfish
directly from the source code with the included Makefile.

Stockfish has support for 32 or 64-bit CPUs, the hardware POPCNT
instruction, big-endian machines such as Power PC, and other platforms.

In general it is recommended to run `make help` to see a list of make
targets with corresponding descriptions. When not using the Makefile to
compile (for instance with Microsoft MSVC) you need to manually
set/unset some switches in the compiler command line; see file *types.h*
for a quick reference.

### Resource For Understanding the Code Base

* [Chess Programming Wiki](https://chessprogramming.wikispaces.com) has good overall chess engines explanations 
(techniques used here are well explained like hash maps etc), it was 
also recommended by the [support team at stockfish.](http://support.stockfishchess.org/discussions/questions/1132-how-to-understand-stockfish-sources)

* [Here](https://chessprogramming.wikispaces.com/Stockfish) you can find a set of features and techniques used by stockfish and each of them is explained at the wiki, however, it's a generic way rather than focusing on stockfish's own implementation, but it will still help you. 


### Terms of use

Stockfish is free, and distributed under the **GNU General Public License**
(GPL). Essentially, this means that you are free to do almost exactly
what you want with the program, including distributing it among your
friends, making it available for download from your web site, selling
it (either by itself or as part of some bigger software package), or
using it as the starting point for a software project of your own.

The only real limitation is that whenever you distribute Stockfish in
some way, you must always include the full source code, or a pointer
to where the source code can be found. If you make any changes to the
source code, these changes must also be made available under the GPL.

For full details, read the copy of the GPL found in the file named
*Copying.txt*.
