#include <array>
#include <string>
#include <string_view>
#include <iostream>
#include "Utils.h"
#include "Random.h"

int WeaponCreationTools::dieThrow(int dieNum)
{
	return Random::get(1, dieNum);
}

std::string_view WeaponCreationTools::getTypeText(WeaponType type)
{
	switch (type)
	{
	case HG:		return "Handgun";
	case H_HG:		return "Heavy Handgun";
	case VH_HG:		return "Very Heavy Handgun";
	case SMG:		return "Submachine Gun";
	case H_SMG:		return "Heavy Submachine Gun";
	case SG:		return "Shotgun";
	case AR:		return "Assault Rifle";
	case SR:		return "Sniper Rifle";
	case Bow:		return "Crossbow";
	case GL:		return "Grenade Launcher";
	case RL:		return "Rocket Launcher";
	case Melee:		return "Light Melee Weapon";
	case I_Melee:	return "Intermediate Melee Weapon";
	case H_Melee:	return "Heavy Melee Weapon";
	case VH_Melee:	return "Very Heavy Melee Weapon";
	case Util_G:	return "Utility Grenade";
	case Explo_G:	return "Explosive Grenade";
	case Pers_G:	return "Persistent Effect Grenade";
	default:		return "Something went wrong: getTypeText()";
	}
}

std::string_view WeaponCreationTools::getBrandText(BrandName brand)
{
	switch (brand)
	{
	case militech:			return "Militech";
	case arasaka:			return "Arasaka";
	case gunmart:			return "GunMart Inc.";
	case tsunami:			return "Tsunami Arms";
	case nova:				return "Nova";
	case dai_lung:			return "Dai Lung";
	case constitution:		return "Constitution Arms";
	case techtronika:		return "Techtronika Russia";
	case sanroo:			return "Sanroo";
	case hydrosubsidium:	return "Hydrosubsidium";
	case rostovic:			return "Rostovic";
	case malorian:			return "Malorian Arms";
	case kendachi:			return "Kendachi Arms";
	case everest:			return "Everest VentureWare";
	case slamdance:			return "Slam Dance Inc.";
	case centurian:			return "Centurian Essentials";
	case great_lakes:		return "Great Lakes Cutlery";
	case ktech:				return "KTech";
	case max_brand_names:	return "None";
	default:				return "Something went wrong: getBrandText()";
	}
}

std::string_view WeaponCreationTools::getRarityText(Rarity rarity)
{
	switch (rarity)
	{
	case common:	return "Common";
	case mediocre:	return "Mediocre";
	case superior:	return "Superior";
	case excellent:	return "Excellent";
	case exotic:	return "Exotic";
	default:		return "Something went wrong: getRarityText()";
	}
}

const Part& Weapon::generateRandomPart(const Weapon& weapon)
{
	using namespace WeaponCreationTools;
	switch (weapon.getType())
	{
	case HG:		return Part{ HG_Brand[dieThrow(static_cast<int>(HG_Brand.size())) -1] };
	case H_HG:		return Part{ H_HG_Brand[dieThrow(static_cast<int>(H_HG_Brand.size()))-1] };
	case VH_HG:		return Part{ VH_HG_Brand[dieThrow(static_cast<int>(VH_HG_Brand.size()))-1] };
	case SMG:		return Part{ SMG_Brand[dieThrow(static_cast<int>(SMG_Brand.size()))-1] };
	case H_SMG:		return Part{ H_SMG_Brand[dieThrow(static_cast<int>(H_SMG_Brand.size()))-1] };
	case SG:		return Part{ SG_Brand[dieThrow(static_cast<int>(SG_Brand.size()))-1] };
	case AR:		return Part{ AR_Brand[dieThrow(static_cast<int>(AR_Brand.size()))-1] };
	case SR:		return Part{ SR_Brand[dieThrow(static_cast<int>(SR_Brand.size()))-1] };
	case Bow:		return Part{ Bow_Brand[dieThrow(static_cast<int>(Bow_Brand.size()))-1] };
	case GL:		return Part{ GL_Brand[dieThrow(static_cast<int>(GL_Brand.size()))-1] };
	case RL:		return Part{ RL_Brand[dieThrow(static_cast<int>(RL_Brand.size()))-1] };

	case Melee:		return Part{ Melee_Brand[dieThrow(static_cast<int>(Melee_Brand.size()))-1] };
	case I_Melee:	return Part{ I_Melee_Brand[dieThrow(static_cast<int>(I_Melee_Brand.size()))-1] };
	case H_Melee:	return Part{ H_Melee_Brand[dieThrow(static_cast<int>(H_Melee_Brand.size()))-1] };
	case VH_Melee:	return Part{ VH_Melee_Brand[dieThrow(static_cast<int>(VH_Melee_Brand.size()))-1] };

	case Util_G:	return Part{ Util_G_Brand[dieThrow(static_cast<int>(Util_G_Brand.size()))-1] };
	case Explo_G:	return Part{ Explo_G_Brand[dieThrow(static_cast<int>(Explo_G_Brand.size()))-1] };
	case Pers_G:	return Part{ Pers_G_Brand[dieThrow(static_cast<int>(Pers_G_Brand.size()))-1] };

	default:		return Part{ max_brand_names };
	}
}

