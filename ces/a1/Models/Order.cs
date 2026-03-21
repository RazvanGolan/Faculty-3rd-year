namespace A1.Models;

public class Order
{
    public int Id { get; set; }
    public Customer Customer { get; set; }
    public List<Product> Products { get; set; }

    public Order(int id, Customer customer, List<Product> products)
    {
        Id = id;
        Customer = customer;
        Products = products;
    }
}
