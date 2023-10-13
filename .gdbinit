# File: .gdbinit
# --------------
# Add gdb commands to this file that you want executed upon starting gdb.
# WARNING: the contents of this local .gdbinit file will be entirely
# ignored unless you have set your auto-load safe-path in your
# personal gdb configuration file. You can add the necessary line
# by executing the command below in the terminal:
# bash -c 'echo set auto-load safe-path / >> ~/.gdbinit'
#

echo Successfully executing commands from .gdbinit in current directory\n

#break if I am about to detonate the bomb
break *0x40160c
commands 1
  p "nice"
  signal SIGKILL
end

#temporary breakpoints for stepping through levels/functions
b *0x401ed7
#before something....
b *0x401dd1
