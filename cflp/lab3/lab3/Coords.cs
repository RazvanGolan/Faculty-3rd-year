namespace lab3;

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