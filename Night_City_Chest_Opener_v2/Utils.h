#ifndef WEAPONUTILS
#define WEAPONUTILS

#include <array>
#include "Random.h"
#include <string_view>
#include <string>
#include <iostream>

namespace WeaponCreationTools
{
	enum WeaponType
	{
		HG,
		H_HG,
		VH_HG,
		SMG,
		H_SMG,
		SG,
		AR,
		SR,
		Bow,
		GL,
		RL,
		Melee,
		I_Melee,
		H_Melee,
		VH_Melee,
		Util_G,
		Explo_G,
		Pers_G,
		max_weapon_types
	};

	std::string_view getTypeText(WeaponType type);

	enum BrandName
	{
		militech,
		arasaka,
		gunmart,
		tsunami,
		nova,
		dai_lung,
		constitution,
		techtronika,
		sanroo,
		hydrosubsidium,
		rostovic,
		malorian,
		kendachi,
		everest,
		slamdance,
		centurian,
		great_lakes,
		ktech,
		max_brand_names
	};

	std::string_view getBrandText(BrandName brand);

	static constexpr std::array<BrandName, 9> HG_Brand{ militech, gunmart, tsunami, nova, dai_lung, techtronika, sanroo, hydrosubsidium, rostovic };
	static constexpr std::array<BrandName, 6> H_HG_Brand{ arasaka, tsunami, nova, dai_lung, techtronika, hydrosubsidium };
	static constexpr std::array<BrandName, 5> VH_HG_Brand{ militech, nova, constitution, rostovic, malorian };
	static constexpr std::array<BrandName, 6> SMG_Brand{ gunmart, nova, dai_lung, techtronika, sanroo, rostovic };
	static constexpr std::array<BrandName, 6> H_SMG_Brand{ militech, arasaka, tsunami, nova, hydrosubsidium, malorian };
	static constexpr std::array<BrandName, 8> SG_Brand{ militech, gunmart, nova, constitution, techtronika, sanroo, hydrosubsidium, rostovic };
	static constexpr std::array<BrandName, 8> AR_Brand{ militech, arasaka, tsunami, dai_lung, constitution, techtronika, rostovic, malorian };
	static constexpr std::array<BrandName, 6> SR_Brand{ arasaka, tsunami, constitution, techtronika, sanroo, malorian };
	static constexpr std::array<BrandName, 4> Bow_Brand{ arasaka, dai_lung, sanroo, hydrosubsidium };
	static constexpr std::array<BrandName, 5> GL_Brand{ militech, gunmart, dai_lung, constitution, hydrosubsidium };
	static constexpr std::array<BrandName, 7> RL_Brand{ militech, arasaka, gunmart, constitution, techtronika, hydrosubsidium, malorian };

	static constexpr std::array<BrandName, 5> Melee_Brand{ arasaka, militech, kendachi, everest, sanroo };
	static constexpr std::array<BrandName, 4> I_Melee_Brand{ militech, everest, sanroo, slamdance };
	static constexpr std::array<BrandName, 4> H_Melee_Brand{ arasaka, kendachi, sanroo, slamdance };
	static constexpr std::array<BrandName, 3> VH_Melee_Brand{ arasaka, militech, everest };

	static constexpr std::array<BrandName, 5> Util_G_Brand{ gunmart, centurian, hydrosubsidium, ktech, militech };
	static constexpr std::array<BrandName, 4> Explo_G_Brand{ gunmart, great_lakes, ktech, militech };
	static constexpr std::array<BrandName, 3> Pers_G_Brand{ centurian, great_lakes, hydrosubsidium };

	enum Rarity
	{
		common,
		mediocre,
		superior,
		excellent,
		exotic,
		max_rarity
	};

	std::string_view getRarityText(Rarity rarity);

	int dieThrow(int dieNum);
	const WeaponCreationTools::WeaponType& generateRandomType();
	const WeaponCreationTools::Rarity& getRandomRarity();
}

class Part
{
private:
	WeaponCreationTools::BrandName m_brand{ WeaponCreationTools::max_brand_names };

public:
	Part(const WeaponCreationTools::BrandName brand)
		: m_brand{ brand }
	{}

	const WeaponCreationTools::BrandName& getBrand() const { return m_brand; }
};

class Weapon
{
private:
	WeaponCreationTools::WeaponType m_type{};
	WeaponCreationTools::Rarity m_rarity{};
	bool m_concealable{};
	int m_concealBonus{};
	int m_hands{};
	int m_price{};
	int m_damage_extra{};
	int m_num_dice{};
	int m_skillBonus{};
	int m_specialBonus{};
	std::string m_prefix{};

public:
	const Part& generateRandomPart(const Weapon& weapon);

