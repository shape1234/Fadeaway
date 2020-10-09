#include "Switcher.h"

Switcher::Switcher() : IModule(0x0, Category::COMBAT, "Switches to first hotbar on attack (Meant for Pocketmine [PMMP] Servers)") {
}

Switcher::~Switcher() {
}

const char* Switcher::getModuleName() {
	return ("Switcher");
}

void Switcher::onAttack(C_Entity* attackedEnt) {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	//int slot = supplies->selectedHotbarSlot;
	//supplies->selectedHotbarSlot = slot;

	supplies->selectedHotbarSlot = 0;
}
