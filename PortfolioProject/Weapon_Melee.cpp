// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Melee.h"
#include "Components/WidgetComponent.h"
#include "WeaponWidget.h"
// Sets default values
AWeapon_Melee::AWeapon_Melee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	 
	//Setup for weapons.
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(InteractableMesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponMeshAsset(TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Weapons/SM_w_morning_star.SM_w_morning_star'"));

	if (WeaponMeshAsset.Succeeded())
	{
		InteractableMesh->SetStaticMesh(WeaponMeshAsset.Object);
		InteractableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InteractableMesh->SetCollisionProfileName(FName("NoCollision"));
	}

	WeaponWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Weapon Widget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> TooltipWidgetBaseClass(TEXT("WidgetBlueprint'/Game/UI/WeaponInfoBP.WeaponInfoBP_C'"));

	if (TooltipWidgetBaseClass.Class != NULL)
	{
		WeaponWidget->SetWidgetClass(TooltipWidgetBaseClass.Class);
		WeaponWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		WeaponWidget->SetWidgetSpace(EWidgetSpace::Screen);
		WeaponWidget->SetDrawSize(FVector2D(250, 100));
	}
}

// Called when the game starts or when spawned
void AWeapon_Melee::BeginPlay()
{
	Super::BeginPlay();
	CurrentTier = 0;
	CurrentWeaponTier = WeaponTiers[CurrentTier];
	WeaponBaseDamage = 10.0f;
	AttackRadius = 50.0f;
	PercentDamageIncrease = 100.0f;
	WeaponName = FText::FromString("Mace");

	WeaponWidget->InitWidget();
	WeaponWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	auto WeaponInfoWidget = Cast<UWeaponWidget>(WeaponWidget->GetUserWidgetObject());
	if (!WeaponInfoWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Failed to Cast to UWeaponWidget"), *GetOwner()->GetName());
		return;
	}
	//UE_LOG(LogTemp, Error, TEXT("WeaponName: %s"), *WeaponName.ToString());
	WeaponInfoWidget->GetWeaponNameBlock()->Text = WeaponName;
	//HealthBarUserWidget->GetWeaponNameBlock()->TextDelegate.BindUFunction(this, FName("GetWeaponName"));
	
	
	//TooltipBar = CreateWidget<UUserWidget>(this, TooltipWidgetClass);
	//if (TooltipBar != nullptr)
	//{
	//	//TooltipBar->AddToViewport();
	//	//TooltipBar->AddToPlayerScreen();
	//	//WeaponWidget->GetUserWidgetObject()->AddToPlayerScreen();
	//	WeaponWidget->InitWidget();
	//	//WeaponWidget->SetWindowVisibility(EWindowVisibility::Visible);
	//	//WeaponWidget->ToggleActive();
	//	//WeaponWidget->ToggleVisibility();
	//	//TooltipBar->space
	//}
	
}

// Called every frame
void AWeapon_Melee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWeapon_Melee::PerformAttack()
{
	TArray<FHitResult> HitResult;

	FCollisionShape MySphere = FCollisionShape::MakeSphere(AttackRadius);
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);
	queryParams.AddIgnoredActor(GetOwner());
	FCollisionResponseParams responseParams;
	FCollisionResponseContainer cont;
	cont.GameTraceChannel2;
	responseParams.CollisionResponse = cont;

	bool result = GetWorld()->SweepMultiByChannel(HitResult, InteractableMesh->GetSocketLocation(FName("AttackStart")),
		InteractableMesh->GetSocketLocation(FName("AttackEnd")), FQuat::Identity, ECollisionChannel::ECC_WorldDynamic, MySphere, queryParams, responseParams);



	if (result)
	{
		TMap<AActor*, FHitResult> UniqueHits;
		for (auto& Hit : HitResult)
		{
			AActor* hitActor = Hit.GetActor();
			if (hitActor != nullptr)
			{
				if (!UniqueHits.Contains(hitActor))
				{
					UniqueHits.Add(hitActor, Hit);
				}
				else
				{
					continue;
				}
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Hit %d"), UniqueHits.Num());
		for (auto& Hit : UniqueHits)
		{
			if (Hit.Key != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hitting Actor: %s"), *Hit.Key->GetName());
				FVector HitDirection = Hit.Key->GetActorLocation() - GetActorLocation();
				FPointDamageEvent DamageEvent(GetWeaponDamage(), Hit.Value, HitDirection, nullptr);
				Hit.Key->TakeDamage(GetWeaponDamage(), DamageEvent, GetOwner()->GetInstigatorController(), this);
			}
		}
	}
	return result;
}

float AWeapon_Melee::GetWeaponDamage()
{
	return ((float)(CurrentWeaponTier.DamageIncrease / 100.0f) * WeaponBaseDamage);
}

FText AWeapon_Melee::GetWeaponName() const
{
	return WeaponName;
}

void AWeapon_Melee::SetWidgetVisibility()
{
	WeaponWidget->SetVisibility(false);
}

