#region sound
            enum WaveType
            {
                sawtooth,
                sine,
                square,
                triangle,
                pwm
            }
            static void GenerateSineWave(double[] frequencies, int[] durations, WaveType[] waveTypes = null)
            {
                try
                {
                    if (frequencies.Length != durations.Length)
                        throw new ArgumentException("Frequencies and durations arrays must have the same length.");

                    if (waveTypes != null && waveTypes.Length != frequencies.Length)
                        throw new ArgumentException("WaveTypes array must have the same length as frequencies and durations arrays.");

                    int sampleRate = 44100;
                    List<short> bufferList = new List<short>();

                    foreach (var pair in frequencies.Zip(durations, (freq, dur) => new { freq, dur }).Select((item, index) => new { item.freq, item.dur, waveType = waveTypes?[index] ?? WaveType.sine }))
                    {
                        double frequency = pair.freq;
                        int duration = pair.dur;
                        WaveType wk = pair.waveType;

                        int sampleCount = (int)(sampleRate * (duration * 0.001));
                        double amplitude = 1 * short.MaxValue;
                        double dutyCycle = 0;

                        if (frequency == 0) // Rest case
                        {
                            for (int i = 0; i < sampleCount; i++)
                            {
                                bufferList.Add(0); // Add silence (zero amplitude)
                            }
                            continue; // Skip to the next pair
                        }

                        for (int i = 0; i < sampleCount; i++)
                        {
                            double time = (double)i / sampleRate;
                            double phase = time * frequency % 1.0;
                            dutyCycle -= 0.0001;
                            if (dutyCycle < 0) dutyCycle = 1.0;

                            short sample;
                            switch (wk)
                            {
                                case WaveType.sawtooth:
                                    sample = (short)(amplitude * (2 * (time * frequency - Math.Floor(0.5 + time * frequency))));
                                    break;
                                case WaveType.sine:
                                    sample = (short)(amplitude * Math.Sin(2 * Math.PI * frequency * time));
                                    break;
                                case WaveType.square:
                                    sample = (short)(amplitude * Math.Sign(Math.Sin(2 * Math.PI * frequency * time)));
                                    break;
                                case WaveType.triangle:
                                    sample = (short)(amplitude * (2 * Math.Abs(2 * (time * frequency - Math.Floor(0.5 + time * frequency))) - 1));
                                    break;
                                case WaveType.pwm:
                                    sample = (short)(amplitude * (phase < dutyCycle ? 1 : -1));
                                    break;
                                default:
                                    sample = 0;
                                    break;
                            }

                            bufferList.Add(sample);
                        }
                    }

                    short[] buffer = bufferList.ToArray();
                    byte[] byteArray = new byte[buffer.Length * sizeof(short)];
                    Buffer.BlockCopy(buffer, 0, byteArray, 0, byteArray.Length);

                    using (MemoryStream ms = new MemoryStream())
                    using (BinaryWriter bw = new BinaryWriter(ms))
                    {
                        // Write WAV header
                        bw.Write(new char[4] { 'R', 'I', 'F', 'F' });
                        bw.Write(36 + byteArray.Length);
                        bw.Write(new char[4] { 'W', 'A', 'V', 'E' });
                        bw.Write(new char[4] { 'f', 'm', 't', ' ' });
                        bw.Write(16);
                        bw.Write((short)1);
                        bw.Write((short)1);
                        bw.Write(sampleRate);
                        bw.Write(sampleRate * sizeof(short));
                        bw.Write((short)(sizeof(short)));
                        bw.Write((short)16);
                        bw.Write(new char[4] { 'd', 'a', 't', 'a' });
                        bw.Write(byteArray.Length);
                        bw.Write(byteArray);

                        ms.Position = 0;
                        SoundPlayer sp = new SoundPlayer(ms);
                        // Get the operating system version
                        Version osVersion = Environment.OSVersion.Version;

                        sp.PlaySync(); // Use PlaySync to ensure all tones play sequentially

                    }
                }
                catch { }
            }
            static List<double> frq = new List<double>();
            static List<int> ml = new List<int>();
            static List<WaveType> waves = new List<WaveType>();

            static void beeps()
            {
                Random random = new Random();
                int rit = 200; //repeat 200 times

                    for (int i = 0; i < rit; i++)
                    {
                        WaveType wk = (WaveType)random.Next(5);
                        int s = 110;
                        int m = 300;
                        int l = 850;
                        double[] freqs = {110,220,440,880,110,220,440,880,110,220,440,880}; //frequency (put 0 for rest)
                        int[] mills = {l,l,l,l,m,m,m,m,s,s,s,s}; //duration
                        WaveType[] wvs = {WaveType.pwm,WaveType.pwm,WaveType.pwm,WaveType.pwm,WaveType.pwm,WaveType.pwm,WaveType.pwm,WaveType.pwm,WaveType.pwm,WaveType.pwm,WaveType.pwm,WaveType.pwm}; //Wavetypes see enum WaveType{}
                        frq.AddRange(freqs);
                        ml.AddRange(mills);
                        waves.AddRange(wvs);
                }
                GenerateSineWave(frq.ToArray(), ml.ToArray(), waves.ToArray()); //Plays
            }

        }
#endregion
