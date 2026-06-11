#include <fstream>
#include <string>
#include "Utils.h"
#include "Saving.h"
#include <iostream>

int getID(char type, std::string username)
{
	std::string usernamecopy{ username };
	std::string userfile{ usernamecopy.insert(username.size() , ".txt") };
	std::fstream save{ userfile };
	int ID{0};

	if (!save)
	{
		std::cerr << username << ".txt could not be opened.\n";
		return -1;
	}

	while (true)
	{
		if (save.eof())
			break;

		if (!save)
			break;

		save.ignore(std::numeric_limits<std::streamsize>::max(), '#');

		if (save.peek() == type)
		{
			save.ignore(1);
			std::string str{};
			std::getline(save, str);
			
			if (std::stoi(str) > ID)
				ID = std::stoi(str);
		}
	}

	return ID;
}

void saveWeapon(const Firearm& firearm, std::string username)
{
	std::string usernamecopy{ username };
	std::string userfile{ usernamecopy.insert(username.size() , ".txt")};
	std::ofstream save{ userfile, std::ios::app };

	static int firearmID{getID('F', username)};
	++firearmID;

	if (!save)
	{
		std::cerr << username << ".txt could not be opened for writing.\n";
		return;
	}

	save << "WeaponID: #F" << firearmID << '\n';

	using namespace WeaponCreationTools;
	save << getRarityText(firearm.getRarity()) << " " << getTypeText(firearm.getType()) << '\n';
	save << "Affix: " << firearm.getPrefix() << '\n';
	save << "Manufacturer: " << getBrandText(firearm.m_body.getBrand()) << '\n';

	save << "Body: " << getBrandText(firearm.m_body.getBrand()) << " | Grip: " << getBrandText(firearm.m_grip.getBrand()) << " | Barrel: " << getBrandText(firearm.m_barrel.getBrand())
		<< " | Scope: " << getBrandText(firearm.m_scope.getBrand()) << " | Stock: " << getBrandText(firearm.m_stock.getBrand()) << '\n';
	save << "Hands: " << firearm.getHands() << "\n\n";

	save << "Damage: " << firearm.getDamage() << "D6 " << (firearm.getDamageExtra() < 0 ? "" : "+ ") << firearm.getDamageExtra() << '\n';
	save << "Magasine: " << static_cast<int>(firearm.m_mag) << " (" << firearm.m_ammoType << ")" << '\n';
	save << "Fire rate: " << firearm.m_fireRate << '\n';
	save << "Accuracy: " << firearm.m_accuracy << '\n';
	save << "Skill Bonus: " << firearm.getSkillBonus() << " (" << firearm.getSkillType() << ")" << '\n';
	save << "Special Bonus: " << firearm.getSpecialBonus() << "\n\n";

	save << "Concealable: " << (firearm.getConcealable() ? "Yes" : "No") << " (" << firearm.getConcealBonus() << ")" << '\n';
	save << "Special: " << firearm.m_weaponSpecial << '\n' << firearm.m_brandSpecial << '\n' << firearm.m_malorianSpecial2 << "\n\n";

	save << "Price: " << firearm.getPrice() << " Eurodollars" << "\n\n;";
}

void saveWeapon(const MeleeWeapon& melee, std::string username)
{
	std::string usernamecopy{ username };
	std::string userfile{ usernamecopy.insert(username.size() , ".txt")};
	std::ofstream save{ userfile, std::ios::app };

	static int meleeID{getID('M', username)};
	++meleeID;

	if (!save)
	{
		std::cerr << username << ".txt could not be opened for writing.\n";
		return;
	}

	save << "WeaponID: #M" << meleeID << '\n';

	using namespace WeaponCreationTools;
	save << getRarityText(melee.getRarity()) << " " << getTypeText(melee.getType()) << '\n';
	save << "Affix: " << melee.getPrefix() << '\n';
	save << "Manufacturer: " << getBrandText(melee.m_material.getBrand()) << '\n';

	save << "Material: " << getBrandText(melee.m_material.getBrand()) << " | Grip: " << getBrandText(melee.m_grip.getBrand()) << " | Body: " << getBrandText(melee.m_body.getBrand()) << '\n';
	save << "Hands: " << melee.getHands() << "\n\n";

	save << "Damage: " << melee.getDamage() << "D6 " << (melee.getDamageExtra() < 0 ? "" : "+ ") << melee.getDamageExtra() << '\n';
	save << "Attack Speed: " << melee.m_attackSpeed << '\n';
	save << "Handling: " << melee.m_handling << '\n';
	save << "Skill Bonus: " << melee.getSkillBonus() << " (" << melee.getSkillType() << ")" << '\n';
	save << "Special Bonus: " << melee.getSpecialBonus() << "\n\n";

	save << "Concealable: " << (melee.getConcealable() ? "Yes" : "No") << " (" << melee.getConcealBonus() << ")" << '\n';
	save << "Throwable: " << (melee.m_throwable ? "Yes" : "No") << '\n';
	save << "Special: " << melee.m_brandSpecial << "\n\n";

	save << "Price: " << melee.getPrice() << " Eurodollars" << "\n\n;";
}

