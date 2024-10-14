using System.Runtime.InteropServices.Marshalling;

namespace lab3;

public class Exercise1
{
    public static void Swap(ref int a, ref int b)
    {
        (a, b) = (b, a);
    }
}