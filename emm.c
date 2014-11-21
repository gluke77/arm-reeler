#include "emm.h"

int kg2emm(int kg)
{
	if (kg < 40)
		return kg;
	else
		return 40 + 3 * (kg - 40);
}

int emm2kg(int emm)
{
	if (emm < 40)
		return emm;
	else
		return 40 + (emm - 40) / 3;	
}
