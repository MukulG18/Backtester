#include <iostream>
#include "BacktesterComponents.h"
#include "debugger.h"

// Implementation for MarketDataReader class

bool MarketDataReader::marketFileReady() {
    if(!marketFile.is_open()) {
        return false;
    }
    std::string line;
    std::string token;
    std::stringstream ss;
    unsigned long long ts = 0;
    if(getline(marketFile,line)) {
        ss << line;
        getline(ss,token,',');
        ts = stoll(token);
        while(ts<startDateTime && getline(marketFile,line)) {
            ss.str("");
            ss << line;
            getline(ss,token,',');
            ts = stoll(token);
        }
    }
    if(ts<startDateTime) {
        // setting the timestamp to after the end of the day
        ts = endDateTime;
    }
    else {
        getline(ss,token,',');
        marketdataRow.setInstrumentIndex(stoi(token));
        getline(ss,token,',');
        marketdataRow.setBidPrice(stoi(token));
        getline(ss,token,',');
        marketdataRow.setBidSize(stoi(token));
        getline(ss,token,',');
        marketdataRow.setAskPrice(stoi(token));
        getline(ss,token,',');
        marketdataRow.setAskSize(stoi(token));
    }
    marketdataRow.setTimeStamp(ts);
    return true;
}

bool MarketDataReader::tradeFileReady() {
    if(!tradeFile.is_open()) {
        return false;
    }
    std::string line;
    std::string token;
    std::stringstream ss;
    unsigned long long ts = 0;
    if(getline(tradeFile,line)) {
        ss << line;
        getline(ss,token,',');
        ts = stoll(token);
        while(ts<startDateTime && getline(tradeFile,line)) {
            ss.str("");
            ss << line;
            getline(ss,token,',');
            ts = stoll(token);
        }
    }
    if(ts<startDateTime) {
        // setting the timestamp to after the end of the day
        ts = endDateTime;
    }
    else {
        getline(ss,token,',');
        tradedataRow.setInstrumentIndex(stoi(token));
        getline(ss,token,',');
        tradedataRow.setPrice(stoi(token));
        getline(ss,token,',');
        tradedataRow.setSize(stoi(token));
        getline(ss,token,',');
        tradedataRow.setAggressor((bool)(stoi(token)));
    }
    tradedataRow.setTimeStamp(ts);
    return true;
}

bool MarketDataReader::readMarketData() {
    if(!marketFile.is_open()) {
        return false;
    }
    std::string line;
    std::string token;
    std::stringstream ss;
    if(getline(marketFile,line)) {
        ss << line;
        getline(ss,token,',');
        marketdataRow.setTimeStamp(stoll(token));
        getline(ss,token,',');
        marketdataRow.setInstrumentIndex(stoi(token));
        getline(ss,token,',');
        marketdataRow.setBidPrice(stoi(token));
        getline(ss,token,',');
        marketdataRow.setBidSize(stoi(token));
        getline(ss,token,',');
        marketdataRow.setAskPrice(stoi(token));
        getline(ss,token,',');
        marketdataRow.setAskSize(stoi(token));
    }
    else {
        marketdataRow.setTimeStamp(endDateTime);
    }
    return true;
}

bool MarketDataReader::readTradeData() {
    if(!tradeFile.is_open()) {
        return false;
    }
    std::string line;
    std::string token;
    std::stringstream ss;
    if(getline(tradeFile,line)) {
        ss << line;
        getline(ss,token,',');
        tradedataRow.setTimeStamp(stoll(token));
        getline(ss,token,',');
        tradedataRow.setInstrumentIndex(stoi(token));
        getline(ss,token,',');
        tradedataRow.setPrice(stoi(token));
        getline(ss,token,',');
        tradedataRow.setSize(stoi(token));
        getline(ss,token,',');
        tradedataRow.setAggressor((bool)(stoi(token)));
    }
    else {
        tradedataRow.setTimeStamp(endDateTime);
    }
    return true;
}

MarketDataReader::MarketDataReader() {
    startDateTime = 0;
    endDateTime = 0;
    // $Edit Filename here
    marketFilename = "data/marketdata.csv";
    // $Edit Filename here
    tradeFilename = "data/tradedata.csv";
}

bool MarketDataReader::init(unsigned long long startDateTime, unsigned long long endDateTime) {
    this->startDateTime = startDateTime;
    this->endDateTime = endDateTime;
    marketFile.open(marketFilename,std::ios::in);
    if(!marketFile.is_open()) {
        std::cerr << "Failed to open file: " << marketFilename << std::endl;
        return false;
    }
    tradeFile.open(tradeFilename,std::ios::in);
    if(!tradeFile.is_open()) {
        std::cerr << "Failed to open file: " << tradeFilename << std::endl;
        return false;
    }
    if(!marketFileReady()) {
        std::cerr << "Error in Setting Market File Ready" << std::endl;
        return false;
    }
    if(!tradeFileReady()) {
        std::cerr << "Error in Setting Trade File Ready" << std::endl;
        return false;
    }
    return true;
}

