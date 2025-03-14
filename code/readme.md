testgen.cpp is the main code which takes in an mDSA/EDT and a particular transition in it, and finds an input which triggers that transition.

### How to run

You can compile and execute the code on test-5bit.in as follows:
```
g++ testgen.cpp -o testgen
./testgen <test-5bit.in
```

### Input Format for testgen.cpp

- First line should have two integers (everything is space-separated) - NumInpPorts, and NumLocalPorts, which denote the number of Input Ports, and the number of Local Ports respectively.
- The next line contains NumInpPorts integers, which denote the size of the alphabet of each of the Input Ports.
- The next line contains NumLocalPorts integers, which denote the size of the alphabet of each of the Local Ports.
- The next line contains NumLocalPorts integers, which denote the default values on the Local Ports.
- [empty line]
- The next line should have a single integer - NumTransitions, which denotes the number of transitions.
- [empty line]
- Then NumTransitions many sets of lines follow, the i-th of which should follow this format:
   - The first NumLocalPorts lines contain a single integer denoting what the Local Port values should be, to trigger this transition.
   - Then NumInpPorts lines contain many integers. The j-th such line denotes what the suffix of the j-th Input Port should be, to trigger the i-th transition. They follow this format:
      - The first integer, say L, is the length of the suffix.
      - The next L integers are the suffix.
   - The next NumLocalPorts lines contain a single integer each, which denote what the Local Port output values should be, for this transition to be triggered.
   - Then a single line with a single integer, which is the integer outputted when this transition is triggered.
- [empty line after each transition]
- A single line with a single integer - the index of the transition (1-indexed) that needs to be trigerred.

### Output Format

The requisite input, two integers in each line.
[empty line]
All the inputs and outputs produced by the above input string, are outputted at the end, interleaved in sequence. Output a is displayed as "Output a".

### Other files

- mdsa.cpp is a code which takes in an mDSA/EDT, and an input, runs the input and displays the output.
- 0.in and 0.out are example input and output files for mdsa.cpp. 0-readme.txt explains the input format in detail for this example.
- 5bit.in and 5bit.out are input and output files for mdsa.cpp which correspond to a binary counter with 5 bits. 5bit-readme.txt explains the input format in detail for this example.
- test-5bit.in and test-5bit.out are the input and output files for testgen.cpp, for the same 5 bit binary counter as above.
- alarm.in/out, and test-alarm.in/out correspond to the car alarm example.
- wiper.in/out, and test-wiper.in/out correspond to the car wiper example.
