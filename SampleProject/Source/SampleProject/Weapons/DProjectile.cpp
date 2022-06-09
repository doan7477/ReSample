// Fill out your copyright notice in the Description page of Project Settings.


#include "DProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ADProjectile::ADProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Create
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	ProjectileTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TRAIL"));
	ProjectMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILEMOVEMENT"));
	//Attach
	RootComponent = SphereCollision;
	Mesh->SetupAttachment(RootComponent);
	ProjectileTrail->SetupAttachment(Mesh);
	//MeshSetting
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_NORMAL(TEXT("/Game/Toon_Soldiers_Armies/Meshes/Weapons/Extras/SM_shell_rifle.SM_shell_rifle"));
	if (SM_NORMAL.Succeeded()) Mesh->SetStaticMesh(SM_NORMAL.Object);
	//Setting
	SphereCollision->SetSphereRadius(2.0f);
	Mesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	ProjectileTrail->SetRelativeLocation(FVector(0.0f, -10.0f, 0.0f));
	ProjectileTrail->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	ProjectileTrail->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));

	
}

// Called when the game starts or when spawned
void ADProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(1.5f);
}

void ADProjectile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ADProjectile::OnBeginOverlap);
	ProjectMovement->MaxSpeed = ProjectileData.Speed;
	ProjectMovement->InitialSpeed = ProjectileData.Speed;
}

// Called every frame
void ADProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;
	UE_LOG(LogTemp, Warning, TEXT("Damage : %f"),ProjectileData.Damage);
	UGameplayStatics::ApplyDamage(OtherActor, ProjectileData.Damage, NULL, GetOwner(), NULL);
	SetLifeSpan(0.01f);
}

/*
void ADProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, ProjectileData.Damage, GetWorld()->GetFirstPlayerController(), nullptr, NULL);
	FVector HitLocation = Hit.Location;
	//Particle
	SetLifeSpan(0.1f);
}
*/

