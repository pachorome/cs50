import cs50
import sys
 
if len(sys.argv) != 2 or int(sys.argv[1]) <= 0 :
    print("Usage: python caesar.py k");
    exit(1)
     
a1 = sys.argv[1]
k = int(a1)
 
s = input("plaintext: ")
 
print("ciphertext: ", end="")
for c in s :
     
    if c.isalpha() and ord(c) > 64 and ord(c) < 91 :
         
        if (ord(c) + k) > 90 :
            print(chr(ord(c) + k - 26), end="")
             
        else :
            print(chr(ord(c) + k), end="")
             
    elif c.isalpha() and ord(c) > 96 and ord(c) < 123 :
         
        if (ord(c) + k) > 122 :
            print(chr(ord(c) + k - 26), end="")
             
        else :
            print(chr(ord(c) + k), end="")
             
    else :
        print(c, end="")
         
print("")
exit(0)