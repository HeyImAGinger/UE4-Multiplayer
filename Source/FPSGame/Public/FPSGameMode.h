// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category="Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

public:

	AFPSGameMode();

	void CompleteMission(APawn* InstigatorPawn, bool IsMissionSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gamemode")
	void OnMissionCompleted(APawn* InstigatorPawn, bool IsMissionSuccess);
};



