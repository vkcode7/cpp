# Bits Manipulations
```console
128 | 64 | 32 | 16 | 8 | 4 | 2 | 1
-----------------------------------
 7    6     5    4   3   2   1   0

 0 = 0
 1 = 1
 2 = 10
 3 = 11
 5 = 101
 6 = 110
 7 = 111
```
 Bitwise operations

 ```console
    int a = 5;  // Binary representation: 0101
    int b = 3;  // Binary representation: 0011

| Operator     | Description                                | Example                  |
|--------------|--------------------------------------------|--------------------------|
| &            | Bitwise AND                                | a & b (result: 0001)     |
| |            | Bitwise OR                                 | a | b (result: 0111)     |
| ^            | Bitwise XOR (Exclusive OR)                 | a ^ b (result: 0110)     |
| ~            | Bitwise NOT (Complement)                   | ~a (result: 11111010)    |
| <<           | Left Shift                                 | a << 1 (result: 1010)    |
| >>           | Right Shift                                | a >> 1 (result: 0010)    |
```

Decimal to Binary:
You can convert a decimal number into binary by repeatedly dividing the decimal number by 2 and keeping track of the remainders. 

```console
125 to binary = 1111101
| Step | Decimal | Divide by 2 | Remainder | Binary |
|------|---------|-------------|-----------|--------|
|  1   |   125   |     62      |     1     |   1    |
|  2   |   62    |     31      |     0     |   01   |
|  3   |   31    |     15      |     1     |   101  |
|  4   |   15    |     7       |     1     |  1101  |
|  5   |   7     |     3       |     1     | 11101  |
|  6   |   3     |     1       |     1     |111101  |
|  7   |   1     |     0       |     1     |1111101 |

48 to binary = 110000
| Step | Decimal | Divide by 2 | Remainder | Binary |
|------|---------|-------------|-----------|--------|
|  1   |   48    |     24      |     0     |   0    |
|  2   |   24    |     12      |     0     |   00   |
|  3   |   12    |     6       |     0     |   000  |
|  4   |   6     |     3       |     0     |  0000  |
|  5   |   3     |     1       |     1     |  10000 |
|  6   |   1     |     0       |     1     | 110000 |
```

### LSB/MSB
For example, consider the 8-bit binary number 10110110:

In this binary number, the rightmost bit (bit 0) is the LSB, which holds the value 0.
The leftmost bit (bit 7) is the MSB, which holds the value 1. An ODD number always has 1 as LSB.

### Truth Table

```bash
|  A  |  B  | A AND B|  A OR B | A XOR B |
|-----|-----|--------|---------|---------|
|  0  |  0  |   0    |    0    |    0    |
|  0  |  1  |   0    |    1    |    1    |
|  1  |  0  |   0    |    1    |    1    |
|  1  |  1  |   1    |    1    |    0    |
```

