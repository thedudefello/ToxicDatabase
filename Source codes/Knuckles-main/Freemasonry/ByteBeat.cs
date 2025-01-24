using System.IO;
using System.Media;
using System;
class ByteBeat
{
    private const int SampleRate = 8000;
    private const int DurationSeconds = 14;
    private const int BufferSize = SampleRate * DurationSeconds;
    private static Func<int, int>[] formulas = new Func<int, int>[] {
        t => (t * t >> 10) ^ (t >> 4) ^ (t >> 888) | (t >> 50) ^ (t * 3),
        t => (t * t >> 15) ^ (t >> 100) | (t >> 3) ^ (t * 7),
        t => (t * t >> 12) | (t >> 80) ^ (t >> 7) ^ (t >> 100),
        t => (t * t >> 40) | (t >> 99) ^ (t >> 1500) | (t >> 5),
        t => (t * t >> 5) ^ (t >> 400) ^ (t >> 99) ^ (t >> 1000)
    };
    public static Func<int, int>[] Formulas { get => formulas; set => formulas = value; }
    private static byte[] GenerateBuffer(Func<int, int> formula)
    {
        byte[] buffer = new byte[BufferSize];
        for (int t = 0; t < BufferSize; t++)
        {
            buffer[t] = (byte)(formula(t) & 0xFF);
        }
        return buffer;
    }
    private static void SaveWav(byte[] buffer, string filePath)
    {
        using (var fs = new FileStream(filePath, FileMode.Create))
        using (var bw = new BinaryWriter(fs))
        {
            bw.Write(new[] { 'R', 'I', 'F', 'F' });
            bw.Write(36 + buffer.Length);
            bw.Write(new[] { 'W', 'A', 'V', 'E' });
            bw.Write(new[] { 'f', 'm', 't', ' ' });
            bw.Write(16);
            bw.Write((short)1);
            bw.Write((short)1);
            bw.Write(SampleRate);
            bw.Write(SampleRate);
            bw.Write((short)1);
            bw.Write((short)8);
            bw.Write(new[] { 'd', 'a', 't', 'a' });
            bw.Write(buffer.Length);
            bw.Write(buffer);
        }
    }
    private static void PlayBuffer(byte[] buffer)
    {
        string tempFilePath = Path.GetTempFileName();
        SaveWav(buffer, tempFilePath);
        using (SoundPlayer player = new SoundPlayer(tempFilePath))
        {
            player.PlaySync();
        }
        File.Delete(tempFilePath);
    }
    public static void PlayBytebeatAudio()
    {
        while (true)
        {
            foreach (var formula in Formulas)
            {
                byte[] buffer = GenerateBuffer(formula);
                PlayBuffer(buffer);
            }
        }
    }
}
