# Exercises

1. Implement a static method called Swap, which receives as parameters two integers (passed by reference) and reverses them.

2. Implement a static method called Middle, which receives two coordinates as parameters and returns the middle of the segment defined by the two coordinates. The Coords structure below will be used:

```C#
 public struct Coords
    {
        public float X { get; set; }
        public float Y { get; set; }

        public Coords(float x, float y)
        {
            X = x;
            Y = y;
        }

        public override string ToString()
        {
            return $"({X}, {Y})";
        }
    }
```

3. Implement a class called Account, which contains the Name and Balance properties (initialized by the constructor), and a Withdraw method that allows the withdrawal of funds. The method receives a parameter that specifies the amount withdrawn and a parameter transmitted by reference (out) that returns the remaining funds. If the entire amount can be successfully withdrawn, the method returns true. Otherwise, the method returns false. The method will have the following signature:

```C#
public bool Withdraw(double amount, out double remainingBalance)
```