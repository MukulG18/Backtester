#ifndef MARKET_DATA_READER
#define MARKET_DATA_READER

#include <bits/stdc++.h>
#include "components.h"

class MarketDataReader {
    public:
        MarketDataReader() {
            startDateTime = 0;
            endDateTime = 0;
            // $Edit Filename here
            marketFilename = "../data/marketdata.csv";
            // $Edit Filename here
            tradeFilename = "tradedata.csv";
        }

        void init(unsigned long long startDateTime, unsigned long long endDateTime) {
            this->startDateTime = startDateTime;
            this->endDateTime = endDateTime;
            marketFile.open(marketFilename,std::ios::in);
            if(!marketFile.is_open()) {
                std::cerr << "Failed to open file: " << marketFilename << std::endl;
                return;
            }
            tradeFile.open(tradeFilename,std::ios::in);
            if(!tradeFile.is_open()) {
                std::cerr << "Failed to open file: " << tradeFilename << std::endl;
                return;
            }
            if(!marketFileReady()) {
                std::cerr << "Error in Setting Market File Ready" << std::endl;
                return;
            }
            if(!tradeFileReady()) {
                std::cerr << "Error in Setting Trade File Ready" << std::endl;
                return;
            }
        }

        void init(unsigned long long startDateTime, unsigned long long endDateTime, std::string marketFilename, std::string tradeFilename) {
            this->startDateTime = startDateTime;
            this->endDateTime = endDateTime;
            this->marketFilename = "../data/" + marketFilename;
            this->tradeFilename = "../data/" + tradeFilename;
            marketFile.open(marketFilename,std::ios::in);
            if(!marketFile.is_open()) {
                std::cerr << "Failed to open file: " << marketFilename << std::endl;
                return;
            }
            tradeFile.open(tradeFilename,std::ios::in);
            if(!tradeFile.is_open()) {
                std::cerr << "Failed to open file: " << tradeFilename << std::endl;
                return;
            }
            if(!marketFileReady()) {
                std::cerr << "Error in Setting Market File Ready" << std::endl;
                return;
            }
            if(!tradeFileReady()) {
                std::cerr << "Error in Setting Trade File Ready" << std::endl;
                return;
            }
        }

        bool getNextEvent(Event* &event) {
            if(tradedataRow.getTimeStamp() >= endDateTime && marketdataRow.getTimeStamp() >= endDateTime) {
                return false;
            }
            event = new Event();
            if(tradedataRow.getTimeStamp()<marketdataRow.getTimeStamp()) {
                TradeData* traderow = new TradeData();
                traderow->setTimeStamp(tradedataRow.getTimeStamp());
                traderow->setInstrumentIndex(tradedataRow.getInstrumentIndex());
                traderow->setPrice(tradedataRow.getPrice());
                traderow->setSize(tradedataRow.getSize());
                traderow->setAggressor(tradedataRow.getAggressor());
                event->setEvent(trade);
                event->setPointer(traderow);
                event->setTimeStamp(tradedataRow.getTimeStamp());
                event->setInstrumentIndex(tradedataRow.getInstrumentIndex());
                readTradeData();
            }
            else {
                MarketData* marketrow = new MarketData();
                marketrow->setTimeStamp(marketdataRow.getTimeStamp());
                marketrow->setInstrumentIndex(marketdataRow.getInstrumentIndex());
                marketrow->setBidPrice(marketdataRow.getBidPrice());
                marketrow->setBidSize(marketdataRow.getBidSize());
                marketrow->setAskPrice(marketdataRow.getAskPrice());
                marketrow->setAskSize(marketdataRow.getAskSize());
                event->setEvent(market);
                event->setPointer(marketrow);
                event->setTimeStamp(marketdataRow.getTimeStamp());
                event->setInstrumentIndex(marketdataRow.getInstrumentIndex());
                readMarketData();
            }
            return true;
        }

    private:
        std::ifstream marketFile;
        std::ifstream tradeFile;
        std::string marketFilename;
        std::string tradeFilename;
        MarketData marketdataRow;
        TradeData tradedataRow;
        unsigned long long startDateTime;
        unsigned long long endDateTime;

        bool marketFileReady() {
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

        bool tradeFileReady() {
            if(!tradeFile.is_open()) {
                std::cerr << "Failed to open file: " << tradeFilename << std::endl;
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

        bool readMarketData() {
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

        bool readTradeData() {
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

};
#endif