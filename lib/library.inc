# library should be included beween primitives and user program.
# compiler takes care of loading both primitives and library.


constant 0 0			# often used number are defined as constants
constant 1 1			# a literal takes two cells to compile, while
constant -1 -1			# a constant just one.

constant false 0
constant true -1

colon here			# here  ( -- a )	read dictionary pointer
   dp				# dp is a variable, containing the dictionary pointer
   @				#   (that is, the first address above last compilation)
semicolon

colon allot			# allot ( x -- )	reserve x memory cells at dp
   dp				# by increasing contents of dp by x, that amount of
   +!				#   cells is hence reserved.
semicolon   

colon 2dup
   over
   over
semicolon

colon nip
   swap
   drop
semicolon

colon tuck
   swap
   over
semicolon

colon 1+
   1
   +
semicolon

colon 1-
   -1
   +
semicolon

colon 2drop
   drop
   drop
semicolon


# this is a very inefficient, but functional implementation of a for...next loop.
# notice that it is build as high level code, no specific support code has been
# added to the VM for alloing to build this for..next construct.
# allowing construction of this.
# but there will be a more flexible and efficient do..loop construct once the need
# arises. for the time being, and simple loops, for..next is adequate.
# this construct can of course be nested.
colon _for	# i			a
   r>		# i a
   swap		# a i
   >r		# a			i
   dup		# a a			i 
   >r		# a			i a
   >r		#			i a a
semicolon

colon _next	#			i a r
   r>		# r			i a
   r>		# r a			i
   r>		# r a i			
   1-		# r a i'
   ?dup		# r a i' i' | r a 0
   _if		# r a i'
      >r	# r a			i'
      dup	# r a a			i'
      >r	# r a			i' a
      swap	# a r
   _then	# r a | a r
   drop		# r | a
   >r		#			r | a
semicolon


# yet untested comparisons, therefore these definitions are for now commented out:
colon <>
   =
   0=
semicolon

colon >
   swap
   <
semicolon

colon >=
   <
   0=
semicolon

colon <=
   >
   0=
semicolon


colon min
   2dup
   >
   _if
      swap
   _then
   drop
semicolon

colon max
   2dup
   <
   _if
      swap
   _then
   drop
semicolon


colon ?dup
   dup
   _if
      dup
   _then
semicolon

# include check.inc   # not good
# led colours for test indicators with expected
constant red    16711680
constant green     65280
constant dark 1

variable errors 0

colon expected
   <>
   negate 
   errors
   +! 
semicolon

colon check
   depth
   errors
   @
   or

   dark
   led

   green	# assume no error
   swap
   _if
      drop	# wrong assumption
      red 
   _then
   led
semicolon


label cold			# cold start entry point (resolves vector at addr 0)
[
   main				# call main program
   bye				# terminate vm
]
