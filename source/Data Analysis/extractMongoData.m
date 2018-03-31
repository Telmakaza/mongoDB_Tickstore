function data = extractMongoData(startDateTime, endDateTime, tempcsvout)

fields = 'DateTime,Type,Price,Volume,BidPrice,BidVolume,AskPrice,AskVolume';

% Convert Start/End dates to ISO date number (milliseconds since Unix
% epoch)
[unixEpoch] = datenum(1970,1,1,0,0,0);
[unixStartDateTime] = round((datenum(startDateTime) - unixEpoch) * 86400000);
[unixEndDateTime] = round((datenum(endDateTime) - unixEpoch) * 86400000);

% Construct the execution string for mongoexport
[executionString] = ['"mongoexport.exe" ',...
    '-d BRICSData ', ...
    '-c testTransactions '...
    '-q ', ...
    '"{''DateTime'': {''$gt'': new Date(', num2str(unixStartDateTime), ') , ''$lte'': new Date(', num2str(unixEndDateTime),')}}" ', ...
    '--type=csv ', ...
    '-f ', ...
    '"', fields, '" ', ...
    '--out ', ...
    '"', tempcsvout, '"'];
% Execute mongoexport, data stored temporarily on disk in CSV file
dos(executionString);

data = textscan(fopen(tempcsvout), '%s %q %f %f %f %f %f %f', 'delimiter', ',', 'headerlines', 1);

% Change dates to datenum
data = cat(2, data{1:2}, num2cell([data{3:end}]));
data(:,1) = num2cell(datenum(data(:,1), 'yyyy-mm-ddTHH:MM:SS.FFF'));
fclose('all');

delete(tempcsvout);
end