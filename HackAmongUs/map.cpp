#include "map.h"




map GetMapStats(HANDLE Proc, uintptr_t BaseModule)
{

	//Offsets Pointer_Offset;

	map Maps[NOMBRE_MAP];

	Maps[0] = { "Skeld",-28,19.9,-21.9,6.7 };
	Maps[1] = { "Mirah",1,2,3,4 };
	Maps[2] = { "Polus",1,2,3,4 };

	//BaseModule += DYNAMIC_BASE_OFFSET_Map;

	//uintptr_t MapIdAddr = FindDMAAddy(Proc,BaseModule, Pointer_Offset.);

	//int MapId = -1;
	//ReadProcessMemory(Proc,(BYTE*)MapIdAddr,&MapId,sizeof(MapId),0);

	//std::cout << "Nom de la map : " << Maps[MapId].name << std::endl;

	//if (MapId >= 0 && MapId <= NOMBRE_MAP)
	//{
		return Maps[0];
	//}

	//else return {"ERROR",0,0,0,0};
}
