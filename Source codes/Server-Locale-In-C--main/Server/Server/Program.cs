using System;
using System.Net;
using System.Threading;

class LocalServer
{
    static void Main()
    {
        HttpListener listener = new HttpListener();
        listener.Prefixes.Add("http://localhost:8080/");// nome del server 

        listener.Start();  

        Console.WriteLine("Local server running at http://localhost:8080/"); //esecuzione del server 

      
        ThreadPool.QueueUserWorkItem((state) =>
        {
            while (true)
            {
                HttpListenerContext context = listener.GetContext(); 
                HttpListenerResponse response = context.Response;

                string responseString = "<html><body>Questo è il mio server in C# </body></html>"; // testo del server
                byte[] buffer = System.Text.Encoding.UTF8.GetBytes(responseString);

                response.ContentLength64 = buffer.Length;
                System.IO.Stream output = response.OutputStream;
                output.Write(buffer, 0, buffer.Length);
                output.Close();
            }
        });
        // premi un tasto per terminarlo 
        Console.ReadLine(); 

        listener.Stop(); 
    }
}
