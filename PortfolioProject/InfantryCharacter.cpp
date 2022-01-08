// Fill out your copyright notice in the Description page of Project Settings.


#include "InfantryCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EntityStatComponent.h"
#include "InventoryWidget.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
// Sets default values
AInfantryCharacter::AInfantryCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	//Setup for body mesh.
	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshAsset(TEXT("SkeletalMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Characters_Parts/Units/Unit_Body_01a.Unit_Body_01a'"));

	if (BodyMeshAsset.Object)
	{
		BodyMesh->SetSkeletalMesh(BodyMeshAsset.Object);
		BodyMesh->SetupAttachment(RootComponent);
		BodyMesh->SetRelativeRotation(FQuat(FVector(0, 0, 1.0f), FMath::DegreesToRadians(-90.0f)));
		BodyMesh->SetRelativeLocation(FVector(0, 0, -90.0f));
	}

	//Setup for animations
	static ConstructorHelpers::FObjectFinder<UClass> BodyAnimInstance(TEXT("AnimBlueprint'/Game/Animations/UnitAnimBP.UnitAnimBP_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> HeadAnimInstance(TEXT("AnimBlueprint'/Game/Animations/UnitHeadAnimBP.UnitHeadAnimBP_C'"));

	if (BodyAnimInstance.Succeeded())
	{
		BodyMesh->SetAnimInstanceClass(BodyAnimInstance.Object);

	}
	if (HeadAnimInstance.Succeeded())
		HeadMesh->SetAnimInstanceClass(HeadAnimInstance.Object);
	
	/*static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponMeshAsset(TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Weapons/SM_w_morning_star.SM_w_morning_star'"));

	if (WeaponMeshAsset.Succeeded())
	{
		Weapon_L->SetStaticMesh(WeaponMeshAsset.Object);
	Weapon_L->SetupAttachment(BodyMesh, TEXT("Weapon_Socket_R"));
		Weapon_L->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Weapon_L->SetCollisionProfileName(FName("NoCollision"));
	}*/

	static ConstructorHelpers::FClassFinder<AWeapon_Melee> MeleeWeaponActorClass(TEXT("Class'/Script/PortfolioProject.Weapon_Melee'"));
	if (MeleeWeaponActorClass.Class != NULL)
	{
		MeleeWeaponClass = MeleeWeaponActorClass.Class;
	}
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetRelativeLocation(FVector(0, 90.0f, 50.0f));
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//InventoryWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Inventory Widget"));
	//static ConstructorHelpers::FClassFinder<UUserWidget> InventoryWidgetBaseClass(TEXT("WidgetBlueprint'/Game/UI/InventoryBP.InventoryBP_C'"));
	//if (InventoryWidgetBaseClass.Class != NULL)
	//{
	//	InventoryWidget->SetWidgetClass(InventoryWidgetBaseClass.Class);
	//	//InventoryWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//	InventoryWidget->SetWidgetSpace(EWidgetSpace::World);
	//	//InventoryWidget->SetDrawSize(FVector2D(100, 20));
	//}

	InventoryComponent = CreateDefaultSubobject<UEntityInventoryComponent>(TEXT("Inventory"));
	
}

bool AInfantryCharacter::GetIsMoving()
{
	return bIsMoving;
}

bool AInfantryCharacter::GetIsRunning()
{
	return bIsRunning;
}

bool AInfantryCharacter::GetIsInCombat()
{
	return bIsInCombat;
}

bool AInfantryCharacter::GetIsAttacking()
{
	return bIsAttacking;
}

// Called when the game starts or when spawned
void AInfantryCharacter::BeginPlay()
{
	Super::BeginPlay();
	bIsMoving = false;
	bIsRunning = false;
	bIsAttacking = false;
	bIsInCombat = false;

	//Setup for weapons.
	Weapon_L = GetWorld()->SpawnActor<AWeapon_Melee>(AWeapon_Melee::StaticClass());
	if (Weapon_L)
	{
		Weapon_L->SetOwner(this);
		Weapon_L->AttachToComponent(BodyMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Weapon_Socket_R"));
		Weapon_L->SetWidgetVisibility();
	}
	if (InventoryComponent)
	{
		InventoryComponent->SetCurrentInventorySize(3);
		APickupObject* tempObject = GetWorld()->SpawnActor<APickupObject>(APickupObject::StaticClass());
		if (tempObject)
		{
			tempObject->SetThumbnail(TempTexture);
			tempObject->SetItemName("Mace");

			InventoryComponent->AddItemToInventory(tempObject);
			InventoryComponent->AddItemToInventory(tempObject);
			InventoryComponent->AddItemToInventory(tempObject);
		}
		
	}
	
	/*InventoryWidget->InitWidget();
	auto InventoryUserWidget = Cast<UInventoryWidget>(InventoryWidget->GetUserWidgetObject());
	if (!InventoryUserWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Failed to Cast to UInventoryWidget"), *GetOwner()->GetName());
		return;
	}*/
	//InventoryUserWidget->GetInventoryPanel()->AddChildToUniformGrid(CreateDefaultSubobject<UButton>(TEXT("Item One")));
	//InventoryUserWidget->AddToViewport();
	////InventoryUserWidget->GetInventoryItems().Add();
}

void AInfantryCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AInfantryCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AInfantryCharacter::StartRun()
{
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}

void AInfantryCharacter::EndRun()
{
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}
void AInfantryCharacter::StartAttack()
{
	if (!bIsAttacking)
	{
		bIsAttacking = true;
		bIsInCombat = true;
	}

}

void AInfantryCharacter::EndAttack()
{
	bIsAttacking = false;
	bIsInCombat = false;
}

void AInfantryCharacter::PerformAttack()
{
	if (Weapon_L)
	{
		Weapon_L->PerformAttack();
	}
	/*FVector End = GetActorLocation() + GetActorRotation().Vector() * 10.0f;

#ifdef DEBUGGING_MODE
	DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, false);
	DrawDebugLine(GetWorld(), Location, End, FColor::Red, false, -1.0f, (uint8)0U, 2.0f);
#endif

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	GetWorld()->*/
	/*FTransform HitSocketTransform = Weapon_L->GetSocketTransform(FName("HitSocket"));
	FVector Start = HitSocketTransform.GetLocation();
	FVector End = HitSocketTransform.GetLocation() + (GetActorForwardVector() * 100.0f);
	UKismetSystemLibrary::BoxTraceMultiForObjects(GetWorld(), Start, End, FVector(10, 10, 10), HitSocketTransform.GetRotation().Rotator());*/

	//TArray<FHitResult> HitResult;

	//TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	//ObjectTypes.Add(TEnumAsByte<EObjectTypeQuery>(EObjectTypeQuery::ObjectTypeQuery1));
	//ObjectTypes.Add(TEnumAsByte<EObjectTypeQuery>(EObjectTypeQuery::ObjectTypeQuery2));
	//ObjectTypes.Add(TEnumAsByte<EObjectTypeQuery>(EObjectTypeQuery::ObjectTypeQuery3));
	//ObjectTypes.Add(TEnumAsByte<EObjectTypeQuery>(EObjectTypeQuery::ObjectTypeQuery4));
	//ObjectTypes.Add(TEnumAsByte<EObjectTypeQuery>(EObjectTypeQuery::ObjectTypeQuery5));

	//TArray<AActor*> ActorsToIgnore;
	//ActorsToIgnore.Add(this);

	/*bool bResult = UKismetSystemLibrary::BoxTraceMultiForObjects(GetWorld(), Weapon_L->GetSocketLocation(FName("AttackStart")),
		Weapon_L->GetSocketLocation(FName("AttackEnd")), FVector(30.f, 10.f, 10.f), FRotator(0.f, 0.f, 0.f), ObjectTypes, false, ActorsToIgnore,
		EDrawDebugTrace::Persistent, HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.f);*/
		/*bool Result = UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), Weapon_L->GetSocketLocation(FName("AttackStart")),
			Weapon_L->GetSocketLocation(FName("AttackEnd")), 50.0f, FName("Enemy"), false, ActorsToIgnore, EDrawDebugTrace::Type::ForDuration, HitResult, true);*/
	
}

// Called every frame
void AInfantryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddMovementInput(GetActorForwardVector());
	if (!GetVelocity().IsZero())
		bIsMoving = true;
	else
		bIsMoving = false;
}

// Called to bind functionality to input
void AInfantryCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AInfantryCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AInfantryCharacter::MoveRight);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AInfantryCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AInfantryCharacter::EndRun);
	PlayerInputComponent->BindAction("LightAttack", IE_Pressed, this, &AInfantryCharacter::StartAttack);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

