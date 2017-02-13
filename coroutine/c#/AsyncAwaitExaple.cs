using System;
using System.Threading.Tasks;
using System.Threading;

namespace AsyncAwaitExample {
    class Program {
        static void Main() {
            Thread.CurrentThread.Name = "Main";

            var demo = new AsyncAwaitDemo();
            demo.DoStuff();

            while (true) {
                Console.WriteLine("Doing Stuff on the Main Thread = {0}",
                        Thread.CurrentThread.Name);
            }
        }
    }

    public class AsyncAwaitDemo {
        public async Task DoStuff() {
            await Task.Run(() => {
                    LongRuingOperation();
                    });
            Console.WriteLine("LongRuingOperation finished");
        }

        private static async Task<string> LongRuingOperation() {
            int counter;

            for (counter = 0; counter < 500; counter++) {
                Console.WriteLine("counter = {0}, thread = {1}", counter, Thread.CurrentThread.Name);
            }

            return "Counter = " + counter;
        }
    }

}
