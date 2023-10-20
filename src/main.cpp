#include <iostream>
#include "BacktesterComponents.h"

// #include <bits/stdc++.h>
// #include <fstream>
// #include <ctime>
// #include <chrono>
// using namespace std;

// // All the instructions for editing fields like date,filenames,instrument ids and timers start with $

// #ifndef Debugging

// #ifndef ONLINE_JUDGE
// #define debug(x) std::cerr << #x <<" "; _print(x); std::cerr << endl;
// #define deb(x,n) std::cerr << #x <<" "; _print(x,n); std::cerr << endl;
// #else
// #define debug(x)
// #define deb(x,n)
// #endif

// template<class T>void _print(T t) {std::cerr << t;}

// template <class T> void _print(T v[], int n);
// template <class T, class V> void _print(std::pair <T, V> p);
// template <class T> void _print(std::vector <T> v);
// template <class T> void _print(std::set <T> v);
// template <class T> void _print(std::unordered_set <T> v);
// template <class T, class V> void _print(std::map <T, V> v);
// template <class T, class V> void _print(std::unordered_map <T, V> v);
// template <class T> void _print(multiset <T> v);
// template <class T, class V> void _print(std::pair <T, V> p) {std::cerr << "{"; _print(p.first); std::cerr << ","; _print(p.second); std::cerr << "}";}
// template <class T> void _print(T v[], int n){std::cerr << "[ ";for (int i = 0; i < n; i++){_print(v[i]);std::cerr << " ";}std::cerr << "]";}
// template <class T> void _print(std::vector <T> v) {std::cerr << "[ "; for (T i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
// template <class T> void _print(std::set <T> v) {std::cerr << "[ "; for (T i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
// template <class T> void _print(std::unordered_set <T> v) {std::cerr << "[ "; for (T i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
// template <class T> void _print(std::multiset <T> v) {std::cerr << "[ "; for (T i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
// template <class T, class V> void _print(std::map <T, V> v) {std::cerr << "[ "; for (auto i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
// template <class T, class V> void _print(std::unordered_map <T, V> v) {std::cerr << "[ "; for (auto i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
// #ifdef PBDS
// void _print(pbds v) {std::cerr << "[ "; for (auto i : v) {_print(i); std::cerr << " ";} std::cerr << "]";}
// #endif

// #endif

// #define DURATION ((6*60*60 + 15*60)*1'000'000'000LL)

// enum eventType {
//     market,
//     trade
// };

// enum orderType {
//     buy,
//     sell
// };

// class Data {
//     private:
//         unsigned long long timeStamp;
//         int instrumentIndex;

//     public:
//         void setInstrumentIndex(int instrumentIndex) {
//             this->instrumentIndex = instrumentIndex;
//         }
//         void setTimeStamp(unsigned long long timeStamp) {
//             this->timeStamp = timeStamp;
//         }
//         int getInstrumentIndex() {
//             return instrumentIndex;
//         }
//         unsigned long long getTimeStamp() {
//             return timeStamp;
//         }
// };

// class MarketData : public Data {
//     private:
//         int bidPrice;
//         int bidSize;
//         int askPrice;
//         int askSize;
    
//     public:
//         int getBidPrice() {
//             return bidPrice;
//         }
//         int getBidSize() {
//             return bidSize;
//         }
//         int getAskPrice() {
//             return askPrice;
//         }
//         int getAskSize() {
//             return askSize;
//         }
//         void setBidPrice(int bidPrice) {
//             this->bidPrice = bidPrice;
//         }
//         void setAskPrice(int askPrice) {
//             this->askPrice = askPrice;
//         }
//         void setBidSize(int bidSize) {
//             this->bidSize = bidSize;
//         }
//         void setAskSize(int askSize) {
//             this->askSize = askSize;
//         }
// };

// class TradeData : public Data {
//     private:
//         int price;
//         int size;
//         bool aggressor;

//     public:
//         int getPrice() {
//             return price;
//         }
//         int getSize() {
//             return size;
//         }
//         bool getAggressor() {
//             return aggressor;
//         }
//         void setPrice(int price) {
//             this->price = price;
//         }
//         void setSize(int size) {
//             this->size = size;
//         }
//         void setAggressor(bool aggressor) {
//             this->aggressor = aggressor;
//         }
// };

