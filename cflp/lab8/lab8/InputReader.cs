namespace lab8;

public class InputReader
{
    public event EventHandler<KeyboardInputEventArgs> OnKeyPressed;

    public void ReadKeys()
    {
        var line = Console.ReadLine();
        
        while (!string.IsNullOrEmpty(line))
        {
            OnKeyPressed?.Invoke(this, new KeyboardInputEventArgs(line));
            line = Console.ReadLine();
        }
    }
}

public class KeyboardInputEventArgs(string s) : EventArgs
{
    public string StringArg { get; set; } = s;
}