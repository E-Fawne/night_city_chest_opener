#ifndef SAVINGIMPLEMENTATION
#define SAVINGIMPLEMENTATION

int getID(char type, std::string username);
int prefixToNum(std::string_view prefix);
std::string_view numToPrefix(std::string prefixNum);
std::string firearmBrandSpecialToText(std::string brandSpecial);
std::string firearmHSDMALexcept(std::string brandSpecial);
std::string MALexcept2(std::string brandSpecial);
std::string meleeArasakaSpecialToText(std::string brandSpecial);
std::string meleeBrandSpecialToText(std::string brandSpecial);
std::string grenadeSpecificsToText(std::string grenadeSpecifics);
Firearm readFirearmSerialNumber(std::string serialNumber);
MeleeWeapon readMeleeSerialNumber(std::string serialNumber);
Grenade readGrenadeSerialNumber(std::string serialNumber);
std::string brandSpecialToString(const Firearm& firearm);
std::string brandSpecialToString(const MeleeWeapon& melee);
std::string specificsToString(const Grenade& grenade);
std::string generateSerialNumber(const Firearm& firearm);
std::string generateSerialNumber(const MeleeWeapon& melee);
std::string generateSerialNumber(const Grenade& grenade);
void deleteWeapon(std::string username, std::string deletionID);
void saveWeapon(const Firearm& firearm, std::string username);
void saveWeapon(const MeleeWeapon& melee, std::string username);
void saveWeapon(const Grenade& grenade, std::string username);
void modifyWeapon(std::string username, std::string weaponID);
void browseSaveFile(std::string username);

#endif