bool MarketDataReader::init(unsigned long long startDateTime, unsigned long long endDateTime, std::string marketfile, std::string tradefile) {
    this->startDateTime = startDateTime;
    this->endDateTime = endDateTime;
    this->marketFilename = marketfile;
    this->tradeFilename = tradefile;
    marketFile.open(marketFilename,std::ios::in);
    if(!marketFile.is_open()) {
        std::cerr << "Failed to open file: " << marketFilename << std::endl;
        return false;
    }
    tradeFile.open(tradeFilename,std::ios::in);
    if(!tradeFile.is_open()) {
        std::cerr << "Failed to open file: " << tradeFilename << std::endl;
        return false;
    }
    if(!marketFileReady()) {
        std::cerr << "Error in Setting Market File Ready" << std::endl;
        return false;
    }
    if(!tradeFileReady()) {
        std::cerr << "Error in Setting Trade File Ready" << std::endl;
        return false;
    }
    return true;
}

bool MarketDataReader::getNextEvent(Event &event) {
    if(tradedataRow.getTimeStamp() >= endDateTime && marketdataRow.getTimeStamp() >= endDateTime) {
        return false;
    }
    if(tradedataRow.getTimeStamp()<marketdataRow.getTimeStamp()) {
        // TradeData* traderow = new TradeData();
        // traderow->setTimeStamp(tradedataRow.getTimeStamp());
        // traderow->setInstrumentIndex(tradedataRow.getInstrumentIndex());
        // traderow->setPrice(tradedataRow.getPrice());
        // traderow->setSize(tradedataRow.getSize());
        // traderow->setAggressor(tradedataRow.getAggressor());
        event.setEvent(trade);
        event.setPointer(tradedataRow);
        event.setTimeStamp(tradedataRow.getTimeStamp());
        event.setInstrumentIndex(tradedataRow.getInstrumentIndex());
        readTradeData();
    }
    else {
        // MarketData* marketrow = new MarketData();
        // marketrow->setTimeStamp(marketdataRow.getTimeStamp());
        // marketrow->setInstrumentIndex(marketdataRow.getInstrumentIndex());
        // marketrow->setBidPrice(marketdataRow.getBidPrice());
        // marketrow->setBidSize(marketdataRow.getBidSize());
        // marketrow->setAskPrice(marketdataRow.getAskPrice());
        // marketrow->setAskSize(marketdataRow.getAskSize());
        event.setEvent(market);
        event.setPointer(marketdataRow);
        event.setTimeStamp(marketdataRow.getTimeStamp());
        event.setInstrumentIndex(marketdataRow.getInstrumentIndex());
        readMarketData();
    }
    return true;
}

// Implementation for PortfolioManager class

PortfolioManager::PortfolioManager() {

}

bool PortfolioManager::addPosition(int instrumentIndex, int size) {
    stocksHeld[instrumentIndex] += size;
    return true;
}

void PortfolioManager::printPortfolio() {
    std::cout << "Portfolio" << std::endl;
    std::cout << "Instrument" << "  " << "Position" << std::endl;
    for(auto instrument:stocksHeld) {
        std::cout << instrument.first << "  " << instrument.second << std::endl;
    }
}

// Implementation for OrderBook class

OrderBook::OrderBook() {

}

void OrderBook::init(const std::set<int>& instruments) {
    for(auto i:instruments) {
        buyOrder[i] = std::map<int,int,std::greater<int>>();
        sellOrder[i] = std::map<int,int>();
    }
}

bool OrderBook::addOrder(int instrumentIndex, orderType order, int price, int size) {
    if(order == buy) {
        if(buyOrder.count(instrumentIndex) <= 0) {
            return false;
        }
        if(buyOrder[instrumentIndex].size()>10000) {
            buyOrder[instrumentIndex].clear();
        }
        buyOrder[instrumentIndex][price] += size;
    }
    else {
        if(sellOrder.count(instrumentIndex) <= 0) {
            return false;
        }
        if(sellOrder[instrumentIndex].size()>10000) {
            sellOrder[instrumentIndex].clear();
        }
        sellOrder[instrumentIndex][price] += size;
    }
    return true;
}