const WeaponCreationTools::WeaponType& WeaponCreationTools::generateRandomType()
{
	using namespace WeaponCreationTools;
	return static_cast<WeaponType>(dieThrow(max_weapon_types -1));
}

const WeaponCreationTools::Rarity& WeaponCreationTools::getRandomRarity()
{
	using namespace WeaponCreationTools;
	int D100{ dieThrow(100) };

	if (D100 <= 35)
		return common;

	else if (D100 <= 65)
		return mediocre;

	else if (D100 <= 85)
		return superior;

	else if (D100 <= 95)
		return excellent;

	else if (D100 <= 100)
		return exotic;

	return max_rarity;
}

std::string_view Weapon::getSkillType() const
{
	using namespace WeaponCreationTools;

	switch (m_type)
	{
	case HG:
	case H_HG:
	case VH_HG:
	case SMG:
	case H_SMG:		return "Handguns";
	case SG:
	case AR:
	case SR:		return "Shoulder Arms";
	case Bow:		return "Archery";
	case GL:
	case RL:		return "Heavy Weapons";
	case Melee:
	case I_Melee:
	case H_Melee:
	case VH_Melee:	return "Melee Weapons";
	default:		return "Null";
	}
}

void Weapon::generateFirearmPrefix()
{
	int rand{ WeaponCreationTools::dieThrow(10) };

	switch (rand)
	{
	case 1: return;
	case 2: m_prefix = "Accurate: Aimed shot with advantage"; return;
	case 3: m_prefix = "Stable: Auto shot with advantage"; return;
	case 4: m_prefix = "High caliber: One advantage die on damage"; return;
	case 5: m_prefix = "Wieldy: Accuracy bonus"; return;
	case 6: m_prefix = "Fast: Fire rate bonus"; return;
	case 7: m_prefix = "Unstoppable: Shoots through cover"; return;
	case 8: m_prefix = "Penetrating: Doubles damage on armor"; return;
	case 9: return;
	case 10: return;
	default: return;
	}
}

void Weapon::generateMeleePrefix()
{
	int rand{ WeaponCreationTools::dieThrow(10) };

	switch (rand)
	{
	case 1: return;
	case 2: "Accurate: Aimed hit with advantage"; return;
	case 3: "Stable: Throw with advantage"; return;
	case 4: "Sharp: One advantage die on damage"; return;
	case 5: "Wieldy: Handling bonus"; return;
	case 6: "Fast: Attack speed bonus"; return;
	case 7: "Handmade: Doubles the bonus on any parts that share the same brand as the weapon"; return;
	case 8: "Penetrating: Ignores armor"; return;
	case 9: return;
	case 10: return;
	default: return;
	}
}

void Weapon::applyRarityBonus()
{
	if (m_rarity == WeaponCreationTools::common)
	{
		addConcealMalus();
		addDamageMalus();
		addPriceMalus();
	}

	else if (m_rarity == WeaponCreationTools::mediocre)
	{
	}

	else if (m_rarity == WeaponCreationTools::superior)
	{
		addConcealBonus();
		addDamageBonus();
		addPriceBonus();
	}

	else if (m_rarity == WeaponCreationTools::excellent)
	{
		addConcealBonus();
		addDamageBonus();
		addPriceBonus();
		addConcealBonus();
		addDamageBonus();
		addPriceBonus();
	}
}

void Weapon::generateHGBase()
{
	m_concealable = true;
	m_concealBonus = 0;
	m_hands = 1;
	m_price = 50;
	m_damage_extra = 0;
	m_num_dice = 2;
}

void Weapon::generateHHGBase()
{
	m_concealable = true;
	m_concealBonus = 0;
	m_hands = 1;
	m_price = 100;
	m_damage_extra = 0;
	m_num_dice = 3;
}

void Weapon::generateVHHGBase()
{
	m_concealable = false;
	m_concealBonus = 0;
	m_hands = 1;
	m_price = 100;
	m_damage_extra = 0;
	m_num_dice = 4;
}

void Weapon::generateSMGBase()
{
	m_concealable = true;
	m_concealBonus = 0;
	m_hands = 1;
	m_price = 100;
	m_damage_extra = 0;
	m_num_dice = 2;
}

void Weapon::generateHSMGBase()
{
	m_concealable = false;
	m_concealBonus = 0;
	m_hands = 2;
	m_price = 150;
	m_damage_extra = 0;
	m_num_dice = 3;
}

void Weapon::generateSGBase()
{
	m_concealable = false;
	m_concealBonus = 0;
	m_hands = 2;
	m_price = 500;
	m_damage_extra = 0;
	m_num_dice = 5;
}

void Weapon::generateARBase()
{
	m_concealable = false;
	m_concealBonus = 0;
	m_hands = 2;
	m_price = 500;
	m_damage_extra = 0;
	m_num_dice = 5;
}

void Weapon::generateSRBase()
{
	m_concealable = false;
	m_concealBonus = 0;
	m_hands = 2;
	m_price = 500;
	m_damage_extra = 0;
	m_num_dice = 5;
}

