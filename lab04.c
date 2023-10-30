// PID: 730481481
// I pledge the COMP 211 honor code.
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "instructions.h"

#define REGISTER_SIZE 32

void execute_r_instruction(r_instruction *instruct);
void execute_i_instruction(i_instruction *instruct);

static uint16_t registers[REGISTER_SIZE] = {0};

int main(){
    uint32_t instruct;

    while(true){
        printf("Please enter your instruction as a 32-bit integer: ");

        if(scanf("%u", &instruct) != 1){
            printf("\n");
            fprintf(stderr, "Failed to read instruction!\n");
            return EXIT_FAILURE;
        }

        if(instruct == UINT_MAX)
            return EXIT_SUCCESS;

        if(get_type_of_instruction(instruct) == R_TYPE){
            r_instruction *r_instruct = create_r_instruction(instruct);
            execute_r_instruction(r_instruct);
            free(r_instruct);
        }else{ // I_TYPE
            i_instruction *i_instruct = create_i_instruction(instruct);
            execute_i_instruction(i_instruct);
            free(i_instruct);
        }

        printf("Current register status:\n");

        printf("[");

        for(int i = 0; i < REGISTER_SIZE; i++){
            printf("%d", registers[i]);

            if(i != REGISTER_SIZE - 1)
                printf(", ");
        }

        printf("]\n");
    }
}

// ------------------------------------
// Function implementation that takes in the r_instruction
// you created in Part 1 and based on the MIPS instruction will update
// the register ('registers' variable given, see top of file).
//
// You will need to determine which MIPS instructions are R-type and
// which are I-type, based on that, you will have to implement the following
// instructions:
// sll, sra, add, sub, and, or, nor, addi, andi, ori
//
// Arguments:   r_instruction structure
//
// Return:      None
//
void execute_r_instruction(r_instruction *instruct){
    if (instruct->func == ADD_FUNC) {
        registers[instruct->rd] = registers[instruct->rs] + registers[instruct->rt];}
    if (instruct->func == SLL_FUNC) {
        registers[instruct->rd] = registers[instruct->rs] << (int)instruct->shamt;}
    if (instruct->func == SRA_FUNC) {
        registers[instruct->rd] = registers[instruct->rs] >> (int)instruct->shamt;}
    if (instruct->func == SUB_FUNC) {
        registers[instruct->rd] = registers[instruct->rs] - registers[instruct->rt];}
    if (instruct->func == AND_FUNC) {
        registers[instruct->rd] = registers[instruct->rs] & registers[instruct->rt];}
    if (instruct->func == OR_FUNC) {
        registers[instruct->rd] = registers[instruct->rs] | registers[instruct->rt];}
    if (instruct->func == NOR_FUNC) {
        registers[instruct->rd] = !(registers[instruct->rs] | registers[instruct->rt]);}
} // end execute_r_instruction() function 

// ------------------------------------
// Function implementation that takes in the i_instruction
// you created in Part 1 and based on the MIPS instruction will update
// the register ('registers' variable given, see top of file).
//
// You will need to determine which MIPS instructions are R-type and
// which are I-type, based on that, you will have to implement the following
// instructions:
// sll, sra, add, sub, and, or, nor, addi, andi, ori
//
// Arguments:   i_instruction structure
//
// Return:      None
//
void execute_i_instruction(i_instruction *instruct){
    if (instruct->opcode == ADDI_OPCODE) {
        int32_t immediate = instruct->immediate;
        registers[instruct->rt] = registers[instruct->rs] + immediate;}
    if(instruct->opcode == ANDI_OPCODE) {
        uint32_t immediate = instruct->immediate & 0xFFFF;
        registers[instruct->rt] = registers[instruct->rs] & immediate;}
    if(instruct->opcode == ORI_OPCODE) {
        uint32_t immediate = instruct->immediate & 0xFFFF;
        registers[instruct->rt] = registers[instruct->rs] | immediate;}
} // end execute_i_instruction() function 
