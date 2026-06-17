#include <fstream>
#include <span>
#include <string>
#include "Utils.h"
#include "Saving.h"
#include <iostream>
#include <filesystem>

int getID(char type, std::string username)
{
	std::fstream save{ username + ".txt"};
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

int prefixToNum(std::string_view prefix)
{
	if (prefix.empty())
		return 0;

	else if (prefix == "Accurate: Aimed shot with advantage")
		return 1;

	else if (prefix == "Stable: Auto shot with advantage")
		return 2;

	else if (prefix == "High caliber: One advantage die on damage")
		return 3;

	else if (prefix == "Wieldy: Accuracy bonus")
		return 4;

	else if (prefix == "Fast: Fire rate bonus")
		return 5;

	else if (prefix == "Unstoppable: Shoots through cover")
		return 6;

	else if (prefix == "Penetrating: Doubles damage on armor")
		return 7;

	else if (prefix == "Accurate: Aimed hit with advantage")
		return 8;

	else if (prefix == "Stable: Throw with advantage")
		return 9;

	else if (prefix == "Sharp: One advantage die on damage")
		return 10;

	else if (prefix == "Wieldy: Handling bonus")
		return 11;

	else if (prefix == "Fast: Attack speed bonus")
		return 12;

	else if (prefix == "Handmade: Doubles the bonus on any parts that share the same brand as the weapon")
		return 13;

	else if (prefix == "Penetrating: Ignores armor")
		return 14;

	else
		return -1;
}

std::string_view numToPrefix(std::string prefixNum)
{
	int prefix{ std::stoi(prefixNum)};
	
	switch (prefix)
	{
	case 0:		return "";
	case 1:		return "Accurate: Aimed shot with advantage";
	case 2:		return "Stable: Auto shot with advantage";
	case 3:		return "High caliber: One advantage die on damage";
	case 4:		return "Wieldy: Accuracy bonus";
	case 5:		return "Fast: Fire rate bonus";
	case 6:		return "Unstoppable: Shoots through cover";
	case 7:		return "Penetrating: Doubles damage on armor";
	case 8:		return "Accurate: Aimed hit with advantage";
	case 9:		return "Stable: Throw with advantage";
	case 10:	return "Sharp: One advantage die on damage";
	case 11:	return "Wieldy: Handling bonus";
	case 12:	return "Fast: Attack speed bonus";
	case 13:	return "Handmade: Doubles the bonus on any parts that share the same brand as the weapon";
	case 14:	return "Penetrating: Ignores armor";
	default:	return "ERROR numToPrefix()";
	}
}

std::string firearmBrandSpecialToText(std::string brandSpecial)
{
	if (brandSpecial == "MIL")
		return "Quickswap";

	else if (brandSpecial == "ARA")
		return "Smart Bullets";

	else if (brandSpecial == "GMI")
		return "Self-Destruct";

	else if (brandSpecial == "TSU")
		return "Interface Spotter";

	else if (brandSpecial == "NOV")
		return "Horsepower";

	else if (brandSpecial == "DAI")
		return "Hit it";

	else if (brandSpecial == "CON")
		return "Safety Off";

	else if (brandSpecial == "TRU")
		return "Burst Fire";

	else if (brandSpecial == "SAN")
		return "Stylish";

	else if (brandSpecial == "ROS")
		return "E-Z-Swap";

	else if (brandSpecial.substr(0, 3) == "HSD")
		return firearmHSDMALexcept(brandSpecial);

	else if (brandSpecial.substr(0, 3) == "MAL")
		return firearmHSDMALexcept(brandSpecial);

	else
		return "Error firearmBrandSpecialToText()";
}

std::string firearmHSDMALexcept(std::string brandSpecial)
{
	if (brandSpecial == "MAL01")
		return "Ammo Mod:\nTracer: Every consecutive hit on the same target gives you a bonus (of 1) to hit rate on them";

	else if (brandSpecial == "MAL02")
		return "Ammo Mod:\nHollow Point: The number of perfect rolls to inflict a serious injury is reduced by 1";

	else if (brandSpecial == "MAL03")
		return "Ammo Mod:\nSubsonic: Your shots are harder to track";

	else if (brandSpecial == "MAL04")
		return "Ammo Mod:\nPiercing: Ignores half of armor (and cover)";

	else if (brandSpecial == "MAL05")
		return "Ammo Mod:\nFull Metal Jacket: Standard Malorian issued round";

	else if (brandSpecial == "MAL06")
		return "Ammo Mod:\nHigh Velocity: Multiplies the effective distances of the round by 2";

	else if (brandSpecial == "MAL07")
		return "Ammo Mod:\nBuckshot: Acts like the standard shotgun Buckshot";

	else if (brandSpecial == "MAL08")
		return "Ammo Mod:\nRubber: Non-lethal, same damage";

	else if (brandSpecial == "HSD1")
		return "Chem Warfare:\nEMP: Adds an extra EMP explosion which deactivate any electrical system touched by the bullet";

	else if (brandSpecial == "HSD2")
		return "Chem Warfare:\nAcid: Adds an extra damage on time effect to the round, equal to setting the target on fire (but doubled on metal)";

	else if (brandSpecial == "HSD3")
		return "Chem Warfare:\nNeurotoxin: Any damage inflicted by this weapon is, instead, removed from maximum health total (Only an expensive operation can fix that)";

	else if (brandSpecial == "HSD4")
		return "Chem Warfare:\nNapalm: Sets the target on fire";

	else if (brandSpecial == "HSD5")
		return "Chem Warfare:\nSleeping gas: The target has to resist torture/drugs (DV defined by the quality of the weapon) in order to not fall asleep";

	else if (brandSpecial == "HSD6")
		return "Chem Warfare:\nNanomachines: Nanomachines that can be reprogrammed to do simple tasks on electrical components";

	else if (brandSpecial == "HSD7")
		return "Chem Warfare:\nSticky: Extremely sticky solution that disturbs movement";

	else if (brandSpecial == "HSD8")
		return "Chem Warfare:\nNeuropsychotic: Any damage inflicted is replicated on Humanity";

	else
		return "Error firearmHSDMALexcept()";
}

std::string MALexcept2(std::string brandSpecial)
{
	if (brandSpecial == "01")
		return "Ammo Mod:\nTracer: Every consecutive hit on the same target gives you a bonus (of 1) to hit rate on them";

	else if (brandSpecial == "02")
		return "Ammo Mod:\nHollow Point: The number of perfect rolls to inflict a serious injury is reduced by 1";

	else if (brandSpecial == "03")
		return "Ammo Mod:\nSubsonic: Your shots are harder to track";

	else if (brandSpecial == "04")
		return "Ammo Mod:\nPiercing: Ignores half of armor (and cover)";

	else if (brandSpecial == "05")
		return "Ammo Mod:\nFull Metal Jacket: Standard Malorian issued round";

	else if (brandSpecial == "06")
		return "Ammo Mod:\nHigh Velocity: Multiplies the effective distances of the round by 2";

	else if (brandSpecial == "07")
		return "Ammo Mod:\nBuckshot: Acts like the standard shotgun Buckshot";

	else if (brandSpecial == "08")
		return "Ammo Mod:\nRubber: Non-lethal, same damage";

	else
		return "";
}

std::string meleeArasakaSpecialToText(std::string brandSpecial)
{
	if (brandSpecial == "ARA1")
		return "Iai:\nVersatile: While fighting, +2 to any throw if the weapon was unsheathed this turn";

	else if (brandSpecial == "ARA2")
		return "Iai:\nTrue Slice: The next attack after unsheathing gets an extra damage die";

	else if (brandSpecial == "ARA3")
		return "Iai:\nFast Strike: You get a free attack after unsheathing";

	else if (brandSpecial == "ARA4")
		return "Iai:\nCharge: The turn you unsheath, you can Charge, which allows you to move an extra time and attack";

	else if (brandSpecial == "ARA5")
		return "Iai:\nTranquil Strike : The next attack after unsheathing cannot miss";

	else if (brandSpecial == "ARA6")
		return "Iai:\nTerror: Unsheathing triggers a Staredown event within which you may not receive any negative effects";

	else if (brandSpecial == "ARA7")
		return "Iai:\nReaction: You may unsheath this weapon as a response to any attack and parry it (this action takes your turn)";

	else if (brandSpecial == "ARA8")
		return "Iai:\nAccurate Slice: The penalty on any aimed attack following the unsheathing is nullified";

	else
		return "Error meleeArasakaSpecialToText()";
}

std::string meleeBrandSpecialToText(std::string brandSpecial)
{
	if (brandSpecial == "MIL")
		return "Feint";

	else if (brandSpecial == "KEN")
		return "Armor Shred";

	else if (brandSpecial == "EVW")
		return "Tool";

	else if (brandSpecial == "SAN")
		return "Stylish";

	else if (brandSpecial == "SDI")
		return "Natural";

	else if (brandSpecial.substr(0,3) == "ARA")
		return meleeArasakaSpecialToText(brandSpecial);

	else
		return "Error meleeBrandSpecialToText()";
}

std::string grenadeSpecificsToText(std::string grenadeSpecifics)
{
	if (grenadeSpecifics.substr(0, 3) == "GMI")
	{
		if (grenadeSpecifics.substr(0, 6) == "GMI&UG")
		{
			if (grenadeSpecifics == "GMI&UG01")
				return "Firesmoke\nGenerates a thin smoke that irritates the throat";

			else if (grenadeSpecifics == "GMI&UG02")
				return "Noise Machine\nGenerates a constant noise that distacts foes out of combat";

			else if (grenadeSpecifics == "GMI&UG03")
				return "Stinky Bomb\nCreates a foul odor that can make people throw up";
		}
		else if (grenadeSpecifics.substr(0, 6) == "GMI&EG")
		{
			if (grenadeSpecifics == "GMI&EG01")
				return "Pipebomb\nClassic grenade, if not low quality";

			else if (grenadeSpecifics == "GMI&EG02")
				return "Unstable\nExplodes into light shrapnel, allowing you to ignore half of armor";

			else if (grenadeSpecifics == "GMI&EG03")
				return "Super Sensitive Mine\nExplodes on light contact or perturbation";
		}
	}

	else if (grenadeSpecifics.substr(0, 3) == "CTE")
	{
		if (grenadeSpecifics.substr(0, 6) == "CTE&UG")
		{
			if (grenadeSpecifics == "CTE&UG01")
				return "EMP\nTemporarily disables any electronics";

			else if (grenadeSpecifics == "CTE&UG02")
				return "Ear Disabler\nGenerates a loud high pitched noise that temporarily reduces or disables hearing";

			else if (grenadeSpecifics == "CTE&UG03")
				return "Deflector\nCreates a magnetic field that temporarily pushes back any metallic objets, making you harder to hit";
		}

		else if (grenadeSpecifics.substr(0, 6) == "CTE&PG")
		{
			if (grenadeSpecifics == "CTE&PG01")
				return "Pulse EMP\nPulses an EMP field each turn, disabling electronics for this turn";

			else if (grenadeSpecifics == "CTE&PG02")
				return "Incendiary\nStandard incendiary grenade";

			else if (grenadeSpecifics == "CTE&PG03")
				return "Pulse Ear Disabler\nLiberates a high pitched loud noise every turn, disabling hearing";
		}
	}

	else if (grenadeSpecifics.substr(0, 3) == "HSD")
	{
		if (grenadeSpecifics.substr(0, 6) == "HSD&UG")
		{
			if (grenadeSpecifics == "HSD&UG01")
				return "Sleeping Gas\nConstantly exhales a sleeping agent that forces any foe to fall unconscious";

			else if (grenadeSpecifics == "HSD&UG02")
				return "Slippery Solution\nExplodes into a slippery liquid that makes every action more difficult";

			else if (grenadeSpecifics == "HSD&UG03")
				return "Sticky Bomb\nExplodes into a pool of quick hardening material that acts like cement once hardened";
		}

		else if (grenadeSpecifics.substr(0, 6) == "HSD&PG")
		{
			if (grenadeSpecifics == "HSD&PG01")
				return "Acid Spray\nSprays acid each turn, coating anyone with it, damage is doubled on metal";

			else if (grenadeSpecifics == "HSD&PG02")
				return "Electric Field\nGenerates a constant electric field, damage is doubled on electronics";

			else if (grenadeSpecifics == "HSD&PG03")
				return "Irradiated Gas\nCreates a thick radioactive smoke that quickly deteriorates any living thing";
		}
	}
	
	else if (grenadeSpecifics.substr(0, 3) == "KTC")
	{
		if (grenadeSpecifics.substr(0, 6) == "KTC&UG")
		{
			if (grenadeSpecifics == "KTC&UG01")
				return "Flashbang\nExplodes into a ball of bright light that temporarily blinds foes";

			else if (grenadeSpecifics == "KTC&UG02")
				return "Push Field\nCreates a harsh force field that pushes anything in its path";

			else if (grenadeSpecifics == "KTC&UG03")
				return "Electronics Resetter\nSends an electric signal forcing any electronics to fully restart";
		}

		else if (grenadeSpecifics.substr(0, 6) == "KTC&EG")
		{
			if (grenadeSpecifics == "KTC&EG01")
				return "Explosive Charge\nRemotely activated charge";

			else if (grenadeSpecifics == "KTC&EG02")
				return "Thermite Bomb\nExplodes and frees thermite anyone caught in the blast, setting them on fire";

			else if (grenadeSpecifics == "KTC&EG03")
				return "Surface Grenade\nDamages foes on a surface level, allowing the environment to be unharmed";
		}
	}

	else if (grenadeSpecifics.substr(0, 3) == "MIL")
	{
		if (grenadeSpecifics.substr(0, 6) == "MIL&UG")
		{
			if (grenadeSpecifics == "MIL&UG01")
				return "Smoke\nGenerates a thick wall of smoke";

			else if (grenadeSpecifics == "MIL&UG02")
				return "Nerve Agent\nGradually damages the humanity of anyone inside the radius";

			else if (grenadeSpecifics == "MIL&UG03")
				return "Ping Grenade\nStealth grenade that quietly detonates and gives you a full view of its radius";
		}

		else if (grenadeSpecifics.substr(0, 6) == "MIL&EG")
		{
			if (grenadeSpecifics == "MIL&EG01")
				return "Frag Grenade\nStandard issued Militech grenade";

			else if (grenadeSpecifics == "MIL&EG02")
				return "Claymore\nDetects any foe in a direct line and explodes in the same radius";

			else if (grenadeSpecifics == "MIL&EG03")
				return "Heat Seeking Grenade\nThis grenades autocorrects its trajectory towards the closest heat source";
		}
	}

	else if (grenadeSpecifics.substr(0, 3) == "GLC")
	{
		if (grenadeSpecifics.substr(0, 6) == "GLC&EG")
		{
			if (grenadeSpecifics == "GLC&EG01")
				return "Shrapnel\nExplodes into rasor sharp sharpnel, allowing you to ignore any and all armor";

			else if (grenadeSpecifics == "GLC&EG02")
				return "Spike Wall\nGrows spikes in its radius";

			else if (grenadeSpecifics == "GLC&EG03")
				return "Targetted Wounder\nHas a higher chance of causing a chosen wound";
		}

		else if (grenadeSpecifics.substr(0, 6) == "GLC&PG")
		{
			if (grenadeSpecifics == "GLC&PG01")
				return "Spikes\nFrees spikes on the ground, damaging anyone stepping in the area";

			else if (grenadeSpecifics == "GLC&PG02")
				return "Senbon\nSends flying projectile each turn, wounding anyone in the area";

			else if (grenadeSpecifics == "GLC&PG03")
				return "Rasor Wire\nCreates long lines of rasor wire that attaches to anything, wounding on movement";
		}
	}

	return "Error grenadeSpecificsToText()";
}

Firearm readFirearmSerialNumber(std::string serialNumber)
{
	// #TYPE_ID - TYPE - RARITY - BODY - BARREL - GRIP - SCOPE - STOCK - PREFIX - BRAND_SPECIAL
	using namespace WeaponCreationTools;

	serialNumber.erase(0, serialNumber.find('-') + 1);
	WeaponType type{ static_cast<WeaponType>(std::stoi(serialNumber.substr(0, serialNumber.find('-'))))};

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Rarity rarity{ static_cast<Rarity>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Part body{ static_cast<BrandName>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Part barrel{ static_cast<BrandName>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Part grip{ static_cast<BrandName>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Part scope{ static_cast<BrandName>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Part stock{ static_cast<BrandName>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('P') + 1);
	std::string prefix{ numToPrefix(serialNumber.substr(0, serialNumber.find('-') + 1)) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	std::string brandSpecial{ firearmBrandSpecialToText(serialNumber.substr(0, serialNumber.find('-'))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	std::string malorianSpecial2{ MALexcept2(serialNumber) };

	return Firearm{ type, rarity, body, barrel, scope, grip, stock, prefix, brandSpecial, malorianSpecial2 };
}

MeleeWeapon readMeleeSerialNumber(std::string serialNumber)
{
	// TYPE_ID - TYPE - RARITY - MATERIAL - GRIP - BODY - PREFIX - BRAND_SPECIAL
	using namespace WeaponCreationTools;

	serialNumber.erase(0, serialNumber.find('-') + 1);
	WeaponType type{ static_cast<WeaponType>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Rarity rarity{ static_cast<Rarity>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Part material{ static_cast<BrandName>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Part grip{ static_cast<BrandName>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Part body{ static_cast<BrandName>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('P') + 1);
	std::string prefix{ numToPrefix(serialNumber.substr(0, serialNumber.find('-') + 1)) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	std::string brandSpecial{ meleeBrandSpecialToText(serialNumber) };

	return MeleeWeapon{ type, rarity, material, grip, body, prefix, brandSpecial };
}

Grenade readGrenadeSerialNumber(std::string serialNumber)
{
	// TYPE_ID - TYPE - RARITY - REAGENT - BODY - FUSE - SPECIFICS
	using namespace WeaponCreationTools;

	serialNumber.erase(0, serialNumber.find('-') + 1);
	WeaponType type{ static_cast<WeaponType>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Rarity rarity{ static_cast<Rarity>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Part reagent{ static_cast<BrandName>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Part body{ static_cast<BrandName>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	Part fuse{ static_cast<BrandName>(std::stoi(serialNumber.substr(0, serialNumber.find('-')))) };

	serialNumber.erase(0, serialNumber.find('-') + 1);
	std::string grenadeSpecifics{grenadeSpecificsToText(serialNumber)};

	return Grenade{ type, rarity, reagent, body, fuse, grenadeSpecifics };
}

std::string brandSpecialToString(const Firearm& firearm)
{
	std::string brandSpecial{};
	using namespace WeaponCreationTools;

	switch (firearm.m_body.getBrand())
	{
	case militech:			brandSpecial = "MIL"; break;
	case arasaka:			brandSpecial = "ARA"; break;
	case gunmart:			brandSpecial = "GMI"; break;
	case tsunami:			brandSpecial = "TSU"; break;
	case nova:				brandSpecial = "NOV"; break;
	case dai_lung:			brandSpecial = "DAI"; break;
	case constitution:		brandSpecial = "CON"; break;
	case techtronika:		brandSpecial = "TRU"; break;
	case sanroo:			brandSpecial = "SAN"; break;
	case hydrosubsidium:	brandSpecial = "HSD"; break;
	case rostovic:			brandSpecial = "ROS"; break;
	case malorian:			brandSpecial = "MAL"; break;
	default:				brandSpecial = "NUL"; break;
	}

	if (brandSpecial == "MAL" || brandSpecial == "HSD")
	{
		if (brandSpecial == "MAL")
		{
			// For first Malorian Special
			if (firearm.m_brandSpecial == "Ammo Mod:\nTracer: Every consecutive hit on the same target gives you a bonus (of 1) to hit rate on them")
				brandSpecial += "01";

			else if (firearm.m_brandSpecial == "Ammo Mod:\nHollow Point: The number of perfect rolls to inflict a serious injury is reduced by 1")
				brandSpecial += "02";

			else if (firearm.m_brandSpecial == "Ammo Mod:\nSubsonic: Your shots are harder to track")
				brandSpecial += "03";

			else if (firearm.m_brandSpecial == "Ammo Mod:\nPiercing: Ignores half of armor (and cover)")
				brandSpecial += "04";

			else if (firearm.m_brandSpecial == "Ammo Mod:\nFull Metal Jacket: Standard Malorian issued round")
				brandSpecial += "05";

			else if (firearm.m_brandSpecial == "Ammo Mod:\nHigh Velocity: Multiplies the effective distances of the round by 2")
				brandSpecial += "06";

			else if (firearm.m_brandSpecial == "Ammo Mod:\nBuckshot: Acts like the standard shotgun Buckshot")
				brandSpecial += "07";

			else if (firearm.m_brandSpecial == "Ammo Mod:\nRubber: Non-lethal, same damage")
				brandSpecial += "08";


			// For second Malorian Special
			if (firearm.m_malorianSpecial2 == "Ammo Mod:\nTracer: Every consecutive hit on the same target gives you a bonus (of 1) to hit rate on them")
				brandSpecial += "-01";

			else if (firearm.m_malorianSpecial2 == "Ammo Mod:\nHollow Point: The number of perfect rolls to inflict a serious injury is reduced by 1")
				brandSpecial += "-02";

			else if (firearm.m_malorianSpecial2 == "Ammo Mod:\nSubsonic: Your shots are harder to track")
				brandSpecial += "-03";

			else if (firearm.m_malorianSpecial2 == "Ammo Mod:\nPiercing: Ignores half of armor (and cover)")
				brandSpecial += "-04";

			else if (firearm.m_malorianSpecial2 == "Ammo Mod:\nFull Metal Jacket: Standard Malorian issued round")
				brandSpecial += "-05";

			else if (firearm.m_malorianSpecial2 == "Ammo Mod:\nHigh Velocity: Multiplies the effective distances of the round by 2")
				brandSpecial += "-06";

			else if (firearm.m_malorianSpecial2 == "Ammo Mod:\nBuckshot: Acts like the standard shotgun Buckshot")
				brandSpecial += "-07";

			else if (firearm.m_malorianSpecial2 == "Ammo Mod:\nRubber: Non-lethal, same damage")
				brandSpecial += "-08";
		}

		else if (brandSpecial == "HSD")
		{
			// For Hydrosubsidum special
			if (firearm.m_brandSpecial == "Chem Warfare:\nEMP: Adds an extra EMP explosion which deactivate any electrical system touched by the bullet")
				brandSpecial += '1';

			else if (firearm.m_brandSpecial == "Chem Warfare:\nAcid: Adds an extra damage on time effect to the round, equal to setting the target on fire (but doubled on metal)")
				brandSpecial += '2';

			else if (firearm.m_brandSpecial == "Chem Warfare:\nNeurotoxin: Any damage inflicted by this weapon is, instead, removed from maximum health total (Only an expensive operation can fix that)")
				brandSpecial += '3';

			else if (firearm.m_brandSpecial == "Chem Warfare:\nNapalm: Sets the target on fire")
				brandSpecial += '4';

			else if (firearm.m_brandSpecial == "Chem Warfare:\nSleeping gas: The target has to resist torture/drugs (DV defined by the quality of the weapon) in order to not fall asleep")
				brandSpecial += '5';

			else if (firearm.m_brandSpecial == "Chem Warfare:\nNanomachines: Nanomachines that can be reprogrammed to do simple tasks on electrical components")
				brandSpecial += '6';

			else if (firearm.m_brandSpecial == "Chem Warfare:\nSticky: Extremely sticky solution that disturbs movement")
				brandSpecial += '7';

			else if (firearm.m_brandSpecial == "Chem Warfare:\nNeuropsychotic: Any damage inflicted is replicated on Humanity")
				brandSpecial += '8';
		}
	}

	return brandSpecial;
}

std::string brandSpecialToString(const MeleeWeapon& melee)
{
	std::string brandSpecial{};
	using namespace WeaponCreationTools;

	switch (melee.m_material.getBrand())
	{
	case militech:			brandSpecial = "MIL"; break;
	case arasaka:			brandSpecial = "ARA"; break;
	case kendachi:			brandSpecial = "KEN"; break;
	case everest:			brandSpecial = "EVW"; break;
	case sanroo:			brandSpecial = "SAN"; break;
	case slamdance:			brandSpecial = "SDI"; break;
	default:				brandSpecial = "NUL"; break;
	}

	if (brandSpecial == "ARA")
	{
		if (melee.m_brandSpecial == "Iai:\nVersatile: While fighting, +2 to any throw if the weapon was unsheathed this turn")
			brandSpecial += '1';

		else if (melee.m_brandSpecial == "Iai:\nTrue Slice: The next attack after unsheathing gets an extra damage die")
			brandSpecial += '2';

		else if (melee.m_brandSpecial == "Iai:\nFast Strike: You get a free attack after unsheathing")
			brandSpecial += '3';

		else if (melee.m_brandSpecial == "Iai:\nCharge: The turn you unsheath, you can Charge, which allows you to move an extra time and attack")
			brandSpecial += '4';

		else if (melee.m_brandSpecial == "Iai:\nTranquil Strike: The next attack after unsheathing cannot miss")
			brandSpecial += '5';

		else if (melee.m_brandSpecial == "Iai:\nTerror: Unsheathing triggers a Staredown event within which you may not receive any negative effects")
			brandSpecial += '6';

		else if (melee.m_brandSpecial == "Iai:\nReaction: You may unsheath this weapon as a response to any attack and parry it (this action takes your turn)")
			brandSpecial += '7';

		else if (melee.m_brandSpecial == "Iai:\nAccurate Slice: The penalty on any aimed attack following the unsheathing is nullified")
			brandSpecial += '8';
	}

	return brandSpecial;
}

std::string specificsToString(const Grenade& grenade)
{
	using namespace WeaponCreationTools;

	std::string grenadeSpecifics{};
	switch (grenade.m_reagent.getBrand())
	{
	case gunmart:			grenadeSpecifics = "GMI"; break;
	case centurian:			grenadeSpecifics = "CTE"; break;
	case great_lakes:		grenadeSpecifics = "GLC"; break;
	case hydrosubsidium:	grenadeSpecifics = "HSD"; break;
	case ktech:				grenadeSpecifics = "KTC"; break;
	case militech:			grenadeSpecifics = "MIL"; break;
	default:				grenadeSpecifics = "NUL"; break;
	}

	switch (grenade.getType())
	{
	case Util_G:			grenadeSpecifics += "&UG"; break;
	case Explo_G:			grenadeSpecifics += "&EG"; break;
	case Pers_G:			grenadeSpecifics += "&PG"; break;
	default:				grenadeSpecifics += "&NUL"; break;
	}

	if (grenade.getType() == Util_G)
	{
		if (grenadeSpecifics == "GMI&UG")
		{
			if (grenade.m_grenadeSpecifics == "Firesmoke\nGenerates a thin smoke that irritates the throat")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Noise Machine\nGenerates a constant noise that distacts foes out of combat")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Stinky Bomb\nCreates a foul odor that can make people throw up")
				grenadeSpecifics += "03";
		}

		else if (grenadeSpecifics == "CTE&UG")
		{
			if (grenade.m_grenadeSpecifics == "EMP\nTemporarily disables any electronics")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Ear Disabler\nGenerates a loud high pitched noise that temporarily reduces or disables hearing")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Deflector\nCreates a magnetic field that temporarily pushes back any metallic objets, making you harder to hit")
				grenadeSpecifics += "03";
		}

		else if (grenadeSpecifics == "HSD&UG")
		{
			if (grenade.m_grenadeSpecifics == "Sleeping Gas\nConstantly exhales a sleeping agent that forces any foe to fall unconscious")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Slippery Solution\nExplodes into a slippery liquid that makes every action more difficult")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Sticky Bomb\nExplodes into a pool of quick hardening material that acts like cement once hardened")
				grenadeSpecifics += "03";
		}

		else if (grenadeSpecifics == "KTC&UG")
		{
			if (grenade.m_grenadeSpecifics == "Flashbang\nExplodes into a ball of bright light that temporarily blinds foes")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Push Field\nCreates a harsh force field that pushes anything in its path")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Electronics Resetter\nSends an electric signal forcing any electronics to fully restart")
				grenadeSpecifics += "03";
		}

		else if (grenadeSpecifics == "MIL&UG")
		{
			if (grenade.m_grenadeSpecifics == "Smoke\nGenerates a thick wall of smoke")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Nerve Agent\nGradually damages the humanity of anyone inside the radius")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Ping Grenade\nStealth grenade that quietly detonates and gives you a full view of its radius")
				grenadeSpecifics += "03";
		}
	}

	else if (grenade.getType() == Explo_G)
	{
		if (grenadeSpecifics == "GMI&EG")
		{
			if (grenade.m_grenadeSpecifics == "Pipebomb\nClassic grenade, if not low quality")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Unstable\nExplodes into light shrapnel, allowing you to ignore half of armor")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Super Sensitive Mine\nExplodes on light contact or perturbation")
				grenadeSpecifics += "03";
		}

		else if (grenadeSpecifics == "GLC&EG")
		{
			if (grenade.m_grenadeSpecifics == "Shrapnel\nExplodes into rasor sharp sharpnel, allowing you to ignore any and all armor")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Spike Wall\nGrows spikes in its radius")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Targetted Wounder\nHas a higher chance of causing a chosen wound")
				grenadeSpecifics += "03";
		}

		else if (grenadeSpecifics == "KTC&EG")
		{
			if (grenade.m_grenadeSpecifics == "Explosive Charge\nRemotely activated charge")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Thermite Bomb\nExplodes and frees thermite anyone caught in the blast, setting them on fire")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Surface Grenade\nDamages foes on a surface level, allowing the environment to be unharmed")
				grenadeSpecifics += "03";
		}

		else if (grenadeSpecifics == "MIL&EG")
		{
			if (grenade.m_grenadeSpecifics == "Frag Grenade\nStandard issued Militech grenade")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Claymore\nDetects any foe in a direct line and explodes in the same radius")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Heat Seeking Grenade\nThis grenades autocorrects its trajectory towards the closest heat source")
				grenadeSpecifics += "03";
		}
	}

	else if (grenade.getType() == Pers_G)
	{
		if (grenadeSpecifics == "CTE&PG")
		{
			if (grenade.m_grenadeSpecifics == "Pulse EMP\nPulses an EMP field each turn, disabling electronics for this turn")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Incendiary\nStandard incendiary grenade")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Pulse Ear Disabler\nLiberates a high pitched loud noise every turn, disabling hearing")
				grenadeSpecifics += "03";
		}

		else if (grenadeSpecifics == "GLC&PG")
		{
			if (grenade.m_grenadeSpecifics == "Spikes\nFrees spikes on the ground, damaging anyone stepping in the area")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Senbon\nSends flying projectile each turn, wounding anyone in the area")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Rasor Wire\nCreates long lines of rasor wire that attaches to anything, wounding on movement")
				grenadeSpecifics += "03";
		}

		else if (grenadeSpecifics == "HSD&PG")
		{
			if (grenade.m_grenadeSpecifics == "Acid Spray\nSprays acid each turn, coating anyone with it, damage is doubled on metal")
				grenadeSpecifics += "01";

			else if (grenade.m_grenadeSpecifics == "Electric Field\nGenerates a constant electric field, damage is doubled on electronics")
				grenadeSpecifics += "02";

			else if (grenade.m_grenadeSpecifics == "Irradiated Gas\nCreates a thick radioactive smoke that quickly deteriorates any living thing")
				grenadeSpecifics += "03";
		}
	}

	return grenadeSpecifics;
}

std::string generateSerialNumber(const Firearm& firearm)
{
	std::string serialNumber{};

	serialNumber += std::to_string(static_cast<int>(firearm.getType()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(firearm.getRarity()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(firearm.m_body.getBrand()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(firearm.m_barrel.getBrand()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(firearm.m_grip.getBrand()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(firearm.m_scope.getBrand()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(firearm.m_stock.getBrand()));
	serialNumber += '-';

	serialNumber += 'P';
	serialNumber += std::to_string(prefixToNum(firearm.getPrefix()));
	serialNumber += '-';

	serialNumber += brandSpecialToString(firearm);

	return serialNumber;
}

std::string generateSerialNumber(const MeleeWeapon& melee)
{
	std::string serialNumber{};

	serialNumber += std::to_string(static_cast<int>(melee.getType()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(melee.getRarity()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(melee.m_material.getBrand()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(melee.m_grip.getBrand()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(melee.m_body.getBrand()));
	serialNumber += '-';

	serialNumber += 'P';
	serialNumber += std::to_string(prefixToNum(melee.getPrefix()));
	serialNumber += '-';

	serialNumber += brandSpecialToString(melee);

	return serialNumber;
}

std::string generateSerialNumber(const Grenade& grenade)
{
	std::string serialNumber{};

	serialNumber += std::to_string(static_cast<int>(grenade.getType()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(grenade.getRarity()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(grenade.m_reagent.getBrand()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(grenade.m_body.getBrand()));
	serialNumber += '-';

	serialNumber += std::to_string(static_cast<int>(grenade.m_fuse.getBrand()));
	serialNumber += '-';

	serialNumber += specificsToString(grenade);

	return serialNumber;
}


void deleteWeapon(std::string username, std::string deletionID)
{
	std::fstream file{ username + ".txt" };
	std::ofstream temp{ "temp.txt" };

	std::string line{};
	std::string altDeletionID{";" + deletionID};
	while (std::getline(file, line))
	{
		if (line == deletionID || line == altDeletionID)
		{
			line.erase();
			file.ignore(std::numeric_limits<std::streamsize>::max(), ';');

			if (file.peek() != ';')
				temp << ';';
		}

		temp << line << std::endl;
	}

	temp.close();
	file.close();

	std::string userfile{ username + ".txt" };
	std::filesystem::rename("temp.txt", userfile.c_str());

	std::cout << "Deletion complete. Returning to menu.\n";
	file.open(userfile.c_str());
	file.seekg(0, std::ios::beg);
}

void saveWeapon(const Firearm& firearm, std::string username)
{
	std::ofstream save{ username + ".txt", std::ios::app};

	if (!save)
	{
		std::cerr << username << ".txt could not be opened for writing.\n";
		return;
	}

	static int firearmID{getID('F', username)};
	++firearmID;

	save << "WeaponID: #F" << firearmID << '-' << generateSerialNumber(firearm) << '\n';

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
	save.close();
}

void saveWeapon(const MeleeWeapon& melee, std::string username)
{
	std::ofstream save{ username + ".txt", std::ios::app};

	if (!save)
	{
		std::cerr << username << ".txt could not be opened for writing.\n";
		return;
	}

	static int meleeID{getID('M', username)};
	++meleeID;

	save << "WeaponID: #M" << meleeID << '-' << generateSerialNumber(melee) << '\n';

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
	save.close();
}

void saveWeapon(const Grenade& grenade, std::string username)
{
	std::ofstream save{ username + ".txt", std::ios::app};

	if (!save)
	{
		std::cerr << username << ".txt could not be opened for writing.\n";
		return;
	}

	static int grenadeID{getID('G', username)};
	++grenadeID;

	save << "WeaponID: #G" << grenadeID << '-' << generateSerialNumber(grenade) <<'\n';

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
	save.close();
}

std::span<const WeaponCreationTools::BrandName> getArrayFromType(const WeaponCreationTools::WeaponType& type)
{
	using namespace WeaponCreationTools;

	switch (type)
	{
	case HG:		return std::span{ HG_Brand };
	case H_HG:		return std::span{ H_HG_Brand };
	case VH_HG:		return std::span{ VH_HG_Brand };
	case SMG:		return std::span{ SMG_Brand };
	case H_SMG:		return std::span{ H_SMG_Brand };
	case SG:		return std::span{ SG_Brand };
	case AR:		return std::span{ AR_Brand };
	case SR:		return std::span{ SR_Brand };
	case Bow:		return std::span{ Bow_Brand };
	case GL:		return std::span{ GL_Brand };
	case RL:		return std::span{ RL_Brand };

	case Melee:		return std::span{ Melee_Brand};
	case I_Melee:	return std::span{ I_Melee_Brand };
	case H_Melee:	return std::span{ H_Melee_Brand };
	case VH_Melee:	return std::span{ VH_Melee_Brand };

	case Util_G:	return std::span{ Util_G_Brand };
	case Explo_G:	return std::span{ Explo_G_Brand };
	case Pers_G:	return std::span{ Pers_G_Brand };
	default:		return { };
	}
}

void modFirearm(std::string username, std::string weaponID)
{
	Firearm firearm{ readFirearmSerialNumber(weaponID) };

	while (true)
	{
		newlineSpam();
		std::cout << firearm;

		std::cout << "\nWhich part would you like to swap?\n";
		std::cout << "1. Barrel: " << getBrandText(firearm.m_barrel.getBrand()) << '\n';
		std::cout << "2. Scope: " << getBrandText(firearm.m_scope.getBrand()) << '\n';
		std::cout << "3. Grip: " << getBrandText(firearm.m_grip.getBrand()) << '\n';
		std::cout << "4. Stock: " << getBrandText(firearm.m_stock.getBrand()) << '\n';
		std::cout << "5. I'm done, thank you.\n";

		int input{};
		do
		{
			std::cin >> input;
		} while (input < 1 || input > 5);

		if (input == 5)
			break;

		const std::span<const WeaponCreationTools::BrandName> arr{ getArrayFromType(firearm.getType()) };

		std::cout << "\nHere are your available options:\n";
		for (int i{}; i < arr.size(); ++i)
		{
			std::cout << i << ". " << getBrandText(arr[i]) << "\n";
		}

		int part{};
		std::cin >> part;
		while (part > arr.size()-1)
		{
			std::cout << "Invalid. Please try again.\n";
			std::cin >> part;
		}

		if (input == 1)
		{
			firearm = { firearm.getType(), firearm.getRarity(), firearm.m_body.getBrand(), arr[part], firearm.m_scope.getBrand(), firearm.m_grip.getBrand(),
				firearm.m_stock.getBrand(), firearm.getPrefix(), firearm.m_brandSpecial, firearm.m_malorianSpecial2 };
			continue;
		}

		else if (input == 2)
		{
			firearm = { firearm.getType(), firearm.getRarity(), firearm.m_body.getBrand(), firearm.m_barrel.getBrand(), arr[part], firearm.m_grip.getBrand(),
	firearm.m_stock.getBrand(), firearm.getPrefix(), firearm.m_brandSpecial, firearm.m_malorianSpecial2 };
		}

		else if (input == 3)
		{
			firearm = { firearm.getType(), firearm.getRarity(), firearm.m_body.getBrand(), firearm.m_barrel.getBrand(), firearm.m_scope.getBrand(), arr[part],
	firearm.m_stock.getBrand(), firearm.getPrefix(), firearm.m_brandSpecial, firearm.m_malorianSpecial2 };
		}

		else if (input == 4)
		{
			firearm = { firearm.getType(), firearm.getRarity(), firearm.m_body.getBrand(), firearm.m_barrel.getBrand(), firearm.m_scope.getBrand(), firearm.m_grip.getBrand(),
	arr[part], firearm.getPrefix(), firearm.m_brandSpecial, firearm.m_malorianSpecial2 };
		}
	}

	saveWeapon(firearm, username);
	std::string oldID{"WeaponID: #" + weaponID};
	deleteWeapon(username, oldID);
}

void modifyWeapon(std::string username, std::string weaponID)
{
	weaponID.erase(0, weaponID.find('#') + 1);

	if (weaponID.front() == 'F')
		modFirearm(username, weaponID);

	else if (weaponID.front() == 'M')
		MeleeWeapon melee{ readMeleeSerialNumber(weaponID) };

	else if (weaponID.front() == 'G')
		Grenade grenade{ readGrenadeSerialNumber(weaponID) };
}

void browseSaveFile(std::string username)
{
	std::cout << "Which type of weapon do you want to browse?\n1. Firearms\n2. Melee Weapons\n3. Grenades\n";
	int input{};
	std::cin >> input;

	std::ifstream save{ username + ".txt"};

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

				std::string weaponID{};
				std::getline(save, weaponID);

				std::getline(save, str, ';');
				std::cout << "WeaponID: " << weaponID << '\n' << str;

				weaponID = "WeaponID: #" + weaponID;

				std::cout << "next ->(n) / modify (m) / delete (d) / quit x(q)\n";
				char browseInput{};
				std::cin >> browseInput;

				if (browseInput == 'n')
					continue;

				else if (browseInput == 'm')
				{
					save.close();
					modifyWeapon(username, weaponID);
					browseSaveFile(username);
					break;
				}

				else if (browseInput == 'd')
				{
					save.close();
					deleteWeapon(username, weaponID);
					browseSaveFile(username);
					break;
				}

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

				std::string weaponID{};
				std::getline(save, weaponID);

				std::getline(save, str, ';');
				std::cout << "WeaponID: " << weaponID << '\n' << str;

				weaponID = "WeaponID: #" + weaponID;

				std::cout << "next ->(n) / quit x(q) / delete(d)\n";
				char browseInput{};
				std::cin >> browseInput;

				if (browseInput == 'n')
					continue;

				else if (browseInput == 'd')
				{
					save.close();
					deleteWeapon(username, weaponID);
					browseSaveFile(username);
					break;
				}

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

				std::string weaponID{};
				std::getline(save, weaponID);

				std::getline(save, str, ';');
				std::cout << "WeaponID: " << weaponID << '\n' << str;

				weaponID = "WeaponID: #" + weaponID;

				std::cout << "next ->(n) / quit x(q) / delete(d)\n";
				char browseInput{};
				std::cin >> browseInput;

				if (browseInput == 'n')
					continue;

				else if (browseInput == 'd')
				{
					save.close();
					deleteWeapon(username, weaponID);
					browseSaveFile(username);
					break;
				}

				else if (browseInput == 'q')
					break;
			}
		}
	}
}