# <h1> CPU-Simulator <h1>

<hr>
  
<h2> Synatax of this language <h2>
  
<hr>
  
labels defination with ':' symbol <br>
registers are "r1 to r10"<br>
commands are mov, cmp, add, sub, mul, div, jmp, jl, jle, je, jne,jz, jnz, jg, jge <br> 
dont put any other symbols in the end of each line <br>
writing functions mov, sub, mul, add, div, cmp which has 2 arguments put between arguments ',' and space after it <br>
it looks like ", " <br>
and jump statements should be written like this "jmp label" with 1 space between command and label name, without any symbols<br>
empty lines are OK <br>
  
Code example bellow<br>
  main: <br>
  mov r2, 10 <br>
  mov r1, 20 <br>
  loop: <br>
  add r2, 1 <br>
  cmp r1, r2 <br>
  jle loop <br>
