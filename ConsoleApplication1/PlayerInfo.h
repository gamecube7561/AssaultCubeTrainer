#pragma once
#include <Windows.h>


class playerInfo {
	public:
		uintptr_t base = 0x57B0B8;
		int xCoord = 0x28;
		int yCoord = 0x2C;
		int zCoord = 0x30;
		int xYaw = 0x34;
		int yPitch = 0x38;
		int zRoll = 0x3C;
		int speed = 0x74;
		int health = 0xEC;
		int armour = 0xF0;
		int ammo_pistol_reserve = 0x108;
		int ammo_ar_reserve = 0x11C;
		int ammo_pistol = 0x12C;
		int ammo_ar = 0x140;
		int grenade = 0x144;
		int username = 0x205;
};