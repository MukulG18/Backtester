#include "DataStructures.h"

void Data::setInstrumentIndex(int instrumentIndex) {
    this->instrumentIndex = instrumentIndex;
}

void Data::setTimeStamp(unsigned long long timeStamp) {
    this->timeStamp = timeStamp;
}

int Data::getInstrumentIndex() {
    return instrumentIndex;
}

unsigned long long Data::getTimeStamp() {
    return timeStamp;
}

int MarketData::getBidPrice() {
    return bidPrice;
}

int MarketData::getBidSize() {
    return bidSize;
}

int MarketData::getAskPrice() {
    return askPrice;
}

int MarketData::getAskSize() {
    return askSize;
}

void MarketData::setBidPrice(int bidPrice) {
    this->bidPrice = bidPrice;
}

void MarketData::setAskPrice(int askPrice) {
    this->askPrice = askPrice;
}

void MarketData::setBidSize(int bidSize) {
    this->bidSize = bidSize;
}

void MarketData::setAskSize(int askSize) {
    this->askSize = askSize;
}

int TradeData::getPrice() {
    return price;
}

int TradeData::getSize() {
    return size;
}

bool TradeData::getAggressor() {
    return aggressor;
}

void TradeData::setPrice(int price) {
    this->price = price;
}

void TradeData::setSize(int size) {
    this->size = size;
}

void TradeData::setAggressor(bool aggressor) {
    this->aggressor = aggressor;
}

Event::Event() {
    marketPointer = nullptr;
    tradePointer = nullptr;
}

Event::~Event() {
    delete marketPointer;
    delete tradePointer;
}

void Event::setInstrumentIndex(int instrumentIndex) {
    this->instrumentIndex = instrumentIndex;
}

void Event::setTimeStamp(unsigned long long timeStamp) {
    this->timeStamp = timeStamp;
}

int Event::getInstrumentIndex() {
    return instrumentIndex;
}

unsigned long long Event::getTimeStamp() {
    return timeStamp;
}

void Event::setEvent(eventType event) {
    this->event = event;
}

eventType Event::getEvent() {
    return event;
}

void Event::setPointer(MarketData* marketPointer) {
    setEvent(market);
    this->marketPointer = marketPointer;
}

void Event::setPointer(TradeData* tradePointer) {
    setEvent(trade);
    this->tradePointer = tradePointer;
}

void Event::getPointer(MarketData* &marketPointer) {
    marketPointer = this->marketPointer;
}

void Event::getPointer(TradeData* &tradePointer) {
    tradePointer = this->tradePointer;
}