```c#
    // Online C# Editor for free
    // Write, Edit and Run your C# code using C# Online Compiler

    using System;
    using System.Collections.Generic;

    public class HelloWorld
    {
        static void PrintBits(int num)
        {
            const int IntSize = sizeof(int) * 8;
            for (int i = IntSize - 1; i >= 0; i--)
            {
                int mask = 1 << i;
                int bit = (num & mask) == 0 ? 0 : 1;
                Console.Write(bit);
            }
            Console.WriteLine("");
        }

        static Func<int, string> printBits = (int k) => {
            int numsetbits = 0;
            Stack<int> st = new();
            while (k > 0)
            {
                st.Push(k & 1);
                k >>= 1; //same as k = k / 2;
            }

            string bits = "";
            foreach (var number in st)
            {
                bits += number;
            }

            return bits;
        };

        static Func<int, int> setBitCounter = (int k) => {
            int numsetbits = 0;
            while (k > 0)
            {
                if ((k & 1) == 1)
                    numsetbits++;

                k >>= 1; //same as k = k / 2;
            }
            return numsetbits;
        };

        static Func<int, int> allBitCounter = (int k) => {
            int numbits = 0;
            while (k > 0)
            {
                numbits++;

                k >>= 1;
            }
            return numbits;
        };

        static Func<int, int> allBitCounterMethod2 = (int k) => {
            int numbits = 0;
            while ((1 << numbits) <= k)
            {
                numbits++;
            }
            return numbits;
        };

        static Func<int, int, int> minusUsingBits = (int j, int k) => {
            int twosComplement = ~k + 1;
            int answer = j + twosComplement;
            return answer;
        };

        static Func<int, bool> isOdd = (int k) => { return (k & 1) == 1; };

        static Func<int, int, (int, int)> swap = (int a, int b) => {
            a = a ^ b;
            b = a ^ b; //(a^b^b) is 1 as b^b is 0; 0^a = a
            a = a ^ b; //a^b^a leaves b
            return (a, b);
        };

        public static void Main(string[] args)
        {
            int num = 125; //for negative, inverse the bits and add 1
            int switchSign = ~num + 1;
            Console.WriteLine("numsetbits for " + num + " are " + setBitCounter(num));

            Console.WriteLine("allsetbits for " + num + " are " + allBitCounter(num));

            Console.WriteLine("allsetbits for " + num + " are " + allBitCounterMethod2(num));

            Console.WriteLine("printing bits for the number " + num + ": " + printBits(num));

            Console.WriteLine("is number odd " + num + ": " + isOdd(num));

            Console.WriteLine(minusUsingBits(19, 7));

            var (a, b) = swap(10, 15);
            Console.WriteLine("a " + a + ", b " + b);

            //create a bit mask
            //4th bit from left
            int bit = 4;
            int mask = 1 << (bit - 1); //4th bit, 1000

            //use this mask to check if 4th (Ith) bit is set
            Console.WriteLine("is " + bit + "th bit is set for " + num + ": " + ((num & mask) > 0));

            //toggling ith bit using mask - use XOR to toggle
            Console.WriteLine("toggled ith bit for " + num + ": " + (num ^ mask));
            Console.WriteLine("printing bits: " + printBits(num ^ mask));
            //set Ith bit again
            int newnum = (num ^ mask) | mask;
            Console.WriteLine("new number is " + newnum);

            //clear Ith bit
            //create a mask where all bits are 1 except ith bit.
            //xor will toggle but & will clear a set bit
            int newmask = ~0; //inverse all 0 bits
            PrintBits(newmask);
            newmask = newmask ^ mask; /// 11111 ^ 00100
            PrintBits(newmask);

            //mask is 0001000
            newmask = ~mask; /// 1110111

            Console.WriteLine("After setting Ith to 0: ");
            PrintBits(newmask);
            num = 256;
            Console.WriteLine("printing bits before clearing: " + num + " : " + printBits(num ^ mask));
            Console.WriteLine("printing bits after: " + newnum + " : ");
            PrintBits(num & newmask);

            //Find how m any bits need to be changed
            //to convert a to b
            //Starategy: do a^b; the bits which are same will become 0
            //those that need to be flipped will become 1; count 1 bits for answer

            //n = n & (n-1) will change the LSB to 0;
            //if there are 4 set bits, n will be 0 in 4 steps
            int n = 125;
            int numsetbits = 0;
            while (n > 0)
            {
                numsetbits++;
                n = n & (n - 1);
            }
            Console.WriteLine("num set bits are : " + numsetbits);

            //for any number whoch is a power of 2, n&(n-1) will be 0
            PrintBits(125);
            PrintBits(-125);

            int num1 = 0b1010;  // Binary literal representation of 10
    
            // Bitwise complement
            int resultComplement = ~num1; // resultComplement = 0b11111111111111111111111111110101 (-11 in decimal)
            Console.WriteLine($"Bitwise Complement: {Convert.ToString(resultComplement, 2)}");
        }
    }
```

