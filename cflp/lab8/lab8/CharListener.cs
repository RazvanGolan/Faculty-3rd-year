namespace lab8;

public class CharListener
{
    private char KeyStored { get; set; }

    public CharListener(char key, InputReader inputReader)
    {
        KeyStored = key;
        inputReader.OnKeyPressed += HandleKeyPressed;
    }

    private void HandleKeyPressed(object? sender, KeyboardInputEventArgs e)
    {
        if (e.StringArg.Contains(KeyStored))
        {
            Console.WriteLine($"The given string {e.StringArg} contains the key {KeyStored}");
        }
    }
}