// class Event {
//     private:
//         unsigned long long timeStamp;
//         int instrumentIndex;
//         eventType event;
//         MarketData* marketPointer;
//         TradeData* tradePointer;
    
//     public:
//         Event() {
//             marketPointer = nullptr;
//             tradePointer = nullptr;
//         }
//         ~Event() {
//             delete marketPointer;
//             delete tradePointer;
//         }
//         void setInstrumentIndex(int instrumentIndex) {
//             this->instrumentIndex = instrumentIndex;
//         }
//         void setTimeStamp(unsigned long long timeStamp) {
//             this->timeStamp = timeStamp;
//         }
//         int getInstrumentIndex() {
//             return instrumentIndex;
//         }
//         unsigned long long getTimeStamp() {
//             return timeStamp;
//         }
//         void setEvent(eventType event) {
//             this->event = event;
//         }
//         eventType getEvent() {
//             return event;
//         }
//         void setPointer(MarketData* marketPointer) {
//             setEvent(market);
//             this->marketPointer = marketPointer;
//         }
//         void setPointer(TradeData* tradePointer) {
//             setEvent(trade);
//             this->tradePointer = tradePointer;
//         }
//         void getPointer(MarketData* &marketPointer) {
//             marketPointer = this->marketPointer;
//         }
//         void getPointer(TradeData* &tradePointer) {
//             tradePointer = this->tradePointer;
//         }
// };

// class MarketDataReader {
//     public:
//         MarketDataReader() {
//             startDateTime = 0;
//             endDateTime = 0;
//             // $Edit Filename here
//             marketFilename = "../data/marketdata.csv";
//             // $Edit Filename here
//             tradeFilename = "../data/tradedata.csv";
//         }

//         void init(unsigned long long startDateTime, unsigned long long endDateTime) {
//             this->startDateTime = startDateTime;
//             this->endDateTime = endDateTime;
//             marketFile.open(marketFilename,ios::in);
//             if(!marketFile.is_open()) {
//                 cerr << "Failed to open file: " << marketFilename << endl;
//                 return;
//             }
//             tradeFile.open(tradeFilename,ios::in);
//             if(!tradeFile.is_open()) {
//                 cerr << "Failed to open file: " << tradeFilename << endl;
//                 return;
//             }
//             if(!marketFileReady()) {
//                 cerr << "Error in Setting Market File Ready" << endl;
//                 return;
//             }
//             if(!tradeFileReady()) {
//                 cerr << "Error in Setting Trade File Ready" << endl;
//                 return;
//             }
//         }

//         bool getNextEvent(Event* &event) {
//             if(tradedataRow.getTimeStamp() >= endDateTime && marketdataRow.getTimeStamp() >= endDateTime) {
//                 return false;
//             }
//             event = new Event();
//             if(tradedataRow.getTimeStamp()<marketdataRow.getTimeStamp()) {
//                 TradeData* traderow = new TradeData();
//                 traderow->setTimeStamp(tradedataRow.getTimeStamp());
//                 traderow->setInstrumentIndex(tradedataRow.getInstrumentIndex());
//                 traderow->setPrice(tradedataRow.getPrice());
//                 traderow->setSize(tradedataRow.getSize());
//                 traderow->setAggressor(tradedataRow.getAggressor());
//                 event->setEvent(trade);
//                 event->setPointer(traderow);
//                 event->setTimeStamp(tradedataRow.getTimeStamp());
//                 event->setInstrumentIndex(tradedataRow.getInstrumentIndex());
//                 readTradeData();
//             }
//             else {
//                 MarketData* marketrow = new MarketData();
//                 marketrow->setTimeStamp(marketdataRow.getTimeStamp());
//                 marketrow->setInstrumentIndex(marketdataRow.getInstrumentIndex());
//                 marketrow->setBidPrice(marketdataRow.getBidPrice());
//                 marketrow->setBidSize(marketdataRow.getBidSize());
//                 marketrow->setAskPrice(marketdataRow.getAskPrice());
//                 marketrow->setAskSize(marketdataRow.getAskSize());
//                 event->setEvent(market);
//                 event->setPointer(marketrow);
//                 event->setTimeStamp(marketdataRow.getTimeStamp());
//                 event->setInstrumentIndex(marketdataRow.getInstrumentIndex());
//                 readMarketData();
//             }
//             return true;
//         }

