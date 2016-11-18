var os = require('os');
var activity = {};
if (os.platform !== 'darwin') {
	activity = os.arch() === 'x64' ? require('./binary/checker') : require('./binary/checker_x32');	
}
module.exports = activity;