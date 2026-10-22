// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolumeQuestCondition.h"

#include "Quest.h"

void UTriggerVolumeQuestCondition::StartCondition()
{
  AQuest* Quest = Cast<AQuest>(GetOuter());

  if (bCompleteOnExit) {
    Quest->OnActorEndOverlap.AddDynamic(this, &UTriggerVolumeQuestCondition::OnOverlap);
  } else {
    Quest->OnActorBeginOverlap.AddDynamic(this, &UTriggerVolumeQuestCondition::OnOverlap);
  }

}

void UTriggerVolumeQuestCondition::StopCondition()
{
  AQuest* Quest = Cast<AQuest>(GetOuter());

  if (bCompleteOnExit)
    Quest->OnActorEndOverlap.RemoveDynamic(this, &UTriggerVolumeQuestCondition::OnOverlap);
  else
    Quest->OnActorBeginOverlap.RemoveDynamic(this, &UTriggerVolumeQuestCondition::OnOverlap);
}

void UTriggerVolumeQuestCondition::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
  if (OtherActor->ActorHasTag(OtherTag))
  {
    Complete();
  }
}