//     private:
//         ifstream marketFile;
//         ifstream tradeFile;
//         string marketFilename;
//         string tradeFilename;
//         MarketData marketdataRow;
//         TradeData tradedataRow;
//         unsigned long long startDateTime;
//         unsigned long long endDateTime;

//         bool marketFileReady() {
//             if(!marketFile.is_open()) {
//                 return false;
//             }
//             string line;
//             string token;
//             stringstream ss;
//             unsigned long long ts = 0;
//             if(getline(marketFile,line)) {
//                 ss << line;
//                 getline(ss,token,',');
//                 ts = stoll(token);
//                 while(ts<startDateTime && getline(marketFile,line)) {
//                     ss.str("");
//                     ss << line;
//                     getline(ss,token,',');
//                     ts = stoll(token);
//                 }
//             }
//             if(ts<startDateTime) {
//                 // setting the timestamp to after the end of the day
//                 ts = endDateTime;
//             }
//             else {
//                 getline(ss,token,',');
//                 marketdataRow.setInstrumentIndex(stoi(token));
//                 getline(ss,token,',');
//                 marketdataRow.setBidPrice(stoi(token));
//                 getline(ss,token,',');
//                 marketdataRow.setBidSize(stoi(token));
//                 getline(ss,token,',');
//                 marketdataRow.setAskPrice(stoi(token));
//                 getline(ss,token,',');
//                 marketdataRow.setAskSize(stoi(token));
//             }
//             marketdataRow.setTimeStamp(ts);
//             return true;
//         }

//         bool tradeFileReady() {
//             if(!tradeFile.is_open()) {
//                 cerr << "Failed to open file: " << tradeFilename << endl;
//                 return false;
//             }
//             string line;
//             string token;
//             stringstream ss;
//             unsigned long long ts = 0;
//             if(getline(tradeFile,line)) {
//                 ss << line;
//                 getline(ss,token,',');
//                 ts = stoll(token);
//                 while(ts<startDateTime && getline(tradeFile,line)) {
//                     ss.str("");
//                     ss << line;
//                     getline(ss,token,',');
//                     ts = stoll(token);
//                 }
//             }
//             if(ts<startDateTime) {
//                 // setting the timestamp to after the end of the day
//                 ts = endDateTime;
//             }
//             else {
//                 getline(ss,token,',');
//                 tradedataRow.setInstrumentIndex(stoi(token));
//                 getline(ss,token,',');
//                 tradedataRow.setPrice(stoi(token));
//                 getline(ss,token,',');
//                 tradedataRow.setSize(stoi(token));
//                 getline(ss,token,',');
//                 tradedataRow.setAggressor((bool)(stoi(token)));
//             }
//             tradedataRow.setTimeStamp(ts);
//             return true;
//         }

//         bool readMarketData() {
//             if(!marketFile.is_open()) {
//                 return false;
//             }
//             string line;
//             string token;
//             stringstream ss;
//             if(getline(marketFile,line)) {
//                 ss << line;
//                 getline(ss,token,',');
//                 marketdataRow.setTimeStamp(stoll(token));
//                 getline(ss,token,',');
//                 marketdataRow.setInstrumentIndex(stoi(token));
//                 getline(ss,token,',');
//                 marketdataRow.setBidPrice(stoi(token));
//                 getline(ss,token,',');
//                 marketdataRow.setBidSize(stoi(token));
//                 getline(ss,token,',');
//                 marketdataRow.setAskPrice(stoi(token));
//                 getline(ss,token,',');
//                 marketdataRow.setAskSize(stoi(token));
//             }
//             else {
//                 marketdataRow.setTimeStamp(endDateTime);
//             }
//             return true;
//         }

//         bool readTradeData() {
//             if(!tradeFile.is_open()) {
//                 return false;
//             }
//             string line;
//             string token;
//             stringstream ss;
//             if(getline(tradeFile,line)) {
//                 ss << line;
//                 getline(ss,token,',');
//                 tradedataRow.setTimeStamp(stoll(token));
//                 getline(ss,token,',');
//                 tradedataRow.setInstrumentIndex(stoi(token));
//                 getline(ss,token,',');
//                 tradedataRow.setPrice(stoi(token));
//                 getline(ss,token,',');
//                 tradedataRow.setSize(stoi(token));
//                 getline(ss,token,',');
//                 tradedataRow.setAggressor((bool)(stoi(token)));
//             }
//             else {
//                 tradedataRow.setTimeStamp(endDateTime);
//             }
//             return true;
//         }

