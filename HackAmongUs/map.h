#pragma once



#ifndef MAP_H

#define MAP_H


#include <iostream>
#include "proc.h"
#include "Const.h"
#include "Offset.h"

#define NOMBRE_MAP 3

struct map
{
	std::string name;

	float minX;				//Position minimum (gauche map)
	float maxX;				//Position maximum (droite map)
	float minY;				//Position minimum (bas map)
	float maxY;				//Position maximum (haut map)

};


map GetMapStats(HANDLE Proc, uintptr_t BaseModule);

#endif // !MAP_H