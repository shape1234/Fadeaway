#include "HiveFly.h"

HiveFly::HiveFly() : IModule('Z', Category::MOVEMENT, "Flight bypass for Hive, 0.7 recommended") {
	registerFloatSetting("speed", &this->speedMod, 1, 0.3f, 2.5f);
	this->registerBoolSetting("V2", &this->isBypass, this->isBypass);
}

HiveFly::~HiveFly() {
}

bool HiveFly::isFlashMode() {
	return true;
}

void HiveFly::onDisable() {
	vec3_t pos = *g_Data.getLocalPlayer()->getPos();
	g_Data.getLocalPlayer()->setPos((pos, pos, pos));
	g_Data.getLocalPlayer()->velocity = vec3_t(0, 0, 0);
}

void HiveFly::onEnable() {
	vec3_t moveVec;
	float calcYaw = (g_Data.getLocalPlayer()->yaw + 90) * (PI / 180);
	float calcPitch = (g_Data.getLocalPlayer()->pitch) * -(PI / 180);
	float teleportX = cos(calcYaw) * cos(calcPitch) * -0.0f;
	float teleportZ = sin(calcYaw) * cos(calcPitch) * -0.0f;
	moveVec.y = +0.5;
	vec3_t pos = *g_Data.getLocalPlayer()->getPos();
	g_Data.getLocalPlayer()->setPos(vec3_t(pos.x + teleportX, pos.y + 0.5f, pos.z + teleportZ));
}

const char* HiveFly::getModuleName() {
	return ("HiveFly");
}

void HiveFly::onTick(C_GameMode* gm) {
	float calcYaw = (gm->player->yaw + 90) * (PI / 180);
	float calcPitch = (gm->player->pitch) * -(PI / 180);
	float calcYawRev = (gm->player->yaw - 90) * (PI / 180);

	if (!isBypass) {
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speedMod;
		moveVec.y = -0.001 * speedMod;
		moveVec.z = sin(calcYaw) * speedMod;

		gm->player->lerpMotion(moveVec);
	} else {
		delay++;
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speedMod;
		moveVec.y = -0.001 * speedMod;
		moveVec.z = sin(calcYaw) * speedMod;

		gm->player->lerpMotion(moveVec);

		if (delay >= 15) {
			vec3_t moveVec;
			moveVec.x = (cos(calcYawRev) * speedMod) / 3;
			moveVec.y = +0.0005 * speedMod;
			moveVec.z = (sin(calcYawRev) * speedMod) / 3;

			gm->player->lerpMotion(moveVec);
			delay = 0;
		}
	}
}
