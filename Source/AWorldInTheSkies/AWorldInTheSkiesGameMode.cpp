#include "AWorldInTheSkiesGameMode.h"

#include "Jumper.h"

AAWorldInTheSkiesGameMode::AAWorldInTheSkiesGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}