void Weapon::generateBowBase()
{
	m_concealable = false;
	m_concealBonus = 0;
	m_hands = 2;
	m_price = 100;
	m_damage_extra = 0;
	m_num_dice = 4;
}

void Weapon::generateGLBase()
{
	m_concealable = false;
	m_concealBonus = 0;
	m_hands = 2;
	m_price = 500;
	m_damage_extra = 0;
	m_num_dice = 6;
}

void Weapon::generateRLBase()
{
	m_concealable = false;
	m_concealBonus = 0;
	m_hands = 2;
	m_price = 500;
	m_damage_extra = 0;
	m_num_dice = 8;
}

void Weapon::generateMeleeBase()
{
	m_concealable = true;
	m_concealBonus = 0;
	m_hands = 1;
	m_price = 50;
	m_damage_extra = 0;
	m_num_dice = 1;
}

void Weapon::generateIMeleeBase()
{
	m_concealable = true;
	m_concealBonus = 0;
	m_hands = 1;
	m_price = 50;
	m_damage_extra = 0;
	m_num_dice = 2;
}

void Weapon::generateHMeleeBase()
{
	m_concealable = false;
	m_concealBonus = 0;
	m_hands = 2;
	m_price = 100;
	m_damage_extra = 0;
	m_num_dice = 3;
}

void Weapon::generateVHMeleeBase()
{
	m_concealable = false;
	m_concealBonus = 0;
	m_hands = 2;
	m_price = 500;
	m_damage_extra = 0;
	m_num_dice = 4;
}

void Weapon::generateUtilGrenadeBase()
{
	m_concealable = true;
	m_concealBonus = 0;
	m_hands = 1;
	m_price = 0;
	m_damage_extra = 0;
	m_num_dice = 0;
}

void Weapon::generateExploGrenadeBase()
{
	m_concealable = true;
	m_concealBonus = 0;
	m_hands = 1;
	m_price = 0;
	m_damage_extra = 0;
	m_num_dice = 6;
}

void Weapon::generatePersGrenadeBase()
{
	m_concealable = true;
	m_concealBonus = 0;
	m_hands = 1;
	m_price = 0;
	m_damage_extra = 0;
	m_num_dice = 2;
}

void Weapon::failSafe()
{
	if (getDamageExtra() >= 3)
	{
		while (getDamageExtra() >= 3)
		{
			++m_num_dice;
			m_damage_extra -= 3;
		}
	}
	if (getPrice() <= 25)
		m_price = 25;
}

void Firearm::setWeaponSpecial()
{
	using namespace WeaponCreationTools;
	switch (getType())
	{
	case SMG: m_weaponSpecial = "Auto (3) / Suppressive fire"; return;
	case H_SMG: m_weaponSpecial = "Auto (3) / Suppressive fire"; return;
	case SG: m_weaponSpecial = "Buckshot"; return;
	case AR: m_weaponSpecial = "Auto (3) / Suppressive fire"; return;
	case Bow: m_weaponSpecial = "Arrows"; return;
	case GL: m_weaponSpecial = "Explosion"; return;
	case RL: m_weaponSpecial = "Explosion"; return;
	}
}

void Firearm::setBrandSpecial()
{
	using namespace WeaponCreationTools;
	switch (m_body.getBrand())
	{
	case militech: m_brandSpecial = "Quickswap"; return;
	case arasaka: m_brandSpecial = "Smart Bullets"; return;
	case gunmart: m_brandSpecial = "Self-Destruct"; return;
	case tsunami: m_brandSpecial = "Interface Spotter"; return;
	case nova: m_brandSpecial = "Horsepower"; return;
	case dai_lung: m_brandSpecial = "Hit it"; return;
	case constitution: m_brandSpecial = "Safety Off"; return;
	case techtronika: m_brandSpecial = "Burst Fire"; return;
	case sanroo: m_brandSpecial = "Stylish"; return;
	case hydrosubsidium: m_brandSpecial = "Chem Warfare"; return;
	case rostovic: m_brandSpecial = "E-Z-Swap"; return;
	case malorian: m_brandSpecial = "Ammo Mod"; return;
	}
}