bool OrderBook::Trade(int instrumentIndex, int price, int size, bool aggressor) {
    if(aggressor == 0) {
        sellOrder[instrumentIndex][price] -= std::min(size,sellOrder[instrumentIndex][price]);
        auto it = buyOrder[instrumentIndex].begin();
        while(size > 0) {
            if(it->second < size) {
                size -= it->second;
                buyOrder[instrumentIndex].erase(it);
                it = buyOrder[instrumentIndex].begin();
            }
            else {
                it->second -= size;
                size = 0;
            }
        }
    }
    else {
        buyOrder[instrumentIndex][price] -= std::min(size,buyOrder[instrumentIndex][price]);
        auto it = sellOrder[instrumentIndex].begin();
        while(size > 0) {
            if(it->second < size) {
                size -= it->second;
                sellOrder[instrumentIndex].erase(it);
                it = sellOrder[instrumentIndex].begin();
            }
            else {
                it->second -= size;
                size = 0;
            }
        }
    }
    return true;
}

std::map<int,int,std::greater<int>> OrderBook::viewBuyOrder(int instrumentIndex) {
    return buyOrder[instrumentIndex];
}

std::map<int,int> OrderBook::viewSellOrder(int instrumentIndex) {
    return sellOrder[instrumentIndex];
}

// Implementation for StrategyManager class

StrategyManager::StrategyManager() {

}

void StrategyManager::init(const std::set<int>& instruments, OrderBook* orderBook) {
    this->orderBook = orderBook;
    for(auto instrument:instruments) {
        strategyOrder[instrument] = std::queue<std::pair<orderType,std::pair<int,int>>>();
    }
}

std::map<int,int,std::greater<int>> StrategyManager::viewBuyOrder(int instrumentIndex) {
    return orderBook->viewBuyOrder(instrumentIndex);
}

std::map<int,int> StrategyManager::viewSellOrder(int instrumentIndex) {
    return orderBook->viewSellOrder(instrumentIndex);
}

bool StrategyManager::listOrder(int instrumentIndex, orderType order, int price, int size) {
    if(strategyOrder.count(instrumentIndex) <= 0) {
        return false;
    }
    strategyOrder[instrumentIndex].push({order,{price,size}});
    debug(strategyOrder[instrumentIndex].size());
    debug(strategyOrder[instrumentIndex].front());
    return true;
}

bool StrategyManager::matchOrder(int instrumentIndex, std::vector<std::pair<orderType,std::pair<int,int>>>& matchedOrder) {
    if(strategyOrder[instrumentIndex].size() == 0) {
        return false;
    }
    std::queue<std::pair<orderType,std::pair<int,int>>> notCompletedOrder;
    while(!strategyOrder[instrumentIndex].empty()) {
        auto order = strategyOrder[instrumentIndex].front();
        strategyOrder[instrumentIndex].pop();
        if(order.first == buy) {
            if(viewSellOrder(instrumentIndex).size() == 0) {
                continue;
            }
            auto sellorder = viewSellOrder(instrumentIndex).begin();
            if(sellorder->first <= order.second.first) {
                matchedOrder.push_back({buy,{sellorder->first,std::min(sellorder->second,order.second.second)}});
                notCompletedOrder.push(order);
            }
        }
        else {
            if(viewBuyOrder(instrumentIndex).size() == 0) {
                continue;
            }
            auto buyorder = viewBuyOrder(instrumentIndex).begin();
            if(buyorder->first >= order.second.first) {
                matchedOrder.push_back({sell,{buyorder->first,std::min(buyorder->second,order.second.second)}});
                notCompletedOrder.push(order);
            }
        }
    }
    while(!notCompletedOrder.empty()) {
        auto order = notCompletedOrder.front();
        notCompletedOrder.pop();
        strategyOrder[instrumentIndex].push(order);
    }
    return true;
}

// Implementation for Strategy class

Strategy::Strategy() {
    // $Edit the list of instruments the strategy is interested in
    instruments = {0,15,25,100};
    // $Edit the list of timers
    timers = {10000000LL,15000000LL};
}

void Strategy::init(std::set<int>& instruments, std::vector<long long>& timers, StrategyManager* strategyManager) {
    for(auto instrument:this->instruments) {
        instruments.insert(instrument);
    }
    timers = this->timers;
    this->strategyManager = strategyManager;
}

bool Strategy::onMarketDataUpdate(int instrumentIndex) {
    int choice = rand()%3;
    debug(choice);
    debug(instrumentIndex);
    if(choice == 0) {
        return sendOrder(instrumentIndex,buy,10,100);
    }
    else if(choice == 1) {
        return sendOrder(instrumentIndex,sell,10,100);
    }
    return false;
}

bool Strategy::onTradePrint(int instrumentIndex) {
    return true;
}

