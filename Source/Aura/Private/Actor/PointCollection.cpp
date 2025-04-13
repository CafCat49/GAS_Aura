// Copyright Caffeinated Cat


#include "Actor/PointCollection.h"

#include "AbilitySystem/AuraAbilitySystemBPLibrary.h"
#include "Kismet/KismetMathLibrary.h"

APointCollection::APointCollection()
{
	PrimaryActorTick.bCanEverTick = false;

	Pt_0 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_0"));
	ImmutablePts.Add(Pt_0);
	SetRootComponent(Pt_0);

	Pt_1 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_1"));
	ImmutablePts.Add(Pt_1);
	Pt_1->SetupAttachment(RootComponent);

	Pt_2 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_2"));
	ImmutablePts.Add(Pt_2);
	Pt_2->SetupAttachment(RootComponent);

	Pt_3 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_3"));
	ImmutablePts.Add(Pt_3);
	Pt_3->SetupAttachment(RootComponent);

	Pt_4 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_4"));
	ImmutablePts.Add(Pt_4);
	Pt_4->SetupAttachment(RootComponent);

	Pt_5 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_5"));
	ImmutablePts.Add(Pt_5);
	Pt_5->SetupAttachment(RootComponent);

	Pt_6 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_6"));
	ImmutablePts.Add(Pt_6);
	Pt_6->SetupAttachment(RootComponent);

	Pt_7 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_7"));
	ImmutablePts.Add(Pt_7);
	Pt_7->SetupAttachment(RootComponent);

	Pt_8 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_8"));
	ImmutablePts.Add(Pt_8);
	Pt_8->SetupAttachment(RootComponent);

	Pt_9 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_9"));
	ImmutablePts.Add(Pt_9);
	Pt_9->SetupAttachment(RootComponent);
	
}

TArray<USceneComponent*> APointCollection::GetGroundPoints(const FVector& GroundLocation, int32 PointAmount, float YawOverride)
{
	checkf(ImmutablePts.Num() >= PointAmount, TEXT("Attempted to access ImmutablePts out of bounds."));

	TArray<USceneComponent*> TempPts;

	for (USceneComponent* Pt : ImmutablePts)
	{
		if (TempPts.Num() >= PointAmount) return TempPts;

		if (Pt != Pt_0)
		{
			FVector ToPoint = Pt->GetComponentLocation() - Pt_0->GetComponentLocation();
			ToPoint = ToPoint.RotateAngleAxis(YawOverride, FVector::UpVector);
			Pt->SetWorldLocation(Pt_0->GetComponentLocation() + ToPoint);
		}

		const float PtX = Pt->GetComponentLocation().X;
		const float PtY = Pt->GetComponentLocation().Y;
		const float PtZ = Pt->GetComponentLocation().Z;

		const FVector RaisedLocation = FVector(PtX, PtY, PtZ + 500.f);
		const FVector LoweredLocation = FVector(PtX, PtY, PtZ - 500.f);

		FHitResult HitResult;
		TArray<AActor*> IgnoreActors;
		UAuraAbilitySystemBPLibrary::GetLivePlayersWithinRadius(
			this,
			IgnoreActors,
			TArray<AActor*>(),
			1500.f,
			GetActorLocation());

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActors(IgnoreActors);
		GetWorld()->LineTraceSingleByProfile(
			HitResult,
			RaisedLocation,
			LoweredLocation,
			FName("BlockAll"),
			QueryParams);

		const FVector AdjustedLocation = FVector(PtX, PtY, HitResult.ImpactPoint.Z);
		Pt->SetWorldLocation(AdjustedLocation);
		Pt->SetWorldRotation(UKismetMathLibrary::MakeRotFromZ(HitResult.ImpactNormal));

		TempPts.Add(Pt);
	}
	return TempPts;
}

void APointCollection::BeginPlay()
{
	Super::BeginPlay();
}
