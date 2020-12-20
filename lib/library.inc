# library should be included beween primitives and user program.
# compiler takes care of loading both primitives and library.


constant 0 0         # often used number are defined as constants
constant 1 1         # a literal takes two cells to compile, while
constant -1 -1       # a constant just one.

constant false 0
constant true -1

: here            # here  ( -- a )  read dictionary pointer
   dp          # dp is a variable, containing the dictionary pointer
   @           #   (that is, the first address above last compilation)
;

: allot           # allot ( x -- )  reserve x memory cells at dp
   dp          # by increasing contents of dp by x, that amount of
   +!          #   cells is hence reserved.
;

: ,
  here
  !
  1
  allot
;

: 2dup
   over
   over
;

: nip
   swap
   drop
;

: tuck
   swap
   over
;

: 1+
   1
   +
;

: 1-
   -1
   +
;

: 2drop
   drop
   drop
;

: ?dup
   dup
   if
      dup
   then
;


# this is a very inefficient, but functional implementation of a for...next loop.
# notice that it is build as high level code, no specific support code has been
# added to the VM for alloing to build this for..next construct.
# allowing construction of this.
# but there will be a more flexible and efficient do..loop construct once the need
# arises. for the time being, and simple loops, for..next is adequate.
# this construct can of course be nested.
: for    # i         a
   r>    # i a
   swap     # a i
   >r    # a         i
   dup      # a a       i
   >r    # a         i a
   >r    #        i a a
;

: next      #        i a r
   r>    # r         i a
   r>    # r a       i
   r>    # r a i
   1-    # r a i'
   ?dup     # r a i' i' | r a 0
   if    # r a i'
      >r # r a       i'
      dup   # r a a        i'
      >r # r a       i' a
      swap  # a r
   then     # r a | a r
   drop     # r | a
   >r    #        r | a
;


: ?exit
   if    # by trashing the return address, exit will not return to
      rdrop    # where it was called, but instead to where the routine
   then     # one level above was called.
;


: <>
   =
   0=
;

: >
   swap
   <
;

: >=
   <
   0=
;

: <=
   >
   0=
;


: min
   2dup
   >
   if
      swap
   then
   drop
;

: max
   2dup
   <
   if
      swap
   then
   drop
;



# led colours
constant dark          1
constant red    16711680
constant green     65280
constant blue        255
constant yellow  8388352
constant cyan      32767
constant magenta 2031871
constant white        -1

: colour  ( r g b -- x )
   swap
   256
   *
   +
   swap
   65536
   *
   +
;


variable errors 0

: expected
   <>
   negate
   errors
   +!
;

: check
   depth
   errors
   @
   or

   dark
   led

   green # assume no error
   swap
   if
      drop  # wrong assumption
      red
   then
   led
;

label cold        # cold start entry point (resolves vector at addr 0)
]           # switch to compilation
   main
   bye            # terminate vm
[           # return to interpreting mode