	Weapon(const WeaponCreationTools::WeaponType& type, const WeaponCreationTools::Rarity& rarity)
		: m_type{ type }
		, m_rarity{ rarity }
	{
	}

	std::string_view getSkillType() const;
	const WeaponCreationTools::WeaponType getType() const { return m_type; }
	const WeaponCreationTools::Rarity& getRarity() const { return m_rarity; }
	bool getConcealable() const { return m_concealable; }
	int getConcealBonus() const { return m_concealBonus; }
	int getHands() const { return m_hands; }
	int getPrice() const { return m_price; }
	int getDamageExtra() const { return m_damage_extra; }
	int getDamage() const { return m_num_dice; }
	int getSkillBonus() const { return m_skillBonus; }
	int getSpecialBonus() const { return m_specialBonus; }
	std::string_view getPrefix() const { return m_prefix; }
	virtual void failSafe();
	void setPrefix(std::string_view prefix) { m_prefix = prefix; }

	virtual void applyRarityBonus();
	void generateFirearmPrefix();

	void generateMeleePrefix();

	void addConcealBonus() { ++m_concealBonus; }
	void addPriceBonus() { m_price += 50; }
	void addDamageBonus() { ++m_damage_extra; }
	void addSkillBonus() { ++m_skillBonus; }
	void addSpecialBonus() { ++m_specialBonus; }

	void addConcealMalus() { --m_concealBonus; }
	void addPriceMalus() { m_price -= 50; }
	void addDamageMalus() { --m_damage_extra; }
	void addSkillMalus() { --m_skillBonus; }
	void addSpecialMalus() { --m_specialBonus; }

	virtual void generateHGBase();
	virtual void generateHHGBase();
	virtual void generateVHHGBase();
	virtual void generateSMGBase();
	virtual void generateHSMGBase();
	virtual void generateSGBase();
	virtual void generateARBase();
	virtual void generateSRBase();
	virtual void generateBowBase();
	virtual void generateGLBase();
	virtual void generateRLBase();
	virtual void generateMeleeBase();
	virtual void generateIMeleeBase();
	virtual void generateHMeleeBase();
	virtual void generateVHMeleeBase();
	virtual void generateUtilGrenadeBase();
	virtual void generateExploGrenadeBase();
	virtual void generatePersGrenadeBase();
};

class Firearm : public Weapon
{
private:
	double m_mag{};
	int m_fireRate{};
	int m_fireRateCounter{};
	int m_accuracy{};
	std::string m_ammoType{};
	Part m_body{ WeaponCreationTools::max_brand_names };
	Part m_barrel{ WeaponCreationTools::max_brand_names };
	Part m_scope{ WeaponCreationTools::max_brand_names };
	Part m_grip{ WeaponCreationTools::max_brand_names };
	Part m_stock{ WeaponCreationTools::max_brand_names };
	std::string m_weaponSpecial{};
	std::string m_brandSpecial{};
	std::string m_malorianSpecial2{};

public:
	Firearm(const WeaponCreationTools::WeaponType& type, const WeaponCreationTools::Rarity& rarity)
		: Weapon{type, rarity}
	{
		using namespace WeaponCreationTools;

		m_body = generateRandomPart(*this);
		m_barrel = generateRandomPart(*this);
		m_scope = generateRandomPart(*this);
		m_grip = generateRandomPart(*this);

		if (getType() == H_SMG || getType() == SG || getType() == AR || getType() == SR || getType() == Bow || getType() == GL || getType() == RL)
			m_stock = generateRandomPart(*this);

		switch (getType())
		{
		case HG: generateHGBase(); break;
		case H_HG: generateHHGBase(); break;
		case VH_HG: generateVHHGBase(); break;
		case SMG: generateSMGBase(); break;
		case H_SMG: generateHSMGBase(); break;
		case SG: generateSGBase(); break;
		case AR: generateARBase(); break;
		case SR: generateSRBase(); break;
		case Bow: generateBowBase(); break;
		case GL: generateGLBase(); break;
		case RL: generateRLBase(); break;
		default: std::cout << "Something went wrong"; break;
		}

		applyRarityBonus();
		tweakStats();

		generateFirearmPrefix();
		setWeaponSpecial();
		setBrandSpecial();
		setSpecialExtra();

		failSafe();
	}

