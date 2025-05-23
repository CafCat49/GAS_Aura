// Copyright Caffeinated Cat


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	//Primary Attributes
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases physical damage")
		);

	GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Dexterity"),
		FString("Increases armor class and armor penetration")
		);

	GameplayTags.Attributes_Primary_Constitution = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Constitution"),
		FString("Increases health and poison resistance")
		);

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increases magic damage and mental resistance")
		);

	//Secondary Attributes
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Maximum amount of health")
		);

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Maximum amount of mana")
		);

	GameplayTags.Attributes_Secondary_PhysicalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.PhysicalDamage"),
		FString("Damage dealt by melee attacks")
		);

	GameplayTags.Attributes_Secondary_MagicDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MagicDamage"),
		FString("Damage dealt by spells")
		);
	
	GameplayTags.Attributes_Secondary_ArmorClass = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorClass"),
		FString("Reduces damage taken, improves Block Chance")
		);

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Amount of armor ignored on attacked target")
		);

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("Chance to reduce incoming physical damage")
		);

	GameplayTags.Attributes_Secondary_CriticalChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalChance"),
		FString("Chance to deal additional damage on successful attack")
		);

	GameplayTags.Attributes_Secondary_CriticalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalDamage"),
		FString("Amount of bonus damage dealt by a critical hit")
		);

	GameplayTags.Attributes_Secondary_CriticalAvoidance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalAvoidance"),
		FString("Reduces chance of incoming attacks being a critical hit")
		);

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("Amount of health restored during a time interval")
		);

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("Amount of mana restored during a time interval")
		);

	//Meta Attributes
	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Meta.IncomingXP"),
		FString("Incoming XP Meta Attribute")
		);

	//Input Tags
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
		);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input tag for Right Mouse Button")
		);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 Key")
		);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 Key")
		);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 Key")
		);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 Key")
		);

	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.Passive.1"),
		FString("Input Tag for Passive Ability 1")
		);

	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.Passive.2"),
		FString("Input Tag for Passive Ability 2")
		);
	
	//Combat Tags
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage")
		);

	//Damage Types
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Fire"),
		FString("Fire Damage Type")
		);

	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Lightning"),
		FString("Lightning Damage Type")
		);

	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Arcane"),
		FString("Arcane Damage Type")
		);

	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString("Physical Damage Type")
		);

	GameplayTags.Damage_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Poison"),
		FString("Poison Damage Type")
		);

	//Resistances
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"),
		FString("Fire Damage Resistance")
		);

	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"),
		FString("Lightning Damage Resistance")
		);

	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Arcane"),
		FString("Arcane Damage Resistance")
		);

	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"),
		FString("Physical Damage Resistance")
		);

	GameplayTags.Attributes_Resistance_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Poison"),
		FString("Poison Damage Resistance")
		);

	//Debuffs
	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Burn"),
		FString("Burn Debuff")
		);

	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Stun"),
		FString("Stun Debuff")
		);

	GameplayTags.Debuff_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Arcane"),
		FString("Arcane Debuff")
		);

	GameplayTags.Debuff_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Physical"),
		FString("Physical Debuff")
		);

	GameplayTags.Debuff_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Poison"),
		FString("Poison Debuff")
		);

	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Chance"),
		FString("Debuff Chance")
		);

	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Damage"),
		FString("Debuff Damage")
		);

	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Frequency"),
		FString("Debuff Frequency")
		);

	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Duration"),
		FString("Debuff Duration")
		);
	

	//Map Damage Types to Resistances
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Fire,
		GameplayTags.Attributes_Resistance_Fire);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Lightning,
		GameplayTags.Attributes_Resistance_Lightning);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Arcane,
		GameplayTags.Attributes_Resistance_Arcane);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Physical,
		GameplayTags.Attributes_Resistance_Physical);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Poison,
		GameplayTags.Attributes_Resistance_Poison);

	//Map Damage Types to Debuffs
	GameplayTags.DamageTypesToDebuffs.Add(
		GameplayTags.Damage_Fire,
		GameplayTags.Debuff_Burn);

	GameplayTags.DamageTypesToDebuffs.Add(
		GameplayTags.Damage_Lightning,
		GameplayTags.Debuff_Stun);

	GameplayTags.DamageTypesToDebuffs.Add(
		GameplayTags.Damage_Arcane,
		GameplayTags.Debuff_Arcane);

	GameplayTags.DamageTypesToDebuffs.Add(
		GameplayTags.Damage_Physical,
		GameplayTags.Debuff_Physical);

	GameplayTags.DamageTypesToDebuffs.Add(
		GameplayTags.Damage_Poison,
		GameplayTags.Debuff_Poison);
	
	//Abilities
	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.None"),
		FString("No Ability")
		);

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack Ability Tag")
		);

	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Summon"),
		FString("Summon Ability Tag")
		);

	//Offensive Spells
	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Fire.FireBolt"),
		FString("Fire Bolt Ability Tag")
		);

	GameplayTags.Abilities_Fire_FireBlast = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Fire.FireBlast"),
		FString("Fire Blast Ability Tag")
		);

	GameplayTags.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Lightning.Electrocute"),
		FString("Electrocute Ability Tag")
		);

	GameplayTags.Abilities_Arcane_ArcaneShards = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Arcane.ArcaneShards"),
		FString("Arcane Shards Ability Tag")
		);

	//Passive Spells
	GameplayTags.Abilities_Passive_HaloOfProtection = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Passive.HaloOfProtection"),
		FString("Halo Of Protection")
		);

	GameplayTags.Abilities_Passive_LifeSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Passive.LifeSiphon"),
		FString("Life Siphon")
		);

	GameplayTags.Abilities_Passive_ManaSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Passive.ManaSiphon"),
		FString("Mana Siphon")
		);

	//Hit React
	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.HitReact"),
		FString("HitReact Ability")
		);

	//Ability Status
	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Locked"),
		FString("Locked Status")
		);

	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Eligible"),
		FString("Eligible Status")
		);

	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Unlocked"),
		FString("Unlocked Status")
		);
	
	GameplayTags.Abilities_Status_Assigned = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Assigned"),
		FString("Assigned Status")
		);

	//Ability Types
	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Offensive"),
		FString("Offensive Type")
		);

	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Passive"),
		FString("Passive Type")
		);

	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.None"),
		FString("No Type")
		);


	//Cooldown
	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Fire.FireBolt"),
		FString("Fire Bolt Cooldown Tag")
		);
	
	//Combat Sockets
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.Weapon"),
		FString("Weapon")
		);
	
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.RightHand"),
		FString("Right hand")
		);
	
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.LeftHand"),
		FString("Left hand")
		);

	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.Tail"),
		FString("Tail")
		);

	//Montages
	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.1"),
		FString("Attack 1")
		);
	
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.2"),
		FString("Attack 2")
		);
	
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.3"),
		FString("Attack 3")
		);
	
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.4"),
		FString("Attack 4")
		);
	
	//Effects
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString("Reaction to being hit")
		);

	//Player Tags
	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputPressed"),
		FString("Block Input Pressed callback")
		);

	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputHeld"),
		FString("Block Input Held callback")
		);

	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputReleased"),
		FString("Block Input Released callback")
		);

	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.CursorTrace"),
		FString("Block tracing under cursor")
		);
}
