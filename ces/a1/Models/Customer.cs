namespace A1.Models;

public class Customer
{
    public string Name { get; set; }
    public string Email { get; set; }

    public Customer(string name, string email)
    {
        Name = name;
        Email = email;
    }
}
