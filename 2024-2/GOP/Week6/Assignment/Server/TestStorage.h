#pragma once
#include <random>
#include "PlayerInfo.pb.h"
using namespace std;
using namespace Week6Assignment;

class TestStorage {
private:
	PlayerInfo* players;
public:
	const static int PLAYER_COUNT = 10;

	TestStorage() {
		players = new PlayerInfo[PLAYER_COUNT];
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> distHp(50, 100);
		uniform_int_distribution<int> distLevel(1, 10);
		uniform_int_distribution<int> distInventory(1, 5);
		uniform_int_distribution<int> distOneToHundred(1, 100);

		for(int i = 0; i < PLAYER_COUNT; i++) {
			players[i].set_id(i);
			players[i].set_displayname("Player" + to_string(i));
			players[i].set_hp(distHp(gen));
			players[i].set_level(distLevel(gen));

			Inventory *inv = players[i].mutable_inventory();
			for (int j = 0, cnt = distInventory(gen); j < cnt; j++) {
				Item* item = inv->add_item();
				item->set_id(j);
				item->set_name("Item" + to_string(j));
				item->set_quantity(distOneToHundred(gen));
			}
		}
	}
	~TestStorage() = default;

	bool GeneratePlayersInfoResponse(AllPlayersInfoResponse *outResponse) const {
		AllPlayersInfoResponse response;

		for (int i = 0; i < PLAYER_COUNT; i++) {
			PlayerInfo* dstPtr = response.add_players();
			dstPtr->CopyFrom(players[i]);
		}

		outResponse->CopyFrom(response);
		return true;
	}

	bool GeneratePlayerInfoResponse(const int id, PlayerInfoResponse *outResponse) const {
		if (id < 0 || id >= PLAYER_COUNT) {
			return false;
		}

		PlayerInfoResponse response;
		response.mutable_player()->CopyFrom(players[id]);

		outResponse->CopyFrom(response);
		return true;
	}

	bool GeneratePlayerInventoryResponse(const int id, PlayerInventoryResponse* outResponse) const {
		if (id < 0 || id >= PLAYER_COUNT) {
			return false;
		}

		PlayerInventoryResponse response;
		response.set_playerid(id);
		response.mutable_inventory()->CopyFrom(players[id].inventory());

		outResponse->CopyFrom(response);
		return true;
	}

	void PrintPlayersInfo() const {
		for(int i = 0; i < PLAYER_COUNT; i++) {
			cout << "ID: " << players[i].id() << endl;
			cout << "Display Name: " << players[i].displayname() << endl;
			cout << "HP: " << players[i].hp() << endl;
			cout << "Level: " << players[i].level() << endl;
			cout << "Inventory: " << endl;
			for (int j = 0; j < players[i].inventory().item_size(); j++) {
				const Item& item = players[i].inventory().item(j);
				cout << "  ID: " << item.id() << endl;
				cout << "  Name: " << item.name() << endl;
				cout << "  Quantity: " << item.quantity() << endl;
			}
			cout << endl;
		}
	}
};