'use strict';
'require view';
'require fs';
'require ui';

return view.extend({
	load: function() {
		return fs.exec_direct('/bin/ubus', [ 'call', 'tr069', 'status' ]).catch(function(err) {
			ui.addNotification(null, E('p', {}, _('Unable to load tr069 status: ' + err.message)));
			return '';
		});
	},

	render: function(logdata) {
		var loglines = logdata.trim().split(/\n/).map(function(line) {
			return line.replace(/^<\d+>/, '');
		});

		return E([], [
			E('h2', {}, [ _('TR-069 Daemon Status') ]),
			E('div', { 'id': 'content_tr069status' }, [
				E('textarea', {
					'id': 'syslog',
					'style': 'font-size:12px',
					'readonly': 'readonly',
					'wrap': 'off',
					'rows': loglines.length + 1
				}, [ loglines.join('\n') ])
			])
		]);
	},

	handleSaveApply: null,
	handleSave: null,
	handleReset: null
});
