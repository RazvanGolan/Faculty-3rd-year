namespace lab9;

public class InputReader
{
    public event EventHandler<string>? OnKeyPressed;

    public void ReadKeys()
    {
        var line = Console.ReadLine();
        
        while (!string.IsNullOrEmpty(line))
        {
            OnKeyPressed?.Invoke(this, line);
            line = Console.ReadLine();
        }
    }
}