void Firearm::setSpecialExtra()
{
	using namespace WeaponCreationTools;
	if (m_body.getBrand() != malorian && m_body.getBrand() != hydrosubsidium)
		return;

	if (m_body.getBrand() == malorian)
	{
		int rand{ WeaponCreationTools::dieThrow(8) };

		switch (rand)
		{
		case 1: m_brandSpecial = "Ammo Mod:\nTracer: Every consecutive hit on the same target gives you a bonus (of 1) to hit rate on them"; break;
		case 2: m_brandSpecial = "Ammo Mod:\nHollow Point: The number of perfect rolls to inflict a serious injury by 1"; break;
		case 3: m_brandSpecial = "Ammo Mod:\nSubsonic: Your shots are harder to track"; break;
		case 4: m_brandSpecial = "Ammo Mod:\nPiercing: Ignores half of armor (and cover)"; break;
		case 5: m_brandSpecial = "Ammo Mod:\nFull Metal Jacket: Standard Malorian issued round"; break;
		case 6: m_brandSpecial = "Ammo Mod:\nHigh Velocity: Multiplies the effective distances of the round by 2"; break;
		case 7: m_brandSpecial = "Ammo Mod:\nBuckshot: Acts like the standard shotgun Buckshot"; break;
		case 8: m_brandSpecial = "Ammo Mod:\nRubber: Non-lethal, same damage"; break;
		default: return;
		}

		int rand2{ WeaponCreationTools::dieThrow(8) };
		while (rand == rand2)
			rand2 = WeaponCreationTools::dieThrow(8);

		switch (rand2)
		{
		case 1: m_malorianSpecial2 = "Ammo Mod:\nTracer: Every consecutive hit on the same target gives you a bonus (of 1) to hit rate on them"; break;
		case 2: m_malorianSpecial2 = "Ammo Mod:\nHollow Point: The number of perfect rolls to inflict a serious injury by 1"; break;
		case 3: m_malorianSpecial2 = "Ammo Mod:\nSubsonic: Your shots are harder to track"; break;
		case 4: m_malorianSpecial2 = "Ammo Mod:\nPiercing: Ignores half of armor (and cover)"; break;
		case 5: m_malorianSpecial2 = "Ammo Mod:\nFull Metal Jacket: Standard Malorian issued round"; break;
		case 6: m_malorianSpecial2 = "Ammo Mod:\nHigh Velocity: Multiplies the effective distances of the round by 2"; break;
		case 7: m_malorianSpecial2 = "Ammo Mod:\nBuckshot: Acts like the standard shotgun Buckshot"; break;
		case 8: m_malorianSpecial2 = "Ammo Mod:\nRubber: Non-lethal, same damage"; break;
		default: return;
		}

	}
	else if (m_body.getBrand() == hydrosubsidium)
	{
		int rand{ WeaponCreationTools::dieThrow(8) };

		switch (rand)
		{
		case 1: m_brandSpecial = "Chem Warfare:\nEMP: Adds an extra EMP explosion which deactivate any electrical system touched by the bullet"; return;
		case 2: m_brandSpecial = "Chem Warfare:\nAcid: Adds an extra damage on time effect to the round, equal to setting the target on fire (but doubled on metal)"; return;
		case 3: m_brandSpecial = "Chem Warfare:\nNeurotoxin: Any damage inflicted by this weapon is, instead, removed from maximum health total (Only an expensive operation can fix that)"; return;
		case 4: m_brandSpecial = "Chem Warfare:\nNapalm: Sets the target on fire"; return;
		case 5: m_brandSpecial = "Chem Warfare:\nSleeping gas: The target has to resist torture/drugs (DV defined by the quality of the weapon) in order to not fall asleep"; return;
		case 6: m_brandSpecial = "Chem Warfare:\nNanomachines: Nanomachines that can be reprogrammed to do simple tasks on electrical components"; return;
		case 7: m_brandSpecial = "Chem Warfare:\nSticky: Extremely sticky solution that disturbs movement"; return;
		case 8: m_brandSpecial = "Chem Warfare:\nNeuropsychotic: Any damage inflicted is replicated on Humanity"; return;
		default: return;
		}
	}
}

void Firearm::generateHGBase()
{
	Weapon::generateHGBase();
	m_mag = 12;
	m_fireRate = 2;
	m_accuracy = 0;
	m_ammoType = "Handgun (M)";
}

void Firearm::generateHHGBase()
{
	Weapon::generateHHGBase();
	m_mag = 8;
	m_fireRate = 2;
	m_accuracy = 0;
	m_ammoType = "Handgun (H)";
}

void Firearm::generateVHHGBase()
{
	Weapon::generateVHHGBase();
	m_mag = 8;
	m_fireRate = 1;
	m_accuracy = -1;
	m_ammoType = "Handgun (VH)";
}

void Firearm::generateSMGBase()
{
	Weapon::generateSMGBase();
	m_mag = 30;
	m_fireRate = 1;
	m_accuracy = -1;
	m_ammoType = "Handgun (M)";
}

void Firearm::generateHSMGBase()
{
	Weapon::generateHSMGBase();
	m_mag = 40;
	m_fireRate = 1;
	m_accuracy = 0;
	m_ammoType = "Handgun (H)";
}

void Firearm::generateSGBase()
{
	Weapon::generateSGBase();
	m_mag = 4;
	m_fireRate = 1;
	m_accuracy = -2;
	m_ammoType = "Slug";
}

void Firearm::generateARBase()
{
	Weapon::generateARBase();
	m_mag = 25;
	m_fireRate = 1;
	m_accuracy = 1;
	m_ammoType = "Rifle";
}

void Firearm::generateSRBase()
{
	Weapon::generateSRBase();
	m_mag = 4;
	m_fireRate = 1;
	m_accuracy = 2;
	m_ammoType = "Rifle";
}

void Firearm::generateBowBase()
{
	Weapon::generateBowBase();
	m_mag = 0;
	m_fireRate = 1;
	m_accuracy = 0;
	m_ammoType = "Arrow";
}

