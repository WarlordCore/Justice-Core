/*
Made by: MoltenX
!DO NOT RELEASE WITHOUT PERMISSIONS!
*/

#include "ScriptPCH.h"
#include "Chat.h"

class chat : public CommandScript
{
	public:
		chat() : CommandScript("chat"){}

	ChatCommand * GetCommands() const
	{
		static ChatCommand ChatCommandTable[] = 
		{
			{"chat",	SEC_PLAYER,		true,		&HandleChatCommand,	"", NULL},
			{NULL,		0,				false,		NULL,						"", NULL}
		};

		return ChatCommandTable;
	}

	static bool HandleChatCommand(ChatHandler * handler, const char * args)
	{
		if (!args)
			return false;

		std::string msg = "";
		Player * player = handler->GetSession()->GetPlayer();

		switch(player->GetSession()->GetSecurity())
		{
			case SEC_PLAYER:
				if (player->GetTeam() == ALLIANCE)
				{
					msg += "|cff00ff00[A] |cffffffff[";
					msg += player->GetName();
					msg += "] |cffB400B4";
				}
				else
				{
					msg += "|cffff0000[H] |cffffffff[";
					msg += player->GetName();
					msg += "] |cffB400B4";
				}
				break;
			case SEC_VIP:
				msg += "|cffff8a00[VIP] |cffffffff[";
				msg += player->GetName();
				msg += "] |cffB400B4";
				break;
			case SEC_MODERATOR:
				msg += "|cff00ffff[Trial GM] |cffffffff[";
				msg += player->GetName();
				msg += "] |cffB400B4";
				break;
			case SEC_GAMEMASTER:
				msg += "|cfffa9900[GM] |cffffffff[";
				msg += player->GetName();
				msg += "] |cffB400B4";
				break;
			case SEC_ADMINISTRATOR:
				msg += "|cfffa9900[Admin] |cffffffff[";
				msg += player->GetName();
				msg += "] |cffB400B4";
				break;
			case SEC_DEV:
				msg += "|cfffa9900[Developer] |cffffffff[";
				msg += player->GetName();
				msg += "] |cffB400B4";
				break;
			case SEC_HD:
				msg += "|cfffa9900[Head Developer] |cffffffff[";
				msg += player->GetName();
				msg += "] |cffB400B4";
				break;
			case SEC_HA:
				msg += "|cfffa9900[Head Admin] |cffffffff[";
				msg += player->GetName();
				msg += "] |cffB400B4";
				break;
			case SEC_CO:
				msg += "|cfffa9900[Co-Owner] |cffffffff[";
				msg += player->GetName();
				msg += "] |cffB400B4";
				break;
			case SEC_O:
				msg += "|cfffa9900[Owner] |cffffffff[";
				msg += player->GetName();
				msg += "] |cffB400B4";
				break;
			case SEC_CONSOLE:
				msg += "|cfffa9900[ROOT] |cffffffff[";
				msg += player->GetName();
				msg += "] |cffB400B4";
				break;

		}
			
		msg += args;
		sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);	

		return true;
	}
};

void AddSC_chat()
{
	new chat();
}