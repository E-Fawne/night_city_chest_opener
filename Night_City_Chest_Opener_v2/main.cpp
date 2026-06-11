// 1.	Definir s'il s'agit d'une arme a feu ou a de corps a corps
// 2.	Prendre la valeur de rarete, entre 1 et 100
// 2.1	Si la valeur est entre 96 et 100, faire un jet de 1 a 100 et skip a 6.
// 3.	Definir le type d'arme, entre 1 et 12 pour les armes a feu et entre 1 et 4 pour les armes de corps a corps
// 4.	Definir les parties d'armes en fonction du type d'arme
// 5.	Definir le prefix
// 6.	Etablir les stats d'arme
// 7.	Definir, si besoin, les speciaux
// 8.	Afficher l'arme finale avec toutes ses stats

#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include "Random.h"
#include "Utils.h"
#include "Saving.h"

int main()
{
	std::cout << "Hello, welcome to the Night City Chest Opener.\nWhat do you want to do?\n1. Create a new weapon\n2. Browse save\n3. Quit\n";
	int input{};
	do
	{
		std::cin >> input;
	} 
	while (input < 1 && input > 3);

	if (input == 2)
	{
		browseSaveFile();
	}

	while (input == 1)
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
					saveWeapon(firearm);
			}

			if (type >= WeaponCreationTools::Melee && type <= WeaponCreationTools::VH_Melee)
			{
				MeleeWeapon melee{ type, rarity };
				std::cout << melee;

				std::cout << "Would you like to save this weapon(y/n)? ";
				char saveinput{};
				std::cin >> saveinput;

				if (saveinput == 'y')
					saveWeapon(melee);
			}

			if (type >= WeaponCreationTools::Util_G && type <= WeaponCreationTools::Pers_G)
			{
				Grenade grenade{ type, rarity };
				std::cout << grenade;

				std::cout << "Would you like to save this weapon(y/n)? ";
				char saveinput{};
				std::cin >> saveinput;

				if (saveinput == 'y')
					saveWeapon(grenade);
			}
		}

			std::cout << "\n\nWould you like to generate another weapon?\n1. Yes 2.No\n";
			std::cin >> input;
	}

	return 0;
}