using System;
using System.Threading;

public class Alpha {
    public void Beta() {
        while (true) {
            Console.WriteLine("Alpha.Beta is runing in its own thread.");
        }
    }
}

public class Simple {
    public static void Main() {
        Console.WriteLine("Thread start/stop/join sample.");

        Alpha oAlpha = new Alpha();

        Thread oThread = new Thread(new ThreadStart(oAlpha.Beta));

        oThread.Start();

        while (!oThread.IsAlive);

        //Thread.Sleep(1);

        oThread.Abort();

        oThread.Join();

        Console.WriteLine();
        Console.WriteLine("Alpha.Beta has finished.");

        try {
            Console.WriteLine("Try to restart the Alpha.Beta thread");
        } catch (ThreadStateException) {
            Console.WriteLine("ThreasStateException trying to restart a thread Alpha.Beta");
        }
    }
}