// };

// class PortfolioManager {
//     private:
//         map<int,int> stocksHeld;
    
//     public:
//         PortfolioManager() {

//         }

//         bool addPosition(int instrumentIndex, int size) {
//             stocksHeld[instrumentIndex] += size;
//             return true;
//         }

//         void printPortfolio() {
//             cout << "Portfolio" << endl;
//             for(auto instrument:stocksHeld) {
//                 cout << instrument.first << "  " << instrument.second << endl;
//             }
//         }
// };

// class OrderBook {
//     private:
//         map<int,map<int,int,greater<int>>> buyOrder;
//         map<int,map<int,int>> sellOrder;

//     public:
//         OrderBook() {

//         }

//         void init(set<int>& instruments) {
//             for(auto i:instruments) {
//                 buyOrder[i] = map<int,int,greater<int>>();
//                 sellOrder[i] = map<int,int>();
//             }
//         }

//         bool addOrder(int instrumentIndex, orderType order, int price, int size) {
//             if(order == buy) {
//                 if(buyOrder.count(instrumentIndex) <= 0) {
//                     return false;
//                 }
//                 if(buyOrder[instrumentIndex].size()>10000) {
//                     buyOrder[instrumentIndex].clear();
//                 }
//                 buyOrder[instrumentIndex][price] += size;
//             }
//             else {
//                 if(sellOrder.count(instrumentIndex) <= 0) {
//                     return false;
//                 }
//                 if(sellOrder[instrumentIndex].size()>10000) {
//                     sellOrder[instrumentIndex].clear();
//                 }
//                 sellOrder[instrumentIndex][price] += size;
//             }
//             return true;
//         }

//         bool Trade(int instrumentIndex, int price, int size, bool aggressor) {
//             if(aggressor == 0) {
//                 sellOrder[instrumentIndex][price] -= min(size,sellOrder[instrumentIndex][price]);
//                 auto it = buyOrder[instrumentIndex].begin();
//                 while(size > 0) {
//                     if(it->second < size) {
//                         size -= it->second;
//                         buyOrder[instrumentIndex].erase(it);
//                         it = buyOrder[instrumentIndex].begin();
//                     }
//                     else {
//                         it->second -= size;
//                         size = 0;
//                     }
//                 }
//             }
//             else {
//                 buyOrder[instrumentIndex][price] -= min(size,buyOrder[instrumentIndex][price]);
//                 auto it = sellOrder[instrumentIndex].begin();
//                 while(size > 0) {
//                     if(it->second < size) {
//                         size -= it->second;
//                         sellOrder[instrumentIndex].erase(it);
//                         it = sellOrder[instrumentIndex].begin();
//                     }
//                     else {
//                         it->second -= size;
//                         size = 0;
//                     }
//                 }
//             }
//             return true;
//         }

//         map<int,int,greater<int>> viewBuyOrder(int instrumentIndex) {
//             return buyOrder[instrumentIndex];
//         }

//         map<int,int> viewSellOrder(int instrumentIndex) {
//             return sellOrder[instrumentIndex];
//         }
// };

// class StrategyManager {
//     private:
//         OrderBook* orderBook;
//         map<int,queue<pair<orderType,pair<int,int>>>> strategyOrder;
        
//     public:
//         StrategyManager() {

//         }

//         void init(set<int> instruments, OrderBook* orderBook) {
//             this->orderBook = orderBook;
//             for(auto instrument:instruments) {
//                 strategyOrder[instrument] = queue<pair<orderType,pair<int,int>>>();
//             }
//         }

//         map<int,int,greater<int>> viewBuyOrder(int instrumentIndex) {
//             return orderBook->viewBuyOrder(instrumentIndex);
//         }

//         map<int,int> viewSellOrder(int instrumentIndex) {
//             return orderBook->viewSellOrder(instrumentIndex);
//         }

