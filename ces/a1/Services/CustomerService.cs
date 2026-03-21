using A1.Models;

namespace A1.Services;

public class CustomerService
{
    public void RegisterCustomer(Customer customer)
    {
        // Intentional duplication block #2: validation logic
        if (string.IsNullOrWhiteSpace(customer.Name))
        {
            throw new ArgumentException("Customer name is required.");
        }

        if (string.IsNullOrWhiteSpace(customer.Email) || !customer.Email.Contains('@'))
        {
            throw new ArgumentException("Valid customer email is required.");
        }

        Console.WriteLine($"Customer registered: {customer.Name} ({customer.Email})");
    }

    public void UpdateCustomerEmail(Customer customer, string newEmail)
    {
        // Intentional duplication block #2 (duplicate): validation logic
        if (string.IsNullOrWhiteSpace(customer.Name))
        {
            throw new ArgumentException("Customer name is required.");
        }

        if (string.IsNullOrWhiteSpace(newEmail) || !newEmail.Contains('@'))
        {
            throw new ArgumentException("Valid customer email is required.");
        }

        customer.Email = newEmail;
        Console.WriteLine($"Customer email updated: {customer.Name} ({customer.Email})");
    }
}
