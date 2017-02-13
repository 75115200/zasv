using System;
public class Hello
{
    public static void Main(string[] args)
    {
        Console.WriteLine("Hello, Mono!");
        Console.WriteLine("args=" + args);
        foreach(string arg in args)
        {
            Console.WriteLine(arg);
        }
    }
}
