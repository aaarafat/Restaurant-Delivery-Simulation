#ifndef __DEFS_H_
#define __DEFS_H_


//The four regions: A, B, C , and D
enum REGION {	
	A_REG,
	B_REG,
	C_REG,
	D_REG,
	REG_CNT		//Total number of regions
};


enum ORD_TYPE	//types of orders
{
	TYPE_NRM,	//normal order
	TYPE_FROZ,	//frozen
	TYPE_VIP,	//VIP
	TYPE_CNT	//Number of types
};
enum MOTO_TYPE	//types of orders
{
	MOTO_NRM,	//normal order
	MOTO_FROZ,	//frozen
	MOTO_VIP,	//VIP
	MOTO_CNT	//Number of types
};
enum STATUS_TYPE
{
	ASSIGNED, //ASSIGNED Means it can be IDLE or in service depends on which queue the motorcycle is at.
	REST_NRM,
	REST_FROZ,
	REST_VIP,
	DMGD,
	STATUS_CNT
};

enum PROG_MODE	//mode of the program interface
{
	MODE_INTR,	//interactive mode
	MODE_STEP,	//Step-by-step mode
	MODE_SLNT,	//Silent mode
	MODE_CNT	//number of possible modes
};
enum GUI_MODE
{
	MODE_DARK,
	MODE_LIGHT,
};

enum DrawMenuItem
{
	INTERACTIVE,
	STEPBYSTEP,
	SILENT,
	EXTRA,
	MENU_COUNT
};

#define MaxPossibleOrdCnt 999	//arbitrary value





#endif