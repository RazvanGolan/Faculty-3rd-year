namespace lab3;

public class Exercise2
{
    public static Coords FindMiddle(Coords a, Coords b)
    {
        return new Coords((a.X + b.X) / 2, (a.Y + b.Y) / 2);
    }
}