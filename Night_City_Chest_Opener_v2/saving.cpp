#include <fstream>
#include "Utils.h"
#include "Saving.h"
#include <iostream>

void saveWeapon(const Firearm& firearm)
{
	static int firearmid{};
	++firearmid;

	std::ofstream save{ "save.txt", std::ios::app };

	if (!save)
	{
		std::cerr << "Save.txt could not be opened for writing.\n";
		return;
	}

	save << "WeaponID: F" << firearmid << '\n';

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

	save << "Price: " << firearm.getPrice() << " Eurodollars" << "\n\n";
}

void saveWeapon(const MeleeWeapon& melee)
{
	static int meleeid{};
	++meleeid;

	std::ofstream save{ "save.txt", std::ios::app };

	if (!save)
	{
		std::cerr << "Save.txt could not be opened for writing.\n";
		return;
	}

	save << "WeaponID: M" << meleeid << '\n';

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

	save << "Price: " << melee.getPrice() << " Eurodollars" << "\n\n";
}

void saveWeapon(const Grenade& grenade)
{
	static int grenadeid{};
	++grenadeid;

	std::ofstream save{ "save.txt", std::ios::app };

	if (!save)
	{
		std::cerr << "Save.txt could not be opened for writing.\n";
		return;
	}

	save << "WeaponID: G" << grenadeid << '\n';

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

	save << "\nPrice: " << grenade.getPrice() << " Eurodollars" << "\n\n";
}

