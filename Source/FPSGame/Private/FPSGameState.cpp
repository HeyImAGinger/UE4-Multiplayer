// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"

#include "EngineUtils.h"
#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool IsMissionSuccess)
{
	for (TActorIterator<APawn> It(GetWorld()); It; ++It)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Controller);
		if (PC && PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigatorPawn, IsMissionSuccess);

			// Disable Input
			APawn* MyPawn = PC->GetPawn();
			if (MyPawn)
			{
				UE_LOG(LogTemp, Warning, TEXT("CA PASSE ICi"));
				MyPawn->DisableInput(PC);
			}
		}
	}
}
