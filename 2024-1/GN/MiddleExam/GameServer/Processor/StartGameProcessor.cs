﻿using GameServer.Database;
using GameServer.Messages.Models;
using MySql.Data.MySqlClient;
using Newtonsoft.Json.Linq;

namespace GameServer.Processor;

public class StartGameProcessor : ProcessorBase {
    public override bool Process(JObject messageRaw) {
        var message = messageRaw.ParseMessage<StartGameRequest>()!;

        long? insertedId = DatabaseUtility.InsertOne(
            connection: DatabaseClient.Instance.Connection,
            tableName: TableNames.Users,
            data: new Dictionary<string, string> { { "name", message.Message.Name } }
        );

        if(insertedId == null) return false;

        UDPServer.Instance.RegisterClientWithDbId(message.ClientId, (int)insertedId, message.Message.Name);
        UDPServer.Instance.QueueSend(message.ClientId, new StartGameResponse {
            Status = true
        });
        UDPServer.Instance.QueueSend(0, new PushPlayerInfoSingle {
            Player = new PlayerData {
                Id = (int)message.ClientId,
                Name = message.Message.Name
            }
        });

        return true;
    }
}
