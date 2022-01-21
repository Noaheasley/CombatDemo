# CombatDemo

Developed with Unreal Engine 4

## TestCharacter

### How to implement the character
  be sure to have the inputs setup
  
  once you have the inputs set up create a blueprint from the character
  enter the character blueprint and connect each input to their respected functions i.e. connect move forward to the forward input
  
 ### fuctions and variables
Name: WeaponRotationArray
     Description: Array for the Weapon Rotation
     Type: public Array<float>

Name: WeaponSizeArray
     Description: Array for the weapon size
     Type: public TArray<FVector>
     
Name: HitboxSpawn
     Description: Ref for the Hitbox
     Type: public TSubclassOf<AActor>

Name: WeaponOffset
     Description: Spawnlocation of the weapon hitbox
     Type: public FVector

Name: AttckTime 
     Description: Time during a attack
     Type: public float
  
Name: WeaponHitboxSize 
     Description: size of the weapon hitbox
     Type: protected FVector
  
Name: WeaponHitboxRotation
     Description: rotation of the weapon hitbox on the roll
     Type: protected float
  
Name: isAttacking
     Description: bool to check if the actor is attacking
     Type: private bool
  
Name: IndexLimit 
     Description: index of the Arrays
     Type: private int

 Name: AttackHandle 
    Description: Timer handle for the attack time
    Type: private FTimerHandle
  
  Name: AttackStart 
       Description: makes the player attack by spawnig a hitbox in front of them
       Type: private void
  
  Name: Interact
       Description: interacts with a interactable object
       Type: private void

  Name: AttackCoolDown 
     Description: cooldown for the attack
     Type: private void

  Name: CollectionRange 
     Description: range the player can pickup
     Type: private USpereComponent

  Name: SpawnObject 
     Description: spawns the hitbox
     Type: private void

  ## HitBox
  
  ### How to use
  make a blueprint from this component
  
  enter the blueprint and create a event ActorBeginOverlap. From that cast it to whatever enemy you want to damage. connect that to a do once node then connect that to apply damage, then connect that to a delay so it doesn't constantly damage the enemy. on apply damage you want to connect the base damage with the damage variable from the code
  
  ### Variables and Functions
  
  Name: TestMeshComponent 
     Description: sets up a mesh for the hitbox (used for testing)
     Type: public UStaticMeshComponent*
  
  Name: Killtime 
     Description: time for the life span of the hitbox
     Type: public float
  
  Name: Damage 
     Description: damage the hitbox deals
     Type: public float

  ##HealthComponent
  
  ### How to use
  attach this component to any actor and they should have health
  
  ### Variables and Functions
  Name: DeafualtHealth 
     Description: deafualt health of the actor
     Type: protected float

  Name: Health 
     Description: currect health of the character
     Type: protected float
  
  Name: TakeDamage
     Description: deals damage to the actor
     Type: protected void
  
  ## WeaponPickup
  
  ### How to use
  you'll be able to drag this onto the world and the player can pick up it by pressing the interact key
  
  Name: Interacted
     Description: called once the actor is interacted with
     Type: public void
  
  Name: DamageMod
     Description: modifier for damage  
     Type: public float
  
  Name: IncreaseDamage
     Description: function to increase the default damage
     Type: public float
