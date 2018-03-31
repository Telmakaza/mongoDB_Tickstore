%% visualiseOrderBook.m -- Visualise sample orderbook data
% Author: E.Nonyane
% Date: March 31, 2018

%% Clear workspace
clc
clear 
close all

%% Set parameters to load data
startDateTime = '16-Jul-2015 12:30';
endDateTime = '16-Jul-2015 13:30';
tempcsv = 'C:\Users\Nnonyane\Documents\tempdata.csv';

%% Load data
data = ...
cleanData(extractMongoData(startDateTime, endDateTime, tempcsv), startDateTime(1:12));

%% Visualise trade prices in time
tradeData = data(:, [1 3 4]);
tradeData(cell2mat(tradeData(:,3)) == 0, :) = [];
tradeTimes = cell2mat(tradeData(:,1));
tradePrices = cell2mat(tradeData(:,2));
tradeVolumes = cell2mat(tradeData(:,3));
plot(tradeTimes, tradePrices)

% Format plot
datetick('x', 'HH:MM')
xlabel('Time')
ylabel('Price')
title('Intraday transaction prices of a stock in data sample')

%% Visualise quote prices
quoteData = data(:, [1, 5:8]);
quoteData(cell2mat(quoteData(:,2)) == 0 | cell2mat(quoteData(:,4)) == 0, :) = [];
bidPrices = cell2mat(quoteData(:,2));
askPrices = cell2mat(quoteData(:,4));
quoteTimes = cell2mat(quoteData(:,1));
figure(2)
hold on
plot(quoteTimes, bidPrices, 'b')
plot(quoteTimes, askPrices, 'r')
datetick('x', 'HH:MM')
xlabel('Time')
ylabel('Price')
title('Quote prices of a stock in the sample data')
legend('Bid prices', 'Ask prices')