using A1.Models;

namespace A1.Services;

public class ReportService
{
    public void PrintOrderReport(Order order, decimal total)
    {
        // Intentional duplication block #3: order reporting format
        Console.WriteLine("-----------------------------");
        Console.WriteLine("ORDER REPORT");
        Console.WriteLine($"Order ID: {order.Id}");
        Console.WriteLine($"Customer: {order.Customer.Name}");
        Console.WriteLine("Products:");
        foreach (var product in order.Products)
        {
            Console.WriteLine($"- {product.Name}: {product.Price:F2}");
        }
        Console.WriteLine($"Total: {total:F2}");
        Console.WriteLine("-----------------------------");
    }

    public void PrintArchivedOrderReport(Order order, decimal total)
    {
        // Intentional duplication block #3 (duplicate): order reporting format
        Console.WriteLine("-----------------------------");
        Console.WriteLine("ARCHIVED ORDER REPORT");
        Console.WriteLine($"Order ID: {order.Id}");
        Console.WriteLine($"Customer: {order.Customer.Name}");
        Console.WriteLine("Products:");
        foreach (var product in order.Products)
        {
            Console.WriteLine($"- {product.Name}: {product.Price:F2}");
        }
        Console.WriteLine($"Total: {total:F2}");
        Console.WriteLine("-----------------------------");
    }
}