bool Strategy::onTimer() {
    return true;
}

bool Strategy::sendOrder(int instrumentIndex, orderType order, int price, int size) {
    return strategyManager->listOrder(instrumentIndex,order,price,size);
}

// TODO Error Handling
// 1. Checking against the orderList where orderList is updated after every sendOrder() and onFill()
void Strategy::onFill(int instrumentIndex, orderType flag, int price, int quantity) {
    if(flag == buy) {
        portfolio.addPosition(instrumentIndex,quantity);
    }
    else if(flag == sell) {
        portfolio.addPosition(instrumentIndex,-quantity);
    }
}

void Strategy::stop() {
    portfolio.printPortfolio();
}

// Implementation for OrderManagementSystem class

void OrderManagementSystem::initDateTime(std::string date) {
    std::string dtime = "09:15:00";
    date = date + " " + dtime;
    tm dateTime = {};
    std::istringstream ss(date);
    ss >> std::get_time(&dateTime, "%Y-%m-%d %H:%M:%S");
    if(ss.fail()) {
        std::cerr << "Invalid Date" << std::endl;
        return;
    }
    std::chrono::system_clock::time_point dateTimePoint = std::chrono::system_clock::from_time_t(mktime(&dateTime));
    std::chrono::nanoseconds nanosecondsSinceEpoch = std::chrono::duration_cast<std::chrono::nanoseconds>(dateTimePoint.time_since_epoch());
    startDateTime = nanosecondsSinceEpoch.count();
    endDateTime = startDateTime + DURATION;
}

void OrderManagementSystem::stop() {
    currentStrategy.stop();
}

void OrderManagementSystem::run() {
    currentTime = startDateTime;
    while(currentTime<endDateTime) {
        // OMS asks event from the MDR
        if(mdr.getNextEvent(event)) {
            long long differenceInTime = event.getTimeStamp()-currentTime;
            // onTimer() is called for all timer updates
            for(auto timer:timers) {
                long long hitsOnTimer = differenceInTime/timer;
                for(int i=0; i<hitsOnTimer; i++) {
                    currentStrategy.onTimer();
                }
                if((event.getTimeStamp()%timer)<(currentTime%timer)) {
                    currentStrategy.onTimer();
                }
            }
            // Check if data is on the list of interesting Instruments
            if(instruments.count(event.getInstrumentIndex()) <= 0) {
                continue;
            }
            if(event.getEvent() == market) {
                MarketData eventData;
                event.getPointer(eventData);
                // OMS stores the current market state on each Instrument
                if(eventData.getBidSize()>0) {
                    orderBook.addOrder(eventData.getInstrumentIndex(),buy,eventData.getBidPrice(),eventData.getBidSize());
                }
                if(eventData.getAskSize()>0) {
                    orderBook.addOrder(eventData.getInstrumentIndex(),sell,eventData.getAskPrice(),eventData.getAskSize());
                }
                debug(strategyManager.viewBuyOrder(eventData.getInstrumentIndex()).size());
                debug(strategyManager.viewSellOrder(eventData.getInstrumentIndex()));
                // OMS makes a callback on Strategy onMarketDataUpdate()
                currentStrategy.onMarketDataUpdate(eventData.getInstrumentIndex());
            }
            else {
                TradeData eventData;
                event.getPointer(eventData);
                // OMS stores the current market state on each Instrument
                orderBook.Trade(eventData.getInstrumentIndex(),eventData.getPrice(),eventData.getSize(),eventData.getAggressor());
                // OMS makes a callback on Strategy onTradePrint()
                currentStrategy.onTradePrint(eventData.getInstrumentIndex());
            }
            // OMS tries to match the orders by strategy
            std::vector<std::pair<orderType,std::pair<int,int>>> matchedOrder;
            strategyManager.matchOrder(event.getInstrumentIndex(),matchedOrder);
            debug(matchedOrder);
            // If an order is matched OMS informs the strategy by calling onFill()
            for(auto order:matchedOrder) {
                currentStrategy.onFill(event.getInstrumentIndex(), order.first, order.second.first, order.second.second);
            }
            currentTime = event.getTimeStamp();
            debug(currentTime);
        }
        else {
            break;
        }
    }
    stop();
}

OrderManagementSystem::OrderManagementSystem() {
    startDateTime = 0;
    endDateTime = 0;
    currentTime = 0;
}

void OrderManagementSystem::start(std::string date) {
    // initialization
    initDateTime(date);
    currentStrategy.init(instruments,timers,&strategyManager);
    orderBook.init(instruments);
    strategyManager.init(instruments,&orderBook);
    if(!mdr.init(startDateTime,endDateTime)) {
        return;
    }
    run();
}