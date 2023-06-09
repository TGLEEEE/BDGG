// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBase.h"

#include "BDGGGameMode.h"
#include "BDGGPlayerState.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/WidgetComponent.h"


// Sets default values
ABrickBase::ABrickBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetRelativeScale3D(FVector(0.25f));

	scoreWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("scoreWidget"));
	scoreWidget->SetupAttachment(meshComp);
	scoreWidget->SetWidgetSpace(EWidgetSpace::Screen);
	scoreWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void ABrickBase::BeginPlay()
{
	Super::BeginPlay();

	gm = Cast<ABDGGGameMode>(GetWorld()->GetAuthGameMode());
	scoreWidget->SetComponentTickEnabled(false);
}

// Called every frame
void ABrickBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrickBase::OnBlockHit()
{
	//점수를 올린다.
	AddScore();
}


void ABrickBase::SpawnFX_Implementation()
{
	auto owningPawn = Cast<APawn>(GetOwner());

	if (owningPawn == nullptr)
	{
		return;
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), niagara, GetActorLocation(), GetActorRotation());

	meshComp->SetHiddenInGame(true);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (owningPawn && owningPawn->GetController() && owningPawn->GetController()->IsLocalController())
	{
		scoreWidget->SetVisibility(true);
		scoreWidget->SetComponentTickEnabled(true);
	}

	//3초 후에 완전히 파괴
	FTimerHandle destroyTimer;
	GetWorldTimerManager().SetTimer(destroyTimer, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
		}), 2.0f, false);
}

void ABrickBase::AddScore_Implementation()
{
	auto owningPawn = Cast<APawn>(GetOwner());

	if(owningPawn == nullptr)
	{
		return;
	}

	auto ps = Cast<ABDGGPlayerState>(owningPawn->GetPlayerState());
	if (ps)
	{
		ps->SetScore(ps->GetScore() + brickScore);
		UE_LOG(LogTemp, Warning, TEXT("%f"), ps->GetScore());
	}
	//나이아가라 스폰, 블럭 안보이게 처리
	SpawnFX();
}