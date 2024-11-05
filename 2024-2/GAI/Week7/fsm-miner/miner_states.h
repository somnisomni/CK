#pragma once
#include "state.h"

class Miner;

class MinerMiningState : public StateBase<Miner> {
  private:
    MinerMiningState() = default;
    MinerMiningState(const MinerMiningState&) = delete;
    MinerMiningState& operator=(const MinerMiningState&) = delete;
  public:
    static StateBase<Miner>* getInstance();
    void enter(Miner* entity) override;
    void execute(Miner* entity) override;
    void exit(Miner* entity) override;
};

class MinerDepositGoldState : public StateBase<Miner> {
  private:
    MinerDepositGoldState() = default;
    MinerDepositGoldState(const MinerDepositGoldState&) = delete;
    MinerDepositGoldState& operator=(const MinerDepositGoldState&) = delete;
  public:
    static StateBase<Miner>* getInstance();
    void enter(Miner* entity) override;
    void execute(Miner* entity) override;
    void exit(Miner* entity) override;
};

class MinerQuenchThirstState : public StateBase<Miner> {
  private:
    MinerQuenchThirstState() = default;
    MinerQuenchThirstState(const MinerQuenchThirstState&) = delete;
    MinerQuenchThirstState& operator=(const MinerQuenchThirstState&) = delete;
  public:
    static StateBase<Miner>* getInstance();
    void enter(Miner* entity) override;
    void execute(Miner* entity) override;
    void exit(Miner* entity) override;
};

class MinerRestState : public StateBase<Miner> {
  private:
    MinerRestState() = default;
    MinerRestState(const MinerRestState&) = delete;
    MinerRestState& operator=(const MinerRestState&) = delete;
  public:
    static StateBase<Miner>* getInstance();
    void enter(Miner* entity) override;
    void execute(Miner* entity) override;
    void exit(Miner* entity) override;
};
