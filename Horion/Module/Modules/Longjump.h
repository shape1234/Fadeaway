#pragma once
#include "Module.h"

class Longjump : public IModule {
private:
	int delay = 0;
	int hasJumped = 0;
	bool isBypass = false;
	float speedMod = 1;
	float upvel = 0.35f;

public:
	C_MovePlayerPacket* jetpack = nullptr;
	Longjump();
	~Longjump();

	virtual void onTick(C_GameMode* gm) override;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
