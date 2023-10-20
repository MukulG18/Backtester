#pragma once

#include "DataStructures.h"
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <chrono>
#include <iomanip>

class MarketDataReader {
private:
    std::ifstream marketFile;
    std::ifstream tradeFile;
    std::string marketFilename;
    std::string tradeFilename;
    MarketData marketdataRow;
    TradeData tradedataRow;
    unsigned long long startDateTime;
    unsigned long long endDateTime;
    
    bool marketFileReady();
    bool tradeFileReady();
    bool readMarketData();
    bool readTradeData();

public:
    MarketDataReader();
    void init(unsigned long long startDateTime, unsigned long long endDateTime);
    void init(unsigned long long startDateTime, unsigned long long endDateTime, std::string marketfile, std::string tradefile);
    bool getNextEvent(Event* &event);
};

class PortfolioManager {
private:
    std::map<int,int> stocksHeld;

public:
    PortfolioManager();
    bool addPosition(int instrumentIndex, int quantity);
    void printPortfolio();
};

class OrderBook {
private:
    std::map<int,std::map<int,int,std::greater<int>>> buyOrder;
    std::map<int,std::map<int,int>> sellOrder;

public:
    OrderBook();
    void init(const std::set<int>& instruments);
    bool addOrder(int instrumentIndex, orderType type, int price, int size);
    bool Trade(int instrumentIndex, int price, int size, bool aggressor);
    std::map<int, int, std::greater<int>> viewBuyOrder(int instrumentIndex);
    std::map<int, int> viewSellOrder(int instrumentIndex);
};

class StrategyManager {
private:
    OrderBook* orderBook;
    std::map<int, std::queue<std::pair<orderType, std::pair<int, int>>>> strategyOrder;

public:
    StrategyManager();
    void init(const std::set<int>& instruments, OrderBook* orderBook);
    std::map<int, int, std::greater<int>> viewBuyOrder(int instrumentIndex);
    std::map<int, int> viewSellOrder(int instrumentIndex);
    bool listOrder(int instrumentIndex, orderType order, int price, int size);
    bool matchOrder(int instrumentIndex, std::vector<std::pair<orderType, std::pair<int, int>>>& matchedOrder);
};

class Strategy {
private:
    StrategyManager* strategyManager;
    PortfolioManager portfolio;
    std::vector<int> instruments;
    std::vector<long long> timers;

public:
    Strategy();
    void init(std::set<int>& instruments, std::vector<long long>& timers, StrategyManager* strategyManager);
    bool onMarketDataUpdate(int instrumentIndex);
    bool onTradePrint(int instrumentIndex);
    bool onTimer();
    bool sendOrder(int instrumentIndex, orderType order, int price, int size);
    void onFill(int instrumentIndex, orderType flag, int price, int quantity);
    void stop();
};

class OrderManagementSystem {
private:
    OrderBook orderBook;
    StrategyManager strategyManager;
    MarketDataReader mdr;
    Strategy currentStrategy;
    std::set<int> instruments;
    std::vector<long long> timers;
    long long startDateTime;
    long long endDateTime;
    long long currentTime;
    Event* event;

    void initDateTime(std::string date);
    void stop();
    void run();

public:
    OrderManagementSystem();
    void start(std::string date);
};
