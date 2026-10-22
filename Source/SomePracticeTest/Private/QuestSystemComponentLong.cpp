// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystemComponentLong.h"

#include "Quest.h"

#include "EngineUtils.h"
#include "QuestCondition.h"

// Sets default values for this component's properties
UQuestSystemComponentLong::UQuestSystemComponentLong()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestSystemComponentLong::BeginPlay()
{
	UE_LOG(QuestLog, Log, TEXT("BeginPlay for Quest System Component"))

	Super::BeginPlay();

	for (const TSubclassOf<AQuest>& QuestClass : Quests)
	{
		GetWorld()->SpawnActor<AQuest>(QuestClass);
	}
	// ...
	
}

// Called every frame
void UQuestSystemComponentLong::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestSystemComponentLong::GetActiveAndStartedQuests(TArray<AQuest*>& OutQuests)
{
	for (AQuest* Quest : ActiveQuests)
	{
		EQuestStatus QuestStatus = Quest->GetQuestStatus();
		if (QuestStatus == EQuestStatus::Started || QuestStatus == EQuestStatus::Completed)
		{
			OutQuests.Add(Quest);
		}
	}
}


void UQuestSystemComponentLong::RegisterQuest(AQuest* NewQuest)
{
	ActiveQuests.AddUnique(NewQuest);
	UE_LOG(QuestLog, Log, TEXT("Register new quest: %s"), *GetNameSafe(NewQuest))
}