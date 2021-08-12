\ library should be included beween primitives and user program.
\ compiler takes care of loading both primitives and library.

 0 constant 0			\ often used number are defined as constants
 1 constant 1			\ a literal takes two cells to compile, while
-1 constant -1			\ a constant just one.

 0 constant false 
-1 constant true
 1 constant cell
	 
: here  ( -- a )  		\ read dictionary pointer
   dp @				\ dp is a variable, containing the dictionary pointer
;

: allot ( x -- )		\ reserve x memory cells at dp
   dp  +!               	\ by adding to contents of dp
;

: ,  ( x -- )			\ store a number at here, allocate space
  here cell allot !
;

: nip ( x1 x2 -- x2 )		\ remove second from top stack item
   swap drop
;

: tuck ( x1 x2 -- x2 x1 x2 )	\ copy tos under second from top
   swap over
;

: 2dup ( x1 x2 -- x1 x2 x1 x2 )	\ duplicate a number pair
   over  over
;

: 2drop ( x1 x2 -- )		\ remove top two stack items
   drop drop
;

: ?dup ( 0 -- 0 | x -- x x )	\ conditionally duplicate tos
   dup if dup then
;

: =   ( x1 x2 -- f )  -  0= ;   \ equal comparison
: <>  ( x1 x2 -- f )  =  0= ;	\ unequal comparison
: >   ( n1 n2 -- f )  swap  < ;	\ signed greater than comparison
: >=  ( n1 n2 -- f )  < 0=  ;	\ signed greater or equal comparison
: <=  ( n1 n2 -- f )  >  0= ;	\ signed less or equal comparison

: 1+ ( x1 -- x2 )   1 +   ;    	\ increment tos by one
: 1- ( x1 -- x2 )   1 -   ;    	\ decrement tos by one
: *  ( n1 n2 -- n ) 1 */  ;
: /  ( n1 n2 -- n )  /mod nip ;
: mod ( n1 n2 -- n ) /mod drop ;

: min ( n1 n2 -- n )		\ keep smaller of two signed numbers
   2dup > if swap then drop ;

: max ( n1 n2 -- n )            \ keep greater of two signed numbers
   2dup < if swap then drop ;



\ this is a very inefficient, but functional implementation of a for...next loop.
\ notice that it is build as high level code, no specific support code has been
\ added to the VM for alloing to build this for..next construct.
\ allowing construction of this.
\ but there will be a more flexible and efficient do..loop construct once the need
\ arises. for the time being, and simple loops, for..next is adequate.
\ this construct can of course be nested.
: for  ( u -- )
   r> swap  >r
   dup  >r >r
;
: next ( -- )
   r> r> r> 1-
   ?dup if
      >r dup >r	swap
   then 
   drop >r
;


: ?exit ( x -- )		\ conditional premature exit of a word
   if rdrop then ;
\ by trashing the return address, exit will not return to
\ where it was called, but instead to where the routine
\ one level above was called.


\ led colours
	1 constant dark
  $ff0000 constant red
  $00ff00 constant green
  $0000ff constant blue
  $ffff00 constant yellow
  $00ffff constant cyan
  $ff00ff constant magenta
       -1 constant white

: colour  ( r g b -- x )	\ mix led colour from red,green,blue
   swap  8 lshift +
   swap 16 lshift +
;


\ VM components test
create errors 0 ,

: expected  ( x1 x2 -- )	\ mismatch count
   2dup <> if
      2dup . .
      1 errors +!
   then
   2drop
;

: check ( -- )			\ mismatch evaluation
   dark led
   depth dup if "stack bad" type then
   errors @ or
   green			\ assume no error
   swap if drop red then	\ wrong assumption
   led
;

label cold			\ cold start entry point (resolves vector at addr 0)
] main bye [			\ compile main program call and program termination
