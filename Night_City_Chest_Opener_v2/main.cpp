// add bug fix for ";" in save file on deletion
// add input sanitization

#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include "Random.h"
#include "Utils.h"
#include "Saving.h"

int main()
{
	std::cout << "Hello, welcome to the Night City Chest Opener.\nWhat is your name? ";
	std::string username{};
	std::cin >> username;

	std::cout << "What do you want to do, " << username << "?" << "\n1.Create a new weapon\n2.Browse save\n3.Quit\n";
	int input{};
	do
	{
		std::cin >> input;
	} 
	while (input < 1 && input > 3);

	while (input == 1 || input == 2 )
	{
		if (input == 1)
		{
			newlineSpam();

			WeaponCreationTools::WeaponType type{ WeaponCreationTools::generateRandomType() };
			WeaponCreationTools::Rarity rarity{ WeaponCreationTools::getRandomRarity() };

			if (rarity == WeaponCreationTools::exotic)
			{
				std::cout << "You got an exotic weapon.\n";
				if (type >= WeaponCreationTools::HG && type <= WeaponCreationTools::RL)
					std::cout << "Check the Firearm Exotic List, index " << WeaponCreationTools::dieThrow(100) + 1 << ". Congratulations.\n";
				else
					std::cout << "Check the Melee Weapon Exotic List, index " << WeaponCreationTools::dieThrow(100) + 1 << ". Congratulations.\n";
			}

			else
			{
				if (type >= WeaponCreationTools::HG && type <= WeaponCreationTools::RL)
				{
					Firearm firearm{ type, rarity };
					std::cout << firearm;

					std::cout << "Would you like to save this weapon(y/n)? ";
					char saveinput{};
					std::cin >> saveinput;

					if (saveinput == 'y')
						saveWeapon(firearm, username);
				}

				if (type >= WeaponCreationTools::Melee && type <= WeaponCreationTools::VH_Melee)
				{
					MeleeWeapon melee{ type, rarity };
					std::cout << melee;

					std::cout << "Would you like to save this weapon(y/n)? ";
					char saveinput{};
					std::cin >> saveinput;

					if (saveinput == 'y')
						saveWeapon(melee, username);
				}

				if (type >= WeaponCreationTools::Util_G && type <= WeaponCreationTools::Pers_G)
				{
					Grenade grenade{ type, rarity };
					std::cout << grenade;

					std::cout << "Would you like to save this weapon(y/n)? ";
					char saveinput{};
					std::cin >> saveinput;

					if (saveinput == 'y')
						saveWeapon(grenade, username);
				}
			}

			std::cout << "\n\nWould you like to generate another weapon?\n1. Yes 2.No\n";
			std::cin >> input;
		}

		if (input == 2)
		{
			browseSaveFile(username);
		}

		std::cout << "What do you want to do, " << username << "?" << "\n1.Create a new weapon\n2.Browse save\n3.Quit\n";
		std::cin >> input;
	}

	return 0;
}