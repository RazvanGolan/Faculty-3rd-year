# Program for Managing Bank Accounts

The **Bank** class has the following structure:

**Bank**:
- Name
- Swift
- List<Account>

The **Account** class has the following structure:

**Account**:
- Account holder
- Account type (person / company)
- IBAN
- Amount

> **Note**: For the **account type**, an enum will be used. All properties should be public and readonly.

## Operations on **Account** Object:

- **Deposit cash**
- **Withdraw cash**
- **Display account details** (ToString method)


## Operations on **Bank** Object:

- **Open a new account**
- **Search for an account by IBAN and display its details**
- **Deposit cash into an account**
- **Withdraw cash from an account**
- **Transfer money between two accounts**

## Suggestion:

You can define an additional private method `GetAccount(string iban)` that is used to search for an account by IBAN and return it.
