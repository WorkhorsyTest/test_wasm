
if (! ('WebAssembly' in window)) {
	alert('you need a browser with wasm support enabled :(');
}

function loadWebAssembly(filename) {
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

			imports.env['__Z4Herpi'] = function(derps) {
				alert(derps);
			};

			return new WebAssembly.Instance(module, imports);
		});
}

loadWebAssembly('main.wasm')
	.then(instance => {
		let doubler = instance.exports.__Z7doubleri;

		let button = document.getElementById('run');
		button.value = 'Call a method in the WebAssembly module';
		button.addEventListener('click', function() {
			let input = 21;
			alert(input + ' doubled is ' + doubler(input));
		}, false);
	}
);
