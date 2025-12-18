target remote localhost:3333
monitor reset halt
print debug_counter
print debug_key_pressed
info registers r0 r1 r2 r3 pc sp
bt