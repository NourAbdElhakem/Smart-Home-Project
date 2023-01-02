
#ifndef UTILS_H_
#define UTILS_H_


#define SET_BIT(REG,BIT)  (REG=REG|(1<<BIT))
#define READ_BIT(REG,BIT)  ((REG>>BIT)&1)
#define CLEAR_BIT(REG,BIT)  (REG=REG&(~(1<<BIT)))
#define Write_BIT(REG,BIT,VALUE) REG=(REG|((REG&~(1<<BIT)|VALUE)))
#define TOGGLE_BIT(REG,BIT)  (REG=REG^(1<<BIT))


typedef enum
{
	FULL=0,
	EMPTY=0,
	DONE

	}stack_t;


typedef struct Node
{
	int data;
	
	struct Node* Next;
	
}Node_t;




#endif /* UTILS_H_ */