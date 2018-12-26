#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

void halt(chipset *chip);
void add(chipset *chip);
void subtract(chipset *chip);
void increment_r0(chipset *chip);
void increment_r1(chipset *chip);
void decrement_r0(chipset *chip);
void decrement_r1(chipset *chip);
void swap(chipset *chip);
void print(chipset *chip);
void load_into_r0(chipset *chip);
void load_into_r1(chipset *chip);
void store_r0_in_address(chipset *chip);
void store_r1_in_address(chipset *chip);
void jump_to_address(chipset *chip);
void jump_if_r0_zero(chipset *chip);
void jump_if_r0_not_zero(chipset *chip);

#endif
