#include "Longjump.h"

Longjump::Longjump() : IModule('G', Category::MOVEMENT, "Jump farther with speed") {
	registerFloatSetting("speed", &this->speedMod, 1, 0.5f, 4.f);
	registerFloatSetting("up", &this->upvel, 1, 0.1f, 4.f);
}

Longjump::~Longjump() {
}

const char* Longjump::getModuleName() {
	return ("LongJump");
}

void Longjump::onTick(C_GameMode* gm) {
	float calcYaw = (gm->player->yaw + 90) * (PI / 180);
	float calcPitch = (gm->player->pitch) * -(PI / 180);
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (input == nullptr)
		return;

	if (localPlayer->onGround == true && GameData::isKeyDown(*input->spaceBarKey) && hasJumped == 0) {
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
		moveVec.y = + upvel;
		moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

		gm->player->lerpMotion(moveVec);
		hasJumped = 1;
	} else if (!GameData::isKeyDown(*input->spaceBarKey) && localPlayer->onGround == true) {
		hasJumped = 0;
	}
}
