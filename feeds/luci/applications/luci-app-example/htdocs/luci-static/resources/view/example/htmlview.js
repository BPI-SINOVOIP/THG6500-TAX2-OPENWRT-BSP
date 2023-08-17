'use strict';
'require uci';
'require view';

return view.extend({
  handleSaveApply: null,
  handleSave: null,
  handleReset: null,
  load: function() {
    return Promise.all([
      uci.load('example')
    ]);
  },
  render: function(data) {
    var body = E([
      E('h2', _('Example HTML Page'))
    ]);
    var sections = uci.sections('example');
    var listContainer = E('div');
    var list = E('ul');
    list.appendChild(E('li', { 'class': 'css-class' }, ['First Option in first section: ', E('em', {}, [sections[0].first_option])]));
    list.appendChild(E('li', { 'class': 'css-class' }, ['Flag in second section: ', E('em', {}, [sections[1].flag])]));
    list.appendChild(E('li', { 'class': 'css-class' }, ['Select in second section: ', E('em', {}, [sections[1].select])]));
    listContainer.appendChild(list);
    body.appendChild(listContainer);
    console.log(sections);
    return body;
  }
  });

