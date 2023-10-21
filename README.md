# Backtester

## Overview

This project contains a set of classes and data structures intended for backtesting trading strategies. The components are organized into two main files: `BacktesterComponents` and `DataStructures`.

---

## `BacktesterComponents`

### 1. **MarketDataReader**

Handles reading of market data, including initializing, checking file readiness, and fetching events.

#### Methods:

- Constructor: `MarketDataReader()`
- `getNextEvent()`: Fetches the next market event.
- `init()`: Initializes the data reader.
- `marketFileReady()`: Checks if the market file is ready for reading.
- `readMarketData()`: Reads the market data.
- `readTradeData()`: Reads the trade data.
- `tradeFileReady()`: Checks if the trade file is ready for reading.

### 2. **PortfolioManager**

Manages a portfolio of stocks, allowing for the addition of positions and viewing the current portfolio.

#### Methods:

- Constructor: `PortfolioManager()`
- `addPosition()`: Adds a position to the portfolio.
- `printPortfolio()`: Prints the current portfolio.

### 3. **OrderBook**

Represents a trading order book. It provides functionalities to initialize, add orders, view orders, and execute trades.

#### Methods:

- Constructor: `OrderBook()`
- `Trade()`: Executes a trade.
- `addOrder()`: Adds an order to the order book.
- `init()`: Initializes the order book.
- `viewBuyOrder()`: Views buy orders.
- `viewSellOrder()`: Views sell orders.

### 4. **StrategyManager**

Manages trading strategies. It supports the initialization, listing of orders, matching of orders, and viewing of buy and sell orders.

#### Methods:

- Constructor: `StrategyManager()`
- `init()`: Initializes the strategy manager.
- `listOrder()`: Lists an order.
- `matchOrder()`: Matches an order.
- `viewBuyOrder()`: Views buy orders.
- `viewSellOrder()`: Views sell orders.

### 5. **Strategy**

Implements the trading strategy.

#### Methods:

- Constructor: `Strategy()`
- `init()`: Initializes the strategy.
- `onFill()`: Executes when an order is filled.
- `onMarketDataUpdate()`: Executes when market data is updated.
- `onTimer()`: Executes on a timer event.
- `onTradePrint()`: Executes when a trade is printed.
- `sendOrder()`: Sends an order.
- `stop()`: Stops the strategy.

### 6. **OrderManagementSystem**

Manages the order system.

#### Methods:

- Constructor: `OrderManagementSystem()`
- `initDateTime()`: Initializes the date and time.
- `run()`: Runs the order management system.
- `start()`: Starts the order management system.
- `stop()`: Stops the order management system.

---

## `DataStructures`

### 1. **Data**

A foundational class that provides basic data structure functionalities. It includes attributes like timestamp and instrument index which are essential for both market and trade data.

#### Methods:

- `getInstrumentIndex()`
- `getTimeStamp()`
- `setInstrumentIndex()`
- `setTimeStamp()`

### 2. **MarketData**

Derived from the `Data` class, this represents detailed market data. It encapsulates bid and ask prices, along with their respective sizes, giving a snapshot of the current state of the market for a particular instrument.

#### Methods:

- `getAskPrice()`
- `getAskSize()`
- `getBidPrice()`
- `getBidSize()`
- `setAskPrice()`
- `setAskSize()`
- `setBidPrice()`
- `setBidSize()`

### 3. **TradeData**

Inherits from the `Data` class and represents individual trades. It contains information about the trade price, size, and whether the trade was initiated by a buying or selling aggressor.

#### Methods:

- `getAggressor()`
- `getPrice()`
- `getSize()`
- `setAggressor()`
- `setPrice()`
- `setSize()`

### 4. **Event**

Represents specific market events. It captures timestamps, instrument indices, and can point to either market data or trade data, providing a comprehensive view of what's happening in the market at any given moment.

#### Methods:

- Constructor: `Event()`
- `getEvent()`
- `getInstrumentIndex()`
- `getPointer()`
- `getTimeStamp()`
- `setEvent()`
- `setInstrumentIndex()`
- `setPointer()`
- `setTimeStamp()`

---
---

## Building and Executing the Code

### Cloning the Project:

To get a copy of the project on your local machine, use the following command:

```
git clone https://github.com/MukulG18/Backtester.git
```

### Customizing Strategy:

Before building, if you want to modify the list of instruments and timers that the strategy focuses on, you can do so by editing the constructor of the `Strategy` class located in: `src/BacktesterComponents.cpp`

### Building:

1. Navigate to the root directory of the project.
2. The historical market and trade data are present in the `data` subdirectory as `marketdata.csv` and `tradedata.csv`. If you wish to use different data files, please ensure to upload them with the same names.
3. Enter the following command in the terminal to build the code:
   ```
   g++ -o build/backtester -I./include src/main.cpp src/DataStructures.cpp src/BacktesterComponents.cpp
   ```

### Execution:

1. Once built, you can execute the compiled binary using:
   ```
   ./build/backtester
   ```
2. You will need to input the date in the format `YYYY-MM-DD`.
3. The output and error logs will be present in the `output.txt` and `error.txt` files respectively, located in the `logs` subdirectory.

---
