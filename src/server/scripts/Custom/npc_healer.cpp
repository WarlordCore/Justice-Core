#include "ScriptPCH.h"

class npc_helper : public CreatureScript
{
public:
	npc_helper():CreatureScript("npc_helper")
	{
	}

	bool OnGossipHello(Player * player, Creature * pCreature)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Heal me up!", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Buff me!", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reset my talent please", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reset my cooldowns please", GOSSIP_SENDER_MAIN, 4);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Repair my items please", GOSSIP_SENDER_MAIN, 5);
		player->PlayerTalkClass->SendGossipMenu(1, pCreature->GetGUID());

		return true;
	}

	void ReturnToMainMenu(Player * player, Creature * creature)
	{
	player->PlayerTalkClass->ClearMenus();
	OnGossipHello(player, creature);
	}

	char str[255];

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
		case 1:
			player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
			player->SetHealth(player->GetMaxHealth());
			creature->MonsterTextEmote("your health and mana get restored!", player->GetGUID());
			ReturnToMainMenu(player, creature);

			break;
		case 2:
			player->AddAura(71954, player); // id=71954 = holy champion (you can change the id)
			player->AddAura(1126, player); // id= 1126 = Mark of the Wild (you can change the id)
			player->AddAura(21562, player); // id= 21562 = Power Word: Fortitude (you can change the id)
			player->AddAura(20217, player); // id= 20217 = Blessing of Kings (you can change the id)
			player->AddAura(19740, player); // id= 19740 = Blessing of Might (you can change the id)
			player->AddAura(6673, player); // id= 6673 = Battle Shout (you can change the id)
			player->AddAura(469, player); // id= 469 = Commanding Shout (you can change the id)

			sprintf(str, "You have been Buffed!");

			player->MonsterTextEmote(str, player->GetGUID(), true);

			ReturnToMainMenu(player, creature);
			break;
		case 3:
			player->resetTalents(true);
			player->SendTalentsInfoData(false);
			creature->MonsterTextEmote("your talent has been reseted!", player->GetGUID());
			ReturnToMainMenu(player, creature);
			break;
		case 4:
			player->RemoveAllSpellCooldown();
			creature->MonsterTextEmote("your cooldowns has been reseted!", player->GetGUID());
			ReturnToMainMenu(player, creature);
			break;
		case 5:
			player->DurabilityRepairAll(false, 0, false);
			creature->MonsterTextEmote("your items has been repaired", player->GetGUID());
			ReturnToMainMenu(player, creature);
			break;
		}

		return true;
	}
};

void AddSc_npc_helper()
{
	new npc_helper();
}