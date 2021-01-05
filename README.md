# FlowForth
Another curious Forth alike interpreter, running on flow charts as host computer

FlowForth runs on a flow charts interpreter, specifically on
[Automate](https://llamalab.com/automate/), which is an automation app
for Android devices.  
Currently does the [VM](https://llamalab.com/automate/community/flows/37943)
look like this: [FlowForth VM (pdf)](http://fachkurs.de/vm/vm.pdf)  

Flow starting points are on the left. One for manually launching the VM,
with a file selector popping up. The other starting point monitors a file,
and is triggered when that file is written to. From that file is the
program file read, loaded into (emulated) memory, and a cold start performed,
which leads to the [VM](https://llamalab.com/automate/community/flows/37943)
"next" routine, the core of the emulator (lower left).
The bulk of remaining blocks are used for primitives implementation.

Programs written as far are exclusively test routines. A failing test
lights the device LED in red.  
The LED turning green indicates a successfully accomplished test.

For output and debugging, type and . are provided. There is an inkling of
console I/O now, witnessed by files stdin.txt (read by query) and stdout.txt
(type and . write to that file, besides pushing a toast). To interface these
files with a terminal, pushing their contents through
[MQTT](https://en.wikipedia.org/wiki/MQTT) upon change (stdout.txt)
or writing to when an [MQTT](https://en.wikipedia.org/wiki/MQTT) message
is received (stdin.txt) is considered.

Previously generated trace files have been disabled now.

The [VM](https://llamalab.com/automate/community/flows/37943)
is no performance monster, but seems quick enough to attempt
porting a complete interpreter to it. It runs about 5000 to 10000
empty loops per second on my phone, which puts it into the performance
class of my [Bashforth](https://github.com/Bushmills/Bashforth) interpreter
which shows a rather acceptable interactive performance.

Currently are [programs](https://github.com/Bushmills/FlowForth/blob/master/code)
for the [VM](https://llamalab.com/automate/community/flows/37943)
cross compiled on a host computer, and compiler output copied to
the device over the air, using rsync.  
The [compiler](https://github.com/Bushmills/FlowForth/blob/master/compile)
has been written in bash.

This github repository is mostly suited for the file based components
(programs, library, compiler, support scripts).  
For the [VM](https://llamalab.com/automate/community/flows/37943),
the [Automate forum](https://llamalab.com/automate/community/flows/37943)
is likely a better place, as it provides a preview possibility.

This project is in a very alpha state, in fact, it's hardly useful at this
point, though it's hard to speak of "useful" with such a project. It's
fun though, trying to run Forth on another rather unlikely platform.

Goal and purpose of the
[Flowforth VM](https://llamalab.com/automate/community/flows/37943)
was to give me a kickstart into the [Automate](https://llamalab.com/automate/)
tool: As former [Automagic](https://automagic4android.com) (a similar automation app which
isn't maintained any longer) user I needed an alternative, and to get
familiar with it quickly.
