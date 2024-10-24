#pragma once
//#include "bullet.h"
//#include "skeet.h"
//#include "UiPackage.h"

class Skeet;
class UiPackage;
class Missile;

class UiMessage
{
public:
	virtual ~UiMessage() = default;
	virtual void send(UiPackage* package) = 0;

	UiMessage() = default;
};


class FirePelletMessage : public UiMessage
{
public:
	void send(UiPackage* package) override;
	FirePelletMessage(Skeet* skeet) {Skeet = skeet;}

private:
	Skeet* Skeet;
};


class FireBombMessage : public UiMessage {
public:
	void send(UiPackage* package) override;
	FireBombMessage(Skeet* skeet){Skeet = skeet;}

private:
	Skeet* Skeet;
};


class FireMissileMessage : public UiMessage
{
public:
	void send(UiPackage* package) override;
	FireMissileMessage(Skeet* skeet);
	
private:
	Skeet* pSkeet;
};


class ResetGameMessage : public UiMessage {
public:
	void send(UiPackage* package) override;
	ResetGameMessage(Skeet* skeet);

private:
	Skeet* pSkeet;
};


class DisplayBullseyeMessage : public UiMessage {
public:
	void send(UiPackage* package) override;
	DisplayBullseyeMessage(Skeet* skeet);

private:
	Skeet* pSkeet;
};


class GetMovementMessage : public UiMessage{

public:
	void send(UiPackage* package) override;
	GetMovementMessage(Missile* target);
	
private:
	Missile* Target;
};