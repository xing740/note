import os
import sys
from ctypes import *
import subprocess

user32 = windll.LoadLibrary('user32.dll')
 
#user32.LockWorkStation()
os.chdir('F:\\git_code\\note')
subprocess.call(['git', 'add', '*'])
subprocess.call(['git', 'commit', '-am', '//tick sync'])
subprocess.call(['git', 'status'])
print("fadsf")
#t input()
