#name	aliases	  stack			description
#--------------------------------------------------------------------------------
unnest	exit	# ( -- )
noop		# ( -- )
bye		# ( -- )		terminate the VM, end flow
branch		# ( -- )		unconditional branch
branch0		# ( x -- )		conditional branch
execute		# ( a -- ? )		call execution token
dolit		# ( -- x )		push in-code literal to data stack
slit		# ( -- ) ( ss: -- s )	push in-code literal string to string stack
dup		# ( x -- x x )
drop		# ( x -- )
swap		# ( x1 x2 -- x2 x1 )
over		# ( x1 x2 -- x1 x2 x1 )
depth		# ( -- u )		data stack element count
>r		# ( x -- )		pop data stack, push to return stack
r>		# ( -- x )		pop return stack, push to data stack
r@		# ( -- x )		read return stack top, push to data stack
rdrop		# ( -- )		drop return stack top
@		# ( a -- x )		read from address
!		# ( x a -- )		write x to address
+!		# ( u a -- )		add u to contents of a
and		# ( u1 u2 -- u )
or		# ( u1 u2 -- u )
xor		# ( u1 u2 -- u )
invert		# ( x -- x )		bitwise complement
lshift		# ( u n -- u )		shift x left by n
rshift		# ( u n -- u )  	logical right shift u by n
+		# ( n1 n2 -- n )
-		# ( n1 n2 -- n )
*		# ( n1 n2 -- n )
/		# ( n1 n2 -- n )	divide n1 by n2
negate		# ( n -- n )		negate n
abs		# ( n -- u )		strip sign
int		# ( n -- n )		strips fraction
=		# ( x1 x2 -- u )
0<		# ( x1 x2 -- u )
<		# ( x1 x2 -- u )
0=	not	# ( x1 x2 -- u )
/mod		# ( n1 n2 -- n3 n4 )	divide n1 by n2, return quotient n2 and remainder n4
*/		# ( n1 n2 n3 -- n )	n1*n2/n3
.		# ( n -- )		outputs n as toast
type		# ( -- )		write topmost string stack item as toast to screen
led		# ( colour -- )		set led to 24 bit RRGGBB colour
