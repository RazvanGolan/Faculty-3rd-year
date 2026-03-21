using A1.Models;

namespace A1.Services;

public class CheckoutService
{
    private const decimal TaxRate = 0.19m;

    public decimal ProcessStandardOrder(Order order)
    {
        // Intentional duplication block #1: subtotal + tax + total calculation
        decimal subtotal = 0;
        foreach (var product in order.Products)
        {
            subtotal += product.Price;
        }

        decimal tax = subtotal * TaxRate;
        decimal total = subtotal + tax;

        Console.WriteLine($"[STANDARD] Order #{order.Id} subtotal: {subtotal:F2}");
        Console.WriteLine($"[STANDARD] Order #{order.Id} tax: {tax:F2}");
        Console.WriteLine($"[STANDARD] Order #{order.Id} total: {total:F2}");

        return total;
    }

    public decimal ProcessPriorityOrder(Order order, decimal priorityFee)
    {
        // Intentional duplication block #1 (duplicate): subtotal + tax + total calculation
        decimal subtotal = 0;
        foreach (var product in order.Products)
        {
            subtotal += product.Price;
        }

        decimal tax = subtotal * TaxRate;
        decimal total = subtotal + tax + priorityFee;

        Console.WriteLine($"[PRIORITY] Order #{order.Id} subtotal: {subtotal:F2}");
        Console.WriteLine($"[PRIORITY] Order #{order.Id} tax: {tax:F2}");
        Console.WriteLine($"[PRIORITY] Order #{order.Id} priority fee: {priorityFee:F2}");
        Console.WriteLine($"[PRIORITY] Order #{order.Id} total: {total:F2}");

        return total;
    }
}
