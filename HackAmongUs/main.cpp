#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "graphics.h"
#include "Const.h"
#include "Player.h"
#include "proc.h"
#include "map.h"
#include "Maths.h"
#include "Offset.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "Hack Among Us", sf::Style::Titlebar | sf::Style::Close);

	Offsets Pointer_Offset;

	Player Players[MAX_PLAYER_COUNT];

	for (int i{ 0 }; i < MAX_PLAYER_COUNT; i++)
	{
		Players[i].CreatePlayer(&Players[i], i);
	}

	sf::Texture map_texture = charger_texture("Skeld.png");
	sf::Texture player_texture = charger_texture("crewmate.png");

	sf::Sprite map_sprite = creer_sprite(map_texture, LARGEUR_FENETRE, HAUTEUR_FENETRE, true);
	sf::Sprite player_sprite = creer_sprite(player_texture, 25, 25, true);

	player_sprite.setOrigin(player_texture.getSize().x / 2, player_texture.getSize().y / 2);

	Process Proc;

	Proc.Id = GetProcId(L"Among Us.exe");
	Proc.Handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, Proc.Id);
	Proc.ModuleBase = GetModuleBaseAddress(Proc.Id, L"GameAssembly.dll");
	Proc.DynamicPoiterBaseModule = Proc.ModuleBase + DYNAMIC_BASE_OFFSET;


	uintptr_t AdressPosX = FindDMAAddy(Proc.Handle, Proc.DynamicPoiterBaseModule, Pointer_Offset.XArray[0]);

	uintptr_t AdressPosY = FindDMAAddy(Proc.Handle, Proc.DynamicPoiterBaseModule, Pointer_Offset.YArray[0]);

	float PosX = 0;
	float PosY = 0;

	map Map = GetMapStats(Proc.Handle, Proc.ModuleBase);


	while (window.isOpen()) {
		window.clear(sf::Color::Black);

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::LControl)
				{

					std::cout << "Refresh... " << std::endl;

					CloseHandle(Proc.Handle);

					Proc.Id = GetProcId(L"Among Us.exe");
					Proc.Handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, Proc.Id);
					Proc.ModuleBase = GetModuleBaseAddress(Proc.Id, L"GameAssembly.dll");
					Proc.DynamicPoiterBaseModule = Proc.ModuleBase + DYNAMIC_BASE_OFFSET;

					AdressPosX = FindDMAAddy(Proc.Handle, Proc.DynamicPoiterBaseModule, Pointer_Offset.XArray[0]);

					AdressPosY = FindDMAAddy(Proc.Handle, Proc.DynamicPoiterBaseModule, Pointer_Offset.YArray[0]);

					Map = GetMapStats(Proc.Handle, Proc.ModuleBase);

					std::cout << "\nProcId : " << Proc.Id << std::endl;

					std::cout << "Pointer Base Module : " << std::hex << Proc.DynamicPoiterBaseModule << std::endl;

					std::cout << "Adresse PosX : " << std::hex << AdressPosX << std::endl;
					std::cout << "Adresse PosY : " << std::hex << AdressPosY << std::endl;
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus())
			{			
				float MouseX = sf::Mouse::getPosition(window).x;
				float MouseY = sf::Mouse::getPosition(window).y;

				float NewX = mapping(MouseX, 0, LARGEUR_FENETRE, Map.minX, Map.maxX);
				float NewY = mapping(MouseY, 0, HAUTEUR_FENETRE, Map.maxY, Map.minY);


				std::cout << "\nNewX : " << (float)NewX << std::endl;
				std::cout << "NewY : " << (float)NewY << std::endl;

				WriteProcessMemory(Proc.Handle, (BYTE*)AdressPosX, &NewX, sizeof(NewX), 0);
				WriteProcessMemory(Proc.Handle, (BYTE*)AdressPosY, &NewY, sizeof(NewY), 0);

			}

		}


		ReadProcessMemory(Proc.Handle, (BYTE*)AdressPosX, &PosX, sizeof(PosX), 0);
		ReadProcessMemory(Proc.Handle, (BYTE*)AdressPosY, &PosY, sizeof(PosY), 0);

		PosX = mapping(PosX, Map.minX, Map.maxX, 0, LARGEUR_FENETRE);
		PosY = mapping(PosY, Map.maxY, Map.minY, 0, HAUTEUR_FENETRE);

		//std::cout << "\nPos X : " << PosX << std::endl;
		//std::cout << "Pos Y : " << PosY << std::endl;


		afficher_sprite(&window, &map_sprite, map_texture, 0, 0);
		afficher_sprite(&window, &player_sprite, player_texture, PosX, PosY);

		window.display();
	}
	return EXIT_SUCCESS;
}