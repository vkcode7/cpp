using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;

class Customer
{
    public int Id { get; set; }
    public string Name { get; set; }
}

class Order
{
    public Customer Customer { get; set; }
    public int Amount { get; set; }
    public DateTime Date { get; set; }
}
interface IReporting
{
    void AddOrder(Order order);
    int TotalOrderAmountPerCustomer(int customerId);
    int TotalOrderAmountOnDate(DateTime date);
    (List<Order> order, int customerId) GetOrder(int customerId);
}
class Reporting : IReporting
{

    /*
     * Implement the 'IReporting' interface below..
     */

    public Reporting()
    {
        m_orders = new List<Order>();
    }

    public void AddOrder(Order order)
    {
        m_orders.Add(order); 
    }

    public int TotalOrderAmountPerCustomer(int customerId)
    {
        var (orders, Id) = GetOrder(customerId);
        
        int totalAmt = 0;
        
        foreach(var order in orders)
            totalAmt += order.Amount;
        
        return totalAmt;
    }

    public int TotalOrderAmountOnDate(DateTime date)
    {
        var orders = m_orders.Where( (order) => 
            order.Date.Date == date.Date).ToList();
        
        int totalAmt = 0;
        
        foreach(var order in orders)
            totalAmt += order.Amount;
        
        return totalAmt;
    }
    
    public (List<Order> order, int customerId) GetOrder(int customerId)
    {
        var orders = m_orders.Where( (order) => 
            order.Customer.Id == customerId
        ).ToList();
        
        return (orders, customerId);
    }
 

    private List<Order> m_orders;
}


class Solution
{
    public static void Main(string[] args)
    {
        TextWriter textWriter = new StreamWriter(@System.Environment.GetEnvironmentVariable("OUTPUT_PATH"), true);
        List<Customer> customers = new List<Customer>();
        IReporting reporting = new Reporting();
        int cCount = Convert.ToInt32(Console.ReadLine().Trim());
        for (int i = 1; i <= cCount; i++)
        {
            var a = Console.ReadLine().Trim().Split(" ");
            Customer e = new Customer();
            e.Id = Convert.ToInt32(a[0]);
            e.Name = a[1];
            customers.Add(e);
        } 
        int oCount = Convert.ToInt32(Console.ReadLine().Trim());
        for (int i = 1; i <= oCount; i++)
        {
            var a = Console.ReadLine().Trim().Split(" ");
            var customerId = Convert.ToInt32(a[0]);
            var customer = customers.FirstOrDefault(x=>x.Id == customerId);
            Order e = new Order();
            e.Customer = customer;
            e.Amount = Convert.ToInt32(a[1]);
            e.Date = Convert.ToDateTime(a[2]);
            reporting.AddOrder(e);
        }
        var b = Console.ReadLine().Trim();
        var totalOrderAmountOnDate = reporting.TotalOrderAmountOnDate(Convert.ToDateTime(b));
        textWriter.WriteLine(b + ":" + totalOrderAmountOnDate);
        
        foreach (var c in customers)
        {
            int totalOrderAmount = reporting.TotalOrderAmountPerCustomer(c.Id);
            textWriter.WriteLine(c.Name + ":" + totalOrderAmount);
        }

        textWriter.Flush();
        textWriter.Close();
    }
}
