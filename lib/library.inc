# library should be included beween primitives and user program.
# compiler takes care of loading both primitives and library.


constant 0 0			# often used number are defined as constants
constant 1 1			# a literal takes two cells to compile, while
constant -1 -1			# a constant just one.

constant false 0
constant true -1

: here				# here  ( -- a )	read dictionary pointer
   dp				# dp is a variable, containing the dictionary pointer
   @				#   (that is, the first address above last compilation)
semicolon

: allot				# allot ( x -- )	reserve x memory cells at dp
   dp				# by increasing contents of dp by x, that amount of
   +!				#   cells is hence reserved.
semicolon   

: 2dup
   over
   over
semicolon

: nip
   swap
   drop
semicolon

: tuck
   swap
   over
semicolon

: 1+
   1
   +
semicolon

: 1-
   -1
   +
semicolon

: 2drop
   drop
   drop
semicolon

: ?dup
   dup
   IF
      dup
   THEN
semicolon


# this is a very inefficient, but functional implementation of a for...next loop.
# notice that it is build as high level code, no specific support code has been
# added to the VM for alloing to build this for..next construct.
# allowing construction of this.
# but there will be a more flexible and efficient do..loop construct once the need
# arises. for the time being, and simple loops, for..next is adequate.
# this construct can of course be nested.
: FOR		# i			a
   r>		# i a
   swap		# a i
   >r		# a			i
   dup		# a a			i 
   >r		# a			i a
   >r		#			i a a
semicolon

: NEXT		#			i a r
   r>		# r			i a
   r>		# r a			i
   r>		# r a i			
   1-		# r a i'
   ?dup		# r a i' i' | r a 0
   IF		# r a i'
      >r	# r a			i'
      dup	# r a a			i'
      >r	# r a			i' a
      swap	# a r
   THEN		# r a | a r
   drop		# r | a
   >r		#			r | a
semicolon


: ?exit
   IF		# by trashing the return address, exit will not return to
      rdrop 	# where it was called, but instead to where the routine
   THEN		# one level above was called.
semicolon	

: exit
   rdrop
semicolon


: <>
   =
   0=
semicolon

: >
   swap
   <
semicolon

: >=
   <
   0=
semicolon

: <=
   >
   0=
semicolon


: min
   2dup
   >
   IF
      swap
   THEN
   drop
semicolon

: max
   2dup
   <
   IF
      swap
   THEN
   drop
semicolon



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
semicolon


variable errors 0

: expected
   <>
   negate 
   errors
   +! 
semicolon

: check
   depth
   errors
   @
   or

   dark
   led

   green	# assume no error
   swap
   IF
      drop	# wrong assumption
      red 
   THEN
   led
semicolon

label cold			# cold start entry point (resolves vector at addr 0)
]				# switch to compilation
   main
   bye				# terminate vm
[				# return to interpreting mode
