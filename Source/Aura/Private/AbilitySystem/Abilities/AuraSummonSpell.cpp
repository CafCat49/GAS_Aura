// Copyright Caffeinated Cat


#include "AbilitySystem/Abilities/AuraSummonSpell.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonSpell::GetSpawnLocations()
{
	const FVector Fwd = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Pos = GetAvatarActorFromActorInfo()->GetActorLocation();

	const FVector RSpread = Fwd.RotateAngleAxis(SpreadAngle / 2.f, FVector::UpVector);
	UKismetSystemLibrary::DrawDebugArrow(
		GetAvatarActorFromActorInfo(),
		Pos,
		Pos + RSpread * MaxSpawnDistance,
		4.f,
		FLinearColor::Green,
		3.f
		);

	const FVector LSpread = Fwd.RotateAngleAxis(-SpreadAngle / 2.f, FVector::UpVector);
	UKismetSystemLibrary::DrawDebugArrow(
	GetAvatarActorFromActorInfo(),
	Pos,
	Pos + LSpread * MaxSpawnDistance,
	4.f,
	FLinearColor::Gray,
	3.f
	);

	return TArray<FVector>();
}