	Firearm(const WeaponCreationTools::WeaponType& type, const WeaponCreationTools::Rarity& rarity, const Part& body, const Part& barrel, const Part& scope, const Part& grip, const Part& stock, std::string_view prefix,
	std::string_view brandSpecial, std::string_view malorianSpecial2)
		: Weapon{type, rarity}
		, m_body {body}
		, m_barrel {barrel}
		, m_scope {scope}
		, m_grip {grip}
		, m_brandSpecial{ brandSpecial }
		, m_malorianSpecial2 {malorianSpecial2}
	{
		using namespace WeaponCreationTools;

		if (getType() == H_SMG || getType() == SG || getType() == AR || getType() == SR || getType() == Bow || getType() == GL || getType() == RL)
			m_stock = stock;

		switch (getType())
		{
		case HG: generateHGBase(); break;
		case H_HG: generateHHGBase(); break;
		case VH_HG: generateVHHGBase(); break;
		case SMG: generateSMGBase(); break;
		case H_SMG: generateHSMGBase(); break;
		case SG: generateSGBase(); break;
		case AR: generateARBase(); break;
		case SR: generateSRBase(); break;
		case Bow: generateBowBase(); break;
		case GL: generateGLBase(); break;
		case RL: generateRLBase(); break;
		default: std::cout << "Something went wrong"; break;
		}

		applyRarityBonus();
		tweakStats();

		setWeaponSpecial();
		setPrefix(prefix);

		failSafe();
	}

	friend const std::ostream& operator<<(const std::ostream& out, const Firearm& firearm);

	void applyRarityBonus();
	void tweakStats();

	void setWeaponSpecial();
	void setBrandSpecial();
	void setSpecialExtra();

	void addMagBonus() { m_mag *= 1.25; }
	void addFireRateBonus()
	{
		++m_fireRateCounter;
		if (m_fireRateCounter == 2)
		{
			++m_fireRate;
			m_fireRateCounter = 0;
		}
	}
	void addAccuracyBonus() { ++m_accuracy; }

	void addMagMalus() { m_mag *= 0.75; }
	void addFireRateMalus()
	{
		--m_fireRateCounter;
		if (m_fireRateCounter == -2)
		{
			--m_fireRate;
			m_fireRateCounter = 0;
		}
	}
	void addAccuracyMalus() { --m_accuracy; }

	void generateHGBase();
	void generateHHGBase();
	void generateVHHGBase();
	void generateSMGBase();
	void generateHSMGBase();
	void generateSGBase();
	void generateARBase();
	void generateSRBase();
	void generateBowBase();
	void generateGLBase();
	void generateRLBase();

	void failSafe();
	friend void saveWeapon(const Firearm& weapon, std::string username);
	friend std::string generateSerialNumber(const Firearm& firearm);
	friend std::string brandSpecialToString(const Firearm& firearm);
	friend void modFirearm(std::string username, std::string weaponID);
};

class MeleeWeapon : public Weapon
{
private:
	int m_handling{};
	int m_attackSpeed{};
	int m_attackSpeedCounter{};
	bool m_throwable{};
	Part m_material{ WeaponCreationTools::max_brand_names };
	Part m_body{ WeaponCreationTools::max_brand_names };
	Part m_grip{ WeaponCreationTools::max_brand_names };
	std::string m_brandSpecial{};

public:
	MeleeWeapon(const WeaponCreationTools::WeaponType& type, const WeaponCreationTools::Rarity& rarity)
		: Weapon{type, rarity}
	{
		using namespace WeaponCreationTools;

		m_material = generateRandomPart(*this);
		m_body = generateRandomPart(*this);
		m_grip = generateRandomPart(*this);

		switch (getType())
		{
		case Melee: generateMeleeBase(); break;
		case I_Melee: generateIMeleeBase(); break;
		case H_Melee: generateHMeleeBase(); break;
		case VH_Melee: generateVHMeleeBase(); break;
		default: std::cout << "Something went wrong"; break;
		}
		
		applyRarityBonus();
		tweakStats();

		generateMeleePrefix();
		setBrandSpecial();
		setSpecialExtra();
		failSafe();

	}

	MeleeWeapon(const WeaponCreationTools::WeaponType& type, const WeaponCreationTools::Rarity& rarity, const Part& material, const Part& body, const Part& grip, std::string_view brandSpecial,
		std::string_view prefix)
		: Weapon{ type, rarity }
		, m_material {material}
		, m_body {body}
		, m_grip {grip}
		, m_brandSpecial {brandSpecial}
	{
		using namespace WeaponCreationTools;

		switch (getType())
		{
		case Melee: generateMeleeBase(); break;
		case I_Melee: generateIMeleeBase(); break;
		case H_Melee: generateHMeleeBase(); break;
		case VH_Melee: generateVHMeleeBase(); break;
		default: std::cout << "Something went wrong"; break;
		}

		applyRarityBonus();
		tweakStats();

		setPrefix(prefix);
		failSafe();
	}

