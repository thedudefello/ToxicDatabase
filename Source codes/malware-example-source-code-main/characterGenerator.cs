using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace malware_example
{
    public class characterGenerator
    {
        public static string gen_filename()
        {
            Random rand = new Random();
            char[] rnd_char = {
                '☼', '◙', '♂', '♀', '♪', '♫', '►', '◄', '↕', '¶', '▬', '☺', '☻', '♥', '♦', '♣', '♠',
            '•', '◘', '○', '▲', '▼', 'ž', 'ř', 'č', 'é', 'í', 'ÿ', 'ï', 'ä', 'ö', 'ó', 'š', 'ě', '╚', '╔',
            '╩', '╠', '╬', '╧', '╤', '╥', '↑', '■', '±', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'œ', 'Ÿ', '¼', '½',
            '¾', 'ń', '£', '¤', '¥', 'Â' , '¢', 'Æ', 'Ç', '«', '¬', '®' , 'å', 'ß', 'ø', 'õ', '×', 'ñ' , 'æ', '√', 'ε',
            '₧', 'Σ', 'σ' , 'µ', '█', '▄', '▌', '▐', '▀', '∞', 'π', '≈', 'φ', '²', '∩', '—' ,'™' };
            string rnd_name;
            string rnd_str = "";
            for (int num = 0; num < 14; num++)
            {
                rnd_name = rnd_char[rand.Next(rnd_char.Length)].ToString();
                rnd_str = rnd_str + rnd_name;
            }
            return rnd_str;
        }

        public static string gen_filetext()
        {
            Random rand = new Random();
            char[] rnd_char = {
                '☼', '◙', '♂', '♀', '♪', '♫', '►', '◄', '↕', '¶', '▬', '☺', '☻', '♥', '♦', '♣', '♠',
            '•', '◘', '○', '▲', '▼', 'ž', 'ř', 'č', 'é', 'í', 'ÿ', 'ï', 'ä', 'ö', 'ó', 'š', 'ě', '╚', '╔',
            '╩', '╠', '╬', '╧', '╤', '╥', '↑', '■', '±', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'œ', 'Ÿ', '¼', '½',
            '¾', 'ń', '£', '¤', '¥', 'Â' , '¢', 'Æ', 'Ç', '«', '¬', '®' , 'å', 'ß', 'ø', 'õ', '×', 'ñ' , 'æ', '√', 'ε',
            '₧', 'Σ', 'σ' , 'µ', '█', '▄', '▌', '▐', '▀', '∞', 'π', '≈', 'φ', '²', '∩', '—' ,'™' };
            string rnd_name;
            string rnd_str = "";
            for (int num = 0; num < 6210; num++)
            {
                rnd_name = rnd_char[rand.Next(rnd_char.Length)].ToString();
                rnd_str = rnd_str + rnd_name;
            }
            return rnd_str;
        }
    }
}