//         bool listOrder(int instrumentIndex, orderType order, int price, int size) {
//             if(strategyOrder.count(instrumentIndex) <= 0) {
//                 return false;
//             }
//             strategyOrder[instrumentIndex].push({order,{price,size}});
//             debug(strategyOrder[instrumentIndex].size());
//             debug(strategyOrder[instrumentIndex].front());
//             return true;
//         }

//         bool matchOrder(int instrumentIndex, vector<pair<orderType,pair<int,int>>>& matchedOrder) {
//             if(strategyOrder[instrumentIndex].size() == 0) {
//                 return false;
//             }
//             queue<pair<orderType,pair<int,int>>> notCompletedOrder;
//             while(!strategyOrder[instrumentIndex].empty()) {
//                 auto order = strategyOrder[instrumentIndex].front();
//                 strategyOrder[instrumentIndex].pop();
//                 if(order.first == buy) {
//                     if(viewSellOrder(instrumentIndex).size() == 0) {
//                         continue;
//                     }
//                     auto sellorder = viewSellOrder(instrumentIndex).begin();
//                     if(sellorder->first <= order.second.first) {
//                         matchedOrder.push_back({buy,{sellorder->first,min(sellorder->second,order.second.second)}});
//                         notCompletedOrder.push(order);
//                     }
//                 }
//                 else {
//                     if(viewBuyOrder(instrumentIndex).size() == 0) {
//                         continue;
//                     }
//                     auto buyorder = viewBuyOrder(instrumentIndex).begin();
//                     if(buyorder->first >= order.second.first) {
//                         matchedOrder.push_back({sell,{buyorder->first,min(buyorder->second,order.second.second)}});
//                         notCompletedOrder.push(order);
//                     }
//                 }
//             }
//             while(!notCompletedOrder.empty()) {
//                 auto order = notCompletedOrder.front();
//                 notCompletedOrder.pop();
//                 strategyOrder[instrumentIndex].push(order);
//             }
//             return true;
//         }
// };

// class Strategy {
//     private:
//         StrategyManager* strategyManager;
//         PortfolioManager portfolio;
        
//         vector<int> instruments;
//         vector<long long> timers;
//     public:
//         Strategy() {
//             // $Edit the list of instruments the strategy is interested in
//             instruments = {0,15,25,100};
//             // $Edit the list of timers
//             timers = {10000000LL,15000000LL};
//         }

//         void init(set<int>& instruments, vector<long long>& timers, StrategyManager* strategyManager) {
//             for(auto instrument:this->instruments) {
//                 instruments.insert(instrument);
//             }
//             timers = this->timers;
//             this->strategyManager = strategyManager;
//         }

//         bool onMarketDataUpdate(int instrumentIndex) {
//             int choice = rand()%3;
//             debug(choice);
//             debug(instrumentIndex);
//             if(choice == 0) {
//                 return sendOrder(instrumentIndex,buy,10,100);
//             }
//             else if(choice == 1) {
//                 return sendOrder(instrumentIndex,sell,10,100);
//             }
//             return false;
//         }

//         bool onTradePrint(int instrumentIndex) {
//             return true;
//         }

//         bool onTimer() {
//             return true;
//         }

//         bool sendOrder(int instrumentIndex, orderType order, int price, int size) {
//             return strategyManager->listOrder(instrumentIndex,order,price,size);
//         }

//         // TODO Error Handling
//         // 1. Checking against the orderList where orderList is updated after every sendOrder() and onFill()
//         void onFill(int instrumentIndex, orderType flag, int price, int quantity) {
//             if(flag == buy) {
//                 portfolio.addPosition(instrumentIndex,quantity);
//             }
//             else if(flag == sell) {
//                 portfolio.addPosition(instrumentIndex,-quantity);
//             }
//         }

//         void stop() {
//             portfolio.printPortfolio();
//         }
// };

// class OrderManagementSystem {
//     private:
//         OrderBook orderBook;
//         StrategyManager strategyManager;
//         MarketDataReader mdr;
//         Strategy currentStrategy;

//         set<int> instruments;
//         vector<long long> timers;
//         long long startDateTime;
//         long long endDateTime;
//         long long currentTime;
//         Event* event;

