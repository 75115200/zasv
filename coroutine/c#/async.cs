using System;
using System.Threading.Tasks;
using System.Net.Http;

public class AsycsExample {
    static async Task<int> AccessTheWebAsync() {
        var client = new HttpClient();

        Task<string> getStringTask = client.GetStringAsync("http://www.qq.com");

        Console.WriteLine("lalala~~");

        string urlContents = await getStringTask;

        return urlContents.Length;
    }

    public static void Main() {
        string urlContents = AccessTheWebAsync();

        Console.WriteLine("urlContents: " + urlContents);
    }
}
