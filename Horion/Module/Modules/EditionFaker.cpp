#include "EditionFaker.h"

EditionFaker::EditionFaker() : IModule(0x0, Category::MISC, "Fakes your device to IOS") {
}

EditionFaker::~EditionFaker() {
}

int EditionFaker::getFakedEditon() {
	// static const char* gameEditons[] = { "Unknown", "Android", "iOS", "macOS", "FireOS", "GearVR", "HoloLens", "Windows 10 (PC)", "Windows", "Dedicated", "Orbis", "NX" };

	return 2;  // IOS
}

const char* EditionFaker::getModuleName() {
	return ("EditionFaker");
}
