using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Media;

namespace Gen_PCM
{
    public class PCM_Audio
    {
        public enum Waves
        {
            Sine = 0,
            Square = 1,
            Sawtooth = 2,
            Triangle = 3,
            Whitenoise = 4
        }
        public void pcm()
        {
            //HEADER
            byte[] ChunkID = Encoding.ASCII.GetBytes("RIFF");
            int SampleRate = 16000;
            short NumChannels = 2;
            int duration = 10;
            int NumSamples = SampleRate * duration;
            short BitsPerSample = 16;
            int SubChunk2Size = NumSamples * NumChannels * BitsPerSample / 8;
            int ChunkSize = 36 + SubChunk2Size;
            byte[] Format = Encoding.ASCII.GetBytes("WAVE");
            byte[] Subchunk1ID = Encoding.ASCII.GetBytes("fmt ");
            int Subchunk1Size = 16;
            short AudioFormat = 1;
            int ByteRate = SampleRate * NumChannels * BitsPerSample / 8;
            short BlockAlign = (short)(NumChannels * BitsPerSample / 8);
            byte[] Subchunk2ID = Encoding.ASCII.GetBytes("data");

            int amplitude = short.MaxValue / 2;

            short[] wave = new short[NumSamples * NumChannels];
            byte[] wave_byte = new byte[NumSamples * NumChannels * sizeof(short)];

            float[] freqs = { 50f, 70f, 80f, 40f, 100f, 150f, 200f, 80f };

            short[] new_wave = new_waves(Waves.Whitenoise, wave, NumSamples, SampleRate, NumChannels, 
                amplitude, freqs, 10);

            Buffer.BlockCopy(wave, 0, wave_byte, 0, new_wave.Length * sizeof(short));
            using (MemoryStream mem = new MemoryStream())
            {
                using(BinaryWriter wr = new BinaryWriter(mem))
                {
                    wr.Write(ChunkID);
                    wr.Write(ChunkSize);
                    wr.Write(Format);
                    wr.Write(Subchunk1ID);
                    wr.Write(Subchunk1Size);
                    wr.Write(AudioFormat);
                    wr.Write(NumChannels);
                    wr.Write(SampleRate);
                    wr.Write(ByteRate);
                    wr.Write(BlockAlign);
                    wr.Write(BitsPerSample);
                    wr.Write(Subchunk2ID);
                    wr.Write(SubChunk2Size);

                    wr.Write(wave_byte);
                    var snd = new SoundPlayer(mem);

                    mem.Position = 0;
                    snd.PlayLooping();
                    snd.Dispose();
                }
            }
        }
        public short[] new_waves(Waves waves, short[] old_wave, int NumSamples, int SampleRate, 
            int NumberChannels, int amplitude, float[] frequency, int tempo)
        {
            short[] wave = old_wave;
            int freq_row = -1;
            int tempo_count = 0;

            double timeIncrement = 1.0 / SampleRate;

            Random rand;

            switch (waves)
            {
                case Waves.Sine:
                    for (int i = 0; i < NumSamples * NumberChannels; i++)
                    {
                        if(tempo_count == 0)
                        {
                            if (freq_row < frequency.Length - 1)
                                freq_row++;
                            else
                                freq_row = 0;
                        }

                        tempo_count++;

                        if (tempo_count == (NumSamples * NumberChannels) / tempo)
                            tempo_count = 0;

                        float freq = frequency[freq_row];
                        for (int channel = 0; channel < NumberChannels; channel++)
                        {
                            wave[i] = Convert.ToInt16(amplitude * Math.Sin(freq * i));
                        }
                    }
                    break;
                case Waves.Square:
                    for (int i = 0; i < NumSamples * NumberChannels; i++)
                    {
                        if (tempo_count == 0)
                        {
                            if (freq_row < frequency.Length - 1)
                                freq_row++;
                            else
                                freq_row = 0;
                        }

                        tempo_count++;

                        if (tempo_count == (NumSamples * NumberChannels) / tempo)
                            tempo_count = 0;

                        float freq = frequency[freq_row];
                        for (int channel = 0; channel < NumberChannels; channel++)
                        {
                            wave[i] = Convert.ToInt16(amplitude * Math.Sign(Math.Sin(freq * i)));
                        }
                    }
                    break;
                case Waves.Sawtooth:
                    for (int i = 0; i < NumSamples * NumberChannels; i++)
                    {
                        if (tempo_count == 0)
                        {
                            if (freq_row < frequency.Length - 1)
                                freq_row++;
                            else
                                freq_row = 0;
                        }

                        tempo_count++;

                        if (tempo_count == (NumSamples * NumberChannels) / tempo)
                            tempo_count = 0;

                        float freq = frequency[freq_row];

                        double t = i * timeIncrement;
                        for (int channel = 0; channel < NumberChannels; channel++)
                        {
                            wave[i] = Convert.ToInt16(amplitude * (2.0 * (t * freq - 
                                Math.Floor(0.5 + t * freq))));
                        }
                    }
                    break;
                case Waves.Triangle:
                    for (int i = 0; i < NumSamples * NumberChannels; i++)
                    {
                        if (tempo_count == 0)
                        {
                            if (freq_row < frequency.Length - 1)
                                freq_row++;
                            else
                                freq_row = 0;
                        }

                        tempo_count++;

                        if (tempo_count == (NumSamples * NumberChannels) / tempo)
                            tempo_count = 0;

                        float freq = frequency[freq_row];

                        double t = i * timeIncrement;
                        for (int channel = 0; channel < NumberChannels; channel++)
                        {
                            wave[i] = Convert.ToInt16(amplitude * (2.0 * Math.Abs(2.0 * 
                                (t * freq - Math.Floor(t * freq + 0.5))) - 1.0));
                        }
                    }
                    break;
                case Waves.Whitenoise:
                    rand = new Random();

                    for(int i = 0; i < NumSamples * NumberChannels; i++)
                    {
                        wave[i] = Convert.ToInt16(rand.Next(-amplitude, amplitude));
                    }    
                    break;
            }

            return wave;
        }
    }
}
