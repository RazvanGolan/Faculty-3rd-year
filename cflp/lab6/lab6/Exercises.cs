namespace lab6;

public static class Exercises
{
    public delegate bool MyDelegate(int x);
    public delegate float MyDelegateFloat(float x);
    
    public static List<int> Filter(MyDelegate condition, List<int> list)
    {
        return [..list.Where(x => condition(x))];
    }

    public static float FGX(MyDelegateFloat del1, MyDelegateFloat del2, float x)
    {
        return del1(del2(x));
    }
}