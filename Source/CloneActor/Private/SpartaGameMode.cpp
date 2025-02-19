#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "BadAircraft.h"
#include "SpartaPlayerController.h"
#include "SpartaGameState.h"

ASpartaGameMode::ASpartaGameMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	DefaultPawnClass = ABadAircraft::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
	GameStateClass = ASpartaGameState::StaticClass();
}