void saveWeapon(const Grenade& grenade, std::string username)
{
	std::string usernamecopy{ username };
	std::string userfile{ usernamecopy.insert(username.size(), ".txt")};
	std::ofstream save{ userfile, std::ios::app };

	static int grenadeID{getID('G', username)};
	++grenadeID;

	if (!save)
	{
		std::cerr << username << ".txt could not be opened for writing.\n";
		return;
	}

	save << "WeaponID: #G" << grenadeID << '\n';

	using namespace WeaponCreationTools;
	save << getRarityText(grenade.getRarity()) << " " << getTypeText(grenade.getType()) << '\n';
	save << "Manufacturer: " << getBrandText(grenade.m_reagent.getBrand()) << '\n';
	save << "Special: " << grenade.m_grenadeSpecifics << "\n\n";

	save << "Reagent: " << getBrandText(grenade.m_reagent.getBrand()) << " | Fuse: " << getBrandText(grenade.m_fuse.getBrand()) << " | Body: " << getBrandText(grenade.m_body.getBrand()) << "\n\n";

	save << "Damage: " << grenade.getDamage() << "D6 " << (grenade.getDamageExtra() < 0 ? "" : "+ ") << grenade.getDamageExtra() << '\n';
	save << "Fuse Timer: " << grenade.m_fuseTimer << '\n';
	save << "Radius: " << grenade.m_radius << '\n';
	save << "Duration: " << grenade.m_duration << '\n';
	save << "Special Bonus: " << grenade.getSpecialBonus() << '\n';

	save << "\nPrice: " << grenade.getPrice() << " Eurodollars" << "\n\n;";
}

void browseSaveFile(std::string username)
{
	std::cout << "Which type of weapon do you want to browse?\n1. Firearms\n2. Melee Weapons\n3. Grenades\n";
	int input{};
	std::cin >> input;

	std::string usernamecopy{ username };
	std::string userfile(usernamecopy.insert(username.size(), ".txt"));
	std::ifstream save{ userfile};

	if (!save)
	{
		std::cerr << username << ".txt could not be opened for reading.\n";
		return;
	}

	while (true)
	{
		save.ignore(std::numeric_limits<std::streamsize>::max(), '#');
		
		if (save.eof())
		{
			std::cout << "You have seen all of your weapons. Would you like to go again?(y/n) ";
			char again{};
			std::cin >> again;

			if (again == 'y')
				save.seekg(0, std::ios::beg);

			else
				break;
		}

		if (input == 1)
		{
			if (save.peek() == 'F')
			{
				newlineSpam();
				std::string str{};
				std::getline(save, str, ';');
				std::cout << "WeaponID: " << str;

				std::cout << "next ->(n) / quit x(q)\n";
				char browseInput{};
				std::cin >> browseInput;

				if (browseInput == 'n')
					continue;

				else if (browseInput == 'q')
					break;
			}
		}
		if (input == 2)
		{
			if (save.peek() == 'M')
			{
				newlineSpam();
				std::string str{};
				std::getline(save, str, ';');
				std::cout << "WeaponID: " << str;

				std::cout << "next ->(n) / quit x(q)\n";
				char browseInput{};
				std::cin >> browseInput;

				if (browseInput == 'n')
					continue;

				else if (browseInput == 'q')
					break;
			}
		}
		if (input == 3)
		{
			if (save.peek() == 'G')
			{
				newlineSpam();
				std::string str{};
				std::getline(save, str, ';');
				std::cout << "WeaponID: " << str;

				std::cout << "next ->(n) / quit x(q)\n";
				char browseInput{};
				std::cin >> browseInput;

				if (browseInput == 'n')
					continue;

				else if (browseInput == 'q')
					break;
			}
		}
	}
}