void Firearm::generateGLBase()
{
	Weapon::generateGLBase();
	m_mag = 2;
	m_fireRate = 1;
	m_accuracy = -2;
	m_ammoType = "Grenade";
}

void Firearm::generateRLBase()
{
	Weapon::generateRLBase();
	m_mag = 1;
	m_fireRate = 1;
	m_accuracy = -1;
	m_ammoType = "Rocket";
}

void Firearm::applyRarityBonus()
{
	Weapon::applyRarityBonus();
	if (getRarity() == WeaponCreationTools::common)
	{
		addFireRateMalus();
		addMagMalus();
		addAccuracyMalus();
	}
	else if (getRarity() == WeaponCreationTools::mediocre)
	{
	}
	else if (getRarity() == WeaponCreationTools::superior)
	{
		addFireRateBonus();
		addMagBonus();
		addAccuracyBonus();
	}
	else if (getRarity() == WeaponCreationTools::excellent)
	{
		addFireRateBonus();
		addMagBonus();
		addAccuracyBonus();
		addFireRateBonus();
		addMagBonus();
		addAccuracyBonus();
	}
}

void Firearm::failSafe()
{
	Weapon::failSafe();

	if (m_fireRate < 1)
	{
		m_fireRate = 1;
		if (getType() != WeaponCreationTools::Bow)
			m_weaponSpecial += "\nBolt Action";
	}

	if (m_mag < 1 && getType() != WeaponCreationTools::Bow)
		m_mag = 1;
}

const std::ostream& operator<<(const std::ostream& out, const Firearm& firearm)
{
	using namespace WeaponCreationTools;
	std::cout << getRarityText(firearm.getRarity()) << " " << getTypeText(firearm.getType()) << '\n';
	std::cout << "Affix: " << firearm.getPrefix() << '\n';
	std::cout << "Manufacturer: " << getBrandText(firearm.m_body.getBrand()) << '\n';

	std::cout << "Body: " << getBrandText(firearm.m_body.getBrand()) << " | Grip: " << getBrandText(firearm.m_grip.getBrand()) << " | Barrel: " << getBrandText(firearm.m_barrel.getBrand())
		<< " | Scope: " << getBrandText(firearm.m_scope.getBrand()) << " | Stock: " << getBrandText(firearm.m_stock.getBrand()) << '\n';
	std::cout << "Hands: " << firearm.getHands() << "\n\n";

	std::cout << "Damage: " << firearm.getDamage() << "D6 " << (firearm.getDamageExtra() < 0 ? "" : "+ ") << firearm.getDamageExtra() << '\n';
	std::cout << "Magasine: " << static_cast<int>(firearm.m_mag) << " (" << firearm.m_ammoType << ")" << '\n';
	std::cout << "Fire rate: " << firearm.m_fireRate << '\n';
	std::cout << "Accuracy: " << firearm.m_accuracy << '\n';
	std::cout << "Skill Bonus: " << firearm.getSkillBonus() << " (" << firearm.getSkillType() << ")" << '\n';
	std::cout << "Special Bonus: " << firearm.getSpecialBonus() << "\n\n";

	std::cout << "Concealable: " << (firearm.getConcealable() ? "Yes" : "No") << " (" << firearm.getConcealBonus() << ")" << '\n';
	std::cout << "Special: " << firearm.m_weaponSpecial << '\n' << firearm.m_brandSpecial << '\n' << firearm.m_malorianSpecial2 << "\n\n";

	std::cout << "Price: " << firearm.getPrice() << " Eurodollars" << '\n';

	return out;
}

void MeleeWeapon::setBrandSpecial()
{
	using namespace WeaponCreationTools;
	switch (m_material.getBrand())
	{
	case militech: m_brandSpecial = "Feint"; return;
	case arasaka: m_brandSpecial = "Iai"; return;
	case kendachi: m_brandSpecial = "Armor Shred"; return;
	case everest: m_brandSpecial = "Tool"; return;
	case sanroo: m_brandSpecial = "Stylish"; return;
	case slamdance: m_brandSpecial = "Natural"; return;
	default: return;
	}
}

void MeleeWeapon::setSpecialExtra()
{
	using namespace WeaponCreationTools;
	if (m_material.getBrand() != arasaka)
		return;

	if (m_material.getBrand() == arasaka)
	{
		int rand{ WeaponCreationTools::dieThrow(8) };

		switch (rand)
		{
		case 1: m_brandSpecial = "Iai:\nVersatile: While fighting, +2 to any throw if the weapon was unsheathed this turn"; return;
		case 2: m_brandSpecial = "Iai:\nTrue Slice: The next attack after unsheathing gets an extra damage die"; return;
		case 3: m_brandSpecial = "Iai:\nFast Strike: You get a free attack after unsheathing"; return;
		case 4: m_brandSpecial = "Iai:\nCharge: The turn you unsheath, you can Charge, which allows you to move an extra time and attack"; return;
		case 5: m_brandSpecial = "Iai:\nTranquil Strike: The next attack after unsheathing cannot miss"; return;
		case 6: m_brandSpecial = "Iai:\nTerror: Unsheathing triggers a Staredown event within which you may not receive any negative effects"; return;
		case 7: m_brandSpecial = "Iai:\nReaction: You may unsheath this weapon as a response to any attack and parry it (this action takes your turn)"; return;
		case 8: m_brandSpecial = "Iai:\nAccurate Slice: The penalty on any aimed attack following the unsheathing is nullified"; return;
		default: return;
		}
	}
}

