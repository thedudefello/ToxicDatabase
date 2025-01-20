; this is stack .text, and I am accept it's unreable type of decompiled but ah, its target processor is Intel

jmp    0x7b40005
mov    $0x0,%al
mov    $0x10cd184f,%edx
mov    %ecx,%eax
mov    %eax,%edx
mov    $0xfc507c26,%esi
mov    (%esp,%edi,1),%al
add    %dh,-0x4c(%eax,%ecx,1)
push   %cs
int    $0x10
inc    %esi
jmp    0xfdea0017
call   *0x68(%edi)
outsl  %ds:(%esi),(%dx)
popa   
sub    $0x20,%al
push   %edi
push   $0x20657265
imul   $0x6320756f,%fs:0x79(%eax,%eiz,1),%esp
outsl  %ds:(%esi),(%dx)
insl   (%dx),%es:(%edi)
and    %ah,%gs:0x72(%esi)
outsl  %ds:(%esi),(%dx)
insl   (%dx),%es:(%edi)
aas    
or     $0x6c65570a,%eax
insb   (%dx),%es:(%edi)
$0x20,%al
push   %edi
insb (%dx),%es:(%edi)
arpl   %bp,0x6d(%edi)
and    %dh,%gs:0x20(%edi,%ebp,2)
je     0xc1
and    %dl,%gs:0x6f(%eax)
insb   (%dx),%es:(%edi)
popa   
jb     0xca
jae    0x83
push   %eax
popa   
jns    0xd3
outsl  %ds:(%esi),(%dx)
popa   
and    %ecx,%fs:0x756f590a
and    %ah,0x72(%ecx)
and    %dh,%gs:0x74(%ebx)
popa   
jns    0xe3
outsb  %ds:(%esi),(%dx)
and    %ch,0x65(%bx,%si)
jb     0xe6
and    %ah,0x6f(%esi)
jb     0xa6
insb   (%dx),%es:(%edi)
outsl  %ds:(%esi),(%dx)
outsb  %ds:(%esi),(%dx)
and    %bh,0x443a
add    %al,(%eax)
push   %ebp
stos   %al,%es:(%edi)
