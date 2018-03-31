function cleandata = cleanData(data, dateStamp)

% Remove Auctions
data(strcmp(data(:,2),'Auction'),:) = [];
data(strcmp('',data(:,1)),:) = [];

% Romove events outside of the contious double aution trading
% period
STime = datenum([dateStamp, ' 09:10:00.000']);
ETime = datenum([dateStamp, ' 16:50:00.000']);


% Extract the trade times
eventTimes = [data{:,1}]';

% Clear events 10 minutes after opening
data(eventTimes<STime,:) = [];

% Update event times
eventTimes = [data{:,1}]';

% Clear events 10 minutes before closing
data(eventTimes>ETime,:) = [];

% Separate quotes from trades
dataQ = data(strcmp(data(:,2),'Quote'),:);
dataT = data(strcmp(data(:,2),'Trade'),:);


% Pull down quotes
if ~isempty(dataT) && ~isempty(dataQ)
    for i = 2:size(dataQ,1)
        for Column = 5:8
            if dataQ{i,Column} == 0
                dataQ{i,Column} = dataQ{i-1,Column};
            end
        end
    end
end


% Extract the quote times
quoteTimes = [dataQ{:,1}]';

% Get list of quotes with unique timestamp
[~,uniquerowindex] = unique(quoteTimes,'last');

% Compact quotes
dataQ = dataQ(uniquerowindex,:);


% Clean nonsensical quotes and trades
dataQ(cell2mat(dataQ(:,5))<=0,:) = [];
dataQ(cell2mat(dataQ(:,7))<=0,:) = [];
dataT(cell2mat(dataT(:,3))<=0,:) = [];

if ~isempty(dataT) && ~isempty(dataQ)
    
    % Get trade timestamps
    tradesTimes = [dataT{:,3}]';
    
    %Trades = eventTimes(strcmp(obj.data,'Trades'));
    
    %-----------------------------------------------------%
    
    % VWAP compact trades with the same timestamp
    col5Prices = cell2mat(dataT(:,3));
    col6Vols = cell2mat(dataT(:,4));
    
    % Loop over trades
    for j = 1:numel(tradesTimes)
        P = col5Prices(tradesTimes == tradesTimes(j));
        Q = col6Vols(tradesTimes == tradesTimes(j));
        dataT{j,3} = P'*Q/sum(Q);
        dataT{j,4} = sum(Q);
    end
    
    %-----------------------------------------------------%
    
    % Remove trades with the same timestamp
    [~,utindex] = unique(tradesTimes,'first');
    
    dataT = dataT(utindex,:);
    
    % Replace raw data with clean data
    cleandata = sortrows([dataT;dataQ],1);
end
