#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

void init_i8042();
void send_key(uint8_t scancode, bool is_keydown);

#endif
