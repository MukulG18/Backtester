#ifndef EVENT_TYPE
#define EVENT_TYPE

enum eventType {
    market,
    trade
};
#endif

#ifndef ORDER_TYPE
#define ORDER_TYPE

enum orderType {
    buy,
    sell
};
#endif

#ifndef DATA
#define DATA

class Data {
    private:
        unsigned long long timeStamp;
        int instrumentIndex;

    public:
        void setInstrumentIndex(int instrumentIndex) {
            this->instrumentIndex = instrumentIndex;
        }
        void setTimeStamp(unsigned long long timeStamp) {
            this->timeStamp = timeStamp;
        }
        int getInstrumentIndex() {
            return instrumentIndex;
        }
        unsigned long long getTimeStamp() {
            return timeStamp;
        }
};
#endif

#ifndef MARKET_DATA
#define MARKET_DATA

class MarketData : public Data {
    private:
        int bidPrice;
        int bidSize;
        int askPrice;
        int askSize;
    
    public:
        int getBidPrice() {
            return bidPrice;
        }
        int getBidSize() {
            return bidSize;
        }
        int getAskPrice() {
            return askPrice;
        }
        int getAskSize() {
            return askSize;
        }
        void setBidPrice(int bidPrice) {
            this->bidPrice = bidPrice;
        }
        void setAskPrice(int askPrice) {
            this->askPrice = askPrice;
        }
        void setBidSize(int bidSize) {
            this->bidSize = bidSize;
        }
        void setAskSize(int askSize) {
            this->askSize = askSize;
        }
};
#endif

#ifndef TRADE_DATA
#define TRADE_DATA

class TradeData : public Data {
    private:
        int price;
        int size;
        bool aggressor;

    public:
        int getPrice() {
            return price;
        }
        int getSize() {
            return size;
        }
        bool getAggressor() {
            return aggressor;
        }
        void setPrice(int price) {
            this->price = price;
        }
        void setSize(int size) {
            this->size = size;
        }
        void setAggressor(bool aggressor) {
            this->aggressor = aggressor;
        }
};
#endif

#ifndef EVENT
#define EVENT

class Event {
    private:
        unsigned long long timeStamp;
        int instrumentIndex;
        eventType event;
        MarketData* marketPointer;
        TradeData* tradePointer;
    
    public:
        Event() {
            marketPointer = nullptr;
            tradePointer = nullptr;
        }
        ~Event() {
            delete marketPointer;
            delete tradePointer;
        }
        void setInstrumentIndex(int instrumentIndex) {
            this->instrumentIndex = instrumentIndex;
        }
        void setTimeStamp(unsigned long long timeStamp) {
            this->timeStamp = timeStamp;
        }
        int getInstrumentIndex() {
            return instrumentIndex;
        }
        unsigned long long getTimeStamp() {
            return timeStamp;
        }
        void setEvent(eventType event) {
            this->event = event;
        }
        eventType getEvent() {
            return event;
        }
        void setPointer(MarketData* marketPointer) {
            setEvent(market);
            this->marketPointer = marketPointer;
        }
        void setPointer(TradeData* tradePointer) {
            setEvent(trade);
            this->tradePointer = tradePointer;
        }
        void getPointer(MarketData* &marketPointer) {
            marketPointer = this->marketPointer;
        }
        void getPointer(TradeData* &tradePointer) {
            tradePointer = this->tradePointer;
        }
};
#endif