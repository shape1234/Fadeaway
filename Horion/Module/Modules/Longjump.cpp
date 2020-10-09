#include "Longjump.h"

Longjump::Longjump() : IModule('G', Category::MOVEMENT, "Jump farther with speed") {
	registerFloatSetting("speed", &this->speedMod, 1, 0.5f, 4.f);
	registerFloatSetting("up", &this->upvel, 1, 0.1f, 4.f);
	//this->registerBoolSetting("Bypass", &this->isBypass, this->isBypass);
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

	/*
	if (!isBypass) {
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
		moveVec.y = +0.35f;
		moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

		gm->player->lerpMotion(moveVec);
	} else {
		delay++;

		if (delay >= 5) {
			vec3_t pos = *g_Data.getLocalPlayer()->getPos();
			C_MovePlayerPacket a(g_Data.getLocalPlayer(), pos);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
			pos.y += 0.35f;
			a = C_MovePlayerPacket(g_Data.getLocalPlayer(), pos);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);

			gm->player->velocity.y = 0.465f;
			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
			moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

			gm->player->velocity.x = moveVec.x;
			gm->player->velocity.z = moveVec.z;

			float teleportX = cos(calcYaw) * cos(calcPitch) * 0.00000005f;
			float teleportZ = sin(calcYaw) * cos(calcPitch) * 0.00000005f;

			pos = *gm->player->getPos();
			g_Data.getLocalPlayer()->setPos(vec3_t(pos.x + teleportX, pos.y - 0.15f, pos.z + teleportZ));

			gm->player->velocity.y -= 0.15f;
			delay = 0;
		}
	}*/
}
