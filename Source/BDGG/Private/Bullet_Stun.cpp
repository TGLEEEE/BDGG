// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet_Stun.h"

#include "BDGGPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void ABullet_Stun::BulletCrash(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	//Super::BulletCrash(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bBFromSweep, SweepResult);

	player = Cast<ABDGGPlayer>(OtherActor);

	if(player)
	{
		pc = Cast<APlayerController>(player->GetController());
		//맞은 플레이어 2초간 행동 불가
		if(pc)
		{
			UE_LOG(LogTemp, Warning, TEXT("Stun Bullet Hit"))
			//맞은 플레이어 인풋 비활성화
			pc->GetPawn()->DisableInput(pc);
			//플레이어 몸통에 짜릿짜릿 파티클 추가
			Stunned();
			//2초 후에 플레이어 인풋 활성화
			FTimerHandle stunTimer;
			GetWorldTimerManager().SetTimer(stunTimer, this, &ABullet_Stun::StunOver, 2.0f, false);
		}
	}
	meshComp->SetHiddenInGame(true);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle destroyTimer;
	GetWorldTimerManager().SetTimer(destroyTimer, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
		}), 2.5f, false);
}

void ABullet_Stun::StunOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Stun Bullet Destroy"))
	pc->GetPawn()->EnableInput(pc);
}

void ABullet_Stun::Stunned_Implementation()
{
	if(player)
	{
		auto lightningFX = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), lightning, player->GetActorLocation() + FVector(0, 0, -40), player->GetActorRotation());
		FTimerHandle lightningTimer;
		if(lightningFX)
		{
			GetWorldTimerManager().SetTimer(lightningTimer, FTimerDelegate::CreateLambda([&]()
				{
					lightningFX->DestroyComponent();
				}), 2.0f, false);
		}
	}
}
