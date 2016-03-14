#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_LEN_INPUT 81
#define MAX_LEN_COMMAND 10
#define NUM_OF_OPCODES 58
#define LEN_MNEMONIC 6
#define MEMORY_SIZE 0x100000
#define SEND_ERROR_MESSEGE(str) printf("%s ERROR OCCURED!!\n", str)
#define ADDR_BOUNDARY(addr) ((addr) < 0x100000 ? (addr) : 0xFFFFF)

typedef struct _HIST{
	struct _HIST * next;
	char command_line[MAX_LEN_COMMAND];
}hist_list;

typedef struct _HASH_LINK{
	struct _HASH_LINK * next;
	int opcode;
	char mnemonic[LEN_MNEMONIC];
}op_list;

op_list *table_head[20];
hist_list *history_head;
unsigned char memory[MEMORY_SIZE]; // 2^20

void command_help(void);
void command_dir(void);
void command_history(void);
void memory_print(int start_addr, int end_addr);
void command_dump(int start, int end);
void command_edit(int addr, int val);
void command_fill(int start, int end, int val);
void command_reset(void);
void command_opcode(const char * input_mnem, int * error_flag);
void command_opcodelist(void);
int hash_func(const char * mnemonic);
void make_linking_table(op_list ** table_addr, int opcode, const char * mnemonic);
int opcode_mnem(op_list * table, const char *mnemonic);

int strtoi(const char * str, int* error_flag);

/* error handling */
int error_check_comma (int i,int comma_flag);
int error_check_moreargv (const char * input_str, int idx_input_str);

/* deallocate */
void deallocate_history(void);
void deallocate_opcode(void);