void MeleeWeapon::generateMeleeBase()
{
	Weapon::generateMeleeBase();
	m_handling = 2;
	m_attackSpeed = 2;
	m_throwable = true;
}

void MeleeWeapon::generateIMeleeBase()
{
	Weapon::generateIMeleeBase();
	m_handling = 1;
	m_attackSpeed = 2;
	m_throwable = true;
}

void MeleeWeapon::generateHMeleeBase()
{
	Weapon::generateHMeleeBase();
	m_handling = 0;
	m_attackSpeed = 2;
	m_throwable = false;
}

void MeleeWeapon::generateVHMeleeBase()
{
	Weapon::generateVHMeleeBase();
	m_handling = -1;
	m_attackSpeed = 1;
	m_throwable = false;
}

void MeleeWeapon::applyRarityBonus()
{
	Weapon::applyRarityBonus();
	if (getType() == WeaponCreationTools::common)
	{
		addHandlingMalus();
		addAttackSpeedBonus();
	}
	else if (getType() == WeaponCreationTools::mediocre) {}
	else if (getType() == WeaponCreationTools::superior)
	{
		addHandlingBonus();
		addAttackSpeedBonus();
	}
	else if (getType() == WeaponCreationTools::excellent)
	{
		addHandlingBonus();
		addAttackSpeedBonus();
		addHandlingBonus();
		addAttackSpeedBonus();
	}
}

void MeleeWeapon::failSafe()
{
	Weapon::failSafe();
	if (m_attackSpeed < 1)
	{
		m_attackSpeed = 1;
		m_brandSpecial += "\nHeavy";
	}
}

const std::ostream& operator<<(const std::ostream& out, const MeleeWeapon& melee)
{
	using namespace WeaponCreationTools;
	std::cout << getRarityText(melee.getRarity()) << " " << getTypeText(melee.getType()) << '\n';
	std::cout << "Affix: " << melee.getPrefix() << '\n';
	std::cout << "Manufacturer: " << getBrandText(melee.m_material.getBrand()) << '\n';

	std::cout << "Material: " << getBrandText(melee.m_material.getBrand()) << " | Grip: " << getBrandText(melee.m_grip.getBrand()) << " | Body: " << getBrandText(melee.m_body.getBrand()) << '\n';
	std::cout << "Hands: " << melee.getHands() << "\n\n";

	std::cout << "Damage: " << melee.getDamage() << "D6 " << (melee.getDamageExtra() < 0 ? "" : "+ ") << melee.getDamageExtra() << '\n';
	std::cout << "Attack Speed: " << melee.m_attackSpeed << '\n';
	std::cout << "Handling: " << melee.m_handling << '\n';
	std::cout << "Skill Bonus: " << melee.getSkillBonus() << " (" << melee.getSkillType() << ")" << '\n';
	std::cout << "Special Bonus: " << melee.getSpecialBonus() << "\n\n";

	std::cout << "Concealable: " << (melee.getConcealable() ? "Yes" : "No") << " (" << melee.getConcealBonus() << ")" << '\n';
	std::cout << "Throwable: " << (melee.m_throwable ? "Yes" : "No") << '\n';
	std::cout << "Special: " << melee.m_brandSpecial << "\n\n";

	std::cout << "Price: " << melee.getPrice() << " Eurodollars" << '\n';

	return out;
}

void Grenade::generateUtilGrenadeBase()
{
	Weapon::generateUtilGrenadeBase();
	m_fuseTimer = 2;
	m_radius = 10;
	m_duration = 10;
}

void Grenade::generateExploGrenadeBase()
{
	Weapon::generateExploGrenadeBase();
	m_fuseTimer = 3;
	m_radius = 15;
	m_duration = 0;
}

void Grenade::generatePersGrenadeBase()
{
	Weapon::generatePersGrenadeBase();
	m_fuseTimer = 3;
	m_radius = 5;
	m_duration = 5;
}

void Grenade::applyRarityBonus()
{
	Weapon::applyRarityBonus();
	if (getType() == WeaponCreationTools::common)
	{
		addFuseTimerBonus();
		addRadiusMalus();
		addDurationMalus();
	}
	else if (getType() == WeaponCreationTools::mediocre) {}
	else if (getType() == WeaponCreationTools::superior)
	{
		addFuseTimerMalus();
		addRadiusBonus();
		addDurationBonus();
	}
	else if (getType() == WeaponCreationTools::excellent)
	{
		addFuseTimerMalus();
		addRadiusBonus();
		addDurationBonus();
		addFuseTimerMalus();
		addRadiusBonus();
		addDurationBonus();
	}
}

void Grenade::failSafe()
{
	Weapon::failSafe();
	if (m_radius < 0)
		m_radius = 0;

	if (m_duration < 0)
		m_duration = 0;

	if (m_fuseTimer < 0)
		m_fuseTimer = 0;
}

