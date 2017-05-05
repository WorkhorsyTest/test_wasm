
if (! ('WebAssembly' in window)) {
	alert('you need a browser with wasm support enabled :(');
}

function loadWebAssembly(filename, import_funcs) {
	return fetch(filename)
		.then(response => response.arrayBuffer())
		.then(buffer => WebAssembly.compile(buffer))
		.then(module => {
			let imports = {
				env: {
					memoryBase: 0,
					tableBase: 0,
					memory: new WebAssembly.Memory({ initial: 256 }),
					table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
				}
			};

			// Copy the imported functions into the module
			for (key in import_funcs) {
				imports.env[key] = import_funcs[key];
			}

			return new WebAssembly.Instance(module, imports);
		});
}

const import_funcs = {
	'_Herp': function(derps) {
		alert(derps);
	}
};

loadWebAssembly('main.wasm', import_funcs)
	.then(instance => {
		console.log(instance.exports);
		let doubler = instance.exports._doubler;

		let button = document.getElementById('run');
		button.value = 'Call a method in the WebAssembly module';
		button.addEventListener('click', function() {
			let input = 21;
			alert(input + ' doubled is ' + doubler(input));
		}, false);
	}
);
