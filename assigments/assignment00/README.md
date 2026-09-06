## **ASSIGNMENT B00**
**Description** <br>
This program reads integer values from the command line and prints: <br>
- number of values
- minimum value
- maximum value
- average value <br>
The program accepts from 1 to 12 values <br>

**Build** <br>
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror assignment_b00 -o assignment_b00 <br>

**Run** <br>
Example: <br>
*./assignment_b00 3 -5 150* <br>
Output: <br>
OK count=3 min=-5 max=150 mean=49.33

**Input** <br>
The program accepts integer values as separate command-line arguments. <br>

Valid: <br>

./assignment_b00 10 <br>
./assignment_b00 1 2 3 4 <br>
./assignment_b00 -10 20 30 <br>

Invalid: <br>

./assignment_b00 12x <br>

More than 12 values are also rejected. <br>

**Functions**<br>
*parse_samples()*<br>
Reads and checks the input values. It uses strtol() to convert the arguments.<br>

*summarize_samples()*<br>
Finds the minimum, maximum and total of the values.<br>

*mean_of()*<br>
Calculates the average.<br>

*print_summary()*<br>
Prints the result.<br>

**Error handling**<br>
If the input is invalid, the program prints an error message to stderr and returns exit code 2.

