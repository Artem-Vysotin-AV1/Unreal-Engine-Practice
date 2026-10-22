// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "QuestSettings.h"
#include "QuestCondition.h"
#include "QuestSystemComponentLong.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
AQuest::AQuest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuest::BeginPlay()
{
	UE_LOG(QuestLog, Log, TEXT("BeginPlay for quest: $s"), *GetNameSafe(this))

	Super::BeginPlay();
	if (UQuestSystemComponentLong* QuestComponent = GetWorld()->GetAuthGameMode()->GetComponentByClass<UQuestSystemComponentLong>())
	{
		QuestComponent->RegisterQuest(this);
	}
	for (const TSubclassOf<UQuestCondition>& ConditionTemplate : QuestSettings->StartConditions)
	{
		if (!ensureMsgf(ConditionTemplate, TEXT("bas setup for quest %s"), *GetNameSafe(this)))
			return;

		UQuestCondition* QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
		QuestCondition->StartCondition();
		QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateStartStatus);
		StartConditions.Add(QuestCondition);
	}
	
}

// Called every frame
void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuest::UpdateStartStatus()
{
	UE_LOG(QuestLog, Log, TEXT("UpdateStartStatus for quest: %s"), *GetNameSafe(this))
	for (UQuestCondition* Condition : StartConditions)
	{
		if (!ensure(Condition))
			return;
		if (!Condition->IsCompleted())
		{
			return;
		}
	}
	SetQuestStatus(EQuestStatus::Started);
	for (const TSubclassOf<UQuestCondition>& ConditionTemplate : QuestSettings->EndConditions)
	{
		if (!ensureMsgf(ConditionTemplate, TEXT("bas setup for quest %s"), *GetNameSafe(this)))
			return;
		UQuestCondition* QuestCondition = NewObject<UQuestCondition>(this, ConditionTemplate);
		QuestCondition->StartCondition();
		QuestCondition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateEndStatus);
		EndConditions.Add(QuestCondition);
	}
}

void AQuest::UpdateEndStatus()
{
	UE_LOG(QuestLog, Log, TEXT("UpdateEndStatus for quest: %s"), *GetNameSafe(this))
	for (UQuestCondition* Condition : EndConditions)
	{
		if (!ensure(Condition))
			return;
		if (!Condition->IsCompleted())
		{
			return;
		}
	}
	SetQuestStatus(EQuestStatus::Completed);
}

void AQuest::SetQuestStatus(EQuestStatus Status) {
	UE_LOG(QuestLog, Log, TEXT("SetQuestStatus for quest: %s, status now is: %s"), *GetNameSafe(this), *UEnum::GetValueAsString(Status))

	QuestStatus = Status;
	OnQuestStatusChange.Broadcast(this, Status);
}

