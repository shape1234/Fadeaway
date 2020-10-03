#include "MineplexFly.h"

MineplexFly::MineplexFly() : IModule('R', Category::MOVEMENT, "Flight bypass for Mineplex") {
	registerFloatSetting("speed", &this->speedMod, 1, 0.3f, 2.5f);
	registerFloatSetting("Y-Up", &this->yUp, 1, 0.0f, 1.f);
	this->registerBoolSetting("V2", &this->isBypass, this->isBypass);
}

MineplexFly::~MineplexFly() {
}

bool MineplexFly::isFlashMode() {
	return true;
}

void MineplexFly::onDisable() {
	vec3_t pos = *g_Data.getLocalPlayer()->getPos();
	g_Data.getLocalPlayer()->setPos((pos, pos, pos));
	g_Data.getLocalPlayer()->velocity = vec3_t(0, 0, 0);
}

void MineplexFly::onEnable() {
	vec3_t moveVec;
	float calcYaw = (g_Data.getLocalPlayer()->yaw + 90) * (PI / 180);
	float calcPitch = (g_Data.getLocalPlayer()->pitch) * -(PI / 180);
	float teleportX = cos(calcYaw) * cos(calcPitch) * -0.0f;
	float teleportZ = sin(calcYaw) * cos(calcPitch) * -0.0f;
	moveVec.y = +yUp;
	vec3_t pos = *g_Data.getLocalPlayer()->getPos();
	g_Data.getLocalPlayer()->setPos(vec3_t(pos.x + teleportX, pos.y + yUp, pos.z + teleportZ));
}

const char* MineplexFly::getModuleName() {
	return ("MineplexFly");
}

void MineplexFly::onTick(C_GameMode* gm) {
	float calcYaw = (gm->player->yaw + 90) * (PI / 180);
	float calcPitch = (gm->player->pitch) * -(PI / 180);

	if (!isBypass) {
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speedMod;
		moveVec.y = -0.0 * speedMod;
		moveVec.z = sin(calcYaw) * speedMod;

		gm->player->lerpMotion(moveVec);
	} else {
		delay++;

		if (delay >= 5) {
			vec3_t pos = *g_Data.getLocalPlayer()->getPos();
			C_MovePlayerPacket a(g_Data.getLocalPlayer(), pos);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
			pos.y -= 0.001f;
			a = C_MovePlayerPacket(g_Data.getLocalPlayer(), pos);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);

			gm->player->velocity.y = 0.065f;
			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
			moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

			gm->player->velocity.x = moveVec.x;
			gm->player->velocity.z = moveVec.z;

			float teleportX = cos(calcYaw) * cos(calcPitch) * -0.00000005f;
			float teleportZ = sin(calcYaw) * cos(calcPitch) * -0.00000005f;

			pos = *gm->player->getPos();
			g_Data.getLocalPlayer()->setPos(vec3_t(pos.x + teleportX, pos.y - 0.05f, pos.z + teleportZ));

			gm->player->velocity.y -= 0.05f;
			delay = 0;
		}
	}
}