//         void initDateTime(string date) {
//             string dtime = "09:15:00";
//             date = date + " " + dtime;
//             tm dateTime = {};
//             istringstream ss(date);
//             ss >> get_time(&dateTime, "%Y-%m-%d %H:%M:%S");
//             if(ss.fail()) {
//                 cerr << "Invalid Date" << endl;
//                 return;
//             }
//             chrono::system_clock::time_point dateTimePoint = chrono::system_clock::from_time_t(mktime(&dateTime));
//             chrono::nanoseconds nanosecondsSinceEpoch = chrono::duration_cast<chrono::nanoseconds>(dateTimePoint.time_since_epoch());
//             startDateTime = nanosecondsSinceEpoch.count();
//             endDateTime = startDateTime + DURATION;
//         }

//         void stop() {
//             currentStrategy.stop();
//         }

//         void run() {
//             currentTime = startDateTime;
//             while(currentTime<endDateTime) {
//                 // OMS asks event from the MDR
//                 if(mdr.getNextEvent(event)) {
//                     long long differenceInTime = event->getTimeStamp()-currentTime;
//                     // onTimer() is called for all timer updates
//                     for(auto timer:timers) {
//                         long long hitsOnTimer = differenceInTime/timer;
//                         for(int i=0; i<hitsOnTimer; i++) {
//                             currentStrategy.onTimer();
//                         }
//                         if((event->getTimeStamp()%timer)<(currentTime%timer)) {
//                             currentStrategy.onTimer();
//                         }
//                     }
//                     // Check if data is on the list of interesting Instruments
//                     if(instruments.count(event->getInstrumentIndex()) <= 0) {
//                         continue;
//                     }
//                     if(event->getEvent() == market) {
//                         MarketData* eventData;
//                         event->getPointer(eventData);
//                         // OMS stores the current market state on each Instrument
//                         if(eventData->getBidSize()>0) {
//                             orderBook.addOrder(eventData->getInstrumentIndex(),buy,eventData->getBidPrice(),eventData->getBidSize());
//                         }
//                         if(eventData->getAskSize()>0) {
//                             orderBook.addOrder(eventData->getInstrumentIndex(),sell,eventData->getAskPrice(),eventData->getAskSize());
//                         }
//                         debug(strategyManager.viewBuyOrder(eventData->getInstrumentIndex()).size());
//                         debug(strategyManager.viewSellOrder(eventData->getInstrumentIndex()));
//                         // OMS makes a callback on Strategy onMarketDataUpdate()
//                         currentStrategy.onMarketDataUpdate(eventData->getInstrumentIndex());
//                     }
//                     else {
//                         TradeData* eventData;
//                         event->getPointer(eventData);
//                         // OMS stores the current market state on each Instrument
//                         orderBook.Trade(eventData->getInstrumentIndex(),eventData->getPrice(),eventData->getSize(),eventData->getAggressor());
//                         // OMS makes a callback on Strategy onTradePrint()
//                         currentStrategy.onTradePrint(eventData->getInstrumentIndex());
//                     }
//                     // OMS tries to match the orders by strategy
//                     vector<pair<orderType,pair<int,int>>> matchedOrder;
//                     strategyManager.matchOrder(event->getInstrumentIndex(),matchedOrder);
//                     debug(matchedOrder);
//                     // If an order is matched OMS informs the strategy by calling onFill()
//                     for(auto order:matchedOrder) {
//                         currentStrategy.onFill(event->getInstrumentIndex(), order.first, order.second.first, order.second.second);
//                     }
//                     currentTime = event->getTimeStamp();
//                     debug(currentTime);
//                 }
//                 else {
//                     break;
//                 }
//                 delete event;
//             }
//             delete event;
//             stop();
//         }

//     public:
//         OrderManagementSystem() {
//             startDateTime = 0;
//             endDateTime = 0;
//             currentTime = 0;
//         }

//         void start(string date) {
//             // initialization
//             initDateTime(date);
//             currentStrategy.init(instruments,timers,&strategyManager);
//             orderBook.init(instruments);
//             strategyManager.init(instruments,&orderBook);
//             mdr.init(startDateTime,endDateTime);
//             run();
//         }
// };

int main() {
    freopen("../logs/output.txt","w",stdout);
    freopen("../logs/error.txt","w",stderr);
    std::string date;
    // $Enter the date in format (YYYY-MM-DD)
    std::cin >> date;
    OrderManagementSystem OMS;
    OMS.start(date);

}