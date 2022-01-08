// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "HealthBarWidget.h"
// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GetMesh() = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshAsset(TEXT("SkeletalMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Characters_Parts/Units/Unit_Body_01a.Unit_Body_01a'"));

	if (BodyMeshAsset.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMeshAsset.Object);
		GetMesh()->SetupAttachment(RootComponent);
		GetMesh()->SetRelativeRotation(FQuat(FVector(0, 0, 1.0f), FMath::DegreesToRadians(-90.0f)));
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90.0f));
	}

	//Setup for head mesh.
	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HeadMeshAsset(TEXT("SkeletalMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Characters_Parts/Units/Unit_Head_01a.Unit_Head_01a'"));

	if (HeadMeshAsset.Object)
	{
		HeadMesh->SetSkeletalMesh(HeadMeshAsset.Object);
		HeadMesh->SetupAttachment(RootComponent);
		HeadMesh->SetRelativeRotation(FQuat(FVector(0, 0, 1.0f), FMath::DegreesToRadians(-90.0f)));
		HeadMesh->SetRelativeLocation(FVector(0, 0, -90.0f));
	}

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Healthbar Widget"));

	static ConstructorHelpers::FClassFinder<UUserWidget> HealthWidgetBaseClass(TEXT("WidgetBlueprint'/Game/UI/HealthBarBP.HealthBarBP_C'"));
	if (HealthWidgetBaseClass.Class != NULL)
	{
		HealthBar->SetWidgetClass(HealthWidgetBaseClass.Class);
		HealthBar->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
		HealthBar->SetDrawSize(FVector2D(100, 20));
	}

	//Setup for animations
	static ConstructorHelpers::FObjectFinder<UClass> BodyAnimInstance(TEXT("AnimBlueprint'/Game/Animations/UnitAnimBP.UnitAnimBP_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> HeadAnimInstance(TEXT("AnimBlueprint'/Game/Animations/UnitHeadAnimBP.UnitHeadAnimBP_C'"));

	if (BodyAnimInstance.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BodyAnimInstance.Object);

	}
	if (HeadAnimInstance.Succeeded())
		HeadMesh->SetAnimInstanceClass(HeadAnimInstance.Object);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	MaxHealth = 100.0f;
	Health = 100.0f;
	HealthBar->InitWidget();
	HealthBar->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	auto HealBarUserWidget = Cast<UHealthBarWidget>(HealthBar->GetUserWidgetObject());
	if (!HealBarUserWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Failed to Cast to UHealthBarWidget"), *GetOwner()->GetName());
		return;
	}
	HealBarUserWidget->GetHealthBar()->PercentDelegate.BindUFunction(this, FName("GetHealthPercent"));
}

float AEnemyCharacter::GetHealth()
{
	return MaxHealth / Health;
}

float AEnemyCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}
void AEnemyCharacter::FinishHim()
{
	Destroy();
}
// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);;
	DamageToApply = FMath::Min(Health, DamageToApply);

	Health -= DamageToApply;
	//Stats.TakeDamage(DamageToApply);
	//ThreatLevel = 100.0f;
	//if (GetIsDead())
	//{
	//	AUE5_TestingGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AUE5_TestingGameModeBase>();
	//	if (GameMode != nullptr)
	//	{
	//		GameMode->PawnKilled(this);
	//	}
	//	DetachFromControllerPendingDestroy();
	//	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//	//TODO:: Replace function call when required for fancier death function.
	//	FinishHim();
	//}
#ifdef DebugInfo
	UE_LOG(LogTemp, Warning, TEXT("Taken Damage: %f"), DamageToApply);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	UE_LOG(LogTemp, Warning, TEXT("Health%: %f"), GetHealthPercent());
#endif
	if (Health <= 0)
		FinishHim();

	return DamageToApply;
}

