#include <iostream>
#include <windows.h>
#include "Door.h"

Door::Door(int x, int y, ActorColor color, ActorColor closedColor)
	: PlacableActor(x, y, color)
	, m_IsOpen(false)
	, m_closedColor(closedColor)
{

}

void Door::Draw() {

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_IsOpen) {

		SetConsoleTextAttribute(console, (int)m_color);
	}
	else {

		SetConsoleTextAttribute(console, (int)m_closedColor);
	}
	std::cout << "|";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}