	void applyRarityBonus();
	void setBrandSpecial();
	void setSpecialExtra();

	void tweakStats();

	void addHandlingBonus() { ++m_handling; }
	void addAttackSpeedBonus()
	{
		++m_attackSpeedCounter;

		if (m_attackSpeedCounter == 2)
		{
			++m_attackSpeed;
			m_attackSpeedCounter = 0;
		}
	}

	void addHandlingMalus() { --m_handling; }
	void addAttackSpeedMalus()
	{
		--m_attackSpeedCounter;

		if (m_attackSpeedCounter == -2)
		{
			--m_attackSpeed;
			m_attackSpeedCounter = 0;
		}
	}

	void generateMeleeBase();
	void generateIMeleeBase();
	void generateHMeleeBase();
	void generateVHMeleeBase();

	friend const std::ostream& operator<<(const std::ostream& out, const MeleeWeapon& melee);
	void failSafe();
	friend void saveWeapon(const MeleeWeapon& melee, std::string username);
	friend std::string generateSerialNumber(const MeleeWeapon& melee);
	friend std::string brandSpecialToString(const MeleeWeapon& melee);
};

class Grenade : public Weapon
{
private:
	int m_fuseTimer{};
	int m_fuseTimerCounter{};
	int m_radius{};
	int m_duration{};
	Part m_reagent{ WeaponCreationTools::max_brand_names };
	Part m_body{ WeaponCreationTools::max_brand_names };
	Part m_fuse{ WeaponCreationTools::max_brand_names };
	std::string m_grenadeSpecifics{};

public:
	Grenade(const WeaponCreationTools::WeaponType& type, const WeaponCreationTools::Rarity& rarity)
		: Weapon{ type, rarity }
	{
		using namespace WeaponCreationTools;

		m_reagent = generateRandomPart(*this);
		m_body = generateRandomPart(*this);
		m_fuse = generateRandomPart(*this);

		switch (getType())
		{
		case Explo_G: generateExploGrenadeBase(); break;
		case Util_G: generateUtilGrenadeBase(); break;
		case Pers_G: generatePersGrenadeBase(); break;
		default: std::cout << "Something went wrong"; break;
		}

		applyRarityBonus();
		tweakStats();

		generateSpecifics();

		failSafe();
	}

	Grenade(const WeaponCreationTools::WeaponType& type, const WeaponCreationTools::Rarity& rarity, const Part& reagent, const Part& body, const Part& fuse, std::string_view grenadeSpecifics)
		: Weapon{ type, rarity }
		, m_reagent {reagent}
		, m_body {body}
		, m_fuse {fuse}
		, m_grenadeSpecifics {grenadeSpecifics}
	{
		using namespace WeaponCreationTools;

		switch (getType())
		{
		case Explo_G: generateExploGrenadeBase(); break;
		case Util_G: generateUtilGrenadeBase(); break;
		case Pers_G: generatePersGrenadeBase(); break;
		default: std::cout << "Something went wrong"; break;
		}

		applyRarityBonus();
		tweakStats();

		failSafe();
	}

	void applyRarityBonus();
	void tweakStats();

	void addFuseTimerBonus()
	{
		++m_fuseTimerCounter;

		if (m_fuseTimerCounter == 2)
		{
			++m_fuseTimer;
			m_fuseTimerCounter = 0;
		}
	}

	void addRadiusBonus() { m_radius += 5; }
	void addDurationBonus() { ++m_duration; }

	void addFuseTimerMalus()
	{
		--m_fuseTimerCounter;

		if (m_fuseTimerCounter == -2)
		{
			--m_fuseTimer;
			m_fuseTimerCounter = 0;
		}
	}

	void addRadiusMalus() { m_radius -= 5; }
	void addDurationMalus() { --m_duration; }

	void generateUtilGrenadeBase();
	void generateExploGrenadeBase();
	void generatePersGrenadeBase();

	void generateSpecifics();

	void failSafe();

	friend const std::ostream& operator<<(const std::ostream& out, const Grenade& grenade);
	friend void saveWeapon(const Grenade& grenade, std::string username);
	friend std::string generateSerialNumber(const Grenade& grenade);
	friend std::string specificsToString(const Grenade& grenade);
};

void newlineSpam();

#endif