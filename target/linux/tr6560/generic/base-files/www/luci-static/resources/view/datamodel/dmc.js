'use strict';
'require view';
'require fs';
'require ui';
'require dom';

return view.extend({

	handleCommand: function(exec, args) {
		var buttons = document.querySelectorAll('.dmc-action > .cbi-button');

		for (var i = 0; i < buttons.length; i++)
			buttons[i].setAttribute('disabled', 'true');

		return fs.exec(exec, args).then(function(res) {
			var out = document.querySelector('.command-output');
			    out.style.display = '';

			dom.content(out, [ res.stdout || '', res.stderr || '' ]);
		}).catch(function(err) {
			ui.addNotification(null, E('p', [ err ]))
		}).finally(function() {
			for (var i = 0; i < buttons.length; i++)
				buttons[i].removeAttribute('disabled');
		});
	},

	handledmc: function(ev, cmd) {
		var exec = 'datamodel',
		    dmcrpc = ev.currentTarget.parentNode.previousSibling.previousSibling.value,
		    args = [ '-c', '-t', '-f', '/tmp/.dmc_luci_input' ];

		fs.write('/tmp/.dmc_luci_input', dmcrpc);

		return this.handleCommand(exec, args);
	},

	render: function(res) {
		return E([
			E('h2', _('Datamodel - Command Line Interface')),
			E('p', {'class': 'left'}, 'CLI to execute datamodel command like get_value, set_value, get_name... Type help to see all available commands'),
			E('p', {'class': 'left'}, 'Command:'),
			E('input', {
				'style': 'width:100%',
				'type': 'text',
				'value': ''
			}),
			
			E('p', {}, ''),
			E('span', { 'class': 'dmc-action right' }, [
				E('button', {
					'class': 'cbi-button cbi-button-action',
					'click': ui.createHandlerFn(this, 'handledmc')
				}, [ _('Execute') ])
			]),
			E('p', {}, ''),
			E('pre', { 'class': 'command-output', 'style': 'display:none' })
		]);
	},
	handleSaveApply: null,
	handleSave: null,
	handleReset: null
});

