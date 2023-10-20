#ifndef ORDER_MANAGEMENT_SYSTEM
#define ORDER_MANAGEMENT_SYSTEM

#include <bits/stdc++.h>
#include "components.h"
#include "mdr.h"
#include "debugger.h"

#define DURATION ((6*60*60 + 15*60)*1'000'000'000LL)

class OrderBook {
    private:
        std::map<int,std::map<int,int,std::greater<int>>> buyOrder;
        std::map<int,std::map<int,int>> sellOrder;

    public:
        OrderBook() {

        }

        void init(std::set<int>& instruments) {
            for(auto i:instruments) {
                buyOrder[i] = std::map<int,int,std::greater<int>>();
                sellOrder[i] = std::map<int,int>();
            }
        }

        bool addOrder(int instrumentIndex, orderType order, int price, int size) {
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

        bool Trade(int instrumentIndex, int price, int size, bool aggressor) {
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

        std::map<int,int,std::greater<int>> viewBuyOrder(int instrumentIndex) {
            return buyOrder[instrumentIndex];
        }

        std::map<int,int> viewSellOrder(int instrumentIndex) {
            return sellOrder[instrumentIndex];
        }
};

class StrategyManager {
    private:
        OrderBook* orderBook;
        std::map<int,std::queue<std::pair<orderType,std::pair<int,int>>>> strategyOrder;
        
    public:
        StrategyManager() {

        }

        void init(std::set<int> instruments, OrderBook* orderBook) {
            this->orderBook = orderBook;
            for(auto instrument:instruments) {
                strategyOrder[instrument] = std::queue<std::pair<orderType,std::pair<int,int>>>();
            }
        }

        std::map<int,int,std::greater<int>> viewBuyOrder(int instrumentIndex) {
            return orderBook->viewBuyOrder(instrumentIndex);
        }

        std::map<int,int> viewSellOrder(int instrumentIndex) {
            return orderBook->viewSellOrder(instrumentIndex);
        }

        bool listOrder(int instrumentIndex, orderType order, int price, int size) {
            if(strategyOrder.count(instrumentIndex) <= 0) {
                return false;
            }
            strategyOrder[instrumentIndex].push({order,{price,size}});
            debug(strategyOrder[instrumentIndex].size());
            debug(strategyOrder[instrumentIndex].front());
            return true;
        }

        bool matchOrder(int instrumentIndex, std::vector<std::pair<orderType,std::pair<int,int>>>& matchedOrder) {
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
};

class PortfolioManager {
    private:
        std::map<int,int> stocksHeld;
    
    public:
        PortfolioManager() {

        }

        void addPosition(int instrumentIndex, int size) {
            stocksHeld[instrumentIndex] += size;
        }

        void printPortfolio() {
            std::cout << "Portfolio" << std::endl;
            for(auto instrument:stocksHeld) {
                std::cout << instrument.first << "  " << instrument.second << std::endl;
            }
        }
};

class Strategy {
    private:
        StrategyManager* strategyManager;
        PortfolioManager portfolio;
        
        std::vector<int> instruments;
        std::vector<long long> timers;
    public:
        Strategy() {
            // $Edit the list of instruments the strategy is interested in
            instruments = {0,15,25,100};
            // $Edit the list of timers
            timers = {10000000LL,15000000LL};
        }

        void init(std::set<int>& instruments, std::vector<long long>& timers, StrategyManager* strategyManager) {
            for(auto instrument:this->instruments) {
                instruments.insert(instrument);
            }
            timers = this->timers;
            this->strategyManager = strategyManager;
        }

        bool onMarketDataUpdate(int instrumentIndex) {
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

        bool onTradePrint(int instrumentIndex) {
            return true;
        }

        bool onTimer() {
            return true;
        }

        bool sendOrder(int instrumentIndex, orderType order, int price, int size) {
            return strategyManager->listOrder(instrumentIndex,order,price,size);
        }

        // TODO Error Handling
        // 1. Checking against the orderList where orderList is updated after every sendOrder() and onFill()
        void onFill(int instrumentIndex, orderType flag, int price, int quantity) {
            if(flag == buy) {
                portfolio.addPosition(instrumentIndex,quantity);
            }
            else if(flag == sell) {
                portfolio.addPosition(instrumentIndex,-quantity);
            }
        }

        void stop() {
            portfolio.printPortfolio();
        }
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

        void initDateTime(std::string date) {
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

        void stop() {
            currentStrategy.stop();
        }

        void run() {
            currentTime = startDateTime;
            while(currentTime<endDateTime) {
                // OMS asks event from the MDR
                if(mdr.getNextEvent(event)) {
                    long long differenceInTime = event->getTimeStamp()-currentTime;
                    // onTimer() is called for all timer updates
                    for(auto timer:timers) {
                        long long hitsOnTimer = differenceInTime/timer;
                        for(int i=0; i<hitsOnTimer; i++) {
                            currentStrategy.onTimer();
                        }
                        if((event->getTimeStamp()%timer)<(currentTime%timer)) {
                            currentStrategy.onTimer();
                        }
                    }
                    // Check if data is on the list of interesting Instruments
                    if(instruments.count(event->getInstrumentIndex()) <= 0) {
                        continue;
                    }
                    if(event->getEvent() == market) {
                        MarketData* eventData;
                        event->getPointer(eventData);
                        // OMS stores the current market state on each Instrument
                        if(eventData->getBidSize()>0) {
                            orderBook.addOrder(eventData->getInstrumentIndex(),buy,eventData->getBidPrice(),eventData->getBidSize());
                        }
                        if(eventData->getAskSize()>0) {
                            orderBook.addOrder(eventData->getInstrumentIndex(),sell,eventData->getAskPrice(),eventData->getAskSize());
                        }
                        debug(strategyManager.viewBuyOrder(eventData->getInstrumentIndex()).size());
                        debug(strategyManager.viewSellOrder(eventData->getInstrumentIndex()));
                        // OMS makes a callback on Strategy onMarketDataUpdate()
                        currentStrategy.onMarketDataUpdate(eventData->getInstrumentIndex());
                    }
                    else {
                        TradeData* eventData;
                        event->getPointer(eventData);
                        // OMS stores the current market state on each Instrument
                        orderBook.Trade(eventData->getInstrumentIndex(),eventData->getPrice(),eventData->getSize(),eventData->getAggressor());
                        // OMS makes a callback on Strategy onTradePrint()
                        currentStrategy.onTradePrint(eventData->getInstrumentIndex());
                    }
                    // OMS tries to match the orders by strategy
                    std::vector<std::pair<orderType,std::pair<int,int>>> matchedOrder;
                    strategyManager.matchOrder(event->getInstrumentIndex(),matchedOrder);
                    debug(matchedOrder);
                    // If an order is matched OMS informs the strategy by calling onFill()
                    for(auto order:matchedOrder) {
                        currentStrategy.onFill(event->getInstrumentIndex(), order.first, order.second.first, order.second.second);
                    }
                    currentTime = event->getTimeStamp();
                    debug(currentTime);
                }
                else {
                    break;
                }
                delete event;
            }
            delete event;
            stop();
        }

    public:
        OrderManagementSystem() {
            startDateTime = 0;
            endDateTime = 0;
            currentTime = 0;
        }

        void start(std::string date) {
            // initialization
            initDateTime(date);
            currentStrategy.init(instruments,timers,&strategyManager);
            orderBook.init(instruments);
            strategyManager.init(instruments,&orderBook);
            mdr.init(startDateTime,endDateTime);
            run();
        }

        void start(std::string date, std::string marketfile, std::string tradefile) {
            // initialization
            initDateTime(date);
            currentStrategy.init(instruments,timers,&strategyManager);
            orderBook.init(instruments);
            strategyManager.init(instruments,&orderBook);
            mdr.init(startDateTime,endDateTime,marketfile,tradefile);
            run();
        }
};

#endif