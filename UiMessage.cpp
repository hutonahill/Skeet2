#include "UiMessage.h"
#include "UiPackage.h"

#include "skeet.h"

void FirePelletMessage::send(UiPackage* package) {
	pSkeet->FirePellet(package->Space);
}

void FireBombMessage::send(UiPackage* package) {
	Skeet->FireBomb(package->B);
}

void FireMissileMessage::send(UiPackage* package) {
	pSkeet->FireMissile(package->M);
}

void ResetGameMessage::send(UiPackage* package) {
	pSkeet->ResetGame(package->Space);
}

void DisplayBullseyeMessage::send(UiPackage* package) {
	pSkeet->DisplayBullseye(package->Shift);
}

void GetMovementMessage::send(UiPackage* package) {
	Target->input(package->Up, package->Down, package->B);
}

void MoveGunMessage::send(UiPackage* package) {
	pSkeet->MoveGun( package->Up + package->Right, package->Down + package->Left);
}


FirePelletMessage::FirePelletMessage(Skeet* skeet) {
	pSkeet = skeet;
}

FireMissileMessage::FireMissileMessage(Skeet* skeet) {
	pSkeet = skeet;
}

ResetGameMessage::ResetGameMessage(Skeet* skeet) {
	pSkeet = skeet;
}

DisplayBullseyeMessage::DisplayBullseyeMessage(Skeet* skeet) {
	pSkeet = skeet;
}

GetMovementMessage::GetMovementMessage(Missile* target) {
	Target = target;
}

MoveGunMessage::MoveGunMessage(Skeet* skeet) {
	pSkeet = skeet;
}
