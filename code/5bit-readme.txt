1 Input Port. 
It takes in values 1 or 2.
1 corresponds to "Increment the counter by 1".
2 corresponds to "Reset the counter to 0".

6 Local Ports in total. 
The first 5 local ports correspond to the actual bit counters, with the first one corresponding to 2^4 = 16. The second corresponding to 2^3 = 8, then 2^2 = 4, then 2^1 = 2, and the fifth port corresponding to 2^0 = 1.
These ports are 1-indexed. So 1 in the port corresponds to 0, and 2 in the port corresponds to 1. So if the first 5 ports have values (1, 1, 2, 1, 2), that would correspond to the binary string "00101" = 4 + 1 = 5.
The sixth local port is to be thought of as "Is there anything to be added?". If it is 1, then nothing needs to be added. If it is 2, then 1 needs to be added to the counter.

There are 8 transitions.
The first transition is triggered every time that an 'increment' input comes in. It does nothing apart from changing the last local port to 2. It outputs "100".
The last (8th) transition is triggered every time that a 'reset' input comes in. It changes all local ports to 1. It outputs "111".

The middle 6 transitions do the actual counter changes. They are triggered when the 6th local port is "2" (ie. something needs to be added), and when their specific suffix matches.
The 2nd transition is triggered whenever the 6th port is 2, and the 5th port is 1 (ie. the counter is like "xxxx0"). It changes the 6th port to 1, and the counter to "xxxx1". It outputs "101".
The 3rd transition is triggered whenever the 6th port is 2, the counter is like "xxx01". It changes the 6th port to 1, and the counter to "xxx10". It outputs "102".
The 4th transition is triggered whenever the 6th port is 2, the counter is like "xx011". It changes the 6th port to 1, and the counter to "xx100". It outputs "104".
The 5th transition is triggered whenever the 6th port is 2, the counter is like "x0111". It changes the 6th port to 1, and the counter to "x1000". It outputs "108".
The 6th transition is triggered whenever the 6th port is 2, the counter is like "01111". It changes the 6th port to 1, and the counter to "10000". It outputs "116".
The 7th transition is triggered whenever the 6th port is 2, the counter is like "11111". It changes the 6th port to 1, and the counter to "00000". It outputs "132".


1 6  			1 Input Port, 6 Local Ports
2  				The Input Port alphabet size is 2
2 2 2 2 2 2 	The Local Port alphabets sizes are all 2. 
1 1 1 1 1 1 	The Local Ports have the value 1 by default, ie at the very beginning.

8  				There are 8 transitions

-1 				1st transition
-1
-1
-1
-1
-1
1 1
-1
-1
-1
-1
-1
2
100

-1 				2nd transition
-1
-1
-1
1
2
0
-1
-1
-1
-1
2
1
101

-1 				3rd transition
-1
-1
1
2
2
0
-1
-1
-1
2
1
1
102

-1  			4th transition
-1
1
2
2
2
0
-1
-1
2
1
1
1
104

-1 				5th transition
1
2
2
2
2
0
-1
2
1
1
1
1
108

1 				6th transition
2
2
2
2
2
0
2
1
1
1
1
1
116

2  				7th transition
2
2
2
2
2
0
1
1
1
1
1
1
132

-1   			8th transition
-1
-1
-1
-1
-1
1 2
1
1
1
1
1
1
111
  				Input stream starts, with 32 1's.
1 1
1 1
1 1
1 2
1 2
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
-1 -1
