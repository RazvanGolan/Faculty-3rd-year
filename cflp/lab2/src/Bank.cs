namespace lab2;

public class Bank
{
    public string Name { get; private set; }
    public string Swift { get; private set; }
    private List<Account> Accounts { get; set; } = [];

    public Bank(string name, string swift)
    {
        Name = name;
        Swift = swift;
    }

    public Account OpenAccount(string name, AccountTypeEnum accountTypeEnum)
    {
        var account = new Account(name, accountTypeEnum, Guid.NewGuid().ToString(), 0);
        Accounts.Add(account);

        return account;
    }

    public void GetAccountInfo(string iban)
    {
        try
        {
            var account = GetByIban(iban);
            Console.WriteLine(account);
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            throw;
        }
    }

    public void DepositFunds(string iban, double amount)
    {
        try
        {
            var account = GetByIban(iban);
            account.AddAmount(amount, account);
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            throw;
        }
    }

    public void ExtractFunds(string iban, double amount)
    {
        try
        {
            var account = GetByIban(iban);
            account.SubstractAmount(amount, account);
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            throw;
        }
    }

    public void TransferBetweenAccounts(string iban1, string iban2, double amount)
    {
        try
        {
            var account1 = GetByIban(iban1);
            var account2 = GetByIban(iban2);
            
            account1.SubstractAmount(amount, account1);
            account2.AddAmount(amount, account2);
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            throw;
        }
    }
    private Account GetByIban(string iban)
    {
        var account =  Accounts.FirstOrDefault(a => a.Iban == iban);

        if (account is null)
            throw new Exception($"Account with iban {iban} does not exist");

        return account;
    }
}