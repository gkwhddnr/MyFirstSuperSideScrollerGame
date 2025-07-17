// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperSideScroller2GameMode.h"
#include "SuperSideScroller2Character.h"
#include "UObject/ConstructorHelpers.h"

ASuperSideScroller2GameMode::ASuperSideScroller2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