void Grenade::generateSpecifics()
{
	using namespace WeaponCreationTools;
	int rand{ dieThrow(3) };

	if (getType() == Util_G)
	{
		if (m_reagent.getBrand() == gunmart)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "Firesmoke\nGenerates a thin smoke that irritates the throat"; return;
			case 2: m_grenadeSpecifics = "Noise Machine\nGenerates a constant noise that distacts foes out of combat"; return;
			case 3: m_grenadeSpecifics = "Stinky Bomb\nCreates a foul odor that can make people throw up"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
		if (m_reagent.getBrand() == centurian)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "EMP\nTemporarily disables any electronics"; return;
			case 2: m_grenadeSpecifics = "Ear Disabler\nGenerates a loud high pitched noise that temporarily reduces or disables hearing"; return;
			case 3: m_grenadeSpecifics = "Deflector\nCreates a magnetic field that temporarily pushes back any metallic objets, making you harder to hit"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
		if (m_reagent.getBrand() == hydrosubsidium)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "Sleeping Gas\nConstantly exhales a sleeping agent that forces any foe to fall unconscious"; return;
			case 2: m_grenadeSpecifics = "Slippery Solution\nExplodes into a slippery liquid that makes every action more difficult"; return;
			case 3: m_grenadeSpecifics = "Sticky Bomb\nExplodes into a pool of quick hardening material that acts like cement once hardened"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
		if (m_reagent.getBrand() == ktech)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "Flashbang\nExplodes into a ball of bright light that temporarily blinds foes"; return;
			case 2: m_grenadeSpecifics = "Push Field\nCreates a harsh force field that pushes anything in its path"; return;
			case 3: m_grenadeSpecifics = "Electronics Resetter\nSends an electric signal forcing any electronics to fully restart"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
		if (m_reagent.getBrand() == militech)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "Smoke\nGenerates a thick wall of smoke"; return;
			case 2: m_grenadeSpecifics = "Nerve Agent\nGradually damages the humanity of anyone inside the radius"; return;
			case 3: m_grenadeSpecifics = "Ping Grenade\nStealth grenade that quietly detonates and gives you a full view of its radius"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
	}
	if (getType() == Explo_G)
	{
		if (m_reagent.getBrand() == gunmart)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "Pipebomb\nClassic grenade, if not low quality"; return;
			case 2: m_grenadeSpecifics = "Unstable\nExplodes into light shrapnel, allowing you to ignore half of armor"; return;
			case 3: m_grenadeSpecifics = "Super Sensitive Mine\nExplodes on light contact or perturbation"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
		if (m_reagent.getBrand() == great_lakes)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "Shrapnel\nExplodes into rasor sharp sharpnel, allowing you to ignore any and all armor"; return;
			case 2: m_grenadeSpecifics = "Spike Wall\nGrows spikes in its radius"; return;
			case 3: m_grenadeSpecifics = "Targetted Wounder\nHas a higher chance of causing a chosen wound"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
		if (m_reagent.getBrand() == ktech)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "Explosive Charge\nRemotely activated charge"; return;
			case 2: m_grenadeSpecifics = "Thermite Bomb\nExplodes and frees thermite anyone caught in the blast, setting them on fire"; return;
			case 3: m_grenadeSpecifics = "Surface Grenade\nDamages foes on a surface level, allowing the environment to be unharmed"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
		if (m_reagent.getBrand() == militech)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "Frag Grenade\nStandard issued Militech grenade"; return;
			case 2: m_grenadeSpecifics = "Claymore\nDetects any foe in a direct line and explodes in the same radius"; return;
			case 3: m_grenadeSpecifics = "Heat Seeking Grenade\nThis grenades autocorrects its trajectory towards the closest heat source"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
	}
	if (getType() == Pers_G)
	{
		if (m_reagent.getBrand() == centurian)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "Pulse EMP\nPulses an EMP field each turn, disabling electronics for this turn"; return;
			case 2: m_grenadeSpecifics = "Incendiary\nStandard incendiary grenade"; return;
			case 3: m_grenadeSpecifics = "Pulse Ear Disabler\nLiberates a high pitched loud noise every turn, disabling hearing"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
		if (m_reagent.getBrand() == great_lakes)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "Spikes\nFrees spikes on the ground, damaging anyone stepping in the area"; return;
			case 2: m_grenadeSpecifics = "Senbon\nSends flying projectile each turn, wounding anyone in the area"; return;
			case 3: m_grenadeSpecifics = "Rasor Wire\nCreates long lines of rasor wire that attaches to anything, wounding on movement"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
		if (m_reagent.getBrand() == hydrosubsidium)
		{
			switch (rand)
			{
			case 1: m_grenadeSpecifics = "Acid Spray\nSprays acid each turn, coating anyone with it, damage is doubled on metal"; return;
			case 2: m_grenadeSpecifics = "Electric Field\nGenerates a constant electric field, damage is doubled on electronics"; return;
			case 3: m_grenadeSpecifics = "Irradiated Gas\nCreates a thick radioactive smoke that quickly deteriorates any living thing"; return;
			default: m_grenadeSpecifics = "Something went wrong: generateSpecifics()"; return;
			}
		}
	}
}

