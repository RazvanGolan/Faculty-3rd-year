namespace lab2;

public class Account
{
    public string AccountHolder { get; private set; }
    public AccountTypeEnum AccountType { get; private set; }
    public string Iban { get; private set; }
    public double Amount { get; private set; }

    public Account(string accountHolder, AccountTypeEnum accountType, string iban, double amount)
    {
        AccountHolder = accountHolder;
        AccountType = accountType;
        Iban = iban;
        Amount = amount;
    }

    public void AddAmount(double amount, Account a)
    {
        a.Amount += amount;
    }

    public void SubstractAmount(double amount, Account a)
    {
        if (a.Amount < amount)
            throw new Exception($"Insufficient amount in current account {a.Amount}.");
        
        a.Amount -= amount;
    }

    public override string ToString()
    {
        return $"Name: {AccountHolder} Account type: {AccountType} Iban: {Iban} Amount: {Amount}";
    }
}
