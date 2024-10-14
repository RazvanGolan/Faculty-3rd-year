namespace lab3;

public class Account
{
    public string Name { get; set; }
    public double Balance { get; set; }

    public Account(string name, double balance)
    {
        Name = name;
        Balance = balance;
    }

    public bool Withdraw(double amount, out double remainingBalance)
    {
        var succes = Balance >= amount && (Balance -= amount) >= 0;

        remainingBalance = Balance;

        return succes;
    }
}