const std::ostream& operator<<(const std::ostream& out, const Grenade& grenade)
{
	using namespace WeaponCreationTools;
	std::cout << getRarityText(grenade.getRarity()) << " " << getTypeText(grenade.getType()) << '\n';
	std::cout << "Manufacturer: " << getBrandText(grenade.m_reagent.getBrand()) << '\n';
	std::cout << "Special: " << grenade.m_grenadeSpecifics << "\n\n";

	std::cout << "Reagent: " << getBrandText(grenade.m_reagent.getBrand()) << " | Fuse: " << getBrandText(grenade.m_fuse.getBrand()) << " | Body: " << getBrandText(grenade.m_body.getBrand()) << "\n\n";

	std::cout << "Damage: " << grenade.getDamage() << "D6 " << (grenade.getDamageExtra() < 0 ? "" : "+ ") << grenade.getDamageExtra() << '\n';
	std::cout << "Fuse Timer: " << grenade.m_fuseTimer << '\n';
	std::cout << "Radius: " << grenade.m_radius << '\n';
	std::cout << "Duration: " << grenade.m_duration << '\n';
	std::cout << "Special Bonus: " << grenade.getSpecialBonus() << '\n';

	std::cout << "\nPrice: " << grenade.getPrice() << " Eurodollars" << '\n';

	return out;
}

void Firearm::tweakStats()
{
	std::array<Part, 5> parts{ m_body, m_barrel, m_scope, m_grip, m_stock };

	for (int i{ 0 }; i < parts.size(); ++i)
	{
		if (parts[i].getBrand() == WeaponCreationTools::militech)
		{
			addSkillBonus();
			addFireRateMalus();
			addAccuracyBonus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::arasaka)
		{
			addSkillMalus();
			addAccuracyBonus();
			addAccuracyBonus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::gunmart)
		{
			addDamageMalus();
			addAccuracyMalus();
			addPriceMalus();
			addPriceMalus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::tsunami)
		{
			addDamageBonus();
			addMagMalus();
			addAccuracyBonus();
			addPriceBonus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::nova)
		{
			addDamageBonus();
			addDamageBonus();
			addMagMalus();
			addAccuracyMalus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::dai_lung)
		{
			addDamageMalus();
			addMagBonus();
			addFireRateBonus();
			addSpecialMalus();
			addPriceMalus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::constitution)
		{
			addDamageBonus();
			addDamageBonus();
			addFireRateMalus();
			addFireRateMalus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::techtronika)
		{
			addDamageMalus();
			addMagBonus();
			addFireRateBonus();
			addFireRateBonus();
			addAccuracyMalus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::sanroo)
		{
			addConcealMalus();
			addPriceBonus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::hydrosubsidium)
		{
			addMagBonus();
			addFireRateMalus();
			addSpecialBonus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::rostovic)
		{
			addFireRateBonus();
			addAccuracyMalus();
			addPriceMalus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::malorian)
		{
			addSkillMalus();
			addDamageBonus();
			addPriceBonus();
		}
		else
		{
			continue;
		}
	}
}

void MeleeWeapon::tweakStats()
{
	std::array<Part, 3> parts{ m_material, m_body, m_grip };

	for (int i{ 0 }; i < parts.size(); ++i)
	{
		if (parts[i].getBrand() == WeaponCreationTools::militech)
		{
			addHandlingBonus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::arasaka)
		{
			addDamageBonus();
			addHandlingBonus();
			addAttackSpeedMalus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::kendachi)
		{
			addDamageBonus();
			addHandlingMalus();
			addAttackSpeedBonus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::everest)
		{
			addDamageMalus();
			addHandlingBonus();
			addAttackSpeedBonus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::sanroo)
		{
			addPriceBonus();
			addConcealMalus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::slamdance)
		{
			addHandlingBonus();
			addAttackSpeedBonus();
			addConcealMalus();
		}
		else
		{
			continue;
		}
	}
}

void Grenade::tweakStats()
{
	std::array<Part, 3> parts{ m_reagent, m_body, m_fuse };

	for (int i{ 0 }; i < parts.size(); ++i)
	{
		if (parts[i].getBrand() == WeaponCreationTools::gunmart)
		{
			addFuseTimerBonus();
			addDurationMalus();
			addSpecialMalus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::centurian)
		{
			addDamageBonus();
			addDamageBonus();
			addFuseTimerBonus();
			addRadiusBonus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::great_lakes)
		{
			addFuseTimerMalus();
			addFuseTimerMalus();
			addDurationMalus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::hydrosubsidium)
		{
			addDamageMalus();
			addSpecialBonus();
			addSpecialBonus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::ktech)
		{
			addFuseTimerMalus();
			addRadiusMalus();
		}
		else if (parts[i].getBrand() == WeaponCreationTools::militech)
		{
			addDamageBonus();
			addFuseTimerBonus();
			addRadiusBonus();
			addRadiusBonus();
			addDurationMalus();
		}
		else
		{
			continue;
		}
	}
}