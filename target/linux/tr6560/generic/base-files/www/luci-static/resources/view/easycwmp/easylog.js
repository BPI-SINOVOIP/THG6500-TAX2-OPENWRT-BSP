'use strict';
'require view';
'require fs';
'require ui';

return view.extend({
	load: function() {
		return Promise.all([
			L.resolveDefault(fs.stat('/sbin/logread'), null),
			L.resolveDefault(fs.stat('/usr/sbin/logread'), null)
		]).then(function(stat) {
			var logger = stat[0] ? stat[0].path : stat[1] ? stat[1].path : null;

			return fs.exec_direct(logger, [ '-e', '^' ]).catch(function(err) {
				ui.addNotification(null, E('p', {}, _('Unable to load log data: ' + err.message)));
				return '';
			});
		});
	},

	render: function(logdata) {
		var loglines = (logdata.trim().split(/\n/)).filter(function(s){
			return (s.indexOf(" easycwmpd: ") > 0 || s.indexOf(" bulkdata: ") > 0 || s.indexOf(" obuspa: ") > 0 || s.indexOf(" tr069_stund: ") > 0 || s.indexOf(" tr069_upnp: ") > 0 || s.indexOf(" tr069_xmpp: ") > 0);
		});

		return E([], [
			E('h2', {}, [ _('PMS Log') ]),
			E('div', { 'id': 'pms_syslog' }, [
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
