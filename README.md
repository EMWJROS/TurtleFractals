# TurtleFractals
## Background
I'm not completely certain about the origins of this program. If I remember correctly, it was
a friend and his father who introduced me to L-systems (https://en.wikipedia.org/wiki/L-system)
shortly after New Year 1991. None of us had a computer at home (well I had a Commodore 64 and my
friend a ZX Spectrum, but none had a PC), but my friend's father worked as a teacher. We went to his school during the
winter break and he showed us the Fractint (https://en.wikipedia.org/wiki/Fractint) program on the school's computers that
could generate this type of patterns. I got a copy of the program on a 5.25" disk, but back at Imperial College in London,
where I studied, I decided to write my own version of the program in TurboPascal.

It now strikes me as odd that I wrote my own program when I actually had been given the Fractint program. Maybe I didn't bring it to the UK or maybe I just didn't realise that I had the program. Since I didn't have a PC at home, I couldn't easily check what was on the disks. And even if you do run Fractint, you have to navigate through lots of menus and you have to know that they are called 'L-systems' before you find them.

## Usage
Run as `fractint <file> > graphics.m`. The output comes as Matlab graphics. If the m-file is opened in Matlab, the graphics will be displayed.
(I might add other graphics options later.)

File format of data file: Dragon curve example with comments
```
 ----------------------------------
  4     # number of directions
  2     # number of production rules
  X     # input of first rule
  X+YF+ # output of first rule
  Y     # input of second rule
  -FX-Y # output of second rule
  X     # axiom
  ---------------------------------

  Vocab:

  F: Draw one step forward
  f: Move one step forward
  +: Turn right by angular quantum (360 degrees/number of directions)
  -: Turn left by angular quantum
  |: Turn back
  [: Save turtle state on stack (push)
  ]: Pop turtle stack
```
I include an assortment of dat-files that could be tried as input.

