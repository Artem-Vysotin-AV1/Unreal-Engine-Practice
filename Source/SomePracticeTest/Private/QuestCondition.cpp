// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestCondition.h"

DEFINE_LOG_CATEGORY(QuestLog)

void UQuestCondition::Complete()
{
	UE_LOG(QuestLog, Log, TEXT("Condition %s completed"), *GetNameSafe(this), *GetNameSafe(GetOuter()))

	bCompleted = true;
	OnQuestConditionCompleted.Broadcast();
	StopCondition();
}