// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameMode.h"

#include "EngineUtils.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "FPSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool IsMissionSuccess)
{
	if (InstigatorPawn)
	{

		if (SpectatingViewpointClass) {

			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			//change viewtarget if any valid actors found
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];

				for (TActorIterator<APawn> It(GetWorld()); It; ++It)
				{
					APlayerController* PC = Cast<APlayerController>(It->Controller);
					if (PC)
					{
						PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}

				//APlayerController* PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());
				//if (PlayerController)
				//{
				//	PlayerController->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				//}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update Gamemode class with valid subclass. Cannot change spectating viewtarget."))
		}
	}
	AFPSGameState* GameState = GetGameState<AFPSGameState>();
	if (GameState)
	{
		GameState->MulticastOnMissionComplete(InstigatorPawn, IsMissionSuccess);
	}

	OnMissionCompleted(InstigatorPawn, IsMissionSuccess);

}
