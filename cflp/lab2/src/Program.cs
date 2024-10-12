using lab2;

// strings are inmutable objects once created
// if you have a method which takes a reference to an object, the object will be modified. Everything is by reference

var bank = new Bank("ING", "swift");

var account1 = bank.OpenAccount("account1", AccountTypeEnum.Person);

Console.WriteLine(account1);

var account2 = bank.OpenAccount("account2", AccountTypeEnum.Person);

bank.DepositFunds(account2.Iban, 1000);
bank.ExtractFunds(account2.Iban, 200);

bank.TransferBetweenAccounts(account2.Iban, account1.Iban, 200);
Console.WriteLine(account1);
Console.WriteLine(account2);