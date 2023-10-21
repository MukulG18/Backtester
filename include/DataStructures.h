#pragma once

#define DURATION ((6*60*60 + 15*60)*1'000'000'000LL)

enum eventType {
    market,
    trade
};

enum orderType {
    buy,
    sell
};

class Data {
    private:
        unsigned long long timeStamp;
        int instrumentIndex;
    
    public:
        void setInstrumentIndex(int instrumentIndex);
        void setTimeStamp(unsigned long long timeStamp);
        int getInstrumentIndex();
        unsigned long long getTimeStamp();
};

class MarketData : public Data {
    private:
        int bidPrice;
        int bidSize;
        int askPrice;
        int askSize;
    
    public:
        int getBidPrice();
        int getBidSize();
        int getAskPrice();
        int getAskSize();
        void setBidPrice(int bidPrice);
        void setAskPrice(int askPrice);
        void setBidSize(int bidSize);
        void setAskSize(int askSize);
};

class TradeData : public Data {
    private:
        int price;
        int size;
        bool aggressor;
    
    public:
        int getPrice();
        int getSize();
        bool getAggressor();
        void setPrice(int price);
        void setSize(int size);
        void setAggressor(bool aggressor);
};

class Event {
    private:
        unsigned long long timeStamp;
        int instrumentIndex;
        eventType event;
        MarketData marketPointer;
        TradeData tradePointer;
    
    public:
        Event();
        ~Event();
        
        void setInstrumentIndex(int instrumentIndex);
        void setTimeStamp(unsigned long long timeStamp);
        int getInstrumentIndex();
        unsigned long long getTimeStamp();
        void setEvent(eventType event);
        eventType getEvent();
        void setPointer(MarketData marketPointer);
        void setPointer(TradeData tradePointer);
        void getPointer(MarketData &marketPointer);
        void getPointer(TradeData &tradePointer);
};
