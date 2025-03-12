2 1   		2 Input Ports, 1 Local Port
2 2   		The Input Port alphabet sizes are 2, 2
3  			The Local Port alphabet size is 3
1  			The Local Port has the value 1 by default, i.e. at the very beginning

2  			There are 2 transitions
  			The first transition's definition is below:
1   		The first local port should have value 1 at the end for this to be triggered.
1 1  		The first input port should have suffix "1" for triggering. The "1 1" refers to the fact that the suffix has length 1, and the suffix is 1.
1 1   		The second input port should have suffix "1" for triggering. The "1 1" refers to the fact that the suffix has length 1, and the suffix is 1.
2  			When this is triggered, the first local port has "2" written to it.
101 		When this is triggered, "101" is outputted.
			The first transition's definition is below:
2  			The first local port should have value 2 at the end for this to be triggered.
1 2  		The first input port should have suffix "2" for triggering. The "1 2" refers to the fact that the suffix has length 1, and the suffix is 2.
1 2  		The second input port should have suffix "2" for triggering. The "1 2" refers to the fact that the suffix has length 1, and the suffix is 2.
3  			When this is triggered, the first local port has "3" written to it.
102	 		When this is triggered, "102" is outputted.
 			Now the input stream starts:
1 1 		The first input port's first letter is inputted.
2 1  		The second input port's first letter is inputted.
1 2 		The first input port's second letter is inputted.
2 2 		The second input port's second letter is inputted.
-1 -1  		The input stream ends.
