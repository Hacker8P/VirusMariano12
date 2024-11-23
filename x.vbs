Do While True
   set WshShell = WScript.CreateObject("WScript.Shell")
   WshShell.SendKeys "MyComputer"
   WshShell.Run "wscript .\y.vbs"
   WScript.Sleep